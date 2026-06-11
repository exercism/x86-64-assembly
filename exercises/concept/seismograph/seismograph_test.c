#include "vendor/unity.h"

#include <stdalign.h>
#include <stdint.h>

extern void rectify_trace(float result[4], const float trace[4]);
extern void reading_scale(int32_t result[4], const float trace[4]);
extern void coarsen_displacements(int32_t result[4], const int32_t counts[4], uint64_t shift);
extern void gate_channels(uint32_t result[4], const uint32_t enable_a[4], const uint32_t enable_b[4], const uint32_t faulty[4]);
extern void toggle_calibration(uint32_t result[4], const uint32_t status[4], const uint32_t toggle[4], const uint32_t locked[4]);
extern void amplify_trace(float result[4], const float trace[4], const int32_t gains[4]);

void setUp(void) {
}

void tearDown(void) {
}

// TASK: 1
void test_rectify_trace_example(void) {
    alignas(16) const float trace[4] = {1.5f, -2.25f, 0.0f, -135.75f};
    alignas(16) float result[4];
    rectify_trace(result, trace);
    const float expected[4] = {1.5f, 2.25f, 0.0f, 135.75f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_rectify_trace_all_negative(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {-0.5f, -1.0f, -3.5f, -1000.25f};
    alignas(16) float result[4];
    rectify_trace(result, trace);
    const float expected[4] = {0.5f, 1.0f, 3.5f, 1000.25f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_rectify_trace_all_positive_unchanged(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {0.5f, 1.0f, 3.5f, 1000.25f};
    alignas(16) float result[4];
    rectify_trace(result, trace);
    const float expected[4] = {0.5f, 1.0f, 3.5f, 1000.25f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_rectify_trace_negative_zero(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {-0.0f, 0.0f, -0.0f, 0.0f};
    alignas(16) float result[4];
    rectify_trace(result, trace);
    const float expected[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_rectify_trace_large_magnitudes(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {-123456.0f, 98765.5f, -0.015625f, -7.0f};
    alignas(16) float result[4];
    rectify_trace(result, trace);
    const float expected[4] = {123456.0f, 98765.5f, 0.015625f, 7.0f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

// TASK: 2
void test_reading_scale_example(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {8.0f, 0.25f, 1.0f, 13.5f};
    alignas(16) int32_t result[4];
    reading_scale(result, trace);
    const int32_t expected[4] = {3, -2, 0, 3};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[0], result[0], "The scale at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[1], result[1], "The scale at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[2], result[2], "The scale at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[3], result[3], "The scale at lane 3 is different from expected");
}

void test_reading_scale_powers_of_two(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {1.0f, 2.0f, 4.0f, 1024.0f};
    alignas(16) int32_t result[4];
    reading_scale(result, trace);
    const int32_t expected[4] = {0, 1, 2, 10};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[0], result[0], "The scale at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[1], result[1], "The scale at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[2], result[2], "The scale at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[3], result[3], "The scale at lane 3 is different from expected");
}

void test_reading_scale_small_readings(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {0.5f, 0.125f, 0.03125f, 0.75f};
    alignas(16) int32_t result[4];
    reading_scale(result, trace);
    const int32_t expected[4] = {-1, -3, -5, -1};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[0], result[0], "The scale at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[1], result[1], "The scale at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[2], result[2], "The scale at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[3], result[3], "The scale at lane 3 is different from expected");
}

void test_reading_scale_ignores_fraction(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {1.999f, 2.001f, 15.875f, 16.125f};
    alignas(16) int32_t result[4];
    reading_scale(result, trace);
    const int32_t expected[4] = {0, 1, 3, 4};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[0], result[0], "The scale at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[1], result[1], "The scale at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[2], result[2], "The scale at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[3], result[3], "The scale at lane 3 is different from expected");
}

void test_reading_scale_negative_readings(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {-8.0f, -0.25f, -1.5f, -100.0f};
    alignas(16) int32_t result[4];
    reading_scale(result, trace);
    const int32_t expected[4] = {3, -2, 0, 6};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[0], result[0], "The scale at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[1], result[1], "The scale at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[2], result[2], "The scale at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[3], result[3], "The scale at lane 3 is different from expected");
}

// TASK: 3
void test_coarsen_displacements_example(void) {
    TEST_IGNORE();
    alignas(16) const int32_t counts[4] = {1024, -1024, 25, -25};
    alignas(16) int32_t result[4];
    coarsen_displacements(result, counts, 3);
    const int32_t expected[4] = {128, -128, 3, -4};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[0], result[0], "The coarsened count at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[1], result[1], "The coarsened count at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[2], result[2], "The coarsened count at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[3], result[3], "The coarsened count at lane 3 is different from expected");
}

void test_coarsen_displacements_shift_zero(void) {
    TEST_IGNORE();
    alignas(16) const int32_t counts[4] = {7, -7, 2147483647, -2147483648};
    alignas(16) int32_t result[4];
    coarsen_displacements(result, counts, 0);
    const int32_t expected[4] = {7, -7, 2147483647, -2147483648};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[0], result[0], "The coarsened count at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[1], result[1], "The coarsened count at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[2], result[2], "The coarsened count at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[3], result[3], "The coarsened count at lane 3 is different from expected");
}

void test_coarsen_displacements_rounds_toward_negative_infinity(void) {
    TEST_IGNORE();
    alignas(16) const int32_t counts[4] = {-1, -2, -3, -4};
    alignas(16) int32_t result[4];
    coarsen_displacements(result, counts, 1);
    const int32_t expected[4] = {-1, -1, -2, -2};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[0], result[0], "The coarsened count at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[1], result[1], "The coarsened count at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[2], result[2], "The coarsened count at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[3], result[3], "The coarsened count at lane 3 is different from expected");
}

void test_coarsen_displacements_keeps_sign_with_large_shift(void) {
    TEST_IGNORE();
    alignas(16) const int32_t counts[4] = {-2147483648, 2147483647, -1, 1};
    alignas(16) int32_t result[4];
    coarsen_displacements(result, counts, 31);
    const int32_t expected[4] = {-1, 0, -1, 0};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[0], result[0], "The coarsened count at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[1], result[1], "The coarsened count at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[2], result[2], "The coarsened count at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected[3], result[3], "The coarsened count at lane 3 is different from expected");
}

// TASK: 4
void test_gate_channels_example(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t enable_a[4] = {12, 1, 15, 0};
    alignas(16) const uint32_t enable_b[4] = {6, 1, 0, 0};
    alignas(16) const uint32_t faulty[4] = {4, 3, 9, 15};
    alignas(16) uint32_t result[4];
    gate_channels(result, enable_a, enable_b, faulty);
    const uint32_t expected[4] = {10, 0, 6, 0};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The gated mask at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The gated mask at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The gated mask at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The gated mask at lane 3 is different from expected");
}

void test_gate_channels_no_faults(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t enable_a[4] = {4042322160, 0, 305419896, 4294967295};
    alignas(16) const uint32_t enable_b[4] = {252645135, 0, 2271560481, 0};
    alignas(16) const uint32_t faulty[4] = {0, 0, 0, 0};
    alignas(16) uint32_t result[4];
    gate_channels(result, enable_a, enable_b, faulty);
    const uint32_t expected[4] = {4294967295, 0, 2541049721, 4294967295};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The gated mask at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The gated mask at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The gated mask at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The gated mask at lane 3 is different from expected");
}

void test_gate_channels_all_faulty(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t enable_a[4] = {3735928559, 4294967295, 1, 2147483648};
    alignas(16) const uint32_t enable_b[4] = {4277009102, 4294967295, 2, 1};
    alignas(16) const uint32_t faulty[4] = {4294967295, 4294967295, 4294967295, 4294967295};
    alignas(16) uint32_t result[4];
    gate_channels(result, enable_a, enable_b, faulty);
    const uint32_t expected[4] = {0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The gated mask at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The gated mask at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The gated mask at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The gated mask at lane 3 is different from expected");
}

void test_gate_channels_faults_only_silence_enabled_channels(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t enable_a[4] = {10, 12, 65280, 0};
    alignas(16) const uint32_t enable_b[4] = {5, 10, 255, 0};
    alignas(16) const uint32_t faulty[4] = {1, 6, 4080, 4294967295};
    alignas(16) uint32_t result[4];
    gate_channels(result, enable_a, enable_b, faulty);
    const uint32_t expected[4] = {14, 8, 61455, 0};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The gated mask at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The gated mask at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The gated mask at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The gated mask at lane 3 is different from expected");
}

// TASK: 5
void test_toggle_calibration_example(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t status[4] = {12, 1, 15, 10};
    alignas(16) const uint32_t toggle[4] = {6, 3, 15, 10};
    alignas(16) const uint32_t locked[4] = {2, 1, 12, 0};
    alignas(16) uint32_t result[4];
    toggle_calibration(result, status, toggle, locked);
    const uint32_t expected[4] = {8, 3, 12, 0};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The status word at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The status word at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The status word at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The status word at lane 3 is different from expected");
}

void test_toggle_calibration_nothing_locked_is_a_plain_toggle(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t status[4] = {3735928559, 0, 4294967295, 305419896};
    alignas(16) const uint32_t toggle[4] = {269488144, 4294967295, 252645135, 305419896};
    alignas(16) const uint32_t locked[4] = {0, 0, 0, 0};
    alignas(16) uint32_t result[4];
    toggle_calibration(result, status, toggle, locked);
    const uint32_t expected[4] = {3468537599, 4294967295, 4042322160, 0};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The status word at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The status word at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The status word at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The status word at lane 3 is different from expected");
}

void test_toggle_calibration_everything_locked_is_identity(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t status[4] = {3735928559, 0, 4294967295, 252645135};
    alignas(16) const uint32_t toggle[4] = {4294967295, 4294967295, 305419896, 4042322160};
    alignas(16) const uint32_t locked[4] = {4294967295, 4294967295, 4294967295, 4294967295};
    alignas(16) uint32_t result[4];
    toggle_calibration(result, status, toggle, locked);
    const uint32_t expected[4] = {3735928559, 0, 4294967295, 252645135};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The status word at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The status word at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The status word at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The status word at lane 3 is different from expected");
}

void test_toggle_calibration_locks_outside_the_toggle_change_nothing(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t status[4] = {10, 12, 65280, 3405643776};
    alignas(16) const uint32_t toggle[4] = {5, 2, 240, 48879};
    alignas(16) const uint32_t locked[4] = {10, 13, 65295, 4294901760};
    alignas(16) uint32_t result[4];
    toggle_calibration(result, status, toggle, locked);
    const uint32_t expected[4] = {15, 14, 65520, 3405692655};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The status word at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The status word at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The status word at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The status word at lane 3 is different from expected");
}

void test_toggle_calibration_only_unlocked_bits_flip(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t status[4] = {2863311530, 1431655765, 4294901760, 0};
    alignas(16) const uint32_t toggle[4] = {4294967295, 4294967295, 4294967295, 4294967295};
    alignas(16) const uint32_t locked[4] = {65535, 4294901760, 16711935, 4042322160};
    alignas(16) uint32_t result[4];
    toggle_calibration(result, status, toggle, locked);
    const uint32_t expected[4] = {1431677610, 1431677610, 16776960, 252645135};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The status word at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The status word at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The status word at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The status word at lane 3 is different from expected");
}

void test_toggle_calibration_twice_restores(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t status[4] = {3405705229, 65535, 2863311530, 1431655765};
    alignas(16) const uint32_t toggle[4] = {269488144, 4294967295, 1431655765, 1431655765};
    alignas(16) const uint32_t locked[4] = {1048832, 255, 1145324612, 0};
    alignas(16) uint32_t once[4];
    alignas(16) uint32_t result[4];
    toggle_calibration(once, status, toggle, locked);
    toggle_calibration(result, once, toggle, locked);
    const uint32_t expected[4] = {3405705229, 65535, 2863311530, 1431655765};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The status word at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The status word at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The status word at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The status word at lane 3 is different from expected");
}

// TASK: 6
void test_amplify_trace_example(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {1.5f, -2.0f, 0.25f, 96.0f};
    alignas(16) const int32_t gains[4] = {2, 1, 3, -5};
    alignas(16) float result[4];
    amplify_trace(result, trace, gains);
    const float expected[4] = {6.0f, -4.0f, 2.0f, 3.0f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_amplify_trace_zero_gain_is_identity(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {1.5f, -2.25f, 1000.0f, 0.0078125f};
    alignas(16) const int32_t gains[4] = {0, 0, 0, 0};
    alignas(16) float result[4];
    amplify_trace(result, trace, gains);
    const float expected[4] = {1.5f, -2.25f, 1000.0f, 0.0078125f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_amplify_trace_doubling_chain(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    alignas(16) const int32_t gains[4] = {1, 2, 3, 10};
    alignas(16) float result[4];
    amplify_trace(result, trace, gains);
    const float expected[4] = {2.0f, 4.0f, 8.0f, 1024.0f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_amplify_trace_negative_gains_divide(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {64.0f, -8.0f, 1.0f, 0.5f};
    alignas(16) const int32_t gains[4] = {-6, -3, -1, -9};
    alignas(16) float result[4];
    amplify_trace(result, trace, gains);
    const float expected[4] = {1.0f, -1.0f, 0.5f, 0.0009765625f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

void test_amplify_trace_preserves_sign_and_fraction(void) {
    TEST_IGNORE();
    alignas(16) const float trace[4] = {1.25f, -7.5f, 0.375f, 100.0f};
    alignas(16) const int32_t gains[4] = {3, -2, 5, 1};
    alignas(16) float result[4];
    amplify_trace(result, trace, gains);
    const float expected[4] = {10.0f, -1.875f, 12.0f, 200.0f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_rectify_trace_example);
    RUN_TEST(test_rectify_trace_all_negative);
    RUN_TEST(test_rectify_trace_all_positive_unchanged);
    RUN_TEST(test_rectify_trace_negative_zero);
    RUN_TEST(test_rectify_trace_large_magnitudes);
    RUN_TEST(test_reading_scale_example);
    RUN_TEST(test_reading_scale_powers_of_two);
    RUN_TEST(test_reading_scale_small_readings);
    RUN_TEST(test_reading_scale_ignores_fraction);
    RUN_TEST(test_reading_scale_negative_readings);
    RUN_TEST(test_coarsen_displacements_example);
    RUN_TEST(test_coarsen_displacements_shift_zero);
    RUN_TEST(test_coarsen_displacements_rounds_toward_negative_infinity);
    RUN_TEST(test_coarsen_displacements_keeps_sign_with_large_shift);
    RUN_TEST(test_gate_channels_example);
    RUN_TEST(test_gate_channels_no_faults);
    RUN_TEST(test_gate_channels_all_faulty);
    RUN_TEST(test_gate_channels_faults_only_silence_enabled_channels);
    RUN_TEST(test_toggle_calibration_example);
    RUN_TEST(test_toggle_calibration_nothing_locked_is_a_plain_toggle);
    RUN_TEST(test_toggle_calibration_everything_locked_is_identity);
    RUN_TEST(test_toggle_calibration_locks_outside_the_toggle_change_nothing);
    RUN_TEST(test_toggle_calibration_only_unlocked_bits_flip);
    RUN_TEST(test_toggle_calibration_twice_restores);
    RUN_TEST(test_amplify_trace_example);
    RUN_TEST(test_amplify_trace_zero_gain_is_identity);
    RUN_TEST(test_amplify_trace_doubling_chain);
    RUN_TEST(test_amplify_trace_negative_gains_divide);
    RUN_TEST(test_amplify_trace_preserves_sign_and_fraction);
    return UNITY_END();
}
