#ifndef EFFECT_DESIGN_MUTE_DESIGNER_H
#define EFFECT_DESIGN_MUTE_DESIGNER_H

#include "EffectDesigner.h"
#include "Utils.h"

class MuteDesigner : public EffectDesigner
{
    static constexpr uint8_t EFFECT_CODE = 8;
    static constexpr uint8_t DATA_SIZE = 0;

public:
    explicit MuteDesigner(float samplingFrequency);
    ~MuteDesigner() override;
};

#endif
