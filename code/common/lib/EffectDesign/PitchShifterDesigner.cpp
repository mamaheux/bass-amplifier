#include "PitchShifterDesigner.h"
#include "Utils.h"

#include <Communication.h>

#include <string.h>

constexpr float PitchShifterDesigner::GAINS[];

PitchShifterDesigner::PitchShifterDesigner(float samplingFrequency) :
    EffectDesigner(samplingFrequency, PITCH_SHIFTER_CODE, DATA_SIZE, m_data),
    m_currentPitchStep(0)
{
    reset();
}

PitchShifterDesigner::~PitchShifterDesigner()
{
}

void PitchShifterDesigner::reset()
{
    if (m_currentPitchStep == 0)
    {
        return;
    }

    m_currentPitchStep = 0;
    setIsDirty(true);
    updateData();
}

void PitchShifterDesigner::increasePitch()
{
    if (m_currentPitchStep >= MAX_PITCH_STEP)
    {
        return;
    }

    m_currentPitchStep++;
    setIsDirty(true);
    updateData();
}

void PitchShifterDesigner::decreasePitch()
{
    if (m_currentPitchStep <= MIN_PITCH_STEP)
    {
        return;
    }

    m_currentPitchStep--;
    setIsDirty(true);
    updateData();
}

void PitchShifterDesigner::updateData()
{
    float gain = GAINS[m_currentPitchStep - MIN_PITCH_STEP];

    m_data[0] = static_cast<uint8_t>(m_currentPitchStep);
    memcpy(m_data + 1, &gain, sizeof(float));
}
