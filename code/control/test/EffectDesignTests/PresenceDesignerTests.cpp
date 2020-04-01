#include <unity.h>
#include <EffectDesign.h>

#include "PresenceDesignerTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    PresenceDesigner designer(SAMPLING_FREQUENCY);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(1, designer.effectCode());
    TEST_ASSERT_EQUAL(28, designer.dataSize());
    TEST_ASSERT_EQUAL(true, designer.isDirty());
}

static void test_update()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    constexpr uint8_t GAIN = 255;

    PresenceDesigner designer(SAMPLING_FREQUENCY);

    designer.setIsDirty(false);
    designer.update(GAIN);
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    const float* data = reinterpret_cast<const float*>(designer.data());

    // Low shelving filter
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.85630217, data[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -3.0473136, data[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.2317064, data[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.51712509, data[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.55782005, data[5]);

    // Global gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.5012, data[6]);
    

    designer.setIsDirty(false);
    designer.update(GAIN);
    TEST_ASSERT_EQUAL(false, designer.isDirty());
}

void runPresenceDesignerTests()
{
    RUN_TEST(test_getters);
    RUN_TEST(test_update);
}
