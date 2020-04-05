#ifndef EFFECT_PROCESSING_COMPRESSOR_H
#define EFFECT_PROCESSING_COMPRESSOR_H

#include "Effect.h"

#include <arm_math.h>

template<uint32_t BLOCK_SIZE>
class Compressor : public Effect<BLOCK_SIZE>
{
    static constexpr uint32_t UNLOOP_FACTOR = 8;

    float m_absInput[BLOCK_SIZE];
    float m_levelState;
    float m_level[BLOCK_SIZE];

    float m_output[BLOCK_SIZE];

    float m_threshold;
    float m_ratio;
    float m_attack;
    float m_attackComplement;
    float m_release;
    float m_releaseComplement;

public:
    Compressor();

    void update(const uint8_t* data);
    float* process(float* input);

private:
    void calculateLevel(float* input);
};

template<uint32_t BLOCK_SIZE>
Compressor<BLOCK_SIZE>::Compressor() : m_levelState(0), m_threshold(0), m_ratio(0), m_attack(0), m_release(0)
{
    static_assert(BLOCK_SIZE % UNLOOP_FACTOR == 0, "BLOCK_SIZE must be greater than 0.");
}

template<uint32_t BLOCK_SIZE>
void Compressor<BLOCK_SIZE>::update(const uint8_t* data)
{
    memcpy(&m_threshold, data, sizeof(float));
    memcpy(&m_ratio, data + sizeof(float), sizeof(float));
    memcpy(&m_attack, data + 2 * sizeof(float), sizeof(float));
    memcpy(&m_release, data + 3 * sizeof(float), sizeof(float));

    m_attackComplement = 1 - m_attack;
    m_releaseComplement = 1 - m_release;
}

template<uint32_t BLOCK_SIZE>
float* Compressor<BLOCK_SIZE>::process(float* input)
{
    calculateLevel(input);

    for (uint32_t i = 0; i < BLOCK_SIZE;)
    {
        UNLOOP_8(
            if (m_level[i] > m_threshold)
            {
                m_output[i] = (m_ratio * m_threshold / m_level[i] + (1 - m_ratio)) * input[i];
            }
            else
            {
                m_output[i] = input[i];
            }
            i++;
        );
    }

    return m_output;
}

template<uint32_t BLOCK_SIZE>
void Compressor<BLOCK_SIZE>::calculateLevel(float* input)
{
    arm_abs_f32(input, m_absInput, BLOCK_SIZE);

    for (uint32_t i = 0; i < BLOCK_SIZE;)
    {
        UNLOOP_8(
            float nextLevel;
            if (m_absInput[i] > m_levelState)
            {
                nextLevel = m_attack * m_levelState + m_attackComplement * m_absInput[i];
            }
            else
            {
                nextLevel = m_release * m_levelState + m_releaseComplement * m_absInput[i];
            }
            m_level[i] = nextLevel;
            m_levelState = nextLevel;
            i++;
        );        
    }
}

#endif
