#ifndef EFFECT_DESIGN_PRESENCE_DESIGNER_H
#define EFFECT_DESIGN_PRESENCE_DESIGNER_H

#include "EffectDesigner.h"
#include "Utils.h"

class PresenceDesigner : public EffectDesigner
{
    static constexpr float MIN_GAIN_DB = 0;
    static constexpr float MAX_GAIN_DB = 12;

    static constexpr float CENTER_FREQUENCY = 1750;
    static constexpr float Q = 0.4;

    static constexpr uint8_t EFFECT_CODE = 1;
    static constexpr uint8_t DATA_SIZE = sizeof(BiquadCoefficients) + sizeof(float);

    uint8_t m_data[DATA_SIZE]; // BiquadCoefficients, global gain

    uint8_t m_currentGainLevel;

public:
    PresenceDesigner(float samplingFrequency);
    ~PresenceDesigner() override;
    
    void update(uint8_t gainLevel);
};

#endif
