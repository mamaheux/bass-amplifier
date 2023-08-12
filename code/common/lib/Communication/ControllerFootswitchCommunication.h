#ifndef CONTROLLER_TO_FOOTSWITCH_COMMUNICATION_H
#define CONTROLLER_TO_FOOTSWITCH_COMMUNICATION_H

#include "constants.h"

constexpr uint32_t CONTROLLER_FOOTSWITCH_HEARTBEAT_TIMEOUT_MS = 1000;

enum class PitchShifterUpdateCommand : uint8_t
{
    RESET = 0,
    INCREASE = 1,
    DECREASE = 2
};

uint32_t millis();

template <class TSerial>
class ControllerFootswitchCommunication
{
public:
    typedef void (*HeartbeatHandler)();
    typedef void (*ToogleEffectHandler)(uint8_t effectCode);
    typedef void (*ClippingNotificationHandler)();
    typedef void (*EffectActiveStatesHandler)(bool compressorActiveState,
        bool octaverActiveState,
        bool delayActiveState,
        bool reverbActiveState,
        bool overrideActiveState,
        bool muteActiveState);
    typedef void (*DelayUsHandler)(uint32_t delayUs);
    typedef void (*SetEffectHandler)(uint8_t effectCode, bool isEnabled);
    typedef void (*UpdatePitchShifterHandler)(PitchShifterUpdateCommand command);

    static constexpr uint8_t PREAMBLE = 255;

    static constexpr uint8_t HEARTBEAT_MESSAGE_CODE = 0;
    static constexpr uint8_t TOOGLE_EFFECT_MESSAGE_CODE = 25;
    static constexpr uint8_t CLIPPING_NOTIFICATION_MESSAGE_CODE = 50;
    static constexpr uint8_t EFFECT_ACTIVE_STATES_MESSAGE_CODE = 75;
    static constexpr uint8_t DELAY_US_MESSAGE_CODE = 100;
    static constexpr uint8_t SET_EFFECT_MESSAGE_CODE = 125;
    static constexpr uint8_t UPDATE_PITCH_SHIFTER_CODE = 150;

    static constexpr uint8_t HEARTBEAT_DATA_SIZE = 3;
    static constexpr uint8_t TOOGLE_EFFECT_DATA_SIZE = 4;
    static constexpr uint8_t CLIPPING_NOTIFICATION_DATA_SIZE = 3;
    static constexpr uint8_t EFFECT_ACTIVE_STATES_DATA_SIZE = 9;
    static constexpr uint8_t DELAY_US_DATA_SIZE = 7;
    static constexpr uint8_t SET_EFFECT_DATA_SIZE = 5;
    static constexpr uint8_t UPDATE_PITCH_SHIFTER_DATA_SIZE = 4;

private:
    TSerial& m_serial;

    HeartbeatHandler m_heartbeatHandler;
    ToogleEffectHandler m_toogleEffectHandler;
    ClippingNotificationHandler m_clippingNotificationHandler;
    EffectActiveStatesHandler m_effectActiveStatesHandler;
    DelayUsHandler m_delayUsHandler;
    SetEffectHandler m_setEffectHandler;
    UpdatePitchShifterHandler m_updatePitchShifterHandler;

public:
    ControllerFootswitchCommunication(TSerial& serial);
    void begin(uint32_t baudRate);

    void registerHeartbeatHandler(HeartbeatHandler handler);
    void registerToogleEffectHandler(ToogleEffectHandler handler);
    void registerClippingNotificationHandler(ClippingNotificationHandler handler);
    void registerEffectActiveStatesHandler(EffectActiveStatesHandler handler);
    void registerDelayUsHandler(DelayUsHandler handler);
    void registerSetEffectHandler(SetEffectHandler handler);
    void registerUpdatePitchShifterHandler(UpdatePitchShifterHandler handler);

    void sendHeartbeat();
    void sendToogleEffect(uint8_t effectCode);
    void sendClippingNotification();
    void sendEffectActiveStates(bool compressorActiveState,
        bool octaverActiveState,
        bool delayActiveState,
        bool reverbActiveState,
        bool overrideActiveState,
        bool muteActiveState);
    void sendDelayUs(uint32_t delayUs);
    void sendSetEffect(uint8_t effectCode, bool isEnabled);
    void sendUpdatePitchShifter(PitchShifterUpdateCommand command);

    bool receive(uint8_t* receivedMessageCode = nullptr, uint32_t timeoutMs = 20);

private:
    void handleMessage(uint8_t* data, uint8_t dataSize);
};

