#ifndef EFFECT_PROCESSING_DELAY_H
#define EFFECT_PROCESSING_DELAY_H

#include "Effect.h"

#include <string.h>

template<uint32_t BLOCK_SIZE, uint32_t MAX_DELAY>
class Delay : public Effect<BLOCK_SIZE>
{
    static constexpr uint32_t UNROLL_FACTOR = 8;

    float m_volume;
    uint32_t m_delay;

    float m_output[MAX_DELAY];
    int32_t m_outputIndex;
    int32_t m_delayIndex;

public:
    Delay();

    void update(const uint8_t* data);
    float* process(float* input);
};

template<uint32_t BLOCK_SIZE, uint32_t MAX_DELAY>
Delay<BLOCK_SIZE, MAX_DELAY>::Delay() : m_volume(0), m_delay(0), m_outputIndex(0), m_delayIndex(0)
{
    static_assert(MAX_DELAY % BLOCK_SIZE == 0, "MAX_DELAY must be a factor of BLOCK_SIZE.");
    static_assert(MAX_DELAY < INT32_MAX, "MAX_DELAY must be less than INT32_MAX.");
    static_assert(BLOCK_SIZE % UNROLL_FACTOR == 0, "BLOCK_SIZE must be a factor of UNROLL_FACTOR.");

    memset(m_output, 0, sizeof(m_output));
}

template<uint32_t BLOCK_SIZE, uint32_t MAX_DELAY>
void Delay<BLOCK_SIZE, MAX_DELAY>::update(const uint8_t* data)
{
    memcpy(&m_volume, data, sizeof(float));
    memcpy(&m_delay, data + sizeof(float), sizeof(uint32_t));

    if (m_delay > MAX_DELAY)
    {
        m_delay = MAX_DELAY;
    }

    m_delayIndex = (m_outputIndex - m_delay + MAX_DELAY) % MAX_DELAY;
}

template<uint32_t BLOCK_SIZE, uint32_t MAX_DELAY>
float* Delay<BLOCK_SIZE, MAX_DELAY>::process(float* input)
{
    float* output = m_output + m_outputIndex;

    for (uint32_t i = 0; i < BLOCK_SIZE;)
    {
        UNROLL_8(
            m_output[m_outputIndex] = input[i] + m_volume * m_output[m_delayIndex];

            m_outputIndex++;
            m_delayIndex++;
            i++;

            if (m_outputIndex >= static_cast<int32_t>(MAX_DELAY))
            {
                m_outputIndex = 0;
            }
            if (m_delayIndex >= static_cast<int32_t>(MAX_DELAY))
            {
                m_delayIndex = 0;
            }
        );
    }

    return output;
}

#endif
