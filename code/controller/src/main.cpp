#include "config.h"
#include "ControlAdc.h"
#include "EffectControls.h"
#include "StatusLed.h"
#include "FanController.h"

#include <EffectDesign.h>
#include <ControllerFootswitchCommunication.h>

ControlAdc adc;
EffectControls effectControls(adc);
StatusLed statusLed;
FanController fanController(adc);

ContourDesigner contourDesigner(SAMPLING_FREQUENCY);
PresenceDesigner presenceDesigner(SAMPLING_FREQUENCY);
EqDesigner eqDesigner(SAMPLING_FREQUENCY);
CompressorDesigner compressorDesigner(SAMPLING_FREQUENCY);
OctaverDesigner octaverDesigner(SAMPLING_FREQUENCY);
DelayDesigner delayDesigner(SAMPLING_FREQUENCY, MAX_DELAY);
ReverbDesigner reverbDesigner(SAMPLING_FREQUENCY);
OverdriveDesigner overdriveDesigner(SAMPLING_FREQUENCY);
MuteDesigner muteDesigner(SAMPLING_FREQUENCY);

EffectDesigner* effectDesigners[EFFECT_CODE_COUNT];

ControllerFootswitchCommunication<HardwareSerial2> footswitchCommunication(FOOTSWITCH_SERIAL);
uint32_t lastHeartbeatTimeMs;
bool isHeartbeatPending;

void setupEffectDesigners();

void updateDesigner();
void updateStatusLed();

void updateFootswitchCommunication();
void resetAllEffectEnabledStates();

void footswitchHeatbeatHandler();
void footswitchToogleEffectHandler(uint8_t effectCode);
void footswitchDelayUsHandler(uint32_t delayUs);

void setup()
{
    DEBUG_SERIAL.begin(DEBUG_SERIAL_BAUD_RATE);

    adc.begin();
    effectControls.begin();
    fanController.begin();

    setupEffectDesigners();

    footswitchCommunication.begin(FOOTSWITCH_SERIALL_BAUD_RATE);
    footswitchCommunication.registerHeatbeatHandler(footswitchHeatbeatHandler);
    footswitchCommunication.registerToogleEffectHandler(footswitchToogleEffectHandler);
    footswitchCommunication.registerDelayUsHandler(footswitchDelayUsHandler);

    lastHeartbeatTimeMs = millis();
    isHeartbeatPending = true;
}

void setupEffectDesigners()
{
    effectDesigners[contourDesigner.effectCode()] = &contourDesigner;
    effectDesigners[presenceDesigner.effectCode()] = &presenceDesigner;
    effectDesigners[eqDesigner.effectCode()] = &eqDesigner;
    effectDesigners[compressorDesigner.effectCode()] = &compressorDesigner;
    effectDesigners[octaverDesigner.effectCode()] = &octaverDesigner;
    effectDesigners[delayDesigner.effectCode()] = &delayDesigner;
    effectDesigners[reverbDesigner.effectCode()] = &reverbDesigner;
    effectDesigners[overdriveDesigner.effectCode()] = &overdriveDesigner;
    effectDesigners[muteDesigner.effectCode()] = &muteDesigner;
}

void loop()
{
    updateDesigner();
    updateStatusLed();
    fanController.update();
    updateFootswitchCommunication();
}

void updateDesigner()
{
    contourDesigner.update(effectControls.getContourGain());
    presenceDesigner.update(effectControls.getPresenceGain());
    eqDesigner.update(effectControls.getEqLowGain(),
        effectControls.getEqLowMidGain(),
        effectControls.getEqHighMidGain(),
        effectControls.getEqHighGain());

    compressorDesigner.update(effectControls.getCompressorThreshold(), effectControls.getCompressorRatio());
    octaverDesigner.update(effectControls.getOctaverDownVolume(), effectControls.getOctaverUpVolume());
    delayDesigner.update(effectControls.getDelayVolume(), effectControls.getDelay());
    reverbDesigner.update(effectControls.getReverbVolume());
    overdriveDesigner.update(effectControls.getOverdriveGain(), effectControls.getOverdriveTone());
    muteDesigner.setIsEnabled(effectControls.getMuteState());
}

void updateStatusLed()
{
    statusLed.setCompressorLed(compressorDesigner.isActive());
    statusLed.setOctaverLed(octaverDesigner.isActive());
    statusLed.setDelayLed(delayDesigner.isActive());
    statusLed.setReverbLed(reverbDesigner.isActive());
    statusLed.setOverdriveLed(overdriveDesigner.isActive());
    statusLed.setMuteLed(muteDesigner.isActive());
    statusLed.update();
}

void updateFootswitchCommunication()
{
    while (footswitchCommunication.receive());

    footswitchCommunication.sendEffectActiveStates(compressorDesigner.isActive(),
        octaverDesigner.isActive(),
        delayDesigner.isActive(),
        reverbDesigner.isActive(),
        overdriveDesigner.isActive(),
        muteDesigner.isActive());

    if ((millis() - lastHeartbeatTimeMs) > CONTROLLER_FOOTSWITCH_HEARTBEAT_TIMEOUT_MS && isHeartbeatPending)
    {
        resetAllEffectEnabledStates();
        isHeartbeatPending = false;
    }
}

void resetAllEffectEnabledStates()
{
    for (int i = 0; i < EFFECT_CODE_COUNT; i++)
    {
        effectDesigners[i]->setIsEnabled(true);
    }
    muteDesigner.setIsEnabled(false);
}

void footswitchHeatbeatHandler()
{
    lastHeartbeatTimeMs = millis();
    isHeartbeatPending = true;
}

void footswitchToogleEffectHandler(uint8_t effectCode)
{
    if (effectCode < EFFECT_CODE_COUNT && effectCode != MUTE_CODE)
    {
        effectDesigners[effectCode]->setIsEnabled(!effectDesigners[effectCode]->isEnabled());
    }
    else if (effectCode == MUTE_CODE)
    {
        effectControls.setMuteState(!effectControls.getMuteState());
    }
}

void footswitchDelayUsHandler(uint32_t delayUs)
{
    effectControls.setDelayUs(delayUs);
}
