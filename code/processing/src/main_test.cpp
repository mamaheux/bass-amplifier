#include "config.h"

#include <Arduino.h>

#include <EffectProcessing.h>

#include <math.h>
#include <stdio.h>

#ifdef TEST

constexpr float MAX_ABS_ERROR = 0.00001;

#define TEST_ASSERT_EQUAL(e, v) if (e != v) \
    { \
        char buffer [50]; \
        sprintf(buffer, "%f", (double)e); \
        Serial.printf("Line %d | %s != ", __LINE__, buffer); \
        sprintf(buffer, "%f", (double)v); \
        Serial.printf("%s\n", buffer); \
    }

#define TEST_ASSERT_FLOAT_WITHIN(t, e, v) if (fabs(e - v) > t) \
    { \
        char buffer [50]; \
        sprintf(buffer, "%f", (double)e); \
        Serial.printf("Line %d | %s != ", __LINE__, buffer); \
        sprintf(buffer, "%f", (double)v); \
        Serial.printf("%s\n", buffer); \
    }

#define RUN_TEST(test) \
    do \
    { \
        Serial.printf("Running: %s \n", #test); \
        uint32_t start = micros(); \
        test(); \
        uint32_t duration = micros() - start; \
        Serial.printf("Elapsed time: %d us\n\n", duration); \
    } while(false);


constexpr uint32_t TEST_BLOCK_SIZE = 32;
constexpr uint32_t TEST_MAX_DELAY = 96;

Eq<TEST_BLOCK_SIZE> eq;
Presence<TEST_BLOCK_SIZE> presence;
Contour<TEST_BLOCK_SIZE> contour;
Compressor<TEST_BLOCK_SIZE> compressor;
Octaver<TEST_BLOCK_SIZE> octaver;
DMAMEM Delay<TEST_BLOCK_SIZE, TEST_MAX_DELAY> delayEffect;
Reverb<TEST_BLOCK_SIZE> reverb;
Overdrive<TEST_BLOCK_SIZE> overdrive;
Mute<TEST_BLOCK_SIZE> mute;


void test_biquad()
{
    constexpr uint32_t NUM_STAGES = 1;
    const float COEFFICIENTS[] = {0.00554272, 0.01108543, 0.00554272, 1.77863178, -0.80080265};
    float input[TEST_BLOCK_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};

    BiquadIir<TEST_BLOCK_SIZE, NUM_STAGES> biquadIir;
    biquadIir.update(COEFFICIENTS);

    float* output = biquadIir.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.00554272, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.02094389, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.03835556, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.05144849, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.06079269, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.06692773, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.07035683, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.071543, output[7]);
}

void test_feedbackComb()
{
    constexpr uint32_t DELAY = 2;
    const float GAIN = 0.9;
    float input[2 * TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1, 0};

    FeedbackComb<TEST_BLOCK_SIZE, DELAY> feedbackComb;
    feedbackComb.update(GAIN);

    float* output = feedbackComb.process(input);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.39, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.58, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.651, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.722, output[7]);

    output = feedbackComb.process(input + TEST_BLOCK_SIZE);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.19371842, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.18352271, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.17434658, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.16517044, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.15691192, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1486534, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.14122073, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.13378806, output[7]);
}

void test_allPassComb()
{
    constexpr uint32_t DELAY = 2;
    const float GAIN = 0.9;
    float input[2 * TEST_BLOCK_SIZE] = {10, 20, 30, 40, 30, 20, 10, 0};

    AllPassComb<TEST_BLOCK_SIZE, DELAY> allPassComb;
    allPassComb.update(GAIN);

    float* output = allPassComb.process(input);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 9.007179, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 18.006821, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 28.893539, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 39.793861, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 30.995815, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 22.185524, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 11.103766, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.033028, output[7]);

    output = allPassComb.process(input + TEST_BLOCK_SIZE);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.001867, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.008395, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.001680, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.007556, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.001512, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.006800, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.001361, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.006120, output[7]);
}

