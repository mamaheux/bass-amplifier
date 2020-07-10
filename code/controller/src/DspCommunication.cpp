#include "DspCommunication.h"

#include "config.h"

#include <Communication.h>

DspCommunication::DspCommunication(EffectDesigner* effectDesigners[]) : m_effectDesigners(effectDesigners)
{

}

void DspCommunication::begin()
{
    DSP_SERIAL.begin(DSP_SERIAL_BAUD_RATE);
}

void DspCommunication::update()
{
    for (uint32_t i = 0; i < EFFECT_CODE_COUNT; i++)
    {
        if (m_effectDesigners[i]->isDirty())
        {
            m_effectDesigners[i]->setIsDirty(false);
            sendData(m_effectDesigners[i]);            
        }
    }
}

void DspCommunication::sendData(EffectDesigner* effectDesigner)
{
    uint8_t effectCode = effectDesigner->effectCode();
    uint8_t dataSize = effectDesigner->dataSize();
    uint8_t* data = effectDesigner->data();

    while (DSP_SERIAL.availableForWrite() < 2);
    DSP_SERIAL.write(effectCode);
    DSP_SERIAL.write(dataSize);

    for (uint8_t i = 0; i < dataSize; i++)
    {
        while (DSP_SERIAL.availableForWrite() < 1);
        DSP_SERIAL.write(data[i]);
    }
}
