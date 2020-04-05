#ifndef EFFECT_PROCESSING_PRESENCE_H
#define EFFECT_PROCESSING_PRESENCE_H

#include "Effect.h"
#include "BiquadIir.h"

#include <EffectDesign.h>

template<uint32_t BLOCK_SIZE>
class Presence : public Effect<BLOCK_SIZE>
{
    static constexpr uint32_t NUM_STAGES = 2;

    BiquadIir<BLOCK_SIZE, NUM_STAGES> m_filters;
    float m_globalGain;

    float m_output[BLOCK_SIZE];

public:
    Presence();

    void update(const uint8_t* data);
    float* process(float* input);
};

template<uint32_t BLOCK_SIZE>
Presence<BLOCK_SIZE>::Presence() : m_globalGain(0)
{
}

template<uint32_t BLOCK_SIZE>
void Presence<BLOCK_SIZE>::update(const uint8_t* data)
{
    float filterCoefficients[NUM_STAGES * BiquadCoefficients::COUNT];

    memcpy(filterCoefficients, data, sizeof(BiquadCoefficients));
    memcpy(filterCoefficients + BiquadCoefficients::COUNT, data, sizeof(BiquadCoefficients));
    m_filters.update(filterCoefficients);

    memcpy(&m_globalGain, data + sizeof(BiquadCoefficients), sizeof(float));
}


template<uint32_t BLOCK_SIZE>
float* Presence<BLOCK_SIZE>::process(float* input)
{
    float* filtersOutput = m_filters.process(input);
    arm_scale_f32(filtersOutput, m_globalGain, m_output, BLOCK_SIZE);
    return m_output;
}

#endif