void test_contour()
{
    const float COEFFICIENTS[] = {2, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.5};
    float input[TEST_BLOCK_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};

    contour.update(reinterpret_cast<const uint8_t*>(COEFFICIENTS));

    float* output = contour.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.5, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[7]);
}

void test_presence()
{
    const float COEFFICIENTS[] = {2, 0, 0, 0, 0, 0.5};
    float input[TEST_BLOCK_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};

    presence.update(reinterpret_cast<const uint8_t*>(COEFFICIENTS));

    float* output = presence.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 2.0, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[7]);
}

void test_eq()
{
    const float COEFFICIENTS[] = {2, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.25, 0, 0, 0, 0, 4, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0.125, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0.2, 0, 0, 0, 0};
    float input[TEST_BLOCK_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};

    eq.update(reinterpret_cast<const uint8_t*>(COEFFICIENTS));

    float* output = eq.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[7]);
}

void test_compressor()
{
    const float COEFFICIENTS[] = {0.15, 0.5, 0.5, 0.75};
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1, 0};

    compressor.update(reinterpret_cast<const uint8_t*>(COEFFICIENTS));

    float* output = compressor.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.255882, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.297959, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.223846, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.153857, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.082067, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[7]);
}

void test_octaver()
{
    const float COEFFICIENTS[] = {2, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.25, 0.75};
    float input[TEST_BLOCK_SIZE] = {1, 2, -1, -2};

    octaver.update(reinterpret_cast<const uint8_t*>(COEFFICIENTS));

    float* output = octaver.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.0, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 2.0, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.5, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.0, output[3]);
}

void test_delay()
{
    uint8_t data[8];
    float volume = 0.95;
    uint32_t delayValue = 1;
    memcpy(data, &volume, sizeof(float));
    memcpy(data + sizeof(float), &delayValue, sizeof(uint32_t));

    float input[TEST_BLOCK_SIZE] = {1, 0, 0, 0};

    delayEffect.update(data);

    float* output = delayEffect.process(input);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.95, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9025, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.857375, output[3]);

    input[0] = 0;
    output = delayEffect.process(input);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.19371148, output[0]);

    output = delayEffect.process(input);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.0375241392, output[0]);

    output = delayEffect.process(input);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.0072688567, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.0069054139, output[1]);
}

void test_reverb()
{
    float volume = 0.95;

    float input[TEST_BLOCK_SIZE] = {1, 0, 0, 0};

    reverb.update(reinterpret_cast<uint8_t*>(&volume));

    float* output = reverb.process(input);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.5, output[0]);
}

void test_overdrive()
{
    const float COEFFICIENTS[] = {4, 2, 0, 0, 0, 0};
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    overdrive.update(reinterpret_cast<const uint8_t*>(COEFFICIENTS));

    float* output = overdrive.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.59020401, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.94818084, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.16530476, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.29699708, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.16530476, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.94818084, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.59020401, output[6]);
}

void test_mute()
{
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    float* output = mute.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[6]);
}

void test_pitchShifter_hann()
{
    const uint32_t SIZE = 8;
    float output[SIZE] = {0};
    hann(output, SIZE);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1882551, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.61126047, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.95048443, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.95048443, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.61126047, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1882551, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[7]);
}

void test_pitchShifter_freqRamp()
{
    const uint32_t SIZE = 8;
    float output[SIZE] = {0};
    freqRamp(output, SIZE);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.392699, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.785398, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.178097, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.570796, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.963495, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 2.356194, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 2.748894, output[7]);
}

void test_pitchShifter_complexPhase()
{
    const uint32_t SIZE = 4;
    float input[SIZE * 2] = {1, 2, -3, 4, -5, -6, 7, -8};
    float output[SIZE] = {0};
    complexPhase(input, output, SIZE);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.1071487177940904, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 2.214297435588181, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -2.2655346029916, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.8519663271732721, output[3]);
}

