#include <unity.h>
#include <EffectDesign.h>

#include "CompressorDesignerTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_CompressorDesigner_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    CompressorDesigner designer(SAMPLING_FREQUENCY);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(3, designer.effectCode());
    TEST_ASSERT_EQUAL(16, designer.dataSize());
    TEST_ASSERT_EQUAL(true, designer.isDirty());


    designer.update(0, 0);
    designer.setIsEnabled(false);
    TEST_ASSERT_EQUAL(false, designer.isActive());

    designer.setIsEnabled(true);
    TEST_ASSERT_EQUAL(false, designer.isActive());

    designer.update(1, 0);
    TEST_ASSERT_EQUAL(false, designer.isActive());

    designer.update(0, 1);
    TEST_ASSERT_EQUAL(true, designer.isActive());
}

static void test_CompressorDesigner_update()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    constexpr uint8_t THRESHOLD = 64;
    constexpr uint8_t RATIO = 128;

    CompressorDesigner designer(SAMPLING_FREQUENCY);

    designer.setIsDirty(false);
    designer.update(THRESHOLD, RATIO);
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    const float* data = reinterpret_cast<const float*>(designer.data());

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2510, data[0]); // Threshold
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.5020, data[1]); // Ratio
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.995, data[2]); // Attack
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9997, data[3]); // Release
    

    designer.setIsDirty(false);
    designer.update(THRESHOLD, RATIO);
    TEST_ASSERT_EQUAL(false, designer.isDirty());
}

void runCompressorDesignerTests()
{
    RUN_TEST(test_CompressorDesigner_getters);
    RUN_TEST(test_CompressorDesigner_update);
}
