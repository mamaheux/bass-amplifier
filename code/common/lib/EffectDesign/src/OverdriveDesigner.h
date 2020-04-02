#ifndef EFFECT_DESIGN_OVERDRIVE_DESIGNER_H
#define EFFECT_DESIGN_OVERDRIVE_DESIGNER_H

#include "EffectDesigner.h"
#include "Utils.h"

class OverdriveDesigner : public EffectDesigner
{
    static constexpr float MIN_GAIN_DB = 0;
    static constexpr float MAX_GAIN_DB = 40;

    static constexpr float MIN_TONE_FC = 1000;
    static constexpr float MAX_TONE_FC = 7000;

    static constexpr uint8_t EFFECT_CODE = 7;
    static constexpr uint8_t DATA_SIZE = sizeof(BiquadCoefficients) + sizeof(float);

    uint8_t m_data[DATA_SIZE]; // Gain, BiquadCoefficients

    uint8_t m_currentGainLevel;
    uint8_t m_currentToneLevel;

public:
    explicit OverdriveDesigner(float samplingFrequency);
    ~OverdriveDesigner() override;
    
    void update(uint8_t gainLevel, uint8_t toneLevel);

    bool isActive() const override;
};

inline bool OverdriveDesigner::isActive() const
{
    return EffectDesigner::isActive() && m_currentGainLevel;
}

#endif
