#include "EffectControls.h"

static volatile uint32_t* delayUs = nullptr;
static volatile uint32_t lastDelayTapUs = 0;
static void delayTapInterrupt()
{
    if (delayUs == nullptr)
    {
        return;
    }

    uint32_t timeUs = micros();
    *delayUs = lastDelayTapUs - timeUs;
    lastDelayTapUs = timeUs;
}

static volatile bool* muteState = nullptr;
static void muteInterrupt()
{
    *muteState = !muteState;
}

EffectControls::EffectControls(ControlAdc& adc) : m_adc(adc), m_delayUs(0)
{
}

void EffectControls::begin()
{
    delayUs = &m_delayUs;
    pinMode(DELAY_TAP_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(DELAY_TAP_PIN), delayTapInterrupt, RISING);

    muteState = &m_muteState;
    pinMode(MUTE_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(MUTE_PIN), muteInterrupt, RISING);
}

uint8_t EffectControls::readAdc(AdcChannel channel)
{
    uint32_t value12Bits = m_adc.read(channel);
    if (value12Bits < POT_DEAD_ZONE)
    {
        return 0;
    }
    if (value12Bits > (ADC_MAX_VALUE - POT_DEAD_ZONE))
    {
        return UINT8_MAX;
    }
    
    return (value12Bits - POT_DEAD_ZONE) * UINT8_MAX / (ADC_MAX_VALUE - 2 * POT_DEAD_ZONE);
}
