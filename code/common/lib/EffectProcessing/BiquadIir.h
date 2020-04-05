#ifndef EFFECT_PROCESSING_BIQUAD_IIR_H
#define EFFECT_PROCESSING_BIQUAD_IIR_H

#include <EffectDesign.h>

#include <arm_math.h>
#include <string.h>

template<uint32_t BLOCK_SIZE, uint32_t NUM_STAGES>
class BiquadIir
{
    float m_state[2 * NUM_STAGES];
    float m_coefficients[BiquadCoefficients::COUNT * NUM_STAGES];
    arm_biquad_cascade_df2T_instance_f32 m_biquadInstance;

    float m_output[BLOCK_SIZE];

public:
    BiquadIir();

    void update(const float* coefficients);
    float* process(float* input);
};

template<uint32_t BLOCK_SIZE, uint32_t NUM_STAGES>
BiquadIir<BLOCK_SIZE, NUM_STAGES>::BiquadIir()
{
    static_assert(BLOCK_SIZE > 0, "BLOCK_SIZE must be greater than 0.");
    static_assert(NUM_STAGES > 0, "NUM_STAGES must be greater than 0.");

    memset(m_state, 0, sizeof(m_state));
    memset(m_coefficients, 0, sizeof(m_coefficients));

    m_biquadInstance.numStages = NUM_STAGES;
    m_biquadInstance.pState = m_state;
    m_biquadInstance.pCoeffs = m_coefficients;    
}

template<uint32_t BLOCK_SIZE, uint32_t NUM_STAGES>
void BiquadIir<BLOCK_SIZE, NUM_STAGES>::update(const float* coefficients)
{
    memcpy(m_coefficients, coefficients, sizeof(m_coefficients));
}

template<uint32_t BLOCK_SIZE, uint32_t NUM_STAGES>
float* BiquadIir<BLOCK_SIZE, NUM_STAGES>::process(float* input)
{
    arm_biquad_cascade_df2T_f32(&m_biquadInstance, input, m_output, BLOCK_SIZE);
    return m_output;
}

#endif
