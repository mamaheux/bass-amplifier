#include <unity.h>
#include <EffectDesign.h>

#include "ReverbDesignerTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_ReverbDesigner_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    ReverbDesigner designer(SAMPLING_FREQUENCY);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(6, designer.effectCode());
    TEST_ASSERT_EQUAL(4, designer.dataSize());
    TEST_ASSERT_EQUAL(true, designer.isDirty());


    designer.update(0);
    designer.setIsEnabled(false);
    TEST_ASSERT_EQUAL(false, designer.isActive());

    designer.setIsEnabled(true);
    TEST_ASSERT_EQUAL(false, designer.isActive());

    designer.update(1);
    TEST_ASSERT_EQUAL(true, designer.isActive());
}

static void test_ReverbDesigner_update()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    constexpr uint8_t VOLUME = 64;

    ReverbDesigner designer(SAMPLING_FREQUENCY);

    designer.setIsDirty(false);
    designer.update(VOLUME);
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    const float* volume = reinterpret_cast<const float*>(designer.data());

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.22588, *volume); // Volume


    designer.setIsDirty(false);
    designer.update(VOLUME);
    TEST_ASSERT_EQUAL(false, designer.isDirty());
}

void runReverbDesignerTests()
{
    RUN_TEST(test_ReverbDesigner_getters);
    RUN_TEST(test_ReverbDesigner_update);
}
