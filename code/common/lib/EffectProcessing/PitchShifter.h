#ifndef EFFECT_PROCESSING_PITCH_SHIFTER_H
#define EFFECT_PROCESSING_PITCH_SHIFTER_H

#include "Effect.h"

#include <arm_math.h>
#include <cmath>
#include <cstring>

constexpr float PI_F = M_PI;

inline void hann(float* dst, uint32_t size)
{
    size--;
    for (uint32_t i = 0; i <= size; i++)
    {
        dst[i] = 0.5f * (1.f - arm_cos_f32(2.f * PI_F * i / size));
    }
}

inline void freqRamp(float* dst, uint32_t size)
{
    float step = PI_F / size;
    for (uint32_t i = 0; i <= size; i++)
    {
        dst[i] = i * step;
    }
}

inline void complexPhase(const float* pSrc, float* pDst, uint32_t numSamples)
{
    for (uint32_t i = 0; i < numSamples; i++)
    {
        pDst[i] = atan2f(pSrc[2 * i + 1], pSrc[2 * i]);
    }
}

inline void constraintAngle(const float* pSrc, float* pDst, uint32_t numSamples)
{
    for (uint32_t i = 0; i < numSamples; i++)
    {
        float a = fmodf(pSrc[i] + PI_F, 2 * PI_F);
        if (a < 0)
        {
            a += 2 * PI_F;
        }
        pDst[i] = a - PI_F;
    }
}

inline void complexPolar(const float* pMag, const float* pPhase, float* pDst, uint32_t numSamples)
{
    for (uint32_t i = 0; i < numSamples; i++)
    {
        pDst[2 * i] = pMag[i] * arm_cos_f32(pPhase[i]);
        pDst[2 * i + 1] = pMag[i] * arm_sin_f32(pPhase[i]);
    }
}


template<uint32_t BLOCK_SIZE>
class PitchShifter : public Effect<BLOCK_SIZE>
{
    static constexpr uint32_t INPUT_HOP_SIZE = BLOCK_SIZE / 4;
    static constexpr uint32_t FFT_SIZE = BLOCK_SIZE / 2;

    static constexpr int8_t MAX_PITCH_STEP = 6;

    arm_rfft_fast_instance_f32 m_fftInstance;

    float m_alpha;
    uint32_t m_outputHopSize;
    float m_gain;

    float m_window[BLOCK_SIZE];
    float m_inputWindow[BLOCK_SIZE];
    float m_outputWindow[BLOCK_SIZE];

    float m_previousPhase[FFT_SIZE];
    float m_cumulativePhase[FFT_SIZE];

    float m_inputProcessingBuffer[BLOCK_SIZE * 7 / 4];
    float m_outputProcessingBuffer[BLOCK_SIZE * 4]; // Up to 6 semi steps

    float m_freqRamp[FFT_SIZE];

    float m_windowedInput[BLOCK_SIZE];
    float m_fft[BLOCK_SIZE];
    float m_magnitude[FFT_SIZE];
    float m_phase[FFT_SIZE];
    float m_deltaPhi[FFT_SIZE];
    float m_deltaPhiPrime[FFT_SIZE];

    float m_output[BLOCK_SIZE];

public:
    PitchShifter();

    float alpha() const;
    uint32_t outputHopSize() const;
    float gain() const;

    void update(const uint8_t* data) override;
    float* process(float* input);

private:
    void processBlock(float* input, float* output);
    void resampleOutput(const float* input, float* output);
};

template<uint32_t BLOCK_SIZE>
PitchShifter<BLOCK_SIZE>::PitchShifter() : m_alpha(1.f), m_outputHopSize(INPUT_HOP_SIZE), m_gain(1.f)
{
    static_assert(BLOCK_SIZE == 32 ||
        BLOCK_SIZE == 64 ||
        BLOCK_SIZE == 128 ||
        BLOCK_SIZE == 256 ||
        BLOCK_SIZE == 512 ||
        BLOCK_SIZE == 1024 ||
        BLOCK_SIZE == 2048 ||
        BLOCK_SIZE == 4096, "Incompatible block size");

    arm_rfft_fast_init_f32(&m_fftInstance, BLOCK_SIZE);

    hann(m_window, BLOCK_SIZE);
    arm_scale_f32(m_window, 1.f / sqrtf(float(BLOCK_SIZE) / float(INPUT_HOP_SIZE) / 2.f), m_inputWindow, BLOCK_SIZE);
    memcpy(m_outputWindow, m_inputWindow, sizeof(m_outputWindow));

    memset(m_previousPhase, 0, sizeof(m_previousPhase));
    memset(m_cumulativePhase, 0, sizeof(m_cumulativePhase));
    memset(m_inputProcessingBuffer, 0, sizeof(m_inputProcessingBuffer));
    memset(m_outputProcessingBuffer, 0, sizeof(m_outputProcessingBuffer));

    freqRamp(m_freqRamp, FFT_SIZE);
}

template<uint32_t BLOCK_SIZE>
float PitchShifter<BLOCK_SIZE>::alpha() const
{
    return m_alpha;
}

template<uint32_t BLOCK_SIZE>
uint32_t PitchShifter<BLOCK_SIZE>::outputHopSize() const
{
    return m_outputHopSize;
}

template<uint32_t BLOCK_SIZE>
float PitchShifter<BLOCK_SIZE>::gain() const
{
    return m_gain;
}

template<uint32_t BLOCK_SIZE>
void PitchShifter<BLOCK_SIZE>::update(const uint8_t* data)
{
    int8_t pitchStep = static_cast<int8_t>(data[0]);
    if (pitchStep > MAX_PITCH_STEP)
    {
        pitchStep = MAX_PITCH_STEP;
    }

    m_alpha = powf(2, float(pitchStep) / 12.f);
    m_outputHopSize = static_cast<uint32_t>(roundf(m_alpha * INPUT_HOP_SIZE));
    arm_scale_f32(m_window, 1.f / sqrtf(float(BLOCK_SIZE) / float(m_outputHopSize) / 2.f), m_outputWindow, BLOCK_SIZE);

    memcpy(&m_gain, data + 1, sizeof(float));
}

