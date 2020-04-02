#include "EffectDesigner.h"

EffectDesigner::EffectDesigner(float samplingFrequency, uint8_t effectCode, uint8_t dataSize, const uint8_t* data) :
    m_samplingFrequency(samplingFrequency), m_effectCode(effectCode), m_dataSize(dataSize), m_data(data), m_isDirty(true),
    m_isEnabled(true)
{
}

EffectDesigner::~EffectDesigner()
{    
}
