#include <unity.h>
#include <Communication.h>

#include "ControllerFootswitchCommunicationTests.h"

class SerialMock
{
public:
    static constexpr uint8_t BUFFER_SIZE = 9;
    uint32_t baudRate;
    uint8_t inBuffer[BUFFER_SIZE];
    uint8_t outBuffer[BUFFER_SIZE];
    
    uint8_t inIndex;
    uint8_t outIndex;

    SerialMock() : baudRate(0), inIndex(0), outIndex(0)
    {        
    }

    void begin(uint32_t baudRate)
    {
        this->baudRate = baudRate;
    }

    int available()
    {
        return BUFFER_SIZE - inIndex;
    }

    int read()
    {
        return inBuffer[inIndex++];
    }

    int write(const char* data, int dataSize)
    {
        for (int i = 0; i < dataSize && outIndex < BUFFER_SIZE; i++)
        {
            outBuffer[outIndex] = data[i];
            outIndex++;
        }
    }
};

static bool heartbeatReceived = false;
static void heartbeatHandler()
{
    heartbeatReceived = true;
}

static uint8_t receivedEffectCode = UINT8_MAX;
static void toogleEffectHandler(uint8_t effectCode)
{
    receivedEffectCode = effectCode;
}

static bool clippingNotificationReceived = false;
static void clippingNotificationHandler()
{
    clippingNotificationReceived = true;
}

static bool effectActiveStates[6] = {false};
static void effectActiveStatesHandler(bool compressorActiveState,
    bool octaverActiveState,
    bool delayActiveState,
    bool reverbActiveState,
    bool overrideActiveState,
    bool muteActiveState)
{
    effectActiveStates[0] = compressorActiveState;
    effectActiveStates[1] = octaverActiveState;
    effectActiveStates[2] = delayActiveState;
    effectActiveStates[3] = reverbActiveState;
    effectActiveStates[4] = overrideActiveState;
    effectActiveStates[5] = muteActiveState;
}

static uint32_t receivedDelayUs = 0;
static void delayUsHandler(uint32_t delayUs)
{
    receivedDelayUs = delayUs;
}

static void test_ControllerFootswitchCommunication_begin()
{
    constexpr uint32_t BAUD_RATE = 9600;

    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);
    testee.begin(BAUD_RATE);

    TEST_ASSERT_EQUAL(BAUD_RATE, serialMock.baudRate);
}