void test_pitchShifter_constraintAngle()
{
    const uint32_t SIZE = 8;
    float input[SIZE] = {-9, -6, -3, 0, 3, 6, 9, 12};
    float output[SIZE] = {0};

    constraintAngle(input, output, SIZE);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -2.71681469, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.28318531, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -3, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 3, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.28318531, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 2.71681469, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.56637061, output[7]);
}

void test_pitchShifter_complexPolar()
{
    const uint32_t SIZE = 4;
    float magnitude[SIZE] = {1, 2, 3, 4};
    float phase[SIZE] = {-4, -2, 0, 2};
    float output[SIZE * 2] = {0};

    complexPolar(magnitude, phase, output, SIZE);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.65364362, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.7568025, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.83229367, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.81859485, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 3, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.66458735, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 3.63718971, output[7]);
}

void test_pitchShifter_0()
{
    constexpr int8_t PITCH_STEP = 0;
    constexpr float GAIN = 1.3333333333332817;
    uint8_t data[5];
    data[0] = static_cast<uint8_t>(PITCH_STEP);
    memcpy(data + 1, &GAIN, sizeof(float));

    PitchShifter<TEST_BLOCK_SIZE> pitchShifter;
    pitchShifter.update(data);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, pitchShifter.alpha());
    TEST_ASSERT_EQUAL(8, pitchShifter.outputHopSize());
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, GAIN, pitchShifter.gain());


    float input[TEST_BLOCK_SIZE] = {0};
    for (uint32_t i = 0; i < TEST_BLOCK_SIZE; i++)
    {
        input[i] = i;
    }

    pitchShifter.process(input);
    float* output = pitchShifter.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 7.737812, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 8.713712, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 9.693796, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 10.671672, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 11.641825, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 12.601958, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 13.554690, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 14.508450, output[7]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 15.475661, output[8]);
}

void test_pitchShifter_6()
{
    constexpr int8_t PITCH_STEP = 6;
    constexpr float GAIN = 1.9106411955407752;
    uint8_t data[5];
    data[0] = static_cast<uint8_t>(PITCH_STEP);
    memcpy(data + 1, &GAIN, sizeof(float));

    PitchShifter<TEST_BLOCK_SIZE> pitchShifter;
    pitchShifter.update(data);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.4142135623730951, pitchShifter.alpha());
    TEST_ASSERT_EQUAL(11, pitchShifter.outputHopSize());
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, GAIN, pitchShifter.gain());


    float input[TEST_BLOCK_SIZE] = {0};
    for (uint32_t i = 0; i < TEST_BLOCK_SIZE; i++)
    {
        input[i] = i;
    }

    pitchShifter.process(input);
    float* output = pitchShifter.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 16.808216, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 18.373808, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 19.303288, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 19.698181, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 20.954554, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 20.983122, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 23.602072, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 21.279915, output[7]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 26.826633, output[8]);
}

void test_pitchShifter_m6()
{
    constexpr int8_t PITCH_STEP = -6;
    constexpr float GAIN = 1.2415331892552723;
    uint8_t data[5];
    data[0] = static_cast<uint8_t>(PITCH_STEP);
    memcpy(data + 1, &GAIN, sizeof(float));

    PitchShifter<TEST_BLOCK_SIZE> pitchShifter;
    pitchShifter.update(data);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.7071067811865476, pitchShifter.alpha());
    TEST_ASSERT_EQUAL(6, pitchShifter.outputHopSize());
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, GAIN, pitchShifter.gain());


    float input[TEST_BLOCK_SIZE] = {0};
    for (uint32_t i = 0; i < TEST_BLOCK_SIZE; i++)
    {
        input[i] = i;
    }

    pitchShifter.process(input);
    float* output = pitchShifter.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.396561, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.716322, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.158321, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.790879, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 2.926187, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 3.761713, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 4.628284, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 5.738132, output[7]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 6.765344, output[8]);
}

