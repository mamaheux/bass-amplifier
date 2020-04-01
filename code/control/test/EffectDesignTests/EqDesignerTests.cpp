#include <unity.h>
#include <EffectDesign.h>

#include "EqDesignerTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_EqDesigner_getters()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    EqDesigner designer(SAMPLING_FREQUENCY);

    TEST_ASSERT_EQUAL(SAMPLING_FREQUENCY, designer.samplingFrequency());
    TEST_ASSERT_EQUAL(2, designer.effectCode());
    TEST_ASSERT_EQUAL(192, designer.dataSize());
    TEST_ASSERT_EQUAL(true, designer.isDirty());
}

static void test_EqDesigner_update()
{
    constexpr float SAMPLING_FREQUENCY = 48000;
    constexpr uint8_t LOW_GAIN = 255;
    constexpr uint8_t LOW_MID_GAIN = 0;
    constexpr uint8_t HIGH_MID_GAIN = 255;
    constexpr uint8_t HIGH_GAIN = 0;

    EqDesigner designer(SAMPLING_FREQUENCY);

    designer.setIsDirty(false);
    designer.update(LOW_GAIN, LOW_MID_GAIN, HIGH_MID_GAIN, HIGH_GAIN);
    TEST_ASSERT_EQUAL(true, designer.isDirty());

    const float* data = reinterpret_cast<const float*>(designer.data());

    // Low band
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.00296055, data[0]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.99554477, data[1]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9926116, data[2]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[3]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.99554477, data[4]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.99557213, data[5]);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.01086548, data[6]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.99597535, data[7]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.98521931, data[8]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[9]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.99597535, data[10]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.99608479, data[11]);

    // Low mid band
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.97968243, data[12]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.9503636, data[13]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.97110901, data[14]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[15]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.9503636, data[16]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.95079144, data[17]);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.96123846, data[18]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.90405217, data[19]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.94443349, data[20]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[21]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.90405217, data[22]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.90567195, data[23]);

    // High mid band
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.08012175, data[24]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.95879714, data[25]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.88535498, data[26]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[27]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.95879714, data[28]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.96547674, data[29]);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.15770122, data[30]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.90789173, data[31]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.77601856, data[32]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[33]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.90789173, data[34]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.93371978, data[35]);

    // High band
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.754046, data[36]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.347702, data[37]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.66911633, data[38]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[39]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.347702, data[40]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4232323, data[41]);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.7799124, data[42]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.9598012, data[43]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4298906, data[44]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, data[45]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.9598013, data[46]);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.209803, data[47]);
    

    designer.setIsDirty(false);
    designer.update(LOW_GAIN, LOW_MID_GAIN, HIGH_MID_GAIN, HIGH_GAIN);
    TEST_ASSERT_EQUAL(false, designer.isDirty());
}

void runEqDesignerTests()
{
    RUN_TEST(test_EqDesigner_getters);
    RUN_TEST(test_EqDesigner_update);
}
