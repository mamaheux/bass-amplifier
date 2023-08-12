#include <unity.h>
#include <EffectDesign.h>

#include "PitchShifterDesignerTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_PitchShifterDesigner_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    PitchShifterDesigner designer(SAMPLING_FREQUENCY);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(9, designer.effectCode());
    TEST_ASSERT_EQUAL(5, designer.dataSize());
    TEST_ASSERT_EQUAL(true, designer.isDirty());
}

static void test_PitchShifterDesigner_reset()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    PitchShifterDesigner designer(SAMPLING_FREQUENCY);

    designer.increasePitch();
    designer.setIsDirty(false);
    designer.reset();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(0, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.3333333333332817f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.reset();
    TEST_ASSERT_EQUAL(false, designer.isDirty());
}

static void test_PitchShifterDesigner_increasePitch()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    PitchShifterDesigner designer(SAMPLING_FREQUENCY);

    designer.setIsDirty(false);
    designer.increasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(1, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.3758581127821765f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.increasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(2, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.4344999204123041f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.increasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(3, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.5157718389755686f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.increasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(4, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.6224343855655563f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.increasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(5, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.7459885206225656f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.increasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(6, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.9106411955407752f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.increasePitch();
    TEST_ASSERT_EQUAL(false, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(6, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.9106411955407752f, *reinterpret_cast<const float*>(designer.data() + 1));
}

static void test_PitchShifterDesigner_decreasePitch()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    PitchShifterDesigner designer(SAMPLING_FREQUENCY);

    designer.setIsDirty(false);
    designer.decreasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(-1, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.3001193733644227f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.decreasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(-2, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.2734288784043912f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.decreasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(-3, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.2585542092522932f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.decreasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(-4, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.244615780432574f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.decreasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(-5, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.241652712452141f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.decreasePitch();
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(-6, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.2415331892552723f, *reinterpret_cast<const float*>(designer.data() + 1));


    designer.setIsDirty(false);
    designer.decreasePitch();
    TEST_ASSERT_EQUAL(false, designer.isDirty());

    // Pitch step
    TEST_ASSERT_EQUAL(-6, static_cast<int8_t>(designer.data()[0]));
    // Gain
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.2415331892552723f, *reinterpret_cast<const float*>(designer.data() + 1));
}

void runPitchShifterDesignerTests()
{
    RUN_TEST(test_PitchShifterDesigner_getters);
    RUN_TEST(test_PitchShifterDesigner_reset);
    RUN_TEST(test_PitchShifterDesigner_increasePitch);
    RUN_TEST(test_PitchShifterDesigner_decreasePitch);
}
