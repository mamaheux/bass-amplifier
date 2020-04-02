#include "OverdriveDesigner.h"
#include "Utils.h"

#include <Communication.h>

#include <math.h>
#include <string.h>

OverdriveDesigner::OverdriveDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, OVERDRIVE_CODE, DATA_SIZE, m_data), m_currentGainLevel(1), m_currentToneLevel(1)
{
    update(0, 0);
}

OverdriveDesigner::~OverdriveDesigner()
{    
}
    
void OverdriveDesigner::update(uint8_t gainLevel, uint8_t toneLevel)
{
    if (m_currentGainLevel == gainLevel && m_currentToneLevel == toneLevel)
    {
        return;
    }

    m_currentGainLevel = gainLevel;
    m_currentToneLevel = toneLevel;
    setIsDirty(true);

    float gainDb = map(gainLevel, MIN_GAIN_DB, MAX_GAIN_DB);
    reinterpret_cast<float*>(m_data)[0] = pow(10, gainDb / 20);

    float toneFc = map(toneLevel, MIN_TONE_FC, MAX_TONE_FC);
    BiquadCoefficients filterCoefficients;
    designSecondOrderButterworthLowPassFilter(filterCoefficients, toneFc, samplingFrequency());
    memcpy(m_data + sizeof(float), &filterCoefficients, sizeof(BiquadCoefficients));
}
