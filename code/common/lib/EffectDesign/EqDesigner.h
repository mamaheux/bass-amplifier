#ifndef EFFECT_DESIGN_EQ_DESIGNER_H
#define EFFECT_DESIGN_EQ_DESIGNER_H

#include "EffectDesigner.h"
#include "Utils.h"

#include <math.h>

class EqDesigner : public EffectDesigner
{
    static constexpr int FILTER_COUNT = 8;

    static constexpr float MIN_GAIN_DB = -12;
    static constexpr float MAX_GAIN_DB = 12;

    static constexpr float CENTER_FREQUENCIES[FILTER_COUNT] = {40, 80, 160, 315, 630, 1250, 2500, 5000};
    static constexpr float R = 2;
    static constexpr float INV_B[] = {1.19954606e+00, -5.15750480e-01, 8.13940894e-02, -1.08627792e-02, 1.46682918e-03, -2.03327220e-04, 2.76524616e-05, -3.65017717e-06, -5.15757611e-01, 1.42160258e+00, -5.52906762e-01, 8.86838596e-02, -1.13948754e-02, 1.58313105e-03, -2.16026720e-04, 2.84871225e-05, 8.13898164e-02, -5.52932309e-01, 1.44272377e+00, -5.73621942e-01, 8.89979509e-02, -1.17751455e-02, 1.61022202e-03, -2.13007426e-04, -1.08586606e-02, 8.86640408e-02, -5.73721833e-01, 1.44310713e+00, -5.54847463e-01, 8.78519899e-02, -1.14756157e-02, 1.51859773e-03, 1.46494711e-03, -1.13783184e-02, 8.89224618e-02, -5.55245379e-01, 1.43574772e+00, -5.62682942e-01, 8.83359463e-02, -1.12398497e-02, -2.02259893e-04, 1.57500584e-03, -1.17070368e-02, 8.75509507e-02, -5.64259104e-01, 1.43719885e+00, -5.52374943e-01, 8.38240933e-02, 2.70750025e-05, -2.11559585e-04, 1.57773153e-03, -1.12156291e-02, 8.71546179e-02, -5.58703036e-01, 1.43050159e+00, -5.05429905e-01, -3.44767742e-06, 2.68986706e-05, -2.01307595e-04, 1.43807342e-03, -1.05255604e-02, 8.16740747e-02, -5.46715207e-01, 1.20605063e+00};

    static constexpr uint8_t DATA_SIZE = FILTER_COUNT * sizeof(BiquadCoefficients);

    uint8_t m_data[DATA_SIZE]; // BiquadCoefficients, BiquadCoefficients, ...

    uint8_t m_currentLowGainLevel;
    uint8_t m_currentLowMidGainLevel;
    uint8_t m_currentHighMidGainLevel;
    uint8_t m_currentHighGainLevel;

public:
    explicit EqDesigner(float samplingFrequency);
    ~EqDesigner() override;

    void update(uint8_t lowGainLevel, uint8_t lowMidGainLevel, uint8_t highMidGainLevel, uint8_t highGainLevel);

private:
    float calculateAjustedGainDb(float* gainDb, int filterIndex);
};

#endif
