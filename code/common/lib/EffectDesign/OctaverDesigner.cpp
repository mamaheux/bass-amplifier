#include "OctaverDesigner.h"
#include "Utils.h"

#include <Communication.h>

#include <string.h>

OctaverDesigner::OctaverDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, OCTAVER_CODE, DATA_SIZE, m_data), 
    m_currentDownOctaveVolumeLevel(1), m_currentUpOctaveVolumeLevel(1)
{
    BiquadCoefficients filterCoefficients;
    designSecondOrderButterworthHighPassFilter(filterCoefficients, OCTAVE_UP_BAND_PASS_FC_1, samplingFrequency);
    memcpy(m_data, &filterCoefficients, sizeof(BiquadCoefficients));

    designSecondOrderButterworthLowPassFilter(filterCoefficients, OCTAVE_UP_BAND_PASS_FC_2, samplingFrequency);
    memcpy(m_data + sizeof(BiquadCoefficients), &filterCoefficients, sizeof(BiquadCoefficients));

    update(0, 0);    
}

OctaverDesigner::~OctaverDesigner()
{    
}
    
void OctaverDesigner::update(uint8_t downOctaveVolumeLevel, uint8_t upOctaveVolumeLevel)
{
    if (m_currentDownOctaveVolumeLevel == downOctaveVolumeLevel && m_currentUpOctaveVolumeLevel == upOctaveVolumeLevel)
    {
        return;
    }

    m_currentDownOctaveVolumeLevel = downOctaveVolumeLevel;
    m_currentUpOctaveVolumeLevel = upOctaveVolumeLevel;
    setIsDirty(true);

    float downOctaveVolume = map(downOctaveVolumeLevel, MIN_VOLUME, MAX_VOLUME);
    float upOctaveVolume = map(upOctaveVolumeLevel, MIN_VOLUME, MAX_VOLUME);

    memcpy(m_data + 2 * sizeof(BiquadCoefficients), &downOctaveVolume, sizeof(float));
    memcpy(m_data + 2 * sizeof(BiquadCoefficients) + sizeof(float), &upOctaveVolume, sizeof(float));
}
