#include <unity.h>
#include <EffectDesign.h>

#include "EffectDesignerTests.h"

static void test_EffectDesigner_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    uint8_t EFFECT_CODE = 5;
    constexpr uint8_t DATA_SIZE = 2;
    uint8_t data[DATA_SIZE];

    EffectDesigner designer(SAMPLING_FREQUENCY, EFFECT_CODE, DATA_SIZE, data);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(EFFECT_CODE, designer.effectCode());
    TEST_ASSERT_EQUAL(DATA_SIZE, designer.dataSize());
    TEST_ASSERT_EQUAL(data, designer.data());
}

static void test_EffectDesigner_isDirty()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    uint8_t EFFECT_CODE = 5;
    constexpr uint8_t DATA_SIZE = 2;
    uint8_t data[DATA_SIZE];

    EffectDesigner designer(SAMPLING_FREQUENCY, EFFECT_CODE, DATA_SIZE, data);

    TEST_ASSERT_EQUAL(true, designer.isDirty());

    designer.setIsDirty(false);
    TEST_ASSERT_EQUAL(false, designer.isDirty());
}

void runEffectDesignerTests()
{
    RUN_TEST(test_EffectDesigner_getters);
    RUN_TEST(test_EffectDesigner_isDirty);
}
