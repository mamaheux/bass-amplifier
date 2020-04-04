#include "ReverbDesigner.h"
#include "Utils.h"

#include <Communication.h>

#include <string.h>

ReverbDesigner::ReverbDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, REVERB_CODE, DATA_SIZE, m_data),
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

    memcpy(m_data, &volume, sizeof(float));
}
