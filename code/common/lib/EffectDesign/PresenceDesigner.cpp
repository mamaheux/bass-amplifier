#include "PresenceDesigner.h"
#include "Utils.h"

#include <Communication.h>

#include <math.h>
#include <string.h>

PresenceDesigner::PresenceDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, PRESENCE_CODE, DATA_SIZE, m_data), m_currentGainLevel(1)
{
    update(0);
}

PresenceDesigner::~PresenceDesigner()
{    
}
    
void PresenceDesigner::update(uint8_t gainLevel)
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

    designHighShelvingFilter(filterCoefficients, gainDb, Q, CENTER_FREQUENCY, samplingFrequency());
    memcpy(m_data, &filterCoefficients, sizeof(BiquadCoefficients));

    float globalGain = 1 / pow(10, gainDb / 20);
    memcpy(m_data + sizeof(BiquadCoefficients), &globalGain, sizeof(float));
}