template <class TSerial>
ControllerFootswitchCommunication<TSerial>::ControllerFootswitchCommunication(TSerial& serial) : m_serial(serial),
    m_heartbeatHandler(nullptr), m_toogleEffectHandler(nullptr),
    m_clippingNotificationHandler(nullptr), m_effectActiveStatesHandler(nullptr),
    m_delayUsHandler(nullptr), m_setEffectHandler(nullptr),
    m_updatePitchShifterHandler(nullptr)
{
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::begin(uint32_t baudRate)
{
    m_serial.begin(baudRate);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::registerHeartbeatHandler(HeartbeatHandler handler)
{
    m_heartbeatHandler = handler;
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::registerToogleEffectHandler(ToogleEffectHandler handler)
{
    m_toogleEffectHandler = handler;
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::registerClippingNotificationHandler(ClippingNotificationHandler handler)
{
    m_clippingNotificationHandler = handler;
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::registerEffectActiveStatesHandler(EffectActiveStatesHandler handler)
{
    m_effectActiveStatesHandler = handler;
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::registerDelayUsHandler(DelayUsHandler handler)
{
    m_delayUsHandler = handler;
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::registerSetEffectHandler(SetEffectHandler handler)
{
    m_setEffectHandler = handler;
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::registerUpdatePitchShifterHandler(UpdatePitchShifterHandler handler)
{
    m_updatePitchShifterHandler = handler;
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::sendHeartbeat()
{
    constexpr uint8_t checksum = UINT8_MAX - (HEARTBEAT_DATA_SIZE + HEARTBEAT_MESSAGE_CODE) + 1;
    uint8_t data[HEARTBEAT_DATA_SIZE + 1] = {HEARTBEAT_DATA_SIZE, HEARTBEAT_MESSAGE_CODE, checksum};

    m_serial.write(PREAMBLE);
    m_serial.write(reinterpret_cast<char*>(data), HEARTBEAT_DATA_SIZE);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::sendToogleEffect(uint8_t effectCode)
{
    const uint8_t checksum =  UINT8_MAX - (TOOGLE_EFFECT_DATA_SIZE + TOOGLE_EFFECT_MESSAGE_CODE + effectCode) + 1;
    uint8_t data[TOOGLE_EFFECT_DATA_SIZE] = {TOOGLE_EFFECT_DATA_SIZE, TOOGLE_EFFECT_MESSAGE_CODE, effectCode, checksum};

    m_serial.write(PREAMBLE);
    m_serial.write(reinterpret_cast<char*>(data), TOOGLE_EFFECT_DATA_SIZE);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::sendClippingNotification()
{
    constexpr uint8_t checksum =  UINT8_MAX - (CLIPPING_NOTIFICATION_DATA_SIZE + CLIPPING_NOTIFICATION_MESSAGE_CODE) + 1;
    uint8_t data[CLIPPING_NOTIFICATION_DATA_SIZE] =
    {
        CLIPPING_NOTIFICATION_DATA_SIZE,
        CLIPPING_NOTIFICATION_MESSAGE_CODE, checksum
    };

    m_serial.write(PREAMBLE);
    m_serial.write(reinterpret_cast<char*>(data), CLIPPING_NOTIFICATION_DATA_SIZE);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::sendEffectActiveStates(bool compressorActiveState,
    bool octaverActiveState,
    bool delayActiveState,
    bool reverbActiveState,
    bool overrideActiveState,
    bool muteActiveState)
{
    uint8_t checksum =  UINT8_MAX - (EFFECT_ACTIVE_STATES_DATA_SIZE +
        EFFECT_ACTIVE_STATES_MESSAGE_CODE + compressorActiveState + octaverActiveState +
        delayActiveState + reverbActiveState + overrideActiveState + muteActiveState) + 1;

    uint8_t data[EFFECT_ACTIVE_STATES_DATA_SIZE] =
    {
        EFFECT_ACTIVE_STATES_DATA_SIZE, EFFECT_ACTIVE_STATES_MESSAGE_CODE,
        compressorActiveState, octaverActiveState,
        delayActiveState, reverbActiveState,
        overrideActiveState, muteActiveState,
        checksum
    };

    m_serial.write(PREAMBLE);
    m_serial.write(reinterpret_cast<char*>(data), EFFECT_ACTIVE_STATES_DATA_SIZE);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::sendDelayUs(uint32_t delayUs)
{
    uint8_t b0 = delayUs & 0xFF;
    uint8_t b1 = (delayUs >> 8) & 0xFF;
    uint8_t b2 = (delayUs >> 16) & 0xFF;
    uint8_t b3 = (delayUs >> 24) & 0xFF;

    uint8_t checksum =  UINT8_MAX - (DELAY_US_DATA_SIZE + DELAY_US_MESSAGE_CODE + b0 + b1 + b2 + b3) + 1;
    uint8_t data[DELAY_US_DATA_SIZE] =
    {
        DELAY_US_DATA_SIZE, DELAY_US_MESSAGE_CODE,
        b0, b1, b2, b3,
        checksum
    };

    m_serial.write(PREAMBLE);
    m_serial.write(reinterpret_cast<char*>(data), DELAY_US_DATA_SIZE);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::sendSetEffect(uint8_t effectCode, bool isEnabled)
{
    const uint8_t checksum =  UINT8_MAX - (SET_EFFECT_DATA_SIZE + SET_EFFECT_MESSAGE_CODE + effectCode + isEnabled) + 1;
    uint8_t data[SET_EFFECT_DATA_SIZE] = {SET_EFFECT_DATA_SIZE, SET_EFFECT_MESSAGE_CODE, effectCode, isEnabled, checksum};

    m_serial.write(PREAMBLE);
    m_serial.write(reinterpret_cast<char*>(data), SET_EFFECT_DATA_SIZE);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::sendUpdatePitchShifter(PitchShifterUpdateCommand command)
{
    uint8_t commandValue = static_cast<uint8_t>(command);
    const uint8_t checksum =  UINT8_MAX - (UPDATE_PITCH_SHIFTER_DATA_SIZE + UPDATE_PITCH_SHIFTER_CODE + commandValue) + 1;
    uint8_t data[UPDATE_PITCH_SHIFTER_DATA_SIZE] = {UPDATE_PITCH_SHIFTER_DATA_SIZE, UPDATE_PITCH_SHIFTER_CODE, commandValue, checksum};

    m_serial.write(PREAMBLE);
    m_serial.write(reinterpret_cast<char*>(data), UPDATE_PITCH_SHIFTER_DATA_SIZE);
}

template <class TSerial>
bool ControllerFootswitchCommunication<TSerial>::receive(uint8_t* receivedMessageCode, uint32_t timeoutMs)
{
    if (m_serial.available() < 2)
    {
        return false;
    }
    if (m_serial.read() != PREAMBLE)
    {
        return false;
    }

    constexpr uint8_t MAX_DATA_SIZE = 9;
    uint8_t data[MAX_DATA_SIZE] = {0};

    uint8_t dataSize = m_serial.read();
    data[0] = dataSize;
    uint8_t checksum = dataSize;

    uint32_t startMs = millis();
    for (uint8_t i = 1; i < dataSize && i < MAX_DATA_SIZE; i++)
    {
        while (m_serial.available() == 0)
        {
            if (millis() - startMs)
            {
                return false;
            }
        }
        data[i] = m_serial.read();
        checksum += data[i];
    }

    if (checksum == 0 && dataSize <= MAX_DATA_SIZE)
    {
        handleMessage(data, dataSize);

        if (receivedMessageCode != nullptr)
        {
            *receivedMessageCode = data[1];
        }
    }

    return true;
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::handleMessage(uint8_t* data, uint8_t dataSize)
{
    switch (data[1])
    {
    case HEARTBEAT_MESSAGE_CODE:
        if (dataSize == HEARTBEAT_DATA_SIZE && m_heartbeatHandler != nullptr)
        {
            m_heartbeatHandler();
        }
        break;

    case TOOGLE_EFFECT_MESSAGE_CODE:
        if (dataSize == TOOGLE_EFFECT_DATA_SIZE && m_toogleEffectHandler != nullptr)
        {
            m_toogleEffectHandler(data[2]);
        }
        break;

    case CLIPPING_NOTIFICATION_MESSAGE_CODE:
        if (dataSize == CLIPPING_NOTIFICATION_DATA_SIZE && m_clippingNotificationHandler != nullptr)
        {
            m_clippingNotificationHandler();
        }
        break;

    case EFFECT_ACTIVE_STATES_MESSAGE_CODE:
        if (dataSize == EFFECT_ACTIVE_STATES_DATA_SIZE && m_effectActiveStatesHandler != nullptr)
        {
            m_effectActiveStatesHandler(data[2], data[3], data[4], data[5], data[6], data[7]);
        }
        break;

    case DELAY_US_MESSAGE_CODE:
        if (dataSize == DELAY_US_DATA_SIZE && m_delayUsHandler != nullptr)
        {
            uint32_t delayUs = static_cast<uint32_t>(data[2]) |
                (static_cast<uint32_t>(data[3]) << 8) |
                (static_cast<uint32_t>(data[4]) << 16) |
                (static_cast<uint32_t>(data[5]) << 24);
            m_delayUsHandler(delayUs);
        }

    case SET_EFFECT_MESSAGE_CODE:
        if (dataSize == SET_EFFECT_DATA_SIZE && m_setEffectHandler != nullptr)
        {
            m_setEffectHandler(data[2], data[3]);
        }
        break;

    case UPDATE_PITCH_SHIFTER_CODE:
        if (dataSize == UPDATE_PITCH_SHIFTER_DATA_SIZE && m_updatePitchShifterHandler != nullptr)
        {
            m_updatePitchShifterHandler(static_cast<PitchShifterUpdateCommand>(data[2]));
        }
        break;
    }
}

#endif
