#include <unity.h>
#include <EffectDesign.h>

#include "OverdriveDesignerTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_OverdriveDesigner_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    OverdriveDesigner designer(SAMPLING_FREQUENCY);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(7, designer.effectCode());
    TEST_ASSERT_EQUAL(28, designer.dataSize());
    TEST_ASSERT_EQUAL(true, designer.isDirty());
}

static void test_OverdriveDesigner_update()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    constexpr uint8_t GAIN = 255;
    constexpr uint8_t TONE = 0;

    OverdriveDesigner designer(SAMPLING_FREQUENCY);

    designer.setIsDirty(false);
    designer.update(GAIN, TONE);
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    const float* data = reinterpret_cast<const float*>(designer.data());

    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 100, data[0]);

    // Tone filter
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.00391613, data[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.00783225, data[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.00391613, data[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.81534108, data[5]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.83100559, data[6]);
    

    designer.setIsDirty(false);
    designer.update(GAIN, TONE);
    TEST_ASSERT_EQUAL(false, designer.isDirty());
}

void runOverdriveDesignerTests()
{
    RUN_TEST(test_OverdriveDesigner_getters);
    RUN_TEST(test_OverdriveDesigner_update);
}
