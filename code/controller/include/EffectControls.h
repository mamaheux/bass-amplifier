#ifndef EFFECT_CONTROLS_H
#define EFFECT_CONTROLS_H

#include "config.h"
#include "ControlAdc.h"

class EffectControls
{
    ControlAdc& m_adc;

    volatile uint32_t m_delayUs;

public:
    EffectControls(ControlAdc& adc);

    void begin();

    uint8_t getContourGain();
    uint8_t getPresenceGain();

    uint8_t getEqLowGain();
    uint8_t getEqLowMidGain();
    uint8_t getEqHighMidGain();
    uint8_t getEqHighGain();

    uint8_t getCompressorThreshold();
    uint8_t getCompressorRatio();

    uint8_t getOctaverDownVolume();
    uint8_t getOctaverUpVolume();

    uint8_t getDelayVolume();
    uint32_t getDelay();

    uint8_t getReverbVolume();

    uint8_t getOverdriveGain();
    uint8_t getOverdriveTone();

    bool getMuteState();

private:
    uint8_t readAdc(AdcChannel channel);
};

inline uint8_t EffectControls::getContourGain()
{
    return readAdc(CONTOUR_GAIN_POT);
}

inline uint8_t EffectControls::getPresenceGain()
{
    return readAdc(PRESENCE_GAIN_POT);
}

inline uint8_t EffectControls::getEqLowGain()
{
    return readAdc(EQ_LOW_GAIN_POT);
}

inline uint8_t EffectControls::getEqLowMidGain()
{
    return readAdc(EQ_LOW_MID_GAIN_POT);
}

inline uint8_t EffectControls::getEqHighMidGain()
{
    return readAdc(EQ_HIGH_MID_GAIN_POT);
}

inline uint8_t EffectControls::getEqHighGain()
{
    return readAdc(EQ_HIGH_GAIN_POT);
}

inline uint8_t EffectControls::getCompressorThreshold()
{
    return readAdc(COMPRESSOR_THRESHOLD_POT);
}

inline uint8_t EffectControls::getCompressorRatio()
{
    return readAdc(COMPRESSOR_RATIO_POT);
}

inline uint8_t EffectControls::getOctaverDownVolume()
{
    return readAdc(OCTAVER_DOWM_VOLUME_POT);
}

inline uint8_t EffectControls::getOctaverUpVolume()
{
    return readAdc(OCTAVER_UP_VOLUME_POT);
}

inline uint8_t EffectControls::getDelayVolume()
{
    return readAdc(DELAY_VOLUME_POT);
}

inline uint32_t EffectControls::getDelay()
{
    float delaySec = m_delayUs / 1.0e-6;
    return static_cast<uint32_t>(delaySec * SAMPLING_FREQUENCY);
}

inline uint8_t EffectControls::getReverbVolume()
{
    return readAdc(REVERB_VOLUME_POT);
}

inline uint8_t EffectControls::getOverdriveGain()
{
    return readAdc(OVERDRIVE_GAIN_POT);
}

inline uint8_t EffectControls::getOverdriveTone()
{
    return readAdc(OVERDRIVE_TONE_POT);
}

inline bool EffectControls::getMuteState()
{
    return digitalRead(MUTE_PIN);
}

#endif
