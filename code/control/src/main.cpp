#include "config.h"
#include "ControlAdc.h"
#include "EffectControls.h"
#include "StatusLed.h"
#include "FanController.h"

#include <EffectDesign.h>

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

void updateDesigner();
void updateStatusLed();

void setup()
{
    DEBUG_SERIAL.begin(9600);

    adc.begin();
    effectControls.begin();
    fanController.begin();
}

void loop()
{
    updateDesigner();
    updateStatusLed();
    fanController.update();
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
