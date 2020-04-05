#ifndef EFFECT_PROCESSING_CONTOUR_H
#define EFFECT_PROCESSING_CONTOUR_H

#include "Effect.h"
#include "BiquadIir.h"

#include <EffectDesign.h>

template<uint32_t BLOCK_SIZE>
class Contour : public Effect<BLOCK_SIZE>
{
    static constexpr uint32_t NUM_STAGES = 4;

    BiquadIir<BLOCK_SIZE, NUM_STAGES> m_filters;
    float m_globalGain;

    float m_output[BLOCK_SIZE];

public:
    Contour();

    void update(const uint8_t* data);
    float* process(float* input);
};

template<uint32_t BLOCK_SIZE>
Contour<BLOCK_SIZE>::Contour()
{    
}

template<uint32_t BLOCK_SIZE>
void Contour<BLOCK_SIZE>::update(const uint8_t* data)
{
    float filterCoefficients[NUM_STAGES * BiquadCoefficients::COUNT];

    memcpy(filterCoefficients, data, sizeof(BiquadCoefficients));
    memcpy(filterCoefficients + BiquadCoefficients::COUNT, data, sizeof(BiquadCoefficients));
    memcpy(filterCoefficients + 2 * BiquadCoefficients::COUNT, data + sizeof(BiquadCoefficients), sizeof(BiquadCoefficients));
    memcpy(filterCoefficients + 3 * BiquadCoefficients::COUNT, data + sizeof(BiquadCoefficients), sizeof(BiquadCoefficients));
    m_filters.update(filterCoefficients);

    memcpy(&m_globalGain, data + 2 * sizeof(BiquadCoefficients), sizeof(float));
}


template<uint32_t BLOCK_SIZE>
float* Contour<BLOCK_SIZE>::process(float* input)
{
    float* filtersOutput = m_filters.process(input);
    arm_scale_f32(filtersOutput, m_globalGain, m_output, BLOCK_SIZE);
    return m_output;
}

#endif
