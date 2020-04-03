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
static uint8_t receivedEffectCode = UINT8_MAX;
static bool clippingNotificationReceived = false;
static bool effectActiveStates[6] = {false};
static uint32_t receivedDelayUs = 0;
static uint8_t receivedIsEnabled = false;

static void heartbeatHandler()
{
    heartbeatReceived = true;
}

static void toogleEffectHandler(uint8_t effectCode)
{
    receivedEffectCode = effectCode;
}

static void clippingNotificationHandler()
{
    clippingNotificationReceived = true;
}

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

static void delayUsHandler(uint32_t delayUs)
{
    receivedDelayUs = delayUs;
}

static void setEffectHandler(uint8_t effectCode, bool isEnabled)
{
    receivedEffectCode = effectCode;
    receivedIsEnabled = isEnabled;
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
    TEST_ASSERT_EQUAL(25, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(EFFECT_CODE, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(222, serialMock.outBuffer[3]);
}

static void test_ControllerFootswitchCommunication_sendClippingNotification()
{
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendClippingNotification();

    TEST_ASSERT_EQUAL(3, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(50, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(203, serialMock.outBuffer[2]);
}

static void test_ControllerFootswitchCommunication_sendEffectActiveStates()
{
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendEffectActiveStates(true, false, true, false, true, false);

    TEST_ASSERT_EQUAL(9, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(75, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(true, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(false, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(true, serialMock.outBuffer[4]);
    TEST_ASSERT_EQUAL(false, serialMock.outBuffer[5]);
    TEST_ASSERT_EQUAL(true, serialMock.outBuffer[6]);
    TEST_ASSERT_EQUAL(false, serialMock.outBuffer[7]);
    TEST_ASSERT_EQUAL(169, serialMock.outBuffer[8]);
}

static void test_ControllerFootswitchCommunication_sendDelayUs()
{
    constexpr uint32_t DELAY_US = 0x01020304;
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendDelayUs(DELAY_US);

    TEST_ASSERT_EQUAL(7, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(100, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(0x04, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(0x03, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(0x02, serialMock.outBuffer[4]);
    TEST_ASSERT_EQUAL(0x01, serialMock.outBuffer[5]);
    TEST_ASSERT_EQUAL(139, serialMock.outBuffer[6]);
}

static void test_ControllerFootswitchCommunication_sendSetEffect()
{
    constexpr uint8_t EFFECT_CODE = 5;
    constexpr bool IS_ENABLED = true;

    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendSetEffect(EFFECT_CODE, IS_ENABLED);

    TEST_ASSERT_EQUAL(5, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(125, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(EFFECT_CODE, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(IS_ENABLED, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(120, serialMock.outBuffer[4]);
}

static void test_ControllerFootswitchCommunication_sendAck()
{
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendAck();

    TEST_ASSERT_EQUAL(3, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(150, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(103, serialMock.outBuffer[2]);
}

static void test_ControllerFootswitchCommunication_receiveHeartbeat()
{
    uint8_t receivedMessageCode = UINT8_MAX;
    SerialMock serialMock;
    serialMock.inBuffer[0] = 3;
    serialMock.inBuffer[1] = 0;
    serialMock.inBuffer[2] = 252;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerHeatbeatHandler(heartbeatHandler);

    // Wrong checksum
    heartbeatReceived = false;
    TEST_ASSERT_EQUAL(true, testee.receive(&receivedMessageCode));
    TEST_ASSERT_EQUAL(false, heartbeatReceived);
    TEST_ASSERT_EQUAL(UINT8_MAX, receivedMessageCode);

    // Reset the mock and udpate the checksum    
    serialMock.inIndex = 0;
    serialMock.inBuffer[2] = 253;

    heartbeatReceived = false;
    TEST_ASSERT_EQUAL(true, testee.receive(&receivedMessageCode));
    TEST_ASSERT_EQUAL(true, heartbeatReceived);
    TEST_ASSERT_EQUAL(serialMock.inBuffer[1], receivedMessageCode);
}

static void test_ControllerFootswitchCommunication_receiveToogleEffect()
{
    constexpr uint8_t EFFECT_CODE = 5;
    SerialMock serialMock;
    serialMock.inBuffer[0] = 4;
    serialMock.inBuffer[1] = 25;
    serialMock.inBuffer[2] = EFFECT_CODE;
    serialMock.inBuffer[3] = 222;

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
    serialMock.inBuffer[1] = 50;
    serialMock.inBuffer[2] = 203;

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
    serialMock.inBuffer[1] = 75;
    serialMock.inBuffer[2] = 1;
    serialMock.inBuffer[3] = 1;
    serialMock.inBuffer[4] = 1;
    serialMock.inBuffer[5] = 1;
    serialMock.inBuffer[6] = 1;
    serialMock.inBuffer[7] = 1;
    serialMock.inBuffer[8] = 166;

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
    serialMock.inBuffer[1] = 100;
    serialMock.inBuffer[2] = 1;
    serialMock.inBuffer[3] = 2;
    serialMock.inBuffer[4] = 3;
    serialMock.inBuffer[5] = 4;
    serialMock.inBuffer[6] = 139;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerDelayUsHandler(delayUsHandler);

    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(0x04030201, receivedDelayUs);
}

static void test_ControllerFootswitchCommunication_receiveSetEffect()
{
    constexpr uint8_t EFFECT_CODE = 5;
    constexpr bool IS_ENABLED = true;
    SerialMock serialMock;
    serialMock.inBuffer[0] = 5;
    serialMock.inBuffer[1] = 125;
    serialMock.inBuffer[2] = EFFECT_CODE;
    serialMock.inBuffer[3] = IS_ENABLED;
    serialMock.inBuffer[4] = 120;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerSetEffectHandler(setEffectHandler);

    receivedEffectCode = UINT8_MAX;
    receivedIsEnabled = false;
    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(EFFECT_CODE, receivedEffectCode);
    TEST_ASSERT_EQUAL(IS_ENABLED, receivedIsEnabled);
}

static void test_ControllerFootswitchCommunication_receiveAck()
{
    uint8_t receivedMessageCode = UINT8_MAX;
    SerialMock serialMock;
    serialMock.inBuffer[0] = 3;
    serialMock.inBuffer[1] = 250;
    serialMock.inBuffer[2] = 3;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    TEST_ASSERT_EQUAL(true, testee.receive(&receivedMessageCode));
    TEST_ASSERT_EQUAL(serialMock.inBuffer[1], receivedMessageCode);
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
    RUN_TEST(test_ControllerFootswitchCommunication_sendSetEffect);
    RUN_TEST(test_ControllerFootswitchCommunication_sendAck);

    RUN_TEST(test_ControllerFootswitchCommunication_receiveHeartbeat);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveToogleEffect);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveClippingNotification);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveEffectActiveStates);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveEmptySerial);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveDelayUs);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveSetEffect);
}