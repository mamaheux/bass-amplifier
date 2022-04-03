#ifndef EFFECT_PROCESSING_OCTAVER_H
#define EFFECT_PROCESSING_OCTAVER_H

#include "Effect.h"
#include "BiquadIir.h"

#include <EffectDesign.h>

template<uint32_t BLOCK_SIZE>
class Octaver : public Effect<BLOCK_SIZE>
{
    static constexpr uint32_t UNROLL_FACTOR = 8;

    static constexpr uint32_t DOWN_OCTAVE_NUM_STAGES = 1;
    static constexpr uint32_t UP_OCTAVLE_NUM_STAGES = 2;

    static constexpr float DOWN_OCTAVE_HYSTERESIS = 0.01;

    BiquadIir<BLOCK_SIZE, DOWN_OCTAVE_NUM_STAGES> m_downOctaveLowPassFilter;
    BiquadIir<BLOCK_SIZE, UP_OCTAVLE_NUM_STAGES> m_upOctaveBandPassFilter;
    float m_downOctaveVolume;
    float m_upOctaveVolume;
    float m_scaleFactor;

    bool m_lastInputSquareWave;
    float m_downOctaveSign;
    float m_downOctave[BLOCK_SIZE];
    float m_scaledDownOctave[BLOCK_SIZE];

    float m_absInput[BLOCK_SIZE];
    float m_scaledUpOctave[BLOCK_SIZE];

    float m_output[BLOCK_SIZE];

public:
    Octaver();

    void update(const uint8_t* data) override;
    float* process(float* input);

private:
    void processDownOctave(float* input);
    void processUpOctave(float* input);
};

template<uint32_t BLOCK_SIZE>
Octaver<BLOCK_SIZE>::Octaver() :
    m_downOctaveVolume(0), m_upOctaveVolume(0),
    m_lastInputSquareWave(false), m_downOctaveSign(1)
{
    static_assert(BLOCK_SIZE % UNROLL_FACTOR == 0, "BLOCK_SIZE must be a factor of UNROLL_FACTOR.");
}

template<uint32_t BLOCK_SIZE>
void Octaver<BLOCK_SIZE>::update(const uint8_t* data)
{
    m_downOctaveLowPassFilter.update(reinterpret_cast<const float*>(data));
    m_upOctaveBandPassFilter.update(reinterpret_cast<const float*>(data + sizeof(BiquadCoefficients)));

    memcpy(&m_downOctaveVolume, data + 3 * sizeof(BiquadCoefficients), sizeof(float));
    memcpy(&m_upOctaveVolume, data + 3 * sizeof(BiquadCoefficients) + sizeof(float), sizeof(float));

    m_scaleFactor = 1 / (m_downOctaveVolume + m_upOctaveVolume + 1);
}

template<uint32_t BLOCK_SIZE>
float* Octaver<BLOCK_SIZE>::process(float* input)
{
    processDownOctave(input);
    processUpOctave(input);

    arm_add_f32(m_scaledDownOctave, m_scaledUpOctave, m_output, BLOCK_SIZE);
    arm_add_f32(m_output, input, m_output, BLOCK_SIZE);
    arm_scale_f32(m_output, m_scaleFactor, m_output, BLOCK_SIZE);

    if (!Effect<BLOCK_SIZE>::isEnabled())
    {
        return input;
    }
    return m_output;
}

template<uint32_t BLOCK_SIZE>
void Octaver<BLOCK_SIZE>::processDownOctave(float* input)
{
    for (uint32_t i = 0; i < BLOCK_SIZE;)
    {
        UNROLL_8(
            bool inputSquareWave = m_lastInputSquareWave;
            if ((m_lastInputSquareWave && input[i] <= -DOWN_OCTAVE_HYSTERESIS) ||
                (!m_lastInputSquareWave && input[i] >= DOWN_OCTAVE_HYSTERESIS))
            {
                inputSquareWave = !inputSquareWave;
            }
            if (!m_lastInputSquareWave && inputSquareWave)
            {
                m_downOctaveSign = -m_downOctaveSign;
            }

            m_downOctave[i] = m_downOctaveSign * input[i];

            m_lastInputSquareWave = inputSquareWave;
            i++;
        );
    }

    float* filteredDownOctave = m_downOctaveLowPassFilter.process(m_downOctave);
    arm_scale_f32(filteredDownOctave, m_downOctaveVolume, m_scaledDownOctave, BLOCK_SIZE);
}

template<uint32_t BLOCK_SIZE>
void Octaver<BLOCK_SIZE>::processUpOctave(float* input)
{
    arm_abs_f32(input, m_absInput, BLOCK_SIZE);
    float* upOctave = m_upOctaveBandPassFilter.process(m_absInput);
    arm_scale_f32(upOctave, m_upOctaveVolume, m_scaledUpOctave, BLOCK_SIZE);
}

#endif