void randomize(float* input, uint32_t blockSize)
{
    for (uint32_t i = 0; i < blockSize; i++)
    {
        input[i] = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) - 0.5;
    }
}

void test_performance()
{
    constexpr uint32_t ITERATION_COUNT = 1500;
    float input[TEST_BLOCK_SIZE];

    PitchShifter<TEST_BLOCK_SIZE> pitchShifter;

    uint32_t durationTotal = 0;

    for (uint32_t i = 0; i < ITERATION_COUNT; i++)
    {
        randomize(input, TEST_BLOCK_SIZE);

        uint32_t start = micros();
        float* output = contour.process(input);
        output = presence.process(output);
        output = eq.process(output);

        output = compressor.process(output);
        output = octaver.process(output);
        output = delayEffect.process(output);
        output = reverb.process(output);
        output = overdrive.process(output);
        output = pitchShifter.process(output);
        durationTotal += micros() - start;
    }

    Serial.printf("Duration = %d us\n", durationTotal / ITERATION_COUNT);
}

void test_isEnabled_contour()
{
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    contour.setIsEnabled(false);
    float* output = contour.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[6]);
}

void test_isEnabled_presence()
{
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    presence.setIsEnabled(false);
    float* output = presence.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[6]);
}

void test_isEnabled_eq()
{
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    eq.setIsEnabled(false);
    float* output = eq.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[6]);
}

void test_isEnabled_compressor()
{
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    compressor.setIsEnabled(false);
    float* output = compressor.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[6]);
}

void test_isEnabled_octaver()
{
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    octaver.setIsEnabled(false);
    float* output = octaver.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[6]);
}

void test_isEnabled_delay()
{
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    delayEffect.setIsEnabled(false);
    float* output = delayEffect.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[6]);
}

void test_isEnabled_reverb()
{
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    reverb.setIsEnabled(false);
    float* output = reverb.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.05, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.15, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.15, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.05, output[6]);
}

void test_isEnabled_overdrive()
{
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    overdrive.setIsEnabled(false);
    float* output = overdrive.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[6]);
}

void test_isEnabled_mute()
{
    float input[TEST_BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1};

    mute.setIsEnabled(false);
    float* output = mute.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[6]);
}

void setup()
{
    Serial.begin(9600);

    delay(5000);

    Serial.println("****** Processing tests ******");
    Serial.println();

    RUN_TEST(test_biquad);
    RUN_TEST(test_feedbackComb);
    RUN_TEST(test_allPassComb);

    RUN_TEST(test_contour);
    RUN_TEST(test_presence);
    RUN_TEST(test_eq);
    RUN_TEST(test_compressor);
    RUN_TEST(test_octaver);
    RUN_TEST(test_delay);
    RUN_TEST(test_reverb);
    RUN_TEST(test_overdrive);
    RUN_TEST(test_mute);
    RUN_TEST(test_pitchShifter_hann);
    RUN_TEST(test_pitchShifter_freqRamp);
    RUN_TEST(test_pitchShifter_complexPhase);
    RUN_TEST(test_pitchShifter_constraintAngle);
    RUN_TEST(test_pitchShifter_complexPolar);
    RUN_TEST(test_pitchShifter_0);
    RUN_TEST(test_pitchShifter_6);
    RUN_TEST(test_pitchShifter_m6);

    RUN_TEST(test_performance);

    RUN_TEST(test_isEnabled_contour);
    RUN_TEST(test_isEnabled_presence);
    RUN_TEST(test_isEnabled_eq);
    RUN_TEST(test_isEnabled_compressor);
    RUN_TEST(test_isEnabled_octaver);
    RUN_TEST(test_isEnabled_delay);
    RUN_TEST(test_isEnabled_reverb);
    RUN_TEST(test_isEnabled_overdrive);
    RUN_TEST(test_isEnabled_mute);

    Serial.println();
    Serial.println();
    Serial.println();
}

void loop()
{
}

#endif
