#include <Arduino.h>

#include <EffectDesign.h>

constexpr float SAMPLING_FREQUENCY = 48000;
constexpr uint32_t MAX_DELAY = 96000;

ContourDesigner contourDesigner(SAMPLING_FREQUENCY);
PresenceDesigner presenceDesigner(SAMPLING_FREQUENCY);
EqDesigner eqDesigner(SAMPLING_FREQUENCY);
CompressorDesigner compressorDesigner(SAMPLING_FREQUENCY);
OctaverDesigner octaverDesigner(SAMPLING_FREQUENCY);
DelayDesigner delayDesigner(SAMPLING_FREQUENCY, MAX_DELAY);
ReverbDesigner reverbDesigner(SAMPLING_FREQUENCY);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    uint8_t gain = rand();

    unsigned long start = micros();
    compressorDesigner.update(gain, gain);
    unsigned long end = micros();

    unsigned long duration = end - start;

    Serial.printf("%d us\n", duration);

    delay(1000);
}
