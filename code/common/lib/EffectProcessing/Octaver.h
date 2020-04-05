#ifndef EFFECT_PROCESSING_OCTAVER_H
#define EFFECT_PROCESSING_OCTAVER_H

#include "Effect.h"
#include "BiquadIir.h"

#include <EffectDesign.h>

template<uint32_t BLOCK_SIZE>
class Octaver : public Effect<BLOCK_SIZE>
{
    static constexpr uint32_t NUM_STAGES = 2;

    BiquadIir<BLOCK_SIZE, NUM_STAGES> m_upOctaveBandPassFilter;
    float m_downOctaveVolume;
    float m_upOctaveVolume;
    float m_scaleFactor;

    float m_scaledDownOctave[BLOCK_SIZE];

    float m_absInput[BLOCK_SIZE];
    float m_scaledUpOctave[BLOCK_SIZE];

    float m_output[BLOCK_SIZE];

public:
    Octaver();

    void update(const uint8_t* data);
    float* process(float* input, float* downOctave);
};

template<uint32_t BLOCK_SIZE>
Octaver<BLOCK_SIZE>::Octaver() : m_downOctaveVolume(0), m_upOctaveVolume(0)
{
}

template<uint32_t BLOCK_SIZE>
void Octaver<BLOCK_SIZE>::update(const uint8_t* data)
{
    m_upOctaveBandPassFilter.update(reinterpret_cast<const float*>(data));

    memcpy(&m_downOctaveVolume, data + 2 * sizeof(BiquadCoefficients), sizeof(float));
    memcpy(&m_upOctaveVolume, data + 2 * sizeof(BiquadCoefficients) + sizeof(float), sizeof(float));

    m_scaleFactor = 1 / (m_downOctaveVolume + m_upOctaveVolume + 1);
}


template<uint32_t BLOCK_SIZE>
float* Octaver<BLOCK_SIZE>::process(float* input, float* downOctave)
{
    arm_scale_f32(downOctave, m_downOctaveVolume, m_scaledDownOctave, BLOCK_SIZE);

    arm_abs_f32(input, m_absInput, BLOCK_SIZE);
    float* upOctave = m_upOctaveBandPassFilter.process(m_absInput);
    arm_scale_f32(upOctave, m_upOctaveVolume, m_scaledUpOctave, BLOCK_SIZE);

    arm_add_f32(m_scaledDownOctave, m_scaledUpOctave, m_output, BLOCK_SIZE);
    arm_add_f32(m_output, input, m_output, BLOCK_SIZE);
    arm_scale_f32(m_output, m_scaleFactor, m_output, BLOCK_SIZE);

    return m_output;
}

#endif