template<uint32_t BLOCK_SIZE>
float* PitchShifter<BLOCK_SIZE>::process(float* input)
{
    memcpy(m_inputProcessingBuffer + 3 * INPUT_HOP_SIZE, input, BLOCK_SIZE * sizeof(float));

    processBlock(m_inputProcessingBuffer, m_outputProcessingBuffer);
    processBlock(m_inputProcessingBuffer + INPUT_HOP_SIZE, m_outputProcessingBuffer + m_outputHopSize);
    processBlock(m_inputProcessingBuffer + 2 * INPUT_HOP_SIZE, m_outputProcessingBuffer + 2 * m_outputHopSize);
    processBlock(m_inputProcessingBuffer + 3 * INPUT_HOP_SIZE, m_outputProcessingBuffer + 3 * m_outputHopSize);

    resampleOutput(m_outputProcessingBuffer, m_output);
    arm_scale_f32(m_output, m_gain, m_output, BLOCK_SIZE);

     // Rotate the input buffer
    memmove(m_inputProcessingBuffer, m_inputProcessingBuffer + BLOCK_SIZE, 3 * INPUT_HOP_SIZE * sizeof(float));
    memset(m_inputProcessingBuffer + BLOCK_SIZE, 0, BLOCK_SIZE * sizeof(float));

    // Rotate the output buffer
    uint32_t offset = 4 * m_outputHopSize;
    memmove(m_outputProcessingBuffer, m_outputProcessingBuffer + offset, (3 * m_outputHopSize + BLOCK_SIZE) * sizeof(float) - offset);
    memset(m_outputProcessingBuffer + offset, 0, (BLOCK_SIZE * 4 - offset) * sizeof(float));

    return m_output;
}

template<uint32_t BLOCK_SIZE>
void PitchShifter<BLOCK_SIZE>::processBlock(float* input, float* output)
{
    arm_mult_f32(input, m_inputWindow, m_windowedInput, BLOCK_SIZE);
    arm_rfft_fast_f32(&m_fftInstance, m_windowedInput, m_fft, 0); // rfft(input_window * input_frame)
    arm_cmplx_mag_f32(m_fft, m_magnitude, FFT_SIZE); // abs
    complexPhase(m_fft, m_phase, FFT_SIZE); // angle

    arm_sub_f32(m_phase, m_previousPhase, m_deltaPhi, FFT_SIZE); // m_deltaPhi = phase - previous_phase
    memcpy(m_previousPhase, m_phase, sizeof(m_previousPhase)); // previous_phase = phase

    arm_scale_f32(m_freqRamp, float(INPUT_HOP_SIZE), m_deltaPhiPrime, FFT_SIZE); // delta_phi_prime = HOP_SIZE_IN * freq_ramp
    arm_sub_f32(m_deltaPhi, m_deltaPhiPrime, m_deltaPhiPrime, FFT_SIZE); // delta_phi_prime = delta_phi - HOP_SIZE_IN * freq_ramp
    constraintAngle(m_deltaPhiPrime, m_deltaPhiPrime, FFT_SIZE); // delta_phi_prime = np.remainder(delta_phi_prime + np.pi, 2 * np.pi) - np.pi

    arm_scale_f32(m_deltaPhiPrime, 1.f / float(INPUT_HOP_SIZE), m_deltaPhiPrime, FFT_SIZE); // delta_phi_prime = delta_phi_prime / HOP_SIZE_IN
    arm_add_f32(m_freqRamp, m_deltaPhiPrime, m_deltaPhiPrime, FFT_SIZE); // delta_phi_prime (true_freq) = freq_ramp + delta_phi_prime / HOP_SIZE_IN
    arm_scale_f32(m_deltaPhiPrime, float(m_outputHopSize), m_deltaPhiPrime, FFT_SIZE); // delta_phi_prime = output_hop_size * true_freq

    arm_add_f32(m_cumulativePhase, m_deltaPhiPrime, m_cumulativePhase, FFT_SIZE); // cumulative_phase += output_hop_size * true_freq
    constraintAngle(m_cumulativePhase, m_cumulativePhase, FFT_SIZE); // cumulative_phase = np.remainder(cumulative_phase + np.pi, 2 * np.pi) - np.pi

    complexPolar(m_magnitude, m_cumulativePhase, m_fft, FFT_SIZE); // fft = magnitude * np.exp(1j * phase_cumulative)
    arm_rfft_fast_f32(&m_fftInstance, m_fft, m_output, 1); // irfft(magnitude * np.exp(1j * phase_cumulative))
    arm_mult_f32(m_output, m_outputWindow, m_output, BLOCK_SIZE); // m_output = irfft(magnitude * np.exp(1j * phase_cumulative)) * output_window

    arm_add_f32(output, m_output, output, BLOCK_SIZE);
}

template<uint32_t BLOCK_SIZE>
void PitchShifter<BLOCK_SIZE>::resampleOutput(const float* input, float* output)
{
    float v = 0.f;
    for (uint32_t i = 0; i < BLOCK_SIZE; i++)
    {
        uint32_t j0 = static_cast<uint32_t>(floorf(v));
        uint32_t j1 = static_cast<uint32_t>(ceilf(v));
        if (j0 == j1)
        {
            j1++;
        }

        float frac = v - float(j0);
        output[i] = (1.f - frac) * input[j0] + frac * input[j1];

        v += m_alpha;
    }
}

#endif
