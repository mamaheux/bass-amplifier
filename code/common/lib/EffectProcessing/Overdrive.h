#ifndef EFFECT_PROCESSING_OVERDRIVE_H
#define EFFECT_PROCESSING_OVERDRIVE_H

#include "Effect.h"
#include "BiquadIir.h"

#include <EffectDesign.h>

#include <math.h>

template<uint32_t BLOCK_SIZE>
class Overdrive : public Effect<BLOCK_SIZE>
{
    static constexpr uint32_t UNROLL_FACTOR = 8;
    static constexpr float SIGNAL_GAIN = 0.75;

    static constexpr uint32_t NUM_STAGES = 1;
    BiquadIir<BLOCK_SIZE, NUM_STAGES> m_lowPassFilter;
    float m_gain;

    float m_expOutput[BLOCK_SIZE];
    float m_output[BLOCK_SIZE];

public:
    Overdrive();

    void update(const uint8_t* data);
    float* process(float* input);
};

template<uint32_t BLOCK_SIZE>
Overdrive<BLOCK_SIZE>::Overdrive() : m_gain(0)
{
    static_assert(BLOCK_SIZE % UNROLL_FACTOR == 0, "BLOCK_SIZE must be a factor of UNROLL_FACTOR.");
}

template<uint32_t BLOCK_SIZE>
void Overdrive<BLOCK_SIZE>::update(const uint8_t* data)
{
    m_lowPassFilter.update(reinterpret_cast<const float*>(data));

    memcpy(&m_gain, data + sizeof(BiquadCoefficients), sizeof(float));
}

template<uint32_t BLOCK_SIZE>
float* Overdrive<BLOCK_SIZE>::process(float* input)
{
    float inputGain = 1 + m_gain;
    for (uint32_t i = 0; i < BLOCK_SIZE;)
    {
        UNROLL_8(
            if (input[i] > 0)
            {
                m_expOutput[i] = 1 - exp(-input[i] * inputGain);
            }
            else
            {
                m_expOutput[i] = -1 + exp(input[i] * inputGain);
            }
            i++;
        );
    }

    float* filterOutput = m_lowPassFilter.process(m_expOutput);
    arm_scale_f32(filterOutput, SIGNAL_GAIN, m_output, BLOCK_SIZE);
    return m_output;
}

#endif
