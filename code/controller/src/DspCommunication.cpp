#include "DspCommunication.h"

#include "config.h"

#include <Communication.h>

DspCommunication::DspCommunication(EffectDesigner* effectDesigners[]) :
    m_effectDesigners(effectDesigners),
    m_clippingNotificationHandler(nullptr)
{

}

void DspCommunication::begin(ClippingNotificationHandler clippingNotificationHandler)
{
    m_clippingNotificationHandler = clippingNotificationHandler;
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

    readNotification();
}

void DspCommunication::sendData(EffectDesigner* effectDesigner)
{
    uint8_t effectCode = effectDesigner->effectCode();
    uint8_t dataSize = effectDesigner->dataSize();
    const uint8_t* data = effectDesigner->data();

    while (DSP_SERIAL.availableForWrite() < 5);
    DSP_SERIAL.write(DSP_PREAMBLE);
    DSP_SERIAL.write(DSP_PREAMBLE);
    DSP_SERIAL.write(effectCode);
    DSP_SERIAL.write(static_cast<uint8_t>(effectDesigner->isActive()));
    DSP_SERIAL.write(dataSize);

    for (uint8_t i = 0; i < dataSize; i++)
    {
        while (DSP_SERIAL.availableForWrite() < 1);
        DSP_SERIAL.write(data[i]);
    }
}

void DspCommunication::readNotification()
{
    bool isClippingNotificationSent = false;
    while (DSP_SERIAL.available() > 0)
    {
        DSP_SERIAL.read();
        if (!isClippingNotificationSent && m_clippingNotificationHandler != nullptr)
        {
            m_clippingNotificationHandler();
            isClippingNotificationSent = true;
        }
    }
}
