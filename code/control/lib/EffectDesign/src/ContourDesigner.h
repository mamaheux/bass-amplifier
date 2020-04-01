#ifndef EFFECT_DESIGN_CONTOUR_DESIGNER_H
#define EFFECT_DESIGN_CONTOUR_DESIGNER_H

#include "EffectDesigner.h"
#include "Utils.h"

class ContourDesigner : public EffectDesigner
{
    static constexpr float MIN_GAIN_DB = 0;
    static constexpr float MAX_GAIN_DB = 12;
    
    static constexpr float LOW_CENTER_FREQUENCY = 100;
    static constexpr float LOW_Q = 0.5;

    static constexpr float HIGH_CENTER_FREQUENCY = 2500;
    static constexpr float HIGH_Q = 0.5;

    static constexpr uint8_t EFFECT_CODE = 0;
    static constexpr uint8_t DATA_SIZE = 2 * sizeof(BiquadCoefficients) + sizeof(float);

    uint8_t m_data[DATA_SIZE]; // Low pass BiquadCoefficients, high pass BiquadCoefficients, global gain

    uint8_t m_currentGainLevel;

public:
    ContourDesigner(float samplingFrequency);
    ~ContourDesigner() override;
    
    void update(uint8_t gainLevel);
};

#endif
