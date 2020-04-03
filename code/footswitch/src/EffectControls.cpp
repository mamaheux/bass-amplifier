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
    *delayUs = lastDelayTapUs - timeUs;
    lastDelayTapUs = timeUs;
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

static volatile bool* isOpt3Dirty = nullptr;
static void opt3Interrupt()
{
    if (isOpt3Dirty == nullptr)
    {
        return;
    }
    
    *isOpt3Dirty = true;
}

static volatile bool* isOpt4Dirty = nullptr;
static void opt4Interrupt()
{
    if (isOpt4Dirty == nullptr)
    {
        return;
    }
    
    *isOpt4Dirty = true;
}

static volatile bool* isOpt5Dirty = nullptr;
static void opt5Interrupt()
{
    if (isOpt5Dirty == nullptr)
    {
        return;
    }
    
    *isOpt5Dirty = true;
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
    m_isOpt3Dirty(false),
    m_isOpt4Dirty(false),
    m_isOpt5Dirty(false)
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

    isOpt3Dirty = &m_isOpt3Dirty;
    pinMode(OPT_3_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(OPT_3_PIN), opt3Interrupt, RISING);

    isOpt4Dirty = &m_isOpt4Dirty;
    pinMode(OPT_4_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(OPT_4_PIN), opt4Interrupt, RISING);

    isOpt5Dirty = &m_isOpt5Dirty;
    pinMode(OPT_5_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(OPT_5_PIN), opt5Interrupt, RISING);
}

void EffectControls::update()
{
    if (m_isCompressorDirty)
    {
        toogleEffect(COMPRESSOR_CODE);
        m_isCompressorDirty = false;
    }
    if (m_isOctaverDirty)
    {
        toogleEffect(OCTAVER_CODE);
        m_isOctaverDirty = false;
    }
    if (m_isDelayDirty)
    {
        toogleEffect(DELAY_CODE);
        m_isDelayDirty = false;
    }
    if (m_isReverbDirty)
    {
        toogleEffect(REVERB_CODE);
        m_isReverbDirty = false;
    }
    if (m_isOverdriveDirty)
    {
        toogleEffect(OVERDRIVE_CODE);
        m_isOverdriveDirty = false;
    }
    if (m_isMuteDirty)
    {
        toogleEffect(MUTE_CODE);
        m_isMuteDirty = false;
    }

    if (m_isDelayUsDirty)
    {
        setDelayUs(m_delayUs);
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
    if (m_isOpt3Dirty)
    {
        applyOpt3();
        m_isOpt3Dirty = false;
    }
    if (m_isOpt4Dirty)
    {
        applyOpt4();
        m_isOpt4Dirty = false;
    }
    if (m_isOpt5Dirty)
    {
        applyOpt5();
        m_isOpt5Dirty = false;
    }
}

void EffectControls::toogleEffect(uint8_t effectCode)
{
    do
    {
        m_controllerCommunication.sendToogleEffect(effectCode);
    } while (!m_controllerCommunication.waitAck(millis, ACK_TIMEOUT_MS));    
}

void EffectControls::setEffect(uint8_t effectCode, bool isEnabled)
{
    do
    {
        m_controllerCommunication.sendSetEffect(effectCode, isEnabled);
    } while (!m_controllerCommunication.waitAck(millis, ACK_TIMEOUT_MS));    
}

void EffectControls::setDelayUs(uint32_t delayUs)
{
    do
    {
        m_controllerCommunication.sendDelayUs(delayUs);
    } while (!m_controllerCommunication.waitAck(millis, ACK_TIMEOUT_MS));    
}

void EffectControls::applyOpt1()
{
    setEffect(COMPRESSOR_CODE, false);
    setEffect(OCTAVER_CODE, false);
    setEffect(DELAY_CODE, false);
    setEffect(REVERB_CODE, false);
    setEffect(OVERDRIVE_CODE, false);
}

void EffectControls::applyOpt2()
{
}

void EffectControls::applyOpt3()
{
}

void EffectControls::applyOpt4()
{
}

void EffectControls::applyOpt5()
{
}