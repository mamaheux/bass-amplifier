#ifndef EFFECT_DESIGN_UTILS_H
#define EFFECT_DESIGN_UTILS_H

#include <stdint.h>

struct BiquadCoefficients
{
    float b0;
    float b1;
    float b2;
    float a0;
    float a1;
    float a2;
};

void designLowShelvingFilter(BiquadCoefficients& out, float gainDb, float Q, float centerFrequency, float samplingFrequency);
void designHighShelvingFilter(BiquadCoefficients& out, float gainDb, float Q, float centerFrequency, float samplingFrequency);
void designPeakFilter(BiquadCoefficients& out, float gainDb, float Q, float centerFrequency, float samplingFrequency);

float sqrtGainDb(float gainDb);
float map(uint8_t value, float min, float max);

#endif
