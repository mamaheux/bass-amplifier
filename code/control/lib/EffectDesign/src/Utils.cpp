#include "Utils.h"

#include <math.h>

void designLowShelvingFilter(BiquadCoefficients& out, float gainDb, float Q, float centerFrequency, float samplingFrequency)
{
    float k = tan((M_PI * centerFrequency) / samplingFrequency);
    float v0 = pow(10.0, gainDb / 20.0);
    float root2 = 1.0 / Q;

    if (v0 < 1)
    {
        v0 = 1.0 / v0;
    }

    if (gainDb > 0)
    {
        out.b0 = (1 + sqrt(v0) * root2 * k + v0 * k * k) / (1 + root2 * k + k * k);
        out.b1 = (2 * (v0 * k * k - 1)) / (1 + root2 * k + k * k);
        out.b2 = (1 - sqrt(v0) * root2 * k + v0 * k * k) / (1 + root2 * k + k * k);
        out.a0 = 1;
        out.a1 = (2 * (k * k - 1)) / (1 + root2 * k + k * k);
        out.a2 = (1 - root2 * k + k * k) / (1 + root2 * k + k * k);
    }
    else if (gainDb < 0)
    {
        out.b0 = (1 + root2 * k + k * k) / (1 + root2 * sqrt(v0) * k + v0 * k * k);
        out.b1 = (2 * (k * k - 1)) / (1 + root2 * sqrt(v0) * k + v0 * k * k);
        out.b2 = (1 - root2 * k + k * k) / (1 + root2 * sqrt(v0) * k + v0 * k * k);
        out.a0 = 1;
        out.a1 = (2 * (v0 * k * k - 1)) / (1 + root2 * sqrt(v0) * k + v0 * k * k);
        out.a2 = (1 - root2 * sqrt(v0) * k + v0 * k * k) / (1 + root2 * sqrt(v0) * k + v0 * k * k);
    }
    else
    {
        out.b0 = v0;
        out.b1 = 0;
        out.b2 = 0;
        out.a0 = 1;
        out.a1 = 0;
        out.a2 = 0;
    }
}

void designHighShelvingFilter(BiquadCoefficients& out, float gainDb, float Q, float centerFrequency, float samplingFrequency)
{
    float k = tan((M_PI * centerFrequency) / samplingFrequency);
    float v0 = pow(10.0, gainDb / 20.0);
    float root2 = 1.0 / Q;

    if (v0 < 1)
    {
        v0 = 1.0 / v0;
    }

    if (gainDb > 0)
    {
        out.b0 = (v0 + root2 * sqrt(v0) * k + k * k) / (1 + root2 * k + k * k);
        out.b1 = (2 * (k * k - v0)) / (1 + root2 * k + k * k);
        out.b2 = (v0 - root2 * sqrt(v0) * k + k * k) / (1 + root2 * k + k * k);
        out.a0 = 1;
        out.a1 = (2 * (k * k - 1)) / (1 + root2 * k + k * k);
        out.a2 = (1 - root2 * k + k * k) / (1 + root2 * k + k * k);
    }
    else if (gainDb < 0)
    {
        out.b0 = (1 + root2 * k + k * k) / (v0 + root2 * sqrt(v0) * k + k * k);
        out.b1 = (2 * (k * k - 1)) / (v0 + root2 * sqrt(v0) * k + k * k);
        out.b2 = (1 - root2 * k + k * k) / (v0 + root2 * sqrt(v0) * k + k * k);
        out.a0 = 1;
        out.a1 = (2 * ((k * k) / v0 - 1)) / (1 + root2 / sqrt(v0) * k + (k * k) / v0);
        out.a2 = (1 - root2 / sqrt(v0) * k + (k * k) / v0) / (1 + root2 / sqrt(v0) * k + (k * k) / v0);
    }
    else
    {
        out.b0 = v0;
        out.b1 = 0;
        out.b2 = 0;
        out.a0 = 1;
        out.a1 = 0;
        out.a2 = 0;
    }
}

void designPeakFilter(BiquadCoefficients& out, float gainDb, float Q, float centerFrequency, float samplingFrequency)
{
    float w_c = (2 * M_PI * centerFrequency / samplingFrequency);
    float mu = pow(10.0, gainDb / 20.0);
    float k_q = 4 / (1 + mu) * tan(w_c / (2 * Q));
    float C_pk = (1 + k_q * mu) / (1 + k_q);

    out.b0 = C_pk;
    out.b1 = C_pk * (-2 * cos(w_c) / (1 + k_q * mu));
    out.b2 = C_pk * (1 - k_q * mu) / (1 + k_q * mu);
    out.a0 = 1;
    out.a1 = -2 * cos(w_c) / (1 + k_q);
    out.a2 = (1 - k_q) / (1 + k_q);
}

float sqrtGainDb(float gainDb)
{
    return gainDb / 2;
}

float map(uint8_t value, float min, float max)
{
    return (max - min) * value / 255 + min;
}
