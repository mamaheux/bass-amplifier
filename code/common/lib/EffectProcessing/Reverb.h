#ifndef EFFECT_PROCESSING_REVERB_H
#define EFFECT_PROCESSING_REVERB_H

#include "Effect.h"
#include "FeedbackComb.h"
#include "AllPassComb.h"

template<uint32_t BLOCK_SIZE>
class Reverb : public Effect<BLOCK_SIZE>
{
    static constexpr float FEEDBACK_COMB_GAIN = 0.5;
    static constexpr float ALL_PASS_COMB_GAIN = 0.7;
    static constexpr float SIGNAL_GAIN = 0.5;

    static constexpr float FEEDBACK_COMB_COUNT = 6;

    FeedbackComb<BLOCK_SIZE, 181> m_feedbackComb0;
    FeedbackComb<BLOCK_SIZE, 222> m_feedbackComb1;
    FeedbackComb<BLOCK_SIZE, 1629> m_feedbackComb2;
    FeedbackComb<BLOCK_SIZE, 1756> m_feedbackComb3;
    FeedbackComb<BLOCK_SIZE, 737> m_feedbackComb4;
    FeedbackComb<BLOCK_SIZE, 807> m_feedbackComb5;

    AllPassComb<BLOCK_SIZE, 3840> m_allPassComb;

    float m_volume;

    float m_feedbackCombSum[BLOCK_SIZE];
    float m_filterSum[BLOCK_SIZE];
    float m_output[BLOCK_SIZE];

public:
    Reverb();

    void update(const uint8_t* data) override;
    float* process(float* input);
};

template<uint32_t BLOCK_SIZE>
Reverb<BLOCK_SIZE>::Reverb() : m_volume(0)
{
    m_feedbackComb0.update(FEEDBACK_COMB_GAIN);
    m_feedbackComb1.update(FEEDBACK_COMB_GAIN);
    m_feedbackComb2.update(FEEDBACK_COMB_GAIN);
    m_feedbackComb3.update(FEEDBACK_COMB_GAIN);
    m_feedbackComb4.update(FEEDBACK_COMB_GAIN);

    m_allPassComb.update(m_volume);
}

template<uint32_t BLOCK_SIZE>
void Reverb<BLOCK_SIZE>::update(const uint8_t* data)
{
    memcpy(&m_volume, data, sizeof(float));
    m_allPassComb.update(m_volume);
}

template<uint32_t BLOCK_SIZE>
float* Reverb<BLOCK_SIZE>::process(float* input)
{
    arm_scale_f32(input, SIGNAL_GAIN, m_output, BLOCK_SIZE);

    arm_add_f32(m_feedbackComb0.process(input), m_feedbackComb1.process(input), m_feedbackCombSum, BLOCK_SIZE);
    arm_add_f32(m_feedbackCombSum, m_feedbackComb2.process(input), m_feedbackCombSum, BLOCK_SIZE);
    arm_add_f32(m_feedbackCombSum, m_feedbackComb3.process(input), m_feedbackCombSum, BLOCK_SIZE);
    arm_add_f32(m_feedbackCombSum, m_feedbackComb4.process(input), m_feedbackCombSum, BLOCK_SIZE);
    arm_add_f32(m_feedbackCombSum, m_feedbackComb5.process(input), m_feedbackCombSum, BLOCK_SIZE);
    arm_scale_f32(m_feedbackCombSum, 1 / FEEDBACK_COMB_COUNT, m_feedbackCombSum, BLOCK_SIZE);
    
    arm_scale_f32(m_allPassComb.process(m_feedbackCombSum), m_volume, m_filterSum, BLOCK_SIZE);

    arm_add_f32(m_output, m_filterSum, m_output, BLOCK_SIZE);

    if (!Effect<BLOCK_SIZE>::isEnabled())
    {
        arm_scale_f32(input, SIGNAL_GAIN, m_output, BLOCK_SIZE);
    }
    return m_output;
}

#endif
