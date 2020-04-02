#include <unity.h>
#include <EffectDesign.h>

#include "MuteDesignerTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_MuteDesigner_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    MuteDesigner designer(SAMPLING_FREQUENCY);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(8, designer.effectCode());
    TEST_ASSERT_EQUAL(0, designer.dataSize());
    TEST_ASSERT_EQUAL(true, designer.isDirty());
}

void runMuteDesignerTests()
{
    RUN_TEST(test_MuteDesigner_getters);
}
