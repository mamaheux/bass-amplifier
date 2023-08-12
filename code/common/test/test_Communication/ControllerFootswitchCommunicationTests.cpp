#include <unity.h>
#include <Communication.h>

#include "ControllerFootswitchCommunicationTests.h"

uint32_t millis()
{
    static uint32_t count;
    return count++;
}

class SerialMock
{
public:
    static constexpr uint8_t BUFFER_SIZE = 20;
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
        return dataSize;
    }

    int write(uint8_t v)
    {
        return write(reinterpret_cast<char*>(&v), 1);
    }
};

static bool heartbeatReceived = false;
static uint8_t receivedEffectCode = UINT8_MAX;
static bool clippingNotificationReceived = false;
static bool effectActiveStates[6] = {false};
static uint32_t receivedDelayUs = 0;
static uint8_t receivedIsEnabled = false;
static PitchShifterUpdateCommand receivedPitchShifterUpdateCommand = PitchShifterUpdateCommand::RESET;

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

static void updatePitchShifterHandler(PitchShifterUpdateCommand command)
{
    receivedPitchShifterUpdateCommand = command;
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

    TEST_ASSERT_EQUAL(255, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(3, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(0, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(253, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(4, serialMock.outIndex);
}

static void test_ControllerFootswitchCommunication_sendToogleEffect()
{
    constexpr uint8_t EFFECT_CODE = 5;

    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendToogleEffect(EFFECT_CODE);

    TEST_ASSERT_EQUAL(255, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(4, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(25, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(EFFECT_CODE, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(222, serialMock.outBuffer[4]);
    TEST_ASSERT_EQUAL(5, serialMock.outIndex);
}

static void test_ControllerFootswitchCommunication_sendClippingNotification()
{
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendClippingNotification();

    TEST_ASSERT_EQUAL(255, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(3, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(50, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(203, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(4, serialMock.outIndex);
}

static void test_ControllerFootswitchCommunication_sendEffectActiveStates()
{
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendEffectActiveStates(true, false, true, false, true, false);

    TEST_ASSERT_EQUAL(255, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(9, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(75, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(true, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(false, serialMock.outBuffer[4]);
    TEST_ASSERT_EQUAL(true, serialMock.outBuffer[5]);
    TEST_ASSERT_EQUAL(false, serialMock.outBuffer[6]);
    TEST_ASSERT_EQUAL(true, serialMock.outBuffer[7]);
    TEST_ASSERT_EQUAL(false, serialMock.outBuffer[8]);
    TEST_ASSERT_EQUAL(169, serialMock.outBuffer[9]);
    TEST_ASSERT_EQUAL(10, serialMock.outIndex);
}

static void test_ControllerFootswitchCommunication_sendDelayUs()
{
    constexpr uint32_t DELAY_US = 0x01020304;
    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendDelayUs(DELAY_US);

    TEST_ASSERT_EQUAL(255, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(7, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(100, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(0x04, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(0x03, serialMock.outBuffer[4]);
    TEST_ASSERT_EQUAL(0x02, serialMock.outBuffer[5]);
    TEST_ASSERT_EQUAL(0x01, serialMock.outBuffer[6]);
    TEST_ASSERT_EQUAL(139, serialMock.outBuffer[7]);
    TEST_ASSERT_EQUAL(8, serialMock.outIndex);
}

static void test_ControllerFootswitchCommunication_sendSetEffect()
{
    constexpr uint8_t EFFECT_CODE = 5;
    constexpr bool IS_ENABLED = true;

    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendSetEffect(EFFECT_CODE, IS_ENABLED);

    TEST_ASSERT_EQUAL(255, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(5, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(125, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(EFFECT_CODE, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(IS_ENABLED, serialMock.outBuffer[4]);
    TEST_ASSERT_EQUAL(120, serialMock.outBuffer[5]);
    TEST_ASSERT_EQUAL(6, serialMock.outIndex);
}

static void test_ControllerFootswitchCommunication_sendUpdatePitchShifter()
{
    constexpr PitchShifterUpdateCommand COMMAND = PitchShifterUpdateCommand::DECREASE;

    SerialMock serialMock;
    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.sendUpdatePitchShifter(COMMAND);

    TEST_ASSERT_EQUAL(255, serialMock.outBuffer[0]);
    TEST_ASSERT_EQUAL(4, serialMock.outBuffer[1]);
    TEST_ASSERT_EQUAL(150, serialMock.outBuffer[2]);
    TEST_ASSERT_EQUAL(COMMAND, serialMock.outBuffer[3]);
    TEST_ASSERT_EQUAL(100, serialMock.outBuffer[4]);
    TEST_ASSERT_EQUAL(5, serialMock.outIndex);
}

static void test_ControllerFootswitchCommunication_receiveHeartbeat()
{
    uint8_t receivedMessageCode = UINT8_MAX;
    SerialMock serialMock;
    serialMock.inBuffer[0] = 254; // INVALID PREAMBLE
    serialMock.inBuffer[1] = 255;
    serialMock.inBuffer[2] = 3;
    serialMock.inBuffer[3] = 0;
    serialMock.inBuffer[4] = 252;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerHeartbeatHandler(heartbeatHandler);

    // Wrong checksum
    heartbeatReceived = false;
    TEST_ASSERT_EQUAL(false, testee.receive(&receivedMessageCode));
    TEST_ASSERT_EQUAL(true, testee.receive(&receivedMessageCode));
    TEST_ASSERT_EQUAL(false, heartbeatReceived);
    TEST_ASSERT_EQUAL(UINT8_MAX, receivedMessageCode);

    // Reset the mock and udpate the checksum
    serialMock.inIndex = 0;
    serialMock.inBuffer[4] = 253;

    heartbeatReceived = false;
    TEST_ASSERT_EQUAL(false, testee.receive(&receivedMessageCode));
    TEST_ASSERT_EQUAL(true, testee.receive(&receivedMessageCode));
    TEST_ASSERT_EQUAL(true, heartbeatReceived);
    TEST_ASSERT_EQUAL(serialMock.inBuffer[3], receivedMessageCode);
}

static void test_ControllerFootswitchCommunication_receiveToogleEffect()
{
    constexpr uint8_t EFFECT_CODE = 5;
    SerialMock serialMock;
    serialMock.inBuffer[0] = 255;
    serialMock.inBuffer[1] = 4;
    serialMock.inBuffer[2] = 25;
    serialMock.inBuffer[3] = EFFECT_CODE;
    serialMock.inBuffer[4] = 222;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerToogleEffectHandler(toogleEffectHandler);

    receivedEffectCode = UINT8_MAX;
    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(EFFECT_CODE, receivedEffectCode);
}

static void test_ControllerFootswitchCommunication_receiveClippingNotification()
{
    SerialMock serialMock;
    serialMock.inBuffer[0] = 255;
    serialMock.inBuffer[1] = 3;
    serialMock.inBuffer[2] = 50;
    serialMock.inBuffer[3] = 203;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerClippingNotificationHandler(clippingNotificationHandler);

    clippingNotificationReceived = false;
    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(true, clippingNotificationReceived);
}

static void test_ControllerFootswitchCommunication_receiveEffectActiveStates()
{
    SerialMock serialMock;
    serialMock.inBuffer[0] = 255;
    serialMock.inBuffer[1] = 9;
    serialMock.inBuffer[2] = 75;
    serialMock.inBuffer[3] = 1;
    serialMock.inBuffer[4] = 1;
    serialMock.inBuffer[5] = 1;
    serialMock.inBuffer[6] = 1;
    serialMock.inBuffer[7] = 1;
    serialMock.inBuffer[8] = 1;
    serialMock.inBuffer[9] = 166;

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
    serialMock.inBuffer[0] = 255;
    serialMock.inBuffer[1] = 7;
    serialMock.inBuffer[2] = 100;
    serialMock.inBuffer[3] = 1;
    serialMock.inBuffer[4] = 2;
    serialMock.inBuffer[5] = 3;
    serialMock.inBuffer[6] = 4;
    serialMock.inBuffer[7] = 139;

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
    serialMock.inBuffer[0] = 255;
    serialMock.inBuffer[1] = 5;
    serialMock.inBuffer[2] = 125;
    serialMock.inBuffer[3] = EFFECT_CODE;
    serialMock.inBuffer[4] = IS_ENABLED;
    serialMock.inBuffer[5] = 120;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerSetEffectHandler(setEffectHandler);

    receivedEffectCode = UINT8_MAX;
    receivedIsEnabled = false;
    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(EFFECT_CODE, receivedEffectCode);
    TEST_ASSERT_EQUAL(IS_ENABLED, receivedIsEnabled);
}

static void test_ControllerFootswitchCommunication_receiveUpdatePitchShifter()
{
    constexpr PitchShifterUpdateCommand COMMAND = PitchShifterUpdateCommand::INCREASE;

    SerialMock serialMock;
    serialMock.inBuffer[0] = 255;
    serialMock.inBuffer[1] = 4;
    serialMock.inBuffer[2] = 150;
    serialMock.inBuffer[3] = static_cast<uint8_t>(COMMAND);
    serialMock.inBuffer[4] = 101;

    ControllerFootswitchCommunication<SerialMock> testee(serialMock);

    testee.registerUpdatePitchShifterHandler(updatePitchShifterHandler);

    receivedPitchShifterUpdateCommand = PitchShifterUpdateCommand::RESET;
    TEST_ASSERT_EQUAL(true, testee.receive());
    TEST_ASSERT_EQUAL(COMMAND, receivedPitchShifterUpdateCommand);
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
    RUN_TEST(test_ControllerFootswitchCommunication_sendUpdatePitchShifter);

    RUN_TEST(test_ControllerFootswitchCommunication_receiveHeartbeat);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveToogleEffect);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveClippingNotification);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveEffectActiveStates);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveDelayUs);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveSetEffect);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveUpdatePitchShifter);
    RUN_TEST(test_ControllerFootswitchCommunication_receiveEmptySerial);
}