static void test_ControllerFootswitchCommunication_sendHeartbeat()
{
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendHeartbeat();

    TEST_ASSERT_EQUAL(3, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(0, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(253, serialMock.outBuffer[2]);
}

static void test_ControllerFootswitchCommunication_sendToogleEffect()
{
    constexpr uint8_t EFFECT_CODE = 5;

    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendToogleEffect(EFFECT_CODE);

    TEST_ASSERT_EQUAL(4, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(50, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(EFFECT_CODE, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(197, serialMock.outBuffer[3]);
}

static void test_ControllerFootswitchCommunication_sendClippingNotification()
{
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendClippingNotification();

    TEST_ASSERT_EQUAL(3, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(100, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(153, serialMock.outBuffer[2]);
}

static void test_ControllerFootswitchCommunication_sendEffectActiveStates()
{
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendEffectActiveStates(true, false, true, false, true, false);

    TEST_ASSERT_EQUAL(9, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(150, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(true, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(false, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(true, serialMock.outBuffer[4]);
    TEST_ASSERT_EQUAL(false, serialMock.outBuffer[5]);
    TEST_ASSERT_EQUAL(true, serialMock.outBuffer[6]);
    TEST_ASSERT_EQUAL(false, serialMock.outBuffer[7]);
    TEST_ASSERT_EQUAL(94, serialMock.outBuffer[8]);
}

static void test_ControllerFootswitchCommunication_sendDelayUs()
{
    constexpr uint32_t DELAY_US = 0x01020304;
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendDelayUs(DELAY_US);

    TEST_ASSERT_EQUAL(7, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(200, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(0x04, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(0x03, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(0x02, serialMock.outBuffer[4]);
    TEST_ASSERT_EQUAL(0x01, serialMock.outBuffer[5]);
    TEST_ASSERT_EQUAL(39, serialMock.outBuffer[6]);
}

static void test_ControllerFootswitchCommunication_receiveHeartbeat()
{
    SerialMock serialMock;
    serialMock.inBuffer[0] = 3;
    serialMock.inBuffer[1] = 0;
    serialMock.inBuffer[2] = 252;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerHeatbeatHandler(heartbeatHandler);

    // Wrong checksum
    heartbeatReceived = false;
    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(false, heartbeatReceived);

    // Reset the mock and udpate the checksum    
    serialMock.inIndex = 0;
    serialMock.inBuffer[2] = 253;

    heartbeatReceived = false;
    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(true, heartbeatReceived);
}

static void test_ControllerFootswitchCommunication_receiveToogleEffect()
{
    constexpr uint8_t EFFECT_CODE = 5;
    SerialMock serialMock;
    serialMock.inBuffer[0] = 4;
    serialMock.inBuffer[1] = 50;
    serialMock.inBuffer[2] = EFFECT_CODE;
    serialMock.inBuffer[3] = 197;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerToogleEffectHandler(toogleEffectHandler);

    receivedEffectCode = UINT8_MAX;
    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(EFFECT_CODE, receivedEffectCode);
}

static void test_ControllerFootswitchCommunication_receiveClippingNotification()
{
    SerialMock serialMock;
    serialMock.inBuffer[0] = 3;
    serialMock.inBuffer[1] = 100;
    serialMock.inBuffer[2] = 153;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerClippingNotificationHandler(clippingNotificationHandler);

    clippingNotificationReceived = false;
    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(true, clippingNotificationReceived);
}

static void test_ControllerFootswitchCommunication_receiveEffectActiveStates()
{
    SerialMock serialMock;
    serialMock.inBuffer[0] = 9;
    serialMock.inBuffer[1] = 150;
    serialMock.inBuffer[2] = 1;
    serialMock.inBuffer[3] = 1;
    serialMock.inBuffer[4] = 1;
    serialMock.inBuffer[5] = 1;
    serialMock.inBuffer[6] = 1;
    serialMock.inBuffer[7] = 1;
    serialMock.inBuffer[8] = 91;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerEffectActiveStatesHandler(effectActiveStatesHandler);

    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(true, effectActiveStates[0]);
    TEST_ASSERT_EQUAL(true, effectActiveStates[1]);
    TEST_ASSERT_EQUAL(true, effectActiveStates[2]);
    TEST_ASSERT_EQUAL(true, effectActiveStates[3]);
    TEST_ASSERT_EQUAL(true, effectActiveStates[4]);
    TEST_ASSERT_EQUAL(true, effectActiveStates[5]);
}

static void test_ControllerFootswitchCommunication_receiveDelayUs()
{
    SerialMock serialMock;
    serialMock.inBuffer[0] = 7;
    serialMock.inBuffer[1] = 200;
    serialMock.inBuffer[2] = 1;
    serialMock.inBuffer[3] = 2;
    serialMock.inBuffer[4] = 3;
    serialMock.inBuffer[5] = 4;
    serialMock.inBuffer[6] = 39;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerDelayUsHandler(delayUsHandler);

    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(0x04030201, receivedDelayUs);
}

static void test_ControllerFootswitchCommunication_receiveEmptySerial()
{
    SerialMock serialMock;
    serialMock.inIndex = SerialMock::BUFFER_SIZE;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerEffectActiveStatesHandler(effectActiveStatesHandler);

    TEST_ASSERT_EQUAL(false, testee.receive());
}

void runControllerFootswitchCommunicationTests()
{
    RUN_TEST(test_ControllerFootswitchCommunication_begin);

    RUN_TEST(test_ControllerFootswitchCommunication_sendHeartbeat);
    RUN_TEST(test_ControllerFootswitchCommunication_sendToogleEffect);
    RUN_TEST(test_ControllerFootswitchCommunication_sendClippingNotification);
    RUN_TEST(test_ControllerFootswitchCommunication_sendEffectActiveStates);
    RUN_TEST(test_ControllerFootswitchCommunication_sendDelayUs);

    RUN_TEST(test_ControllerFootswitchCommunication_receiveHeartbeat);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveToogleEffect);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveClippingNotification);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveEffectActiveStates);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveEmptySerial);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveDelayUs);
}