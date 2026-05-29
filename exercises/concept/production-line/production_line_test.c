#include "vendor/unity.h"

#include <stdalign.h>
#include <stddef.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern void sum_yields(const float line_a[4], const float line_b[4], float result[4]);
extern void scaled_deviation(const double measured[], const double target[], const double sensitivity[], double result[]);
extern void calibrate_batch(const float raw[], const double reference[2], const double offset[2], double result[2]);
extern void normalize_scores(double scores[], const double gains[], const double scale[2], size_t n);

void setUp(void) {
}

void tearDown(void) {
}

// TASK: 1
void test_sum_yields_example(void) {
    alignas(16) const float line_a[4] = {10.0, 20.0, 30.0, 40.0};
    alignas(16) const float line_b[4] = {5.0, 15.0, 25.0, 35.0};
    alignas(16) float result[4];
    sum_yields(line_a, line_b, result);
    const float expected[4] = {15.0, 35.0, 55.0, 75.0};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_sum_yields_all_zeros(void) {
    TEST_IGNORE();
    alignas(16) const float line_a[4] = {0.0, 0.0, 0.0, 0.0};
    alignas(16) const float line_b[4] = {0.0, 0.0, 0.0, 0.0};
    alignas(16) float result[4];
    sum_yields(line_a, line_b, result);
    const float expected[4] = {0.0, 0.0, 0.0, 0.0};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_sum_yields_cancels_to_zero(void) {
    TEST_IGNORE();
    alignas(16) const float line_a[4] = {-1.0, -2.0, -3.0, -4.0};
    alignas(16) const float line_b[4] = {1.0, 2.0, 3.0, 4.0};
    alignas(16) float result[4];
    sum_yields(line_a, line_b, result);
    const float expected[4] = {0.0, 0.0, 0.0, 0.0};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_sum_yields_mixed_signs(void) {
    TEST_IGNORE();
    alignas(16) const float line_a[4] = {1.5, -2.5, 3.5, -4.5};
    alignas(16) const float line_b[4] = {-0.5, 2.5, -1.5, 4.5};
    alignas(16) float result[4];
    sum_yields(line_a, line_b, result);
    const float expected[4] = {1.0, 0.0, 2.0, 0.0};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_sum_yields_fractional(void) {
    TEST_IGNORE();
    alignas(16) const float line_a[4] = {0.5, 0.25, 0.125, 0.75};
    alignas(16) const float line_b[4] = {0.5, 0.75, 0.875, 0.25};
    alignas(16) float result[4];
    sum_yields(line_a, line_b, result);
    const float expected[4] = {1.0, 1.0, 1.0, 1.0};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_sum_yields_large_values(void) {
    TEST_IGNORE();
    alignas(16) const float line_a[4] = {1000000.0, 2000000.0, 3000000.0, 4000000.0};
    alignas(16) const float line_b[4] = {500000.0, 500000.0, 500000.0, 500000.0};
    alignas(16) float result[4];
    sum_yields(line_a, line_b, result);
    const float expected[4] = {1500000.0, 2500000.0, 3500000.0, 4500000.0};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_sum_yields_one_operand_zero(void) {
    TEST_IGNORE();
    alignas(16) const float line_a[4] = {7.0, 8.0, 9.0, 10.0};
    alignas(16) const float line_b[4] = {0.0, 0.0, 0.0, 0.0};
    alignas(16) float result[4];
    sum_yields(line_a, line_b, result);
    const float expected[4] = {7.0, 8.0, 9.0, 10.0};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_sum_yields_both_negative(void) {
    TEST_IGNORE();
    alignas(16) const float line_a[4] = {-10.0, -20.0, -30.0, -40.0};
    alignas(16) const float line_b[4] = {-5.0, -15.0, -25.0, -35.0};
    alignas(16) float result[4];
    sum_yields(line_a, line_b, result);
    const float expected[4] = {-15.0, -35.0, -55.0, -75.0};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

// TASK: 2
void test_scaled_deviation_example(void) {
    TEST_IGNORE();
    alignas(16) const double measured[2] = {10.5, 20.5};
    const char x1 = 'X';
    (void)x1;
    alignas(8) const double target[2] = {10.0, 20.0};
    const char x2 = 'X';
    (void)x2;
    alignas(8) const double sensitivity[2] = {2.0, 4.0};
    const char x3 = 'X';
    (void)x3;
    alignas(8) double result[2];
    scaled_deviation(measured, target, sensitivity, result);
    const double expected[2] = {1.0, 2.0};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0], "The 64-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1], "The 64-bit floating-point number at lane 1 is different from expected");
}

void test_scaled_deviation_zero_deviation(void) {
    TEST_IGNORE();
    alignas(16) const double measured[2] = {5.0, 5.0};
    const char x1 = 'X';
    (void)x1;
    alignas(8) const double target[2] = {5.0, 5.0};
    const char x2 = 'X';
    (void)x2;
    alignas(8) const double sensitivity[2] = {2.0, 2.0};
    const char x3 = 'X';
    (void)x3;
    alignas(8) double result[2];
    scaled_deviation(measured, target, sensitivity, result);
    const double expected[2] = {0.0, 0.0};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0], "The 64-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1], "The 64-bit floating-point number at lane 1 is different from expected");
}

void test_scaled_deviation_negative_deviation(void) {
    TEST_IGNORE();
    alignas(16) const double measured[2] = {1.0, 2.0};
    const char x1 = 'X';
    (void)x1;
    alignas(8) const double target[2] = {3.0, 5.0};
    const char x2 = 'X';
    (void)x2;
    alignas(8) const double sensitivity[2] = {1.0, 1.0};
    const char x3 = 'X';
    (void)x3;
    alignas(8) double result[2];
    scaled_deviation(measured, target, sensitivity, result);
    const double expected[2] = {-2.0, -3.0};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0], "The 64-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1], "The 64-bit floating-point number at lane 1 is different from expected");
}

void test_scaled_deviation_zero_sensitivity(void) {
    TEST_IGNORE();
    alignas(16) const double measured[2] = {100.0, 200.0};
    const char x1 = 'X';
    (void)x1;
    alignas(8) const double target[2] = {50.0, 50.0};
    const char x2 = 'X';
    (void)x2;
    alignas(8) const double sensitivity[2] = {0.0, 0.0};
    const char x3 = 'X';
    (void)x3;
    alignas(8) double result[2];
    scaled_deviation(measured, target, sensitivity, result);
    const double expected[2] = {0.0, 0.0};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0], "The 64-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1], "The 64-bit floating-point number at lane 1 is different from expected");
}

void test_scaled_deviation_fractional_sensitivity(void) {
    TEST_IGNORE();
    alignas(16) const double measured[2] = {4.0, 8.0};
    const char x1 = 'X';
    (void)x1;
    alignas(8) const double target[2] = {2.0, 4.0};
    const char x2 = 'X';
    (void)x2;
    alignas(8) const double sensitivity[2] = {0.5, 0.25};
    const char x3 = 'X';
    (void)x3;
    alignas(8) double result[2];
    scaled_deviation(measured, target, sensitivity, result);
    const double expected[2] = {1.0, 1.0};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0], "The 64-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1], "The 64-bit floating-point number at lane 1 is different from expected");
}

void test_scaled_deviation_negative_target(void) {
    TEST_IGNORE();
    alignas(16) const double measured[2] = {0.0, 0.0};
    const char x1 = 'X';
    (void)x1;
    alignas(8) const double target[2] = {-3.0, -7.0};
    const char x2 = 'X';
    (void)x2;
    alignas(8) const double sensitivity[2] = {1.0, 1.0};
    const char x3 = 'X';
    (void)x3;
    alignas(8) double result[2];
    scaled_deviation(measured, target, sensitivity, result);
    const double expected[2] = {3.0, 7.0};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0], "The 64-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1], "The 64-bit floating-point number at lane 1 is different from expected");
}

void test_scaled_deviation_negative_sensitivity(void) {
    TEST_IGNORE();
    alignas(16) const double measured[2] = {10.0, 10.0};
    const char x1 = 'X';
    (void)x1;
    alignas(8) const double target[2] = {5.0, 5.0};
    const char x2 = 'X';
    (void)x2;
    alignas(8) const double sensitivity[2] = {-2.0, -3.0};
    const char x3 = 'X';
    (void)x3;
    alignas(8) double result[2];
    scaled_deviation(measured, target, sensitivity, result);
    const double expected[2] = {-10.0, -15.0};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0], "The 64-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1], "The 64-bit floating-point number at lane 1 is different from expected");
}

void test_scaled_deviation_larger_values(void) {
    TEST_IGNORE();
    alignas(16) const double measured[2] = {1000.0, 2000.0};
    const char x1 = 'X';
    (void)x1;
    alignas(8) const double target[2] = {1000.0, 1500.0};
    const char x2 = 'X';
    (void)x2;
    alignas(8) const double sensitivity[2] = {3.0, 2.0};
    const char x3 = 'X';
    (void)x3;
    alignas(8) double result[2];
    scaled_deviation(measured, target, sensitivity, result);
    const double expected[2] = {0.0, 1000.0};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0], "The 64-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1], "The 64-bit floating-point number at lane 1 is different from expected");
}

