#include "EffectControls.h"

static volatile bool* isCompressorDirty = nullptr;
static void compressorInterrupt()
{
    if (isCompressorDirty == nullptr)
    {
        return;
    }

    *isCompressorDirty = true;
}

static volatile bool* isOctaverDirty = nullptr;
static void octaverInterrupt()
{
    if (isOctaverDirty == nullptr)
    {
        return;
    }

    *isOctaverDirty = true;
}

static volatile bool* isDelayDirty = nullptr;
static void delayInterrupt()
{
    if (isDelayDirty == nullptr)
    {
        return;
    }

    *isDelayDirty = true;
}

static volatile bool* isReverbDirty = nullptr;
static void reverbInterrupt()
{
    if (isReverbDirty == nullptr)
    {
        return;
    }

    *isReverbDirty = true;
}

static volatile bool* isOverdriveDirty = nullptr;
static void overdriveInterrupt()
{
    if (isOverdriveDirty == nullptr)
    {
        return;
    }

    *isOverdriveDirty = true;
}

static volatile bool* isMuteDirty = nullptr;
static void muteInterrupt()
{
    if (isMuteDirty == nullptr)
    {
        return;
    }

    *isMuteDirty = true;
}

static volatile uint32_t* delayUs = nullptr;
static volatile bool* isDelayUsDirty = nullptr;
static volatile uint32_t lastDelayTapUs = 0;
static void delayTapInterrupt()
{
    if (delayUs == nullptr || isDelayUsDirty == nullptr)
    {
        return;
    }

    uint32_t timeUs = micros();
    *delayUs = timeUs - lastDelayTapUs;
    lastDelayTapUs = timeUs;
    *isDelayUsDirty = true;
}

static volatile bool* isOpt1Dirty = nullptr;
static void opt1Interrupt()
{
    if (isOpt1Dirty == nullptr)
    {
        return;
    }

    *isOpt1Dirty = true;
}

static volatile bool* isOpt2Dirty = nullptr;
static void opt2Interrupt()
{
    if (isOpt2Dirty == nullptr)
    {
        return;
    }

    *isOpt2Dirty = true;
}

static volatile bool* isIncreasePitchShifterDirty = nullptr;
static void increasePitchShifterInterrupt()
{
    if (isIncreasePitchShifterDirty == nullptr)
    {
        return;
    }

    *isIncreasePitchShifterDirty = true;
}

static volatile bool* isDecreasePitchShifterDirty = nullptr;
static void decreasePitchShifterInterrupt()
{
    if (isDecreasePitchShifterDirty == nullptr)
    {
        return;
    }

    *isDecreasePitchShifterDirty = true;
}

static volatile bool* isResetPitchShifterDirty = nullptr;
static void resetPitchShifterInterrupt()
{
    if (isResetPitchShifterDirty == nullptr)
    {
        return;
    }

    *isResetPitchShifterDirty = true;
}

EffectControls::EffectControls(ControllerFootswitchCommunication<decltype(CONTROLLER_SERIAL)>& controllerCommunication) :
    m_controllerCommunication(controllerCommunication),

    m_isCompressorDirty(false),
    m_isOctaverDirty(false),
    m_isDelayDirty(false),
    m_isReverbDirty(false),
    m_isOverdriveDirty(false),
    m_isMuteDirty(false),

    m_delayUs(0),
    m_isDelayUsDirty(false),

    m_isOpt1Dirty(false),
    m_isOpt2Dirty(false),
    m_isIncreasePitchShifterDirty(false),
    m_isDecreasePitchShifterDirty(false),
    m_isResetPitchShifterDirty(false)
{
}

