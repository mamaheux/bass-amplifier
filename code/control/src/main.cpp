#include <Arduino.h>

#include <EffectDesign.h>

#include "config.h"
#include "ControlAdc.h"
#include "EffectControls.h"

ControlAdc adc;
EffectControls effectControls(adc);

ContourDesigner contourDesigner(SAMPLING_FREQUENCY);
PresenceDesigner presenceDesigner(SAMPLING_FREQUENCY);
EqDesigner eqDesigner(SAMPLING_FREQUENCY);
CompressorDesigner compressorDesigner(SAMPLING_FREQUENCY);
OctaverDesigner octaverDesigner(SAMPLING_FREQUENCY);
DelayDesigner delayDesigner(SAMPLING_FREQUENCY, MAX_DELAY);
ReverbDesigner reverbDesigner(SAMPLING_FREQUENCY);
OverdriveDesigner overdriveDesigner(SAMPLING_FREQUENCY);

void setup()
{
    DEBUG_SERIAL.begin(9600);

    adc.begin();
    effectControls.begin();
}

void loop()
{
    uint8_t gain = rand();

    unsigned long start = micros();
    overdriveDesigner.update(gain, gain);
    unsigned long end = micros();

    unsigned long duration = end - start;

    DEBUG_SERIAL.printf("%d us\n", duration);

    delay(1000);
}
