#include "CompressorDesigner.h"

#include "Utils.h"

#include <math.h>
#include <string.h>

CompressorDesigner::CompressorDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, EFFECT_CODE, DATA_SIZE, m_data),
    m_currentThresholdLevel(1), m_currentRatioLevel(1)
{
    update(0, 0);
}

CompressorDesigner::~CompressorDesigner()
{    
}
    
void CompressorDesigner::update(uint8_t thresholdLevel, uint8_t ratioLevel)
{
    if (m_currentThresholdLevel == thresholdLevel && m_currentRatioLevel == ratioLevel)
    {
        return;
    }

    m_currentThresholdLevel = thresholdLevel;
    m_currentRatioLevel = ratioLevel;
    setIsDirty(true);

    float threshold = map(thresholdLevel, MIN_THRESHOLD, MAX_THRESHOLD);
    float ratio = map(ratioLevel, MIN_RATIO, MAX_RATIO);

    float* data = reinterpret_cast<float*>(m_data);
    data[0] = threshold;
    data[1] = ratio;
    data[2] = ATTACK;
    data[3] = RELEASE;
}