void EffectControls::begin()
{
    isCompressorDirty = &m_isCompressorDirty;
    pinMode(COMPRESSOR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(COMPRESSOR_PIN), compressorInterrupt, RISING);

    isOctaverDirty = &m_isOctaverDirty;
    pinMode(OCTAVER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(OCTAVER_PIN), octaverInterrupt, RISING);

    isDelayDirty = &m_isDelayDirty;
    pinMode(DELAY_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(DELAY_PIN), delayInterrupt, RISING);

    isReverbDirty = &m_isReverbDirty;
    pinMode(REVERB_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(REVERB_PIN), reverbInterrupt, RISING);

    isOverdriveDirty = &m_isOverdriveDirty;
    pinMode(OVERDRIVE_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(OVERDRIVE_PIN), overdriveInterrupt, RISING);

    isMuteDirty = &m_isMuteDirty;
    pinMode(MUTE_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(MUTE_PIN), muteInterrupt, RISING);


    delayUs = &m_delayUs;
    isDelayUsDirty = &m_isDelayUsDirty;
    pinMode(DELAY_TAP_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(DELAY_TAP_PIN), delayTapInterrupt, RISING);


    isOpt1Dirty = &m_isOpt1Dirty;
    pinMode(OPT_1_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(OPT_1_PIN), opt1Interrupt, RISING);

    isOpt2Dirty = &m_isOpt2Dirty;
    pinMode(OPT_2_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(OPT_2_PIN), opt2Interrupt, RISING);


    isIncreasePitchShifterDirty = &m_isIncreasePitchShifterDirty;
    pinMode(INCREASE_PITCH_SHIFTER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INCREASE_PITCH_SHIFTER_PIN), increasePitchShifterInterrupt, RISING);

    isDecreasePitchShifterDirty = &m_isDecreasePitchShifterDirty;
    pinMode(DECREASE_PITCH_SHIFTER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(DECREASE_PITCH_SHIFTER_PIN), decreasePitchShifterInterrupt, RISING);

    isResetPitchShifterDirty = &m_isResetPitchShifterDirty;
    pinMode(RESET_PITCH_SHIFTER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(RESET_PITCH_SHIFTER_PIN), resetPitchShifterInterrupt, RISING);
}

void EffectControls::update()
{
    if (m_isCompressorDirty)
    {
        m_controllerCommunication.sendToogleEffect(COMPRESSOR_CODE);
        m_isCompressorDirty = false;
    }
    if (m_isOctaverDirty)
    {
        m_controllerCommunication.sendToogleEffect(OCTAVER_CODE);
        m_isOctaverDirty = false;
    }
    if (m_isDelayDirty)
    {
        m_controllerCommunication.sendToogleEffect(DELAY_CODE);
        m_isDelayDirty = false;
    }
    if (m_isReverbDirty)
    {
        m_controllerCommunication.sendToogleEffect(REVERB_CODE);
        m_isReverbDirty = false;
    }
    if (m_isOverdriveDirty)
    {
        m_controllerCommunication.sendToogleEffect(OVERDRIVE_CODE);
        m_isOverdriveDirty = false;
    }
    if (m_isMuteDirty)
    {
        m_controllerCommunication.sendToogleEffect(MUTE_CODE);
        m_isMuteDirty = false;
    }

    if (m_isDelayUsDirty)
    {
        m_controllerCommunication.sendDelayUs(m_delayUs);
        m_isDelayUsDirty = false;
    }

    if (m_isOpt1Dirty)
    {
        applyOpt1();
        m_isOpt1Dirty = false;
    }
    if (m_isOpt2Dirty)
    {
        applyOpt2();
        m_isOpt2Dirty = false;
    }
    if (m_isIncreasePitchShifterDirty)
    {
        m_controllerCommunication.sendUpdatePitchShifter(PitchShifterUpdateCommand::INCREASE);
        m_isIncreasePitchShifterDirty = false;
    }
    if (m_isDecreasePitchShifterDirty)
    {
        m_controllerCommunication.sendUpdatePitchShifter(PitchShifterUpdateCommand::DECREASE);
        m_isDecreasePitchShifterDirty = false;
    }
    if (m_isResetPitchShifterDirty)
    {
        m_controllerCommunication.sendUpdatePitchShifter(PitchShifterUpdateCommand::RESET);
        m_isResetPitchShifterDirty = false;
    }
}

void EffectControls::applyOpt1()
{
    m_controllerCommunication.sendSetEffect(COMPRESSOR_CODE, false);
    m_controllerCommunication.sendSetEffect(OCTAVER_CODE, false);
    m_controllerCommunication.sendSetEffect(DELAY_CODE, false);
    m_controllerCommunication.sendSetEffect(REVERB_CODE, false);
    m_controllerCommunication.sendSetEffect(OVERDRIVE_CODE, false);
}

void EffectControls::applyOpt2()
{
}
