#include "ContourDesigner.h"

#include "Utils.h"

#include <math.h>
#include <string.h>

ContourDesigner::ContourDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, EFFECT_CODE, DATA_SIZE, m_data), m_currentGainLevel(1)
{
    update(0);
}

ContourDesigner::~ContourDesigner()
{    
}
    
void ContourDesigner::update(uint8_t gainLevel)
{
    if (m_currentGainLevel == gainLevel)
    {
        return;
    }

    m_currentGainLevel = gainLevel;
    setIsDirty(true);

    float gainDb = map(gainLevel, MIN_GAIN_DB, MAX_GAIN_DB);
    gainDb = sqrtGainDb(gainDb);
    BiquadCoefficients filterCoefficients;

    designLowShelvingFilter(filterCoefficients, gainDb, LOW_Q, LOW_CENTER_FREQUENCY, samplingFrequency());
    memcpy(m_data, &filterCoefficients, sizeof(BiquadCoefficients));

    designHighShelvingFilter(filterCoefficients, gainDb, HIGH_Q, HIGH_CENTER_FREQUENCY, samplingFrequency());
    memcpy(m_data + sizeof(BiquadCoefficients), &filterCoefficients, sizeof(BiquadCoefficients));

    reinterpret_cast<float*>(m_data + 2 * sizeof(BiquadCoefficients))[0] = 1 / pow(10, gainDb / 20);
}
