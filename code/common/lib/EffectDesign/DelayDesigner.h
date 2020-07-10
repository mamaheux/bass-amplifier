#ifndef EFFECT_DESIGN_DELAY_DESIGNER_H
#define EFFECT_DESIGN_DELAY_DESIGNER_H

#include "EffectDesigner.h"
#include "Utils.h"

class DelayDesigner : public EffectDesigner
{
    static constexpr float MIN_VOLUME = 0;
    static constexpr float MAX_VOLUME = 0.5;

    static constexpr uint8_t DATA_SIZE = sizeof(float) + sizeof(uint32_t);

    uint32_t m_maxDelay;

    uint8_t m_data[DATA_SIZE]; // Volume, delay

    uint8_t m_currentVolumeLevel;
    uint32_t m_currentDelay;

public:
    DelayDesigner(float samplingFrequency, uint32_t maxDelay);
    ~DelayDesigner() override;
    
    void update(uint8_t volumeLevel, uint32_t delay);

    bool isActive() const override;
};

inline bool DelayDesigner::isActive() const
{
    return EffectDesigner::isActive() && m_currentVolumeLevel > 0 && m_currentDelay > 0;
}

#endif
