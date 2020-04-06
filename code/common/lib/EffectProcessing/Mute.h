#ifndef EFFECT_PROCESSING_MUTE_H
#define EFFECT_PROCESSING_MUTE_H

#include "Effect.h"

template<uint32_t BLOCK_SIZE>
class Mute : public Effect<BLOCK_SIZE>
{
    float m_zeros[BLOCK_SIZE];

public:
    Mute();

    float* process(float* input);
};

template<uint32_t BLOCK_SIZE>
Mute<BLOCK_SIZE>::Mute()
{
    memset(m_zeros, 0, BLOCK_SIZE);
}

template<uint32_t BLOCK_SIZE>
float* Mute<BLOCK_SIZE>::process(float* input)
{
    if (!Effect<BLOCK_SIZE>::isEnabled())
    {
        return input;
    }
    
    return m_zeros;
}

#endif
