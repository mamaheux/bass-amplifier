#ifndef CONTROLLER_TO_FOOTSWITCH_COMMUNICATION_H
#define CONTROLLER_TO_FOOTSWITCH_COMMUNICATION_H

#include "constants.h"

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

    static constexpr uint8_t HEARTBEAT_MESSAGE_CODE = 0;
    static constexpr uint8_t TOOGLE_EFFECT_MESSAGE_CODE = 50;
    static constexpr uint8_t CLIPPING_NOTIFICATION_MESSAGE_CODE = 100;
    static constexpr uint8_t EFFECT_ACTIVE_STATES_MESSAGE_CODE = 150;

    static constexpr uint8_t HEARTBEAT_DATA_SIZE = 3;
    static constexpr uint8_t TOOGLE_EFFECT_DATA_SIZE = 4;
    static constexpr uint8_t CLIPPING_NOTIFICATION_DATA_SIZE = 3;    
    static constexpr uint8_t EFFECT_ACTIVE_STATES_DATA_SIZE = 9;

private:
    TSerial& m_serial;

    HeartbeatHandler m_heartbeatHandler;
    ToogleEffectHandler m_toogleEffectHandler;
    ClippingNotificationHandler m_clippingNotificationHandler;
    EffectActiveStatesHandler m_effectActiveStatesHandler;

public:
    ControllerFootswitchCommunication(TSerial& serial);
    void begin(uint32_t baudRate);

    void registerHeatbeatHandler(HeartbeatHandler handler);
    void registerToogleEffectHandler(ToogleEffectHandler handler);
    void registerClippingNotificationHandler(ClippingNotificationHandler handler);
    void registerEffectActiveStatesHandler(EffectActiveStatesHandler handler);

    void sendHeartbeat();
    void sendToogleEffect(uint8_t effectCode);
    void sendClippingNotification();
    void sendEffectActiveStates(bool compressorActiveState,
        bool octaverActiveState,
        bool delayActiveState,
        bool reverbActiveState,
        bool overrideActiveState,
        bool muteActiveState);

    void receive();

private:
    void handleMessage(uint8_t* data, uint8_t dataSize);
};

template <class TSerial>
ControllerFootswitchCommunication<TSerial>::ControllerFootswitchCommunication(TSerial& serial) : m_serial(serial),
    m_heartbeatHandler(nullptr), m_toogleEffectHandler(nullptr),
    m_clippingNotificationHandler(nullptr), m_effectActiveStatesHandler(nullptr)
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
void ControllerFootswitchCommunication<TSerial>::receive()
{
    if (m_serial.available() == 0) 
    {
        return;
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
    }
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
    }
}

#endif
