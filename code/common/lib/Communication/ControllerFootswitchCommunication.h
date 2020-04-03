#ifndef CONTROLLER_TO_FOOTSWITCH_COMMUNICATION_H
#define CONTROLLER_TO_FOOTSWITCH_COMMUNICATION_H

#include "constants.h"

constexpr uint32_t CONTROLLER_FOOTSWITCH_HEARTBEAT_TIMEOUT_MS = 1000;

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

    static constexpr uint8_t HEARTBEAT_MESSAGE_CODE = 0;
    static constexpr uint8_t TOOGLE_EFFECT_MESSAGE_CODE = 25;
    static constexpr uint8_t CLIPPING_NOTIFICATION_MESSAGE_CODE = 50;
    static constexpr uint8_t EFFECT_ACTIVE_STATES_MESSAGE_CODE = 75;
    static constexpr uint8_t DELAY_US_MESSAGE_CODE = 100;
    static constexpr uint8_t SET_EFFECT_MESSAGE_CODE = 125;
    static constexpr uint8_t ACK_MESSAGE_CODE = 150;

    static constexpr uint8_t HEARTBEAT_DATA_SIZE = 3;
    static constexpr uint8_t TOOGLE_EFFECT_DATA_SIZE = 4;
    static constexpr uint8_t CLIPPING_NOTIFICATION_DATA_SIZE = 3;
    static constexpr uint8_t EFFECT_ACTIVE_STATES_DATA_SIZE = 9;
    static constexpr uint8_t DELAY_US_DATA_SIZE = 7;
    static constexpr uint8_t SET_EFFECT_DATA_SIZE = 5;
    static constexpr uint8_t ACK_DATA_SIZE = 3;

private:
    TSerial& m_serial;

    HeartbeatHandler m_heartbeatHandler;
    ToogleEffectHandler m_toogleEffectHandler;
    ClippingNotificationHandler m_clippingNotificationHandler;
    EffectActiveStatesHandler m_effectActiveStatesHandler;
    DelayUsHandler m_delayUsHandler;
    SetEffectHandler m_setEffectHandler;

public:
    ControllerFootswitchCommunication(TSerial& serial);
    void begin(uint32_t baudRate);

    void registerHeatbeatHandler(HeartbeatHandler handler);
    void registerToogleEffectHandler(ToogleEffectHandler handler);
    void registerClippingNotificationHandler(ClippingNotificationHandler handler);
    void registerEffectActiveStatesHandler(EffectActiveStatesHandler handler);
    void registerDelayUsHandler(DelayUsHandler handler);
    void registerSetEffectHandler(SetEffectHandler handler);

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
    void sendAck();

    bool receive(uint8_t* receivedMessageCode = nullptr);

    template <class FMillis>
    bool waitAck(FMillis millis, uint32_t timeoutMs);

private:
    void handleMessage(uint8_t* data, uint8_t dataSize);
};

template <class TSerial>
ControllerFootswitchCommunication<TSerial>::ControllerFootswitchCommunication(TSerial& serial) : m_serial(serial),
    m_heartbeatHandler(nullptr), m_toogleEffectHandler(nullptr),
    m_clippingNotificationHandler(nullptr), m_effectActiveStatesHandler(nullptr),
    m_delayUsHandler(nullptr), m_setEffectHandler(nullptr)
{
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::begin(uint32_t baudRate)
{
    m_serial.begin(baudRate);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::registerHeatbeatHandler(HeartbeatHandler handler)
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
void ControllerFootswitchCommunication<TSerial>::sendHeartbeat()
{
    constexpr uint8_t checksum = UINT8_MAX - (HEARTBEAT_DATA_SIZE + HEARTBEAT_MESSAGE_CODE) + 1;
    uint8_t data[HEARTBEAT_DATA_SIZE] = {HEARTBEAT_DATA_SIZE, HEARTBEAT_MESSAGE_CODE, checksum};

    m_serial.write(reinterpret_cast<char*>(data), HEARTBEAT_DATA_SIZE);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::sendToogleEffect(uint8_t effectCode)
{
    const uint8_t checksum =  UINT8_MAX - (TOOGLE_EFFECT_DATA_SIZE + TOOGLE_EFFECT_MESSAGE_CODE + effectCode) + 1;
    uint8_t data[TOOGLE_EFFECT_DATA_SIZE] = {TOOGLE_EFFECT_DATA_SIZE, TOOGLE_EFFECT_MESSAGE_CODE, effectCode, checksum};

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
        EFFECT_ACTIVE_STATES_MESSAGE_CODE + compressorActiveState + 
        delayActiveState + reverbActiveState + overrideActiveState + muteActiveState) + 1;

    uint8_t data[EFFECT_ACTIVE_STATES_DATA_SIZE] = 
    {
        EFFECT_ACTIVE_STATES_DATA_SIZE, EFFECT_ACTIVE_STATES_MESSAGE_CODE,
        compressorActiveState, octaverActiveState,
        delayActiveState, reverbActiveState,
        overrideActiveState, muteActiveState, 
        checksum
    };

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

    m_serial.write(reinterpret_cast<char*>(data), DELAY_US_DATA_SIZE);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::sendSetEffect(uint8_t effectCode, bool isEnabled)
{
    const uint8_t checksum =  UINT8_MAX - (SET_EFFECT_DATA_SIZE + SET_EFFECT_MESSAGE_CODE + effectCode + isEnabled) + 1;
    uint8_t data[SET_EFFECT_DATA_SIZE] = {SET_EFFECT_DATA_SIZE, SET_EFFECT_MESSAGE_CODE, effectCode, isEnabled, checksum};

    m_serial.write(reinterpret_cast<char*>(data), SET_EFFECT_DATA_SIZE);
}

template <class TSerial>
void ControllerFootswitchCommunication<TSerial>::sendAck()
{
    constexpr uint8_t checksum = UINT8_MAX - (ACK_DATA_SIZE + ACK_MESSAGE_CODE) + 1;
    uint8_t data[ACK_DATA_SIZE] = {ACK_DATA_SIZE, ACK_MESSAGE_CODE, checksum};

    m_serial.write(reinterpret_cast<char*>(data), ACK_DATA_SIZE);
}

template <class TSerial>
bool ControllerFootswitchCommunication<TSerial>::receive(uint8_t* receivedMessageCode)
{
    if (m_serial.available() == 0)
    {
        return false;
    }
    
    constexpr uint8_t MAX_DATA_SIZE = 9;
    uint8_t data[MAX_DATA_SIZE] = {0};

    uint8_t dataSize = m_serial.read();
    data[0] = dataSize;
    uint8_t checksum = dataSize;

    for (uint8_t i = 1; i < dataSize && i < MAX_DATA_SIZE; i++)
    {
        while (m_serial.available() == 0);
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
template <class FMillis>
bool ControllerFootswitchCommunication<TSerial>::waitAck(FMillis millis, uint32_t timeoutMs)
{
    uint32_t startTimeMs = millis();
    uint8_t receivedMessageCode = UINT8_MAX;
    while (receivedMessageCode != ACK_MESSAGE_CODE && (millis() - startTimeMs) < timeoutMs)
    {
        receive(&receivedMessageCode);
    }

    return receivedMessageCode == ACK_MESSAGE_CODE;
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
    }
}

#endif
