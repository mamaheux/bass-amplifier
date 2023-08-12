#ifndef EFFECT_DESIGN_PITCH_SHIFTER_DESIGNER_H
#define EFFECT_DESIGN_PITCH_SHIFTER_DESIGNER_H

#include "EffectDesigner.h"
#include "Utils.h"

class PitchShifterDesigner : public EffectDesigner
{
    static constexpr int8_t MIN_PITCH_STEP = -6;
    static constexpr int8_t MAX_PITCH_STEP = 6;

    static constexpr float GAINS[] =
    {
        1.2415331892552723f, // -6
        1.241652712452141f, // -5
        1.244615780432574f, // -4
        1.2585542092522932f, // -3
        1.2734288784043912f, // -2
        1.3001193733644227f, // -1
        1.3333333333332817f, // 0
        1.3758581127821765f, // 1
        1.4344999204123041f, // 2
        1.5157718389755686f, // 3
        1.6224343855655563f, // 4
        1.7459885206225656f, // 5
        1.9106411955407752f // 6
    };

    static constexpr uint8_t DATA_SIZE = sizeof(int8_t) + sizeof(float);

    uint8_t m_data[DATA_SIZE]; // Pitch Step, Gain

    int8_t m_currentPitchStep;

public:
    explicit PitchShifterDesigner(float samplingFrequency);
    ~PitchShifterDesigner() override;

    void reset();
    void increasePitch();
    void decreasePitch();

    bool isActive() const override;

private:
    void updateData();
};

inline bool PitchShifterDesigner::isActive() const
{
    return true;
}

#endif
