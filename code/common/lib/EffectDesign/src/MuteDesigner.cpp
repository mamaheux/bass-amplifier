#include "MuteDesigner.h"

#include <Communication.h>

MuteDesigner::MuteDesigner(float samplingFrequency) : 
    EffectDesigner(samplingFrequency, MUTE_CODE, DATA_SIZE, nullptr)
{
}

MuteDesigner::~MuteDesigner()
{    
}
