#include "OctaverDesigner.h"

#include "Utils.h"

#include <string.h>

OctaverDesigner::OctaverDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, EFFECT_CODE, DATA_SIZE, m_data), 
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
   
    float* data = reinterpret_cast<float*>(m_data + 2 * sizeof(BiquadCoefficients));
    data[0] = octaveDownVolume;
    data[1] = octaveUpVolume;
}
