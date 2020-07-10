#include "config.h"

#include "Cs4270.h"
#include "ControllerCommunication.h"

#include <EffectProcessing.h>
#include <Communication.h>

#ifndef TEST

Cs4270 cs4270;


Compressor<BLOCK_SIZE> compressor;
Presence<BLOCK_SIZE> presence;
Contour<BLOCK_SIZE> contour;
Eq<BLOCK_SIZE> eq;
Overdrive<BLOCK_SIZE> overdrive;
Octaver<BLOCK_SIZE> octaver;
DMAMEM Delay<BLOCK_SIZE, MAX_DELAY> delayEffect;
Reverb<BLOCK_SIZE> reverb;
Mute<BLOCK_SIZE> mute;

Effect<BLOCK_SIZE>* effects[EFFECT_CODE_COUNT];
ControllerCommunication controllerCommunication(effects);

void setupEffectDesigners();
float* processAudio(float* input, float* downOctave);

void setup()
{
    DEBUG_SERIAL.begin(DEBUG_SERIAL_BAUD_RATE);

    setupEffectDesigners();

    cs4270.begin();
    controllerCommunication.begin();
}

void setupEffectDesigners()
{
    effects[COMPRESSOR_CODE] = &compressor;
    effects[PRESENCE_CODE] = &presence;
    effects[CONTOUR_CODE] = &contour;
    effects[EQ_CODE] = &eq;
    effects[OVERDRIVE_CODE] = &overdrive;
    effects[OCTAVER_CODE] = &octaver;
    effects[DELAY_CODE] = &delayEffect;
    effects[REVERB_CODE] = &reverb;
    effects[MUTE_CODE] = &mute;
}

void loop()
{
    controllerCommunication.update();

    float input[BLOCK_SIZE];
    float downOctave[BLOCK_SIZE];
    if (cs4270.read(input, downOctave))
    {
        float* output = processAudio(input, downOctave);

        while (!cs4270.write(output, output))
        {
            controllerCommunication.update();
        }
    }
}

float* processAudio(float* input, float* downOctave)
{
    float* output = compressor.process(input);

    output = presence.process(output);
    output = contour.process(output);
    output = eq.process(output);

    output = overdrive.process(output);
    output = octaver.process(output, downOctave);

    output = delayEffect.process(output);
    output = reverb.process(output);

    output = mute.process(output);

    return output;
}

#endif
