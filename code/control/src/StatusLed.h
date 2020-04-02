#ifndef STATUC_LED_H
#define STATUC_LED_H

#include "config.h"

class StatusLed
{
    uint32_t m_lastClippingMs;

public:
    StatusLed();
    void begin();
    void update();

    void setCompressorLed(bool value);
    void setOctaverLed(bool value);
    void setDelayLed(bool value);
    void setReverbLed(bool value);
    void setOverdriveLed(bool value);
    void setMuteLed(bool value);

    void notifyClipping();

private:
    void setClippingLed(bool value);
};

inline void StatusLed::setCompressorLed(bool value)
{
    digitalWrite(COMPRESSOR_LED_PIN, value);
}

inline void StatusLed::setOctaverLed(bool value)
{
    digitalWrite(OCTAVER_LED_PIN, value);
}

inline void StatusLed::setDelayLed(bool value)
{
    digitalWrite(DELAY_LED_PIN, value);
}

inline void StatusLed::setReverbLed(bool value)
{
    digitalWrite(REVERB_LED_PIN, value);
}

inline void StatusLed::setOverdriveLed(bool value)
{
    digitalWrite(OVERDRIVE_LED_PIN, value);
}

inline void StatusLed::setMuteLed(bool value)
{
    digitalWrite(MUTE_LED_PIN, value);
}

inline void StatusLed::notifyClipping()
{
    m_lastClippingMs - millis();
    setClippingLed(true);
}

inline void StatusLed::setClippingLed(bool value)
{
    digitalWrite(CLIPPING_LED_PIN, value);
}

#endif
