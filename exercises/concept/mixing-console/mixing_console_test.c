#include "vendor/unity.h"

#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern void mix_tracks(int16_t result[8], const int16_t track_a[8], const int16_t track_b[8]);
extern void remove_bleed(int16_t result[8], const int16_t track[8], const int16_t bleed[8]);
extern void combine_meters(uint8_t result[16], const uint8_t meter_a[16], const uint8_t meter_b[16]);
extern void apply_fade(int16_t result[], const int16_t track[], const int16_t gains[], size_t n);
extern void attenuate_track(int32_t result[], const int16_t samples[], const int32_t divisor[4], size_t n);

void setUp(void) {
}

void tearDown(void) {
}

// TASK: 1
void test_mix_tracks_example(void) {
    alignas(16) const int16_t track_a[8] = {10000, 30000, 20000, -30000, -20000, -100, 100, 0};
    alignas(16) const int16_t track_b[8] = {5000, 5000, 20000, -5000, -20000, 100, -100, 0};
    alignas(16) int16_t result[8];
    mix_tracks(result, track_a, track_b);
    const int16_t expected[8] = {15000, 32767, 32767, -32768, -32768, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_mix_tracks_all_zeros(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track_a[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    alignas(16) const int16_t track_b[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    alignas(16) int16_t result[8];
    mix_tracks(result, track_a, track_b);
    const int16_t expected[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_mix_tracks_no_saturation(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track_a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    alignas(16) const int16_t track_b[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    alignas(16) int16_t result[8];
    mix_tracks(result, track_a, track_b);
    const int16_t expected[8] = {11, 22, 33, 44, 55, 66, 77, 88};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_mix_tracks_saturates_positive(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track_a[8] = {32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767};
    alignas(16) const int16_t track_b[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    alignas(16) int16_t result[8];
    mix_tracks(result, track_a, track_b);
    const int16_t expected[8] = {32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_mix_tracks_saturates_negative(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track_a[8] = {-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768};
    alignas(16) const int16_t track_b[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    alignas(16) int16_t result[8];
    mix_tracks(result, track_a, track_b);
    const int16_t expected[8] = {-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_mix_tracks_reaches_max_without_clamping(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track_a[8] = {16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383};
    alignas(16) const int16_t track_b[8] = {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384};
    alignas(16) int16_t result[8];
    mix_tracks(result, track_a, track_b);
    const int16_t expected[8] = {32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_mix_tracks_one_track_silent(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track_a[8] = {7, 8, 9, 10, 11, 12, 13, 14};
    alignas(16) const int16_t track_b[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    alignas(16) int16_t result[8];
    mix_tracks(result, track_a, track_b);
    const int16_t expected[8] = {7, 8, 9, 10, 11, 12, 13, 14};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_mix_tracks_mixed_extremes(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track_a[8] = {32767, -32768, 100, -100, 0, 16384, -16384, 1};
    alignas(16) const int16_t track_b[8] = {1, -1, -100, 100, 0, 16384, -16384, -1};
    alignas(16) int16_t result[8];
    mix_tracks(result, track_a, track_b);
    const int16_t expected[8] = {32767, -32768, 0, 0, 0, 32767, -32768, 0};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

// TASK: 2
void test_remove_bleed_example(void) {
    TEST_IGNORE();
    const char x1 = 'X';
    (void)x1;
    alignas(2) int16_t result[8];
    alignas(16) const int16_t track[8] = {10000, -30000, 5000, 32767, 0, 200, -200, 15000};
    const char x2 = 'X';
    (void)x2;
    alignas(2) const int16_t bleed[8] = {2000, 5000, 5000, -5, 0, 300, 300, 5000};
    remove_bleed(result, track, bleed);
    const int16_t expected[8] = {8000, -32768, 0, 32767, 0, -100, -500, 10000};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_remove_bleed_all_zeros(void) {
    TEST_IGNORE();
    const char x1 = 'X';
    (void)x1;
    alignas(2) int16_t result[8];
    alignas(16) const int16_t track[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    const char x2 = 'X';
    (void)x2;
    alignas(2) const int16_t bleed[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    remove_bleed(result, track, bleed);
    const int16_t expected[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_remove_bleed_no_saturation(void) {
    TEST_IGNORE();
    const char x1 = 'X';
    (void)x1;
    alignas(2) int16_t result[8];
    alignas(16) const int16_t track[8] = {100, 200, 300, 400, 500, 600, 700, 800};
    const char x2 = 'X';
    (void)x2;
    alignas(2) const int16_t bleed[8] = {50, 50, 50, 50, 50, 50, 50, 50};
    remove_bleed(result, track, bleed);
    const int16_t expected[8] = {50, 150, 250, 350, 450, 550, 650, 750};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_remove_bleed_saturates_negative(void) {
    TEST_IGNORE();
    const char x1 = 'X';
    (void)x1;
    alignas(2) int16_t result[8];
    alignas(16) const int16_t track[8] = {-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768};
    const char x2 = 'X';
    (void)x2;
    alignas(2) const int16_t bleed[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    remove_bleed(result, track, bleed);
    const int16_t expected[8] = {-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_remove_bleed_saturates_positive(void) {
    TEST_IGNORE();
    const char x1 = 'X';
    (void)x1;
    alignas(2) int16_t result[8];
    alignas(16) const int16_t track[8] = {32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767};
    const char x2 = 'X';
    (void)x2;
    alignas(2) const int16_t bleed[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    remove_bleed(result, track, bleed);
    const int16_t expected[8] = {32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_remove_bleed_cancels_to_zero(void) {
    TEST_IGNORE();
    const char x1 = 'X';
    (void)x1;
    alignas(2) int16_t result[8];
    alignas(16) const int16_t track[8] = {5, 10, 15, 20, 25, 30, 35, 40};
    const char x2 = 'X';
    (void)x2;
    alignas(2) const int16_t bleed[8] = {5, 10, 15, 20, 25, 30, 35, 40};
    remove_bleed(result, track, bleed);
    const int16_t expected[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_remove_bleed_mixed_extremes(void) {
    TEST_IGNORE();
    const char x1 = 'X';
    (void)x1;
    alignas(2) int16_t result[8];
    alignas(16) const int16_t track[8] = {0, 0, -100, 100, 32767, -32768, 1000, -1000};
    const char x2 = 'X';
    (void)x2;
    alignas(2) const int16_t bleed[8] = {32767, -32768, 100, -100, -1, 1, 500, -500};
    remove_bleed(result, track, bleed);
    const int16_t expected[8] = {-32767, 32767, -200, 200, 32767, -32768, 500, -500};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

void test_remove_bleed_goes_negative(void) {
    TEST_IGNORE();
    const char x1 = 'X';
    (void)x1;
    alignas(2) int16_t result[8];
    alignas(16) const int16_t track[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    const char x2 = 'X';
    (void)x2;
    alignas(2) const int16_t bleed[8] = {100, 100, 100, 100, 100, 100, 100, 100};
    remove_bleed(result, track, bleed);
    const int16_t expected[8] = {-90, -80, -70, -60, -50, -40, -30, -20};
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[0], result[0], "The 16-bit sample at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[1], result[1], "The 16-bit sample at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[2], result[2], "The 16-bit sample at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[3], result[3], "The 16-bit sample at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[4], result[4], "The 16-bit sample at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[5], result[5], "The 16-bit sample at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[6], result[6], "The 16-bit sample at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[7], result[7], "The 16-bit sample at lane 7 is different from expected");
}

// TASK: 3
void test_combine_meters_example(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t meter_a[16] = {200, 100, 50, 255, 0, 128, 10, 240, 1, 2, 3, 4, 5, 6, 7, 8};
    alignas(16) const uint8_t meter_b[16] = {100, 100, 200, 1, 0, 128, 10, 20, 1, 2, 3, 4, 5, 6, 7, 8};
    alignas(16) uint8_t result[16];
    combine_meters(result, meter_a, meter_b);
    const uint8_t expected[16] = {255, 200, 250, 255, 0, 255, 20, 255, 2, 4, 6, 8, 10, 12, 14, 16};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The 8-bit value at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The 8-bit value at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The 8-bit value at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The 8-bit value at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The 8-bit value at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The 8-bit value at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The 8-bit value at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The 8-bit value at lane 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The 8-bit value at lane 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The 8-bit value at lane 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The 8-bit value at lane 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The 8-bit value at lane 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The 8-bit value at lane 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The 8-bit value at lane 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The 8-bit value at lane 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The 8-bit value at lane 15 is different from expected");
}

void test_combine_meters_all_zeros(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t meter_a[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    alignas(16) const uint8_t meter_b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    alignas(16) uint8_t result[16];
    combine_meters(result, meter_a, meter_b);
    const uint8_t expected[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The 8-bit value at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The 8-bit value at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The 8-bit value at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The 8-bit value at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The 8-bit value at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The 8-bit value at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The 8-bit value at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The 8-bit value at lane 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The 8-bit value at lane 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The 8-bit value at lane 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The 8-bit value at lane 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The 8-bit value at lane 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The 8-bit value at lane 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The 8-bit value at lane 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The 8-bit value at lane 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The 8-bit value at lane 15 is different from expected");
}

void test_combine_meters_no_saturation(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t meter_a[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    alignas(16) const uint8_t meter_b[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    alignas(16) uint8_t result[16];
    combine_meters(result, meter_a, meter_b);
    const uint8_t expected[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The 8-bit value at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The 8-bit value at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The 8-bit value at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The 8-bit value at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The 8-bit value at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The 8-bit value at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The 8-bit value at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The 8-bit value at lane 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The 8-bit value at lane 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The 8-bit value at lane 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The 8-bit value at lane 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The 8-bit value at lane 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The 8-bit value at lane 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The 8-bit value at lane 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The 8-bit value at lane 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The 8-bit value at lane 15 is different from expected");
}

void test_combine_meters_all_saturate(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t meter_a[16] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200};
    alignas(16) const uint8_t meter_b[16] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
    alignas(16) uint8_t result[16];
    combine_meters(result, meter_a, meter_b);
    const uint8_t expected[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The 8-bit value at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The 8-bit value at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The 8-bit value at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The 8-bit value at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The 8-bit value at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The 8-bit value at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The 8-bit value at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The 8-bit value at lane 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The 8-bit value at lane 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The 8-bit value at lane 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The 8-bit value at lane 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The 8-bit value at lane 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The 8-bit value at lane 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The 8-bit value at lane 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The 8-bit value at lane 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The 8-bit value at lane 15 is different from expected");
}

void test_combine_meters_reaches_max_without_clamping(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t meter_a[16] = {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128};
    alignas(16) const uint8_t meter_b[16] = {127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127};
    alignas(16) uint8_t result[16];
    combine_meters(result, meter_a, meter_b);
    const uint8_t expected[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The 8-bit value at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The 8-bit value at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The 8-bit value at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The 8-bit value at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The 8-bit value at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The 8-bit value at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The 8-bit value at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The 8-bit value at lane 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The 8-bit value at lane 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The 8-bit value at lane 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The 8-bit value at lane 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The 8-bit value at lane 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The 8-bit value at lane 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The 8-bit value at lane 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The 8-bit value at lane 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The 8-bit value at lane 15 is different from expected");
}

void test_combine_meters_just_overflows(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t meter_a[16] = {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128};
    alignas(16) const uint8_t meter_b[16] = {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128};
    alignas(16) uint8_t result[16];
    combine_meters(result, meter_a, meter_b);
    const uint8_t expected[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The 8-bit value at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The 8-bit value at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The 8-bit value at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The 8-bit value at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The 8-bit value at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The 8-bit value at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The 8-bit value at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The 8-bit value at lane 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The 8-bit value at lane 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The 8-bit value at lane 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The 8-bit value at lane 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The 8-bit value at lane 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The 8-bit value at lane 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The 8-bit value at lane 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The 8-bit value at lane 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The 8-bit value at lane 15 is different from expected");
}

void test_combine_meters_one_meter_dark(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t meter_a[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    alignas(16) const uint8_t meter_b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    alignas(16) uint8_t result[16];
    combine_meters(result, meter_a, meter_b);
    const uint8_t expected[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The 8-bit value at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The 8-bit value at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The 8-bit value at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The 8-bit value at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The 8-bit value at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The 8-bit value at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The 8-bit value at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The 8-bit value at lane 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The 8-bit value at lane 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The 8-bit value at lane 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The 8-bit value at lane 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The 8-bit value at lane 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The 8-bit value at lane 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The 8-bit value at lane 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The 8-bit value at lane 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The 8-bit value at lane 15 is different from expected");
}

void test_combine_meters_mixed(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t meter_a[16] = {250, 5, 128, 200, 255, 1, 100, 150, 0, 255, 200, 55, 128, 128, 1, 254};
    alignas(16) const uint8_t meter_b[16] = {10, 250, 128, 55, 0, 254, 100, 150, 0, 1, 55, 200, 127, 128, 254, 1};
    alignas(16) uint8_t result[16];
    combine_meters(result, meter_a, meter_b);
    const uint8_t expected[16] = {255, 255, 255, 255, 255, 255, 200, 255, 0, 255, 255, 255, 255, 255, 255, 255};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The 8-bit value at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The 8-bit value at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The 8-bit value at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The 8-bit value at lane 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The 8-bit value at lane 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The 8-bit value at lane 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The 8-bit value at lane 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The 8-bit value at lane 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The 8-bit value at lane 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The 8-bit value at lane 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The 8-bit value at lane 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The 8-bit value at lane 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The 8-bit value at lane 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The 8-bit value at lane 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The 8-bit value at lane 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The 8-bit value at lane 15 is different from expected");
}

// TASK: 4
void test_apply_fade_example(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track[8] = {20000, 20000, 20000, 20000, -20000, -20000, -20000, -20000};
    alignas(16) const int16_t gains[8] = {32767, 24576, 16384, 8192, 32767, 24576, 16384, 8192};
    alignas(16) int16_t result[8];
    apply_fade(result, track, gains, 8);
    const int16_t expected[8] = {9999, 7500, 5000, 2500, -10000, -7500, -5000, -2500};
    TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of scaled samples is different from expected");
}

void test_apply_fade_zero_gain(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track[8] = {1000, -1000, 2000, -2000, 3000, -3000, 32767, -32768};
    alignas(16) const int16_t gains[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    alignas(16) int16_t result[8];
    apply_fade(result, track, gains, 8);
    const int16_t expected[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of scaled samples is different from expected");
}

void test_apply_fade_quarter_gain(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track[8] = {4, 40, 400, 4000, -4, -40, -400, -4000};
    alignas(16) const int16_t gains[8] = {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384};
    alignas(16) int16_t result[8];
    apply_fade(result, track, gains, 8);
    const int16_t expected[8] = {1, 10, 100, 1000, -1, -10, -100, -1000};
    TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of scaled samples is different from expected");
}

void test_apply_fade_rounds_toward_negative_infinity(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track[8] = {-7, -7, -7, -7, 7, 7, 7, 7};
    alignas(16) const int16_t gains[8] = {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384};
    alignas(16) int16_t result[8];
    apply_fade(result, track, gains, 8);
    const int16_t expected[8] = {-2, -2, -2, -2, 1, 1, 1, 1};
    TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of scaled samples is different from expected");
}

void test_apply_fade_near_half_gain(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track[8] = {32767, 16384, 8192, 4096, -32768, -16384, -8192, -4096};
    alignas(16) const int16_t gains[8] = {32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767};
    alignas(16) int16_t result[8];
    apply_fade(result, track, gains, 8);
    const int16_t expected[8] = {16383, 8191, 4095, 2047, -16384, -8192, -4096, -2048};
    TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of scaled samples is different from expected");
}

void test_apply_fade_small_products_vanish(void) {
    TEST_IGNORE();
    alignas(16) const int16_t track[8] = {2, 2, 2, 2, 2, 2, 2, 2};
    alignas(16) const int16_t gains[8] = {32767, 16384, 8192, 4096, 2048, 1024, 512, 1};
    alignas(16) int16_t result[8];
    apply_fade(result, track, gains, 8);
    const int16_t expected[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of scaled samples is different from expected");
}

void test_apply_fade_two_blocks(void) {
    TEST_IGNORE();
    alignas(16)
        const int16_t track[16] = {16384, -16384, 8192, -8192, 30000, -30000, 10000, -10000, 1, -1, 100, -100, 25000, -25000, 5, -5};
    alignas(16) const int16_t gains[16] = {16384, 16384, 32767, 32767, 8192,  8192,  16384, 16384,
                                           32767, 32767, 32767, 32767, 24576, 24576, 16384, 16384};
    alignas(16) int16_t result[16];
    apply_fade(result, track, gains, 16);
    const int16_t expected[16] = {4096, -4096, 4095, -4096, 3750, -3750, 2500, -2500, 0, -1, 49, -50, 9375, -9375, 1, -2};
    TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of scaled samples is different from expected");
}

// TASK: 5
void test_attenuate_track_example(void) {
    TEST_IGNORE();
    alignas(16) const int16_t samples[8] = {300, 150, 90, -120, 100, 50, -50, 7};
    alignas(16) const int32_t divisor[4] = {3, 3, 3, 3};
    alignas(16) int32_t result[8];
    attenuate_track(result, samples, divisor, 8);
    const int32_t expected[8] = {100, 50, 30, -40, 33, 16, -16, 2};
    TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of attenuated samples is different from expected");
}

void test_attenuate_track_divide_by_one(void) {
    TEST_IGNORE();
    alignas(16) const int16_t samples[4] = {5, -5, 1000, -1000};
    alignas(16) const int32_t divisor[4] = {1, 1, 1, 1};
    alignas(16) int32_t result[4];
    attenuate_track(result, samples, divisor, 4);
    const int32_t expected[4] = {5, -5, 1000, -1000};
    TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of attenuated samples is different from expected");
}

void test_attenuate_track_exact_quotients(void) {
    TEST_IGNORE();
    alignas(16) const int16_t samples[4] = {100, 250, 1000, -500};
    alignas(16) const int32_t divisor[4] = {10, 10, 10, 10};
    alignas(16) int32_t result[4];
    attenuate_track(result, samples, divisor, 4);
    const int32_t expected[4] = {10, 25, 100, -50};
    TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of attenuated samples is different from expected");
}

void test_attenuate_track_truncates_toward_zero(void) {
    TEST_IGNORE();
    alignas(16) const int16_t samples[4] = {7, -7, 9, -9};
    alignas(16) const int32_t divisor[4] = {2, 2, 2, 2};
    alignas(16) int32_t result[4];
    attenuate_track(result, samples, divisor, 4);
    const int32_t expected[4] = {3, -3, 4, -4};
    TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of attenuated samples is different from expected");
}

void test_attenuate_track_fractional_by_seven(void) {
    TEST_IGNORE();
    alignas(16) const int16_t samples[8] = {100, -100, 50, -50, 1, -1, 1000, -1000};
    alignas(16) const int32_t divisor[4] = {7, 7, 7, 7};
    alignas(16) int32_t result[8];
    attenuate_track(result, samples, divisor, 8);
    const int32_t expected[8] = {14, -14, 7, -7, 0, 0, 142, -142};
    TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of attenuated samples is different from expected");
}

void test_attenuate_track_near_sample_limits(void) {
    TEST_IGNORE();
    alignas(16) const int16_t samples[4] = {32767, -32768, 16384, -16384};
    alignas(16) const int32_t divisor[4] = {2, 2, 2, 2};
    alignas(16) int32_t result[4];
    attenuate_track(result, samples, divisor, 4);
    const int32_t expected[4] = {16383, -16384, 8192, -8192};
    TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of attenuated samples is different from expected");
}

void test_attenuate_track_by_five(void) {
    TEST_IGNORE();
    alignas(16) const int16_t samples[8] = {12, -12, 5, -5, 17, -17, 100, -100};
    alignas(16) const int32_t divisor[4] = {5, 5, 5, 5};
    alignas(16) int32_t result[8];
    attenuate_track(result, samples, divisor, 8);
    const int32_t expected[8] = {2, -2, 1, -1, 3, -3, 20, -20};
    TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of attenuated samples is different from expected");
}

void test_attenuate_track_all_silent(void) {
    TEST_IGNORE();
    alignas(16) const int16_t samples[4] = {0, 0, 0, 0};
    alignas(16) const int32_t divisor[4] = {9, 9, 9, 9};
    alignas(16) int32_t result[4];
    attenuate_track(result, samples, divisor, 4);
    const int32_t expected[4] = {0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected),
                                          "The sequence of attenuated samples is different from expected");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_mix_tracks_example);
    RUN_TEST(test_mix_tracks_all_zeros);
    RUN_TEST(test_mix_tracks_no_saturation);
    RUN_TEST(test_mix_tracks_saturates_positive);
    RUN_TEST(test_mix_tracks_saturates_negative);
    RUN_TEST(test_mix_tracks_reaches_max_without_clamping);
    RUN_TEST(test_mix_tracks_one_track_silent);
    RUN_TEST(test_mix_tracks_mixed_extremes);
    RUN_TEST(test_remove_bleed_example);
    RUN_TEST(test_remove_bleed_all_zeros);
    RUN_TEST(test_remove_bleed_no_saturation);
    RUN_TEST(test_remove_bleed_saturates_negative);
    RUN_TEST(test_remove_bleed_saturates_positive);
    RUN_TEST(test_remove_bleed_cancels_to_zero);
    RUN_TEST(test_remove_bleed_mixed_extremes);
    RUN_TEST(test_remove_bleed_goes_negative);
    RUN_TEST(test_combine_meters_example);
    RUN_TEST(test_combine_meters_all_zeros);
    RUN_TEST(test_combine_meters_no_saturation);
    RUN_TEST(test_combine_meters_all_saturate);
    RUN_TEST(test_combine_meters_reaches_max_without_clamping);
    RUN_TEST(test_combine_meters_just_overflows);
    RUN_TEST(test_combine_meters_one_meter_dark);
    RUN_TEST(test_combine_meters_mixed);
    RUN_TEST(test_apply_fade_example);
    RUN_TEST(test_apply_fade_zero_gain);
    RUN_TEST(test_apply_fade_quarter_gain);
    RUN_TEST(test_apply_fade_rounds_toward_negative_infinity);
    RUN_TEST(test_apply_fade_near_half_gain);
    RUN_TEST(test_apply_fade_small_products_vanish);
    RUN_TEST(test_apply_fade_two_blocks);
    RUN_TEST(test_attenuate_track_example);
    RUN_TEST(test_attenuate_track_divide_by_one);
    RUN_TEST(test_attenuate_track_exact_quotients);
    RUN_TEST(test_attenuate_track_truncates_toward_zero);
    RUN_TEST(test_attenuate_track_fractional_by_seven);
    RUN_TEST(test_attenuate_track_near_sample_limits);
    RUN_TEST(test_attenuate_track_by_five);
    RUN_TEST(test_attenuate_track_all_silent);
    return UNITY_END();
}
