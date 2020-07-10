#ifndef EFFECT_DESIGN_REVERB_DESIGNER_H
#define EFFECT_DESIGN_REVERB_DESIGNER_H

#include "EffectDesigner.h"
#include "Utils.h"

class ReverbDesigner : public EffectDesigner
{
    static constexpr float MIN_VOLUME = 0;
    static constexpr float MAX_VOLUME = 0.9;

    static constexpr uint8_t DATA_SIZE = sizeof(float);

    uint8_t m_data[DATA_SIZE]; // Volume

    uint8_t m_currentVolumeLevel;

public:
    explicit ReverbDesigner(float samplingFrequency);
    ~ReverbDesigner() override;
    
    void update(uint8_t volumeLevel);

    bool isActive() const override;
};

inline bool ReverbDesigner::isActive() const
{
    return EffectDesigner::isActive() && m_currentVolumeLevel;
}

#endif
