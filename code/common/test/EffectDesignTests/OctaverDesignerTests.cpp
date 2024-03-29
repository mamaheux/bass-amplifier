#include <unity.h>
#include <EffectDesign.h>

#include "OctaverDesignerTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_OctaverDesigner_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    OctaverDesigner designer(SAMPLING_FREQUENCY);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(4, designer.effectCode());
    TEST_ASSERT_EQUAL(68, designer.dataSize());
    TEST_ASSERT_EQUAL(true, designer.isDirty());


    designer.update(0, 0);
    designer.setIsEnabled(false);
    TEST_ASSERT_EQUAL(false, designer.isActive());

    designer.setIsEnabled(true);
    TEST_ASSERT_EQUAL(false, designer.isActive());

    designer.update(1, 0);
    TEST_ASSERT_EQUAL(true, designer.isActive());

    designer.update(0, 1);
    TEST_ASSERT_EQUAL(true, designer.isActive());

    designer.update(1, 1);
    TEST_ASSERT_EQUAL(true, designer.isActive());
}

static void test_OctaverDesigner_update()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    constexpr uint8_t OCTAVE_DOWN_VOLUME = 128;
    constexpr uint8_t OCTAVE_UP_VOLUME = 255;

    OctaverDesigner designer(SAMPLING_FREQUENCY);

    designer.setIsDirty(false);
    designer.update(OCTAVE_DOWN_VOLUME, OCTAVE_UP_VOLUME);
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    const float* data = reinterpret_cast<const float*>(designer.data());

    // Down octave low pass filter
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.0004744678, data[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.0009489357, data[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.0004744678, data[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.937449, data[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.9393467, data[4]);

    // Up octave high pass filter
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9907867, data[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.981573, data[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9907867, data[7]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.981489, data[8]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.9816583, data[9]);

    // Up octave low pass filter
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.003916144, data[10]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.007832288, data[11]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.003916144, data[12]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.815341, data[13]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.8310056, data[14]);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.5019, data[15]); // Octave down volume
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[16]); // Octave up volume


    designer.setIsDirty(false);
    designer.update(OCTAVE_DOWN_VOLUME, OCTAVE_UP_VOLUME);
    TEST_ASSERT_EQUAL(false, designer.isDirty());
}

void runOctaverDesignerTests()
{
    RUN_TEST(test_OctaverDesigner_getters);
    RUN_TEST(test_OctaverDesigner_update);
}
