#ifndef EFFECT_PROCESSING_EQ_H
#define EFFECT_PROCESSING_EQ_H

#include "Effect.h"
#include "BiquadIir.h"

#include <EffectDesign.h>

template<uint32_t BLOCK_SIZE>
class Eq : public Effect<BLOCK_SIZE>
{
    static constexpr uint32_t NUM_STAGES = 8;

    BiquadIir<BLOCK_SIZE, NUM_STAGES> m_filters;

public:
    Eq();

    void update(const uint8_t* data);
    float* process(float* input);
};

template<uint32_t BLOCK_SIZE>
Eq<BLOCK_SIZE>::Eq()
{    
}

template<uint32_t BLOCK_SIZE>
void Eq<BLOCK_SIZE>::update(const uint8_t* data)
{
    m_filters.update(reinterpret_cast<const float*>(data));
}


template<uint32_t BLOCK_SIZE>
float* Eq<BLOCK_SIZE>::process(float* input)
{
    return m_filters.process(input);
}

#endif