// TASK: 3
void test_calibrate_batch_example(void) {
    TEST_IGNORE();
    const char x = 'X';
    (void)x;
    alignas(4) const float raw[] = {10.0, 20.0, 25.0, 50.0};
    alignas(16) const double reference[2] = {100.0, 100.0};
    alignas(16) const double offset[2] = {5.0, 10.0};
    alignas(16) double result[4];
    calibrate_batch(raw, reference, offset, result);
    const double expected[] = {10.0, 5.0, 2.5, 1.25};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0],
                                     "The 64-bit floating-point number at lane 0 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1],
                                     "The 64-bit floating-point number at lane 1 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[2], result[2],
                                     "The 64-bit floating-point number at lane 0 of the second row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[3], result[3],
                                     "The 64-bit floating-point number at lane 1 of the second row is different from expected");
}

void test_calibrate_batch_uniform(void) {
    TEST_IGNORE();
    const char x = 'X';
    (void)x;
    alignas(4) const float raw[] = {6.0, 6.0, 6.0, 6.0};
    alignas(16) const double reference[2] = {12.0, 12.0};
    alignas(16) const double offset[2] = {2.0, 2.0};
    alignas(16) double result[4];
    calibrate_batch(raw, reference, offset, result);
    const double expected[] = {1.5, 1.5, 1.5, 1.5};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0],
                                     "The 64-bit floating-point number at lane 0 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1],
                                     "The 64-bit floating-point number at lane 1 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[2], result[2],
                                     "The 64-bit floating-point number at lane 0 of the second row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[3], result[3],
                                     "The 64-bit floating-point number at lane 1 of the second row is different from expected");
}

