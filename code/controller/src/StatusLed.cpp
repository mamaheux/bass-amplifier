#include "StatusLed.h"

StatusLed::StatusLed()
{
}

void StatusLed::begin()
{
    pinMode(COMPRESSOR_LED_PIN, OUTPUT);
    pinMode(OCTAVER_LED_PIN, OUTPUT);
    pinMode(DELAY_LED_PIN, OUTPUT);
    pinMode(REVERB_LED_PIN, OUTPUT);
    pinMode(OVERDRIVE_LED_PIN, OUTPUT);
    pinMode(MUTE_LED_PIN, OUTPUT);
    pinMode(CLIPPING_LED_PIN, OUTPUT);
}

void StatusLed::update()
{
    if ((millis() - m_lastClippingMs) >= CLIPPING_LED_ON_DURATION_MS)
    {
        setClippingLed(false);
    }
}