#ifndef EFFECT_DESIGN_COMPRESSOR_DESIGNER_H
#define EFFECT_DESIGN_COMPRESSOR_DESIGNER_H

#include "EffectDesigner.h"
#include "Utils.h"

class CompressorDesigner : public EffectDesigner
{
    static constexpr float MIN_THRESHOLD = 0;
    static constexpr float MAX_THRESHOLD = 1;

    static constexpr float MIN_RATIO = 0;
    static constexpr float MAX_RATIO = 1;

    static constexpr float ATTACK = 0.995;
    static constexpr float RELEASE = 0.9997;

    static constexpr uint8_t DATA_SIZE = 4 * sizeof(float);

    uint8_t m_data[DATA_SIZE]; // Threshold, ratio, attack, release

    uint8_t m_currentThresholdLevel;
    uint8_t m_currentRatioLevel;

public:
    explicit CompressorDesigner(float samplingFrequency);
    ~CompressorDesigner() override;
    
    void update(uint8_t thresholdLevel, uint8_t ratioLevel);

    bool isActive() const override;
};

inline bool CompressorDesigner::isActive() const
{
    return EffectDesigner::isActive() && m_currentRatioLevel > 0;
}

#endif