void test_calibrate_batch_different_offset_per_lane(void) {
    TEST_IGNORE();
    const char x = 'X';
    (void)x;
    alignas(4) const float raw[] = {10.0, 10.0, 10.0, 10.0};
    alignas(16) const double reference[2] = {20.0, 20.0};
    alignas(16) const double offset[2] = {5.0, 8.0};
    alignas(16) double result[4];
    calibrate_batch(raw, reference, offset, result);
    const double expected[] = {2.0, 5.0, 2.0, 5.0};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0],
                                     "The 64-bit floating-point number at lane 0 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1],
                                     "The 64-bit floating-point number at lane 1 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[2], result[2],
                                     "The 64-bit floating-point number at lane 0 of the second row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[3], result[3],
                                     "The 64-bit floating-point number at lane 1 of the second row is different from expected");
}

void test_calibrate_batch_negative_raw(void) {
    TEST_IGNORE();
    const char x = 'X';
    (void)x;
    alignas(4) const float raw[] = {-2.0, -4.0, -8.0, -16.0};
    alignas(16) const double reference[2] = {16.0, 16.0};
    alignas(16) const double offset[2] = {0.0, 0.0};
    alignas(16) double result[4];
    calibrate_batch(raw, reference, offset, result);
    const double expected[] = {-4.0, -2.0, -1.0, -0.5};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0],
                                     "The 64-bit floating-point number at lane 0 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1],
                                     "The 64-bit floating-point number at lane 1 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[2], result[2],
                                     "The 64-bit floating-point number at lane 0 of the second row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[3], result[3],
                                     "The 64-bit floating-point number at lane 1 of the second row is different from expected");
}

void test_calibrate_batch_different_reference_per_lane(void) {
    TEST_IGNORE();
    const char x = 'X';
    (void)x;
    alignas(4) const float raw[] = {10.0, 10.0, 10.0, 10.0};
    alignas(16) const double reference[2] = {100.0, 50.0};
    alignas(16) const double offset[2] = {0.0, 0.0};
    alignas(16) double result[4];
    calibrate_batch(raw, reference, offset, result);
    const double expected[] = {5.0, 2.5, 5.0, 2.5};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0],
                                     "The 64-bit floating-point number at lane 0 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1],
                                     "The 64-bit floating-point number at lane 1 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[2], result[2],
                                     "The 64-bit floating-point number at lane 0 of the second row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[3], result[3],
                                     "The 64-bit floating-point number at lane 1 of the second row is different from expected");
}

