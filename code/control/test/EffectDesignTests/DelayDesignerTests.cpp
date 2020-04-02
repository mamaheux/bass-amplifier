#include <unity.h>
#include <EffectDesign.h>

#include "DelayDesignerTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_DelayDesigner_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    constexpr uint32_t MAX_DELAY = 10000;
    DelayDesigner designer(SAMPLING_FREQUENCY, MAX_DELAY);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(5, designer.effectCode());
    TEST_ASSERT_EQUAL(8, designer.dataSize());
    TEST_ASSERT_EQUAL(true, designer.isDirty());
}

static void test_DelayDesigner_update()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    constexpr uint32_t MAX_DELAY = 10000;
    constexpr uint8_t VOLUME = 64;
    constexpr uint32_t DELAY_1 = 8500;
    constexpr uint32_t DELAY_2 = 11000;

    DelayDesigner designer(SAMPLING_FREQUENCY, MAX_DELAY);

    designer.setIsDirty(false);
    designer.update(VOLUME, DELAY_1);
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    const float* volume = reinterpret_cast<const float*>(designer.data());
    const uint32_t* delay = reinterpret_cast<const uint32_t*>(designer.data() + sizeof(float));

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.12549, *volume); // Volume
    TEST_ASSERT_EQUAL(DELAY_1, *delay); // Delay


    designer.setIsDirty(false);
    designer.update(VOLUME, DELAY_2);
    TEST_ASSERT_EQUAL(true, designer.isDirty());
    
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.12549, *volume); // Volume
    TEST_ASSERT_EQUAL(MAX_DELAY, *delay); // Delay


    designer.setIsDirty(false);
    designer.update(VOLUME, DELAY_2);
    TEST_ASSERT_EQUAL(false, designer.isDirty());
}

void runDelayDesignerTests()
{
    RUN_TEST(test_DelayDesigner_getters);
    RUN_TEST(test_DelayDesigner_update);
}
