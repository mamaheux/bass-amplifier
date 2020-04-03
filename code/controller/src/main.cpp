#include "config.h"
#include "ControlAdc.h"
#include "EffectControls.h"
#include "StatusLed.h"
#include "FanController.h"

#include <EffectDesign.h>
#include <ControllerFootswitchCommunication.h>
#include <Ticker.h>

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
void setupFootswitchCommunication();

void updateEffectDesigners();
void updateStatusLed();
void updateFan();

void updateFootswitchCommunicationFast();
void updateFootswitchCommunicationSlow();
void resetAllEffectEnabledStates();

void footswitchHeatbeatHandler();
void footswitchToogleEffectHandler(uint8_t effectCode);
void footswitchDelayUsHandler(uint32_t delayUs);

Ticker updateEffectDesignersTicker(updateEffectDesigners, EFFECT_DESIGNER_UPDATE_INTERVAL_US, MICROS);
Ticker updateStatusLedTicker(updateStatusLed, STATUS_LED_UPDATE_INTERVAL_US, MICROS);
Ticker updateFanTicker(updateFan, FAN_UPDATE_INTERVAL_US, MICROS);

Ticker updateFootswitchCommunicationFastTicker(updateFootswitchCommunicationFast,
    FOOTSWITCH_COMMUNICATION_FAST_UPDATE_INTERVAL_US, MICROS);
Ticker updateFootswitchCommunicationSlowTicker(updateFootswitchCommunicationSlow,
    FOOTSWITCH_COMMUNICATION_SLOW_UPDATE_INTERVAL_US, MICROS);

void setup()
{
    DEBUG_SERIAL.begin(DEBUG_SERIAL_BAUD_RATE);

    adc.begin();
    effectControls.begin();
    fanController.begin();

    setupEffectDesigners();
    setupFootswitchCommunication();

    updateEffectDesignersTicker.start();
    updateStatusLedTicker.start();
    updateFanTicker.start();
    updateFootswitchCommunicationFastTicker.start();
    updateFootswitchCommunicationSlowTicker.start();
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

void setupFootswitchCommunication()
{
    footswitchCommunication.begin(FOOTSWITCH_SERIALL_BAUD_RATE);
    footswitchCommunication.registerHeatbeatHandler(footswitchHeatbeatHandler);
    footswitchCommunication.registerToogleEffectHandler(footswitchToogleEffectHandler);
    footswitchCommunication.registerDelayUsHandler(footswitchDelayUsHandler);

    lastHeartbeatTimeMs = millis();
    isHeartbeatPending = true;
}

void loop()
{
    updateEffectDesignersTicker.update();
    updateStatusLedTicker.update();
    updateFanTicker.update();
    updateFootswitchCommunicationFastTicker.update();
    updateFootswitchCommunicationSlowTicker.update();
}

void updateEffectDesigners()
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

void updateFan()
{
    fanController.update();
}

void updateFootswitchCommunicationFast()
{
    while (footswitchCommunication.receive());
}

void updateFootswitchCommunicationSlow()
{
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
