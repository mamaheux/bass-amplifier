#include "CompressorDesigner.h"
#include "Utils.h"

#include <Communication.h>

#include <string.h>

CompressorDesigner::CompressorDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, COMPRESSOR_CODE, DATA_SIZE, m_data),
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
    float attack = ATTACK;
    float release = RELEASE;

    memcpy(m_data, &threshold, sizeof(float));
    memcpy(m_data + sizeof(float), &ratio, sizeof(float));
    memcpy(m_data + 2 * sizeof(float), &attack, sizeof(float));
    memcpy(m_data + 3 * sizeof(float), &release, sizeof(float));
}
