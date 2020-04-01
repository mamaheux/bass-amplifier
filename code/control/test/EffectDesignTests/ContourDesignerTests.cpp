#include <unity.h>
#include <EffectDesign.h>

#include "ContourDesignerTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_ContourDesigner_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    ContourDesigner designer(SAMPLING_FREQUENCY);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(0, designer.effectCode());
    TEST_ASSERT_EQUAL(52, designer.dataSize());
    TEST_ASSERT_EQUAL(true, designer.isDirty());
}

static void test_ContourDesigner_update()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    constexpr uint8_t GAIN = 255;

    ContourDesigner designer(SAMPLING_FREQUENCY);

    designer.setIsDirty(false);
    designer.update(GAIN);
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    const float* data = reinterpret_cast<const float*>(designer.data());

    // Low shelving filter
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.00537226, data[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.97390576, data[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.96887096, data[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.97398993, data[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.97415906, data[5]);

    // High shelving filter
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.83352962, data[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -2.89953989, data[7]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.14633157, data[8]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[9]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.43317973, data[10]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.51350104, data[11]);

    // Global gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.5012, data[12]);
    

    designer.setIsDirty(false);
    designer.update(GAIN);
    TEST_ASSERT_EQUAL(false, designer.isDirty());
}

void runContourDesignerTests()
{
    RUN_TEST(test_ContourDesigner_getters);
    RUN_TEST(test_ContourDesigner_update);
}
