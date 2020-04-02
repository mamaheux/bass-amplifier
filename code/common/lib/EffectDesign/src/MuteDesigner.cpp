#include "MuteDesigner.h"

MuteDesigner::MuteDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, EFFECT_CODE, DATA_SIZE, nullptr)
{
}

MuteDesigner::~MuteDesigner()
{    
}
