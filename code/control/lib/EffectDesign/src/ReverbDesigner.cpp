#include "ReverbDesigner.h"

#include "Utils.h"

ReverbDesigner::ReverbDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, EFFECT_CODE, DATA_SIZE, m_data),
    m_currentVolumeLevel(1)
{
    update(0);
}

ReverbDesigner::~ReverbDesigner()
{
}

void ReverbDesigner::update(uint8_t volumeLevel)
{
    if (m_currentVolumeLevel == volumeLevel)
    {
        return;
    }

    m_currentVolumeLevel = volumeLevel;
    setIsDirty(true);

    float volume = map(volumeLevel, MIN_VOLUME, MAX_VOLUME);

    reinterpret_cast<float*>(m_data)[0] = volume;
}
