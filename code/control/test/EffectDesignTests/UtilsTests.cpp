#include <unity.h>
#include <EffectDesign.h>

#include "UtilsTests.h"

constexpr float MAX_ABS_ERROR = 0.0001;

static void test_designLowShelvingFilter_negativeGainDb()
{
    constexpr float GAIN_DB = -10;
    constexpr float Q = 1;
    constexpr float CENTER_FREQUENCY = 100;
    constexpr float SAMPLING_FREQUENCY = 48000;
    BiquadCoefficients out;

    designLowShelvingFilter(out, GAIN_DB, Q, CENTER_FREQUENCY, SAMPLING_FREQUENCY);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9949, out.b0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.9766, out.b1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9819, out.b2);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, out.a0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.9765, out.a1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9770, out.a2);
}

static void test_designLowShelvingFilter_positiveGainDb()
{
    constexpr float GAIN_DB = 12;
    constexpr float Q = 1;
    constexpr float CENTER_FREQUENCY = 50;
    constexpr float SAMPLING_FREQUENCY = 48000;
    BiquadCoefficients out;

    designLowShelvingFilter(out, GAIN_DB, Q, CENTER_FREQUENCY, SAMPLING_FREQUENCY);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.0033, out.b0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.9934, out.b1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9903, out.b2);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, out.a0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.9934, out.a1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9935, out.a2);
}

static void test_designLowShelvingFilter_zeroGainDb()
{
    constexpr float GAIN_DB = 0;
    constexpr float Q = 1;
    constexpr float CENTER_FREQUENCY = 50;
    constexpr float SAMPLING_FREQUENCY = 48000;
    BiquadCoefficients out;

    designLowShelvingFilter(out, GAIN_DB, Q, CENTER_FREQUENCY, SAMPLING_FREQUENCY);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, out.b0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, out.b1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, out.b2);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, out.a0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, out.a1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, out.a2);
}

static void test_designHighShelvingFilter_negativeGainDb()
{
    constexpr float GAIN_DB = -5;
    constexpr float Q = 1;
    constexpr float CENTER_FREQUENCY = 12000;
    constexpr float SAMPLING_FREQUENCY = 48000;
    BiquadCoefficients out;

    designHighShelvingFilter(out, GAIN_DB, Q, CENTER_FREQUENCY, SAMPLING_FREQUENCY);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.7296, out.b0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, out.b1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.2432, out.b2);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, out.a0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.3786, out.a1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3514, out.a2);
}

static void test_designHighShelvingFilter_positiveGainDb()
{
    constexpr float GAIN_DB = 2;
    constexpr float Q = 1;
    constexpr float CENTER_FREQUENCY = 8000;
    constexpr float SAMPLING_FREQUENCY = 48000;
    BiquadCoefficients out;

    designHighShelvingFilter(out, GAIN_DB, Q, CENTER_FREQUENCY, SAMPLING_FREQUENCY);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.1724, out.b0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.9689, out.b1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.4943, out.b2);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, out.a0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -0.6978, out.a1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.3957, out.a2);
}

static void test_designHighShelvingFilter_zeroGainDb()
{
    constexpr float GAIN_DB = 0;
    constexpr float Q = 1;
    constexpr float CENTER_FREQUENCY = 50;
    constexpr float SAMPLING_FREQUENCY = 48000;
    BiquadCoefficients out;

    designHighShelvingFilter(out, GAIN_DB, Q, CENTER_FREQUENCY, SAMPLING_FREQUENCY);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, out.b0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, out.b1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, out.b2);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, out.a0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, out.a1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0, out.a2);
}

static void test_designPeakFilter()
{
    constexpr float GAIN_DB = 5;
    constexpr float Q = 5;
    constexpr float CENTER_FREQUENCY = 300;
    constexpr float SAMPLING_FREQUENCY = 48000;
    BiquadCoefficients out;

    designPeakFilter(out, GAIN_DB, Q, CENTER_FREQUENCY, SAMPLING_FREQUENCY);

    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1.0044, out.b0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.9872, out.b1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9844, out.b2);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 1, out.a0);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, -1.9872, out.a1);
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 0.9888, out.a2);
}

static void test_sqrtGainDb()
{
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 10, sqrtGainDb(20));
}

static void test_map()
{
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 2, map(0, 2, 5));
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 5, map(255, 2, 5));
    TEST_ASSERT_FLOAT_WITHIN(MAX_ABS_ERROR, 3.0039, map(128, 2, 4));
}

void runUtilsTests()
{
    RUN_TEST(test_designLowShelvingFilter_negativeGainDb);
    RUN_TEST(test_designLowShelvingFilter_positiveGainDb);
    RUN_TEST(test_designLowShelvingFilter_zeroGainDb);

    RUN_TEST(test_designHighShelvingFilter_negativeGainDb);
    RUN_TEST(test_designHighShelvingFilter_positiveGainDb);
    RUN_TEST(test_designHighShelvingFilter_zeroGainDb);

    RUN_TEST(test_designPeakFilter);
    RUN_TEST(test_map);
}
