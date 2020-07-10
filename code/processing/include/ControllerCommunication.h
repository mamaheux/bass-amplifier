#ifndef CONTROLLER_COMMUNICATION_H
#define CONTROLLER_COMMUNICATION_H

#include "config.h"

#include <EffectProcessing.h>

class ControllerCommunication
{
    Effect<BLOCK_SIZE>** m_effects;

    bool m_isWaitingForNewCommand;

    uint8_t m_effectCode;
    bool m_isActive;
    uint8_t m_dataSize;
    uint8_t m_data[UINT8_MAX];
    uint8_t m_dataIndex;

public:
    ControllerCommunication(Effect<BLOCK_SIZE>* effects[]);
    void begin();

    void update();

private:
    void updateEffectIfReady();
};

#endif
