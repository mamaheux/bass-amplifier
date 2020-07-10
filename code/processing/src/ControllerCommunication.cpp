#include "ControllerCommunication.h"

ControllerCommunication::ControllerCommunication(Effect<BLOCK_SIZE>* effects[]) :
    m_effects(effects),
    m_isWaitingForNewCommand(true),
    m_effectCode(0),
    m_isActive(false),
    m_dataSize(0),
    m_dataIndex(0)
{
}

void ControllerCommunication::begin()
{
    CONTROLLER_SERIAL.begin(CONTROLLER_SERIAL_BAUD_RATE);
}

void ControllerCommunication::update()
{
    if (m_isWaitingForNewCommand)
    {
        if (CONTROLLER_SERIAL.available() >= 3)
        {
            m_effectCode = CONTROLLER_SERIAL.read();
            m_isActive = static_cast<bool>(CONTROLLER_SERIAL.read());
            m_dataSize = CONTROLLER_SERIAL.read();
            m_dataIndex = 0;
            m_isWaitingForNewCommand = false;
        }
    }

    if (!m_isWaitingForNewCommand)
    {
        updateEffectIfReady();        

        while (CONTROLLER_SERIAL.available() > 0 && !m_isWaitingForNewCommand)
        {
            m_data[m_dataIndex] = CONTROLLER_SERIAL.read();
            m_dataIndex++;
            updateEffectIfReady();        
        }
    }
}

void ControllerCommunication::updateEffectIfReady()
{
    if (m_dataIndex == m_dataSize)
    {
        m_isWaitingForNewCommand = true;
        m_effects[m_effectCode]->setIsEnabled(m_isActive);
        m_effects[m_effectCode]->update(m_data);
    }
}