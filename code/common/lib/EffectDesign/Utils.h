#ifndef EFFECT_DESIGN_UTILS_H
#define EFFECT_DESIGN_UTILS_H

#include <stdint.h>

struct BiquadCoefficients
{
    static constexpr uint32_t COUNT = 5;

    float b0;
    float b1;
    float b2;
    float a1;
    float a2;
};

void designLowShelvingFilter(BiquadCoefficients& out, float gainDb, float Q, float centerFrequency, float samplingFrequency);
void designHighShelvingFilter(BiquadCoefficients& out, float gainDb, float Q, float centerFrequency, float samplingFrequency);
void designPeakFilter(BiquadCoefficients& out, float gainDb, float Q, float centerFrequency, float samplingFrequency);

void designSecondOrderButterworthLowPassFilter(BiquadCoefficients& out, float cutoffFrequency, float samplingFrequency);
void designSecondOrderButterworthHighPassFilter(BiquadCoefficients& out, float cutoffFrequency, float samplingFrequency);

float sqrtGainDb(float gainDb);
float map(uint8_t value, float min, float max);

#endif