void test_calibrate_batch_fractional_raw(void) {
    TEST_IGNORE();
    const char x = 'X';
    (void)x;
    alignas(4) const float raw[] = {0.5, 1.0, 2.0, 4.0};
    alignas(16) const double reference[2] = {4.0, 4.0};
    alignas(16) const double offset[2] = {0.0, 0.0};
    alignas(16) double result[4];
    calibrate_batch(raw, reference, offset, result);
    const double expected[] = {4.0, 2.0, 1.0, 0.5};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0],
                                     "The 64-bit floating-point number at lane 0 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1],
                                     "The 64-bit floating-point number at lane 1 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[2], result[2],
                                     "The 64-bit floating-point number at lane 0 of the second row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[3], result[3],
                                     "The 64-bit floating-point number at lane 1 of the second row is different from expected");
}

void test_calibrate_batch_offset_exceeds_raw(void) {
    TEST_IGNORE();
    const char x = 'X';
    (void)x;
    alignas(4) const float raw[] = {2.0, 2.0, 6.0, 8.0};
    alignas(16) const double reference[2] = {8.0, 8.0};
    alignas(16) const double offset[2] = {10.0, 10.0};
    alignas(16) double result[4];
    calibrate_batch(raw, reference, offset, result);
    const double expected[] = {-0.5, -0.5, -1.0, -2.0};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0],
                                     "The 64-bit floating-point number at lane 0 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1],
                                     "The 64-bit floating-point number at lane 1 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[2], result[2],
                                     "The 64-bit floating-point number at lane 0 of the second row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[3], result[3],
                                     "The 64-bit floating-point number at lane 1 of the second row is different from expected");
}

void test_calibrate_batch_mixed_reference_offset(void) {
    TEST_IGNORE();
    const char x = 'X';
    (void)x;
    alignas(4) const float raw[] = {3.0, 5.0, 9.0, 17.0};
    alignas(16) const double reference[2] = {2.0, 4.0};
    alignas(16) const double offset[2] = {1.0, 1.0};
    alignas(16) double result[4];
    calibrate_batch(raw, reference, offset, result);
    const double expected[] = {0.5, 0.5, 0.125, 0.125};
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0],
                                     "The 64-bit floating-point number at lane 0 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1],
                                     "The 64-bit floating-point number at lane 1 of the first row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[2], result[2],
                                     "The 64-bit floating-point number at lane 0 of the second row is different from expected");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[3], result[3],
                                     "The 64-bit floating-point number at lane 1 of the second row is different from expected");
}

// TASK: 4
void test_normalize_scores_example(void) {
    TEST_IGNORE();
    alignas(16) double scores[] = {10.0, 20.0, 30.0, 40.0};
    alignas(16) const double gains[] = {2.0, 1.5, 1.0, 0.5};
    alignas(16) const double scale[2] = {2.0, 4.0};
    normalize_scores(scores, gains, scale, 4);
    const double expected[] = {10.0, 7.5, 15.0, 5.0};
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, scores, ARRAY_SIZE(expected),
                                           "The sequence of 64-bit floating-point numbers is different from expected");
}

void test_normalize_scores_single_iteration(void) {
    TEST_IGNORE();
    alignas(16) double scores[] = {8.0, 16.0};
    alignas(16) const double gains[] = {2.0, 2.0};
    alignas(16) const double scale[2] = {4.0, 8.0};
    normalize_scores(scores, gains, scale, 2);
    const double expected[] = {4.0, 4.0};
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, scores, ARRAY_SIZE(expected),
                                           "The sequence of 64-bit floating-point numbers is different from expected");
}

void test_normalize_scores_identity(void) {
    TEST_IGNORE();
    alignas(16) double scores[] = {1.0, 2.0, 3.0, 4.0};
    alignas(16) const double gains[] = {1.0, 1.0, 1.0, 1.0};
    alignas(16) const double scale[2] = {1.0, 1.0};
    normalize_scores(scores, gains, scale, 4);
    const double expected[] = {1.0, 2.0, 3.0, 4.0};
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, scores, ARRAY_SIZE(expected),
                                           "The sequence of 64-bit floating-point numbers is different from expected");
}

void test_normalize_scores_three_iterations(void) {
    TEST_IGNORE();
    alignas(16) double scores[] = {2.0, 4.0, 6.0, 8.0, 10.0, 12.0};
    alignas(16) const double gains[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    alignas(16) const double scale[2] = {2.0, 4.0};
    normalize_scores(scores, gains, scale, 6);
    const double expected[] = {1.0, 1.0, 3.0, 2.0, 5.0, 3.0};
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, scores, ARRAY_SIZE(expected),
                                           "The sequence of 64-bit floating-point numbers is different from expected");
}

