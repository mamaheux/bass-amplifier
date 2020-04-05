#ifndef EFFECT_PROCESSING_ALL_PASS_COMB_H
#define EFFECT_PROCESSING_ALL_PASS_COMB_H

#include <EffectDesign.h>

#include <string.h>

template<uint32_t BLOCK_SIZE, uint32_t DELAY>
class AllPassComb
{
    static constexpr uint32_t UNROLL_FACTOR = 8;

    float m_gain;

    float m_state[DELAY + 1];
    float m_output[BLOCK_SIZE];
    int32_t m_outputIndex;
    int32_t m_currentIndex;

public:
    AllPassComb();

    void update(float gain);
    float* process(float* input);
};

template<uint32_t BLOCK_SIZE, uint32_t DELAY>
AllPassComb<BLOCK_SIZE, DELAY>::AllPassComb()
{
    static_assert(BLOCK_SIZE > 0, "BLOCK_SIZE must be greater than 0.");
    static_assert(DELAY < INT32_MAX, "DELAY must be less than INT32_MAX.");
    static_assert(DELAY > 0, "DELAY must be greater than 0.");
    static_assert(BLOCK_SIZE % UNROLL_FACTOR == 0, "BLOCK_SIZE must be a factor of UNROLL_FACTOR.");

    memset(m_output, 0, sizeof(m_output));
    m_currentIndex = DELAY;
    m_outputIndex = 0;
}

template<uint32_t BLOCK_SIZE, uint32_t DELAY>
void AllPassComb<BLOCK_SIZE, DELAY>::update(float gain)
{
    m_gain = gain;
}

template<uint32_t BLOCK_SIZE, uint32_t DELAY>
float* AllPassComb<BLOCK_SIZE, DELAY>::process(float* input)
{
    for (uint32_t i = 0; i < BLOCK_SIZE;)
    {
        UNROLL_8(
            m_state[m_currentIndex] = input[i] + -m_gain * m_state[m_outputIndex];
            m_output[i] = m_state[m_outputIndex] + m_gain * m_state[m_currentIndex];

            m_outputIndex++;
            m_currentIndex++;
            i++;

            if (m_outputIndex > static_cast<int32_t>(DELAY))
            {
                m_outputIndex = 0;
            }
            if (m_currentIndex > static_cast<int32_t>(DELAY))
            {
                m_currentIndex = 0;
            }
        );
    }

    return m_output;
}

#endif
