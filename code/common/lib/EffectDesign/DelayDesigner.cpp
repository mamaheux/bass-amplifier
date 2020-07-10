#include "DelayDesigner.h"
#include "Utils.h"

#include <Communication.h>

#include <string.h>

DelayDesigner::DelayDesigner(float samplingFrequency, uint32_t maxDelay) : 
    EffectDesigner(samplingFrequency, DELAY_CODE, DATA_SIZE, m_data),
    m_maxDelay(maxDelay), m_currentVolumeLevel(1), m_currentDelay(1)
{
    update(0, 0);
}

DelayDesigner::~DelayDesigner()
{
}

void DelayDesigner::update(uint8_t volumeLevel, uint32_t delay)
{
    if (delay > m_maxDelay)
    {
        delay = m_maxDelay;
    }

    if (m_currentVolumeLevel == volumeLevel && m_currentDelay == delay)
    {
        return;
    }

    m_currentVolumeLevel = volumeLevel;
    m_currentDelay = delay;
    setIsDirty(true);

    float volume = map(volumeLevel, MIN_VOLUME, MAX_VOLUME);

    memcpy(m_data, &volume, sizeof(float));
    memcpy(m_data + sizeof(float), &delay, sizeof(uint32_t));
}
