#include "OctaverDesigner.h"
#include "Utils.h"

#include <Communication.h>

#include <string.h>

OctaverDesigner::OctaverDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, OCTAVER_CODE, DATA_SIZE, m_data), 
    m_currentOctaveDownVolumeLevel(1), m_currentOctaveUpVolumeLevel(1)
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
    
void OctaverDesigner::update(uint8_t octaveDownVolumeLevel, uint8_t octaveUpVolumeLevel)
{
    if (m_currentOctaveDownVolumeLevel == octaveDownVolumeLevel && m_currentOctaveUpVolumeLevel == octaveUpVolumeLevel)
    {
        return;
    }

    m_currentOctaveDownVolumeLevel = octaveDownVolumeLevel;
    m_currentOctaveUpVolumeLevel = octaveUpVolumeLevel;
    setIsDirty(true);

    float octaveDownVolume = map(octaveDownVolumeLevel, MIN_VOLUME, MAX_VOLUME);
    float octaveUpVolume = map(octaveUpVolumeLevel, MIN_VOLUME, MAX_VOLUME);

    memcpy(m_data + 2 * sizeof(BiquadCoefficients), &octaveDownVolume, sizeof(float));
    memcpy(m_data + 2 * sizeof(BiquadCoefficients) + sizeof(float), &octaveUpVolume, sizeof(float));
}