void test_normalize_scores_negative_scores(void) {
    TEST_IGNORE();
    alignas(16) double scores[] = {-4.0, -8.0, -12.0, -16.0};
    alignas(16) const double gains[] = {1.0, 1.0, 1.0, 1.0};
    alignas(16) const double scale[2] = {2.0, 4.0};
    normalize_scores(scores, gains, scale, 4);
    const double expected[] = {-2.0, -2.0, -6.0, -4.0};
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, scores, ARRAY_SIZE(expected),
                                           "The sequence of 64-bit floating-point numbers is different from expected");
}

void test_normalize_scores_negative_gains(void) {
    TEST_IGNORE();
    alignas(16) double scores[] = {10.0, 10.0};
    alignas(16) const double gains[] = {-2.0, -4.0};
    alignas(16) const double scale[2] = {1.0, 1.0};
    normalize_scores(scores, gains, scale, 2);
    const double expected[] = {-20.0, -40.0};
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, scores, ARRAY_SIZE(expected),
                                           "The sequence of 64-bit floating-point numbers is different from expected");
}

void test_normalize_scores_fractional_gains(void) {
    TEST_IGNORE();
    alignas(16) double scores[] = {8.0, 8.0, 8.0, 8.0};
    alignas(16) const double gains[] = {0.5, 0.25, 0.125, 0.5};
    alignas(16) const double scale[2] = {1.0, 1.0};
    normalize_scores(scores, gains, scale, 4);
    const double expected[] = {4.0, 2.0, 1.0, 4.0};
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, scores, ARRAY_SIZE(expected),
                                           "The sequence of 64-bit floating-point numbers is different from expected");
}

void test_normalize_scores_negative_scale(void) {
    TEST_IGNORE();
    alignas(16) double scores[] = {6.0, 8.0};
    alignas(16) const double gains[] = {2.0, 2.0};
    alignas(16) const double scale[2] = {-3.0, -4.0};
    normalize_scores(scores, gains, scale, 2);
    const double expected[] = {-4.0, -4.0};
    TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, scores, ARRAY_SIZE(expected),
                                           "The sequence of 64-bit floating-point numbers is different from expected");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sum_yields_example);
    RUN_TEST(test_sum_yields_all_zeros);
    RUN_TEST(test_sum_yields_cancels_to_zero);
    RUN_TEST(test_sum_yields_mixed_signs);
    RUN_TEST(test_sum_yields_fractional);
    RUN_TEST(test_sum_yields_large_values);
    RUN_TEST(test_sum_yields_one_operand_zero);
    RUN_TEST(test_sum_yields_both_negative);
    RUN_TEST(test_scaled_deviation_example);
    RUN_TEST(test_scaled_deviation_zero_deviation);
    RUN_TEST(test_scaled_deviation_negative_deviation);
    RUN_TEST(test_scaled_deviation_zero_sensitivity);
    RUN_TEST(test_scaled_deviation_fractional_sensitivity);
    RUN_TEST(test_scaled_deviation_negative_target);
    RUN_TEST(test_scaled_deviation_negative_sensitivity);
    RUN_TEST(test_scaled_deviation_larger_values);
    RUN_TEST(test_calibrate_batch_example);
    RUN_TEST(test_calibrate_batch_uniform);
    RUN_TEST(test_calibrate_batch_different_offset_per_lane);
    RUN_TEST(test_calibrate_batch_negative_raw);
    RUN_TEST(test_calibrate_batch_different_reference_per_lane);
    RUN_TEST(test_calibrate_batch_fractional_raw);
    RUN_TEST(test_calibrate_batch_offset_exceeds_raw);
    RUN_TEST(test_calibrate_batch_mixed_reference_offset);
    RUN_TEST(test_normalize_scores_example);
    RUN_TEST(test_normalize_scores_single_iteration);
    RUN_TEST(test_normalize_scores_identity);
    RUN_TEST(test_normalize_scores_three_iterations);
    RUN_TEST(test_normalize_scores_negative_scores);
    RUN_TEST(test_normalize_scores_negative_gains);
    RUN_TEST(test_normalize_scores_fractional_gains);
    RUN_TEST(test_normalize_scores_negative_scale);
    return UNITY_END();
}
