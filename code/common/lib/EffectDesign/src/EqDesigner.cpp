#include "EqDesigner.h"

#include "Utils.h"

#include <math.h>
#include <string.h>

constexpr float EqDesigner::CENTER_FREQUENCIES[];
constexpr float EqDesigner::INV_B[];

EqDesigner::EqDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, EFFECT_CODE, DATA_SIZE, m_data),
     m_currentLowGainLevel(1), m_currentLowMidGainLevel(1),
     m_currentHighMidGainLevel(1), m_currentHighGainLevel(1)
{
    update(128, 128, 128, 128);
}

EqDesigner::~EqDesigner()
{    
}
    
void EqDesigner::update(uint8_t lowGainLevel, uint8_t lowMidGainLevel, uint8_t highMidGainLevel, uint8_t highGainLevel)
{
    if (m_currentLowGainLevel == lowGainLevel && m_currentLowMidGainLevel == lowMidGainLevel && 
        m_currentHighMidGainLevel == highMidGainLevel && m_currentHighGainLevel == highGainLevel)
    {
        return;
    }

    m_currentLowGainLevel = lowGainLevel;
    m_currentLowMidGainLevel = lowMidGainLevel;
    m_currentHighMidGainLevel = highMidGainLevel;
    m_currentHighGainLevel = highGainLevel;
    setIsDirty(true);

    float lowGainDb = map(lowGainLevel, MIN_GAIN_DB, MAX_GAIN_DB);
    float lowMidGainDb = map(lowMidGainLevel, MIN_GAIN_DB, MAX_GAIN_DB);
    float highMidGainDb = map(highMidGainLevel, MIN_GAIN_DB, MAX_GAIN_DB);
    float highGainDb = map(highGainLevel, MIN_GAIN_DB, MAX_GAIN_DB);

    float gainDb[] = {lowGainDb, lowGainDb, lowMidGainDb, lowMidGainDb, highMidGainDb, highMidGainDb, highGainDb, highGainDb};
    float Q = sqrt(R) / (R - 1);

    for (int i = 0; i < FILTER_COUNT; i++)
    {
        BiquadCoefficients filterCoefficients;
        designPeakFilter(filterCoefficients, calculateAjustedGainDb(gainDb, i), Q, CENTER_FREQUENCIES[i], samplingFrequency());
        memcpy(m_data + i * sizeof(BiquadCoefficients), &filterCoefficients, sizeof(BiquadCoefficients));
    }
}

float EqDesigner::calculateAjustedGainDb(float* gainDb, int filterIndex)
{
    float ajustedGainDb = 0;
    for (int i = 0; i < FILTER_COUNT; i++)
    {
        ajustedGainDb += INV_B[filterIndex * FILTER_COUNT + i] * gainDb[i];
    }

    return ajustedGainDb;
}
