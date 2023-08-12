#ifndef EFFECT_CONTROLS_H
#define EFFECT_CONTROLS_H

#include "config.h"

#include <Communication.h>


class EffectControls
{
    ControllerFootswitchCommunication<decltype(CONTROLLER_SERIAL)>& m_controllerCommunication;

    volatile bool m_isCompressorDirty;
    volatile bool m_isOctaverDirty;
    volatile bool m_isDelayDirty;
    volatile bool m_isReverbDirty;
    volatile bool m_isOverdriveDirty;
    volatile bool m_isMuteDirty;

    volatile uint32_t m_delayUs;
    volatile bool m_isDelayUsDirty;

    volatile bool m_isOpt1Dirty;
    volatile bool m_isOpt2Dirty;
    volatile bool m_isIncreasePitchShifterDirty;
    volatile bool m_isDecreasePitchShifterDirty;
    volatile bool m_isResetPitchShifterDirty;

public:
    EffectControls(ControllerFootswitchCommunication<decltype(CONTROLLER_SERIAL)>& controllerCommunication);

    void begin();
    void update();

private:
    void applyOpt1();
    void applyOpt2();
};

#endif
