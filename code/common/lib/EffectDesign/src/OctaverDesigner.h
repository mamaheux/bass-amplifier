#ifndef EFFECT_DESIGN_OCTAVER_DESIGNER_H
#define EFFECT_DESIGN_OCTAVER_DESIGNER_H

#include "EffectDesigner.h"
#include "Utils.h"

class OctaverDesigner : public EffectDesigner
{
    static constexpr float MIN_VOLUME = 0;
    static constexpr float MAX_VOLUME = 1;

    static constexpr float OCTAVE_UP_BAND_PASS_FC_1 = 100;
    static constexpr float OCTAVE_UP_BAND_PASS_FC_2 = 1000;

    static constexpr uint8_t DATA_SIZE = 2 *sizeof(BiquadCoefficients) + 2 * sizeof(float);

    uint8_t m_data[DATA_SIZE]; // 2 x BiquadCoefficients, octaver down volume, octaver up volume

    uint8_t m_currentOctaveDownVolumeLevel;
    uint8_t m_currentOctaveUpVolumeLevel;

public:
    explicit OctaverDesigner(float samplingFrequency);
    ~OctaverDesigner() override;
    
    void update(uint8_t octaveDownVolumeLevel, uint8_t octaveUpVolumeLevel);

    bool isActive() const override;
};

inline bool OctaverDesigner::isActive() const
{
    return EffectDesigner::isActive() &&
        (m_currentOctaveDownVolumeLevel > 0 || m_currentOctaveUpVolumeLevel > 0);
}

#endif
