#include <Arduino.h>

#include <EffectProcessing.h>

#include <math.h>
#include <stdio.h>

constexpr float MAX_ABS_ERROR = 0.0001;

#define TEST_ASSERT_FLOAT_WITHIN(t, e, v) if (abs(e - v) > t) \
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


constexpr uint32_t BLOCK_SIZE = 32;
constexpr uint32_t MAX_DELAY = 96;

Eq<BLOCK_SIZE> eq;
Presence<BLOCK_SIZE> presence;
Contour<BLOCK_SIZE> contour;
Compressor<BLOCK_SIZE> compressor;
Octaver<BLOCK_SIZE> octaver;
DMAMEM Delay<BLOCK_SIZE, MAX_DELAY> delayEffect;

void test_biquad()
{
    constexpr uint32_t NUM_STAGES = 1;
    const float COEFFICIENTS[] = {0.00554272, 0.01108543, 0.00554272, 1.77863178, -0.80080265};
    float input[BLOCK_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};
    
    BiquadIir<BLOCK_SIZE, NUM_STAGES> biquadIir;
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

void test_contour()
{
    const float COEFFICIENTS[] = {2, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.5};
    float input[BLOCK_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};

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
    float input[BLOCK_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};

    presence.update(reinterpret_cast<const uint8_t*>(COEFFICIENTS));

    float* output = presence.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 2, output[0]);
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
    float input[BLOCK_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};

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
    float input[BLOCK_SIZE] = {0.1, 0.2, 0.3, 0.4, 0.3, 0.2, 0.1, 0};

    compressor.update(reinterpret_cast<const uint8_t*>(COEFFICIENTS));

    float* output = compressor.process(input);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.1, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.25588235, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.29795918, output[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.22384615, output[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.15385694, output[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.08206681, output[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, output[7]);
}

void test_octaver()
{
    const float COEFFICIENTS[] = {4, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.25, 0.75};
    float input[BLOCK_SIZE] = {1, 2, -1, -2};
    float downOctave[BLOCK_SIZE] = {2, 2, 2, 2};

    octaver.update(reinterpret_cast<const uint8_t*>(COEFFICIENTS));

    float* output = octaver.process(input, downOctave);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.5, output[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 2.75, output[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.5, output[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.75, output[3]);
}

void test_delay()
{
    uint8_t data[8];
    float volume = 0.95;
    uint32_t delayValue = 1;
    memcpy(data, &volume, sizeof(float));
    memcpy(data + sizeof(float), &delayValue, sizeof(uint32_t));

    float input[BLOCK_SIZE] = {1, 0, 0, 0};

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

void setup()
{
    Serial.begin(9600);

    delay(5000);

    Serial.printf("Processing tests:\n");
    RUN_TEST(test_biquad);
    RUN_TEST(test_contour);
    RUN_TEST(test_presence);
    RUN_TEST(test_eq);
    RUN_TEST(test_compressor);
    RUN_TEST(test_octaver);
    RUN_TEST(test_delay);
}

void loop()
{
}
