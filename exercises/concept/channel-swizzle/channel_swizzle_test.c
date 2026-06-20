#include "vendor/unity.h"

#include <stdalign.h>
#include <stdint.h>

extern void to_display_order(uint8_t result[], const uint8_t pixels[], uint64_t block_count);
extern void fill_region(uint8_t result[], const uint8_t color[4], uint64_t block_count);
extern void weave_scanlines(uint8_t result[32], const uint8_t first[16], const uint8_t second[16]);
extern void pack_samples(uint8_t result[16], const int16_t first[8], const int16_t second[8]);
extern void split_coordinates(float xs[4], float ys[4], const float first[4], const float second[4]);

void setUp(void) {
}

void tearDown(void) {
}

// TASK: 1
void test_display_order_example_two_blocks(void) {
    alignas(16) const uint8_t pixels[32] = {200, 64, 32, 255, 10, 20, 30, 40, 0, 0,  0,  255, 12, 34, 56, 78,
                                            1,   2,  3,  4,   5,  6,  7,  8,  9, 10, 11, 12,  13, 14, 15, 16};
    alignas(16) uint8_t result[32];
    to_display_order(result, pixels, 2);
    const uint8_t expected[32] = {32, 64, 200, 255, 30, 20, 10, 40, 0,  0,  0, 255, 56, 34, 12, 78,
                                  3,  2,  1,   4,   7,  6,  5,  8,  11, 10, 9, 12,  15, 14, 13, 16};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The converted byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The converted byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The converted byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The converted byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The converted byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The converted byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The converted byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The converted byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The converted byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The converted byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The converted byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The converted byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The converted byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The converted byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The converted byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The converted byte at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The converted byte at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The converted byte at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The converted byte at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The converted byte at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The converted byte at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The converted byte at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The converted byte at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The converted byte at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The converted byte at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The converted byte at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The converted byte at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The converted byte at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The converted byte at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The converted byte at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The converted byte at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The converted byte at index 31 is different from expected");
}

void test_display_order_single_block(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t pixels[16] = {200, 64, 32, 255, 10, 20, 30, 40, 0, 0, 0, 255, 12, 34, 56, 78};
    alignas(16) uint8_t result[16];
    to_display_order(result, pixels, 1);
    const uint8_t expected[16] = {32, 64, 200, 255, 30, 20, 10, 40, 0, 0, 0, 255, 56, 34, 12, 78};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The converted byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The converted byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The converted byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The converted byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The converted byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The converted byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The converted byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The converted byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The converted byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The converted byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The converted byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The converted byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The converted byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The converted byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The converted byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The converted byte at index 15 is different from expected");
}

void test_display_order_three_blocks(void) {
    TEST_IGNORE();
    alignas(16)
        const uint8_t pixels[48] = {200, 64, 32, 255, 10, 20, 30, 40, 0,   0, 0, 255, 12, 34,  56, 78,  1, 2, 3,   4,  5,   6,   7,   8,
                                    9,   10, 11, 12,  13, 14, 15, 16, 255, 0, 0, 255, 0,  255, 0,  128, 0, 0, 255, 64, 100, 110, 120, 130};
    alignas(16) uint8_t result[48];
    to_display_order(result, pixels, 3);
    const uint8_t expected[48] = {32, 64, 200, 255, 30, 20, 10, 40, 0, 0, 0,   255, 56, 34,  12, 78,  3,   2, 1, 4,  7,   6,   5,   8,
                                  11, 10, 9,   12,  15, 14, 13, 16, 0, 0, 255, 255, 0,  255, 0,  128, 255, 0, 0, 64, 120, 110, 100, 130};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The converted byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The converted byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The converted byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The converted byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The converted byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The converted byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The converted byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The converted byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The converted byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The converted byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The converted byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The converted byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The converted byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The converted byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The converted byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The converted byte at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The converted byte at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The converted byte at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The converted byte at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The converted byte at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The converted byte at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The converted byte at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The converted byte at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The converted byte at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The converted byte at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The converted byte at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The converted byte at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The converted byte at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The converted byte at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The converted byte at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The converted byte at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The converted byte at index 31 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[32], result[32], "The converted byte at index 32 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[33], result[33], "The converted byte at index 33 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[34], result[34], "The converted byte at index 34 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[35], result[35], "The converted byte at index 35 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[36], result[36], "The converted byte at index 36 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[37], result[37], "The converted byte at index 37 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[38], result[38], "The converted byte at index 38 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[39], result[39], "The converted byte at index 39 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[40], result[40], "The converted byte at index 40 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[41], result[41], "The converted byte at index 41 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[42], result[42], "The converted byte at index 42 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[43], result[43], "The converted byte at index 43 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[44], result[44], "The converted byte at index 44 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[45], result[45], "The converted byte at index 45 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[46], result[46], "The converted byte at index 46 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[47], result[47], "The converted byte at index 47 is different from expected");
}

void test_display_order_red_equals_blue_unchanged(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t pixels[32] = {50, 60, 50, 255, 0, 9, 0, 1, 128, 7, 128, 64, 200, 1, 200, 2,
                                            50, 60, 50, 255, 0, 9, 0, 1, 128, 7, 128, 64, 200, 1, 200, 2};
    alignas(16) uint8_t result[32];
    to_display_order(result, pixels, 2);
    const uint8_t expected[32] = {50, 60, 50, 255, 0, 9, 0, 1, 128, 7, 128, 64, 200, 1, 200, 2,
                                  50, 60, 50, 255, 0, 9, 0, 1, 128, 7, 128, 64, 200, 1, 200, 2};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The converted byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The converted byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The converted byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The converted byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The converted byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The converted byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The converted byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The converted byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The converted byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The converted byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The converted byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The converted byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The converted byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The converted byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The converted byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The converted byte at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The converted byte at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The converted byte at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The converted byte at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The converted byte at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The converted byte at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The converted byte at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The converted byte at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The converted byte at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The converted byte at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The converted byte at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The converted byte at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The converted byte at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The converted byte at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The converted byte at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The converted byte at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The converted byte at index 31 is different from expected");
}

// TASK: 2
void test_fill_region_example_two_blocks(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t color[4] = {18, 52, 86, 120};
    alignas(16) uint8_t result[32];
    fill_region(result, color, 2);
    const uint8_t expected[32] = {18, 52, 86, 120, 18, 52, 86, 120, 18, 52, 86, 120, 18, 52, 86, 120,
                                  18, 52, 86, 120, 18, 52, 86, 120, 18, 52, 86, 120, 18, 52, 86, 120};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The filled byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The filled byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The filled byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The filled byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The filled byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The filled byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The filled byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The filled byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The filled byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The filled byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The filled byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The filled byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The filled byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The filled byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The filled byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The filled byte at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The filled byte at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The filled byte at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The filled byte at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The filled byte at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The filled byte at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The filled byte at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The filled byte at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The filled byte at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The filled byte at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The filled byte at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The filled byte at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The filled byte at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The filled byte at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The filled byte at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The filled byte at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The filled byte at index 31 is different from expected");
}

void test_fill_region_single_block(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t color[4] = {1, 2, 3, 4};
    alignas(16) uint8_t result[16];
    fill_region(result, color, 1);
    const uint8_t expected[16] = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The filled byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The filled byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The filled byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The filled byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The filled byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The filled byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The filled byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The filled byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The filled byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The filled byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The filled byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The filled byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The filled byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The filled byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The filled byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The filled byte at index 15 is different from expected");
}

void test_fill_region_three_blocks_transparent_black(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t color[4] = {0, 0, 0, 0};
    alignas(16) uint8_t result[48];
    fill_region(result, color, 3);
    const uint8_t expected[48] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The filled byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The filled byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The filled byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The filled byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The filled byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The filled byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The filled byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The filled byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The filled byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The filled byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The filled byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The filled byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The filled byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The filled byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The filled byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The filled byte at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The filled byte at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The filled byte at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The filled byte at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The filled byte at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The filled byte at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The filled byte at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The filled byte at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The filled byte at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The filled byte at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The filled byte at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The filled byte at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The filled byte at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The filled byte at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The filled byte at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The filled byte at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The filled byte at index 31 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[32], result[32], "The filled byte at index 32 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[33], result[33], "The filled byte at index 33 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[34], result[34], "The filled byte at index 34 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[35], result[35], "The filled byte at index 35 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[36], result[36], "The filled byte at index 36 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[37], result[37], "The filled byte at index 37 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[38], result[38], "The filled byte at index 38 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[39], result[39], "The filled byte at index 39 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[40], result[40], "The filled byte at index 40 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[41], result[41], "The filled byte at index 41 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[42], result[42], "The filled byte at index 42 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[43], result[43], "The filled byte at index 43 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[44], result[44], "The filled byte at index 44 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[45], result[45], "The filled byte at index 45 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[46], result[46], "The filled byte at index 46 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[47], result[47], "The filled byte at index 47 is different from expected");
}

void test_fill_region_opaque_white_two_blocks(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t color[4] = {255, 255, 255, 255};
    alignas(16) uint8_t result[32];
    fill_region(result, color, 2);
    const uint8_t expected[32] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
                                  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The filled byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The filled byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The filled byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The filled byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The filled byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The filled byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The filled byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The filled byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The filled byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The filled byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The filled byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The filled byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The filled byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The filled byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The filled byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The filled byte at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The filled byte at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The filled byte at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The filled byte at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The filled byte at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The filled byte at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The filled byte at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The filled byte at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The filled byte at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The filled byte at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The filled byte at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The filled byte at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The filled byte at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The filled byte at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The filled byte at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The filled byte at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The filled byte at index 31 is different from expected");
}

// TASK: 3
void test_weave_scanlines_example(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t first[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    alignas(16) const uint8_t second[16] = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115};
    alignas(16) uint8_t result[32];
    weave_scanlines(result, first, second);
    const uint8_t expected[32] = {0, 100, 1, 101, 2,  102, 3,  103, 4,  104, 5,  105, 6,  106, 7,  107,
                                  8, 108, 9, 109, 10, 110, 11, 111, 12, 112, 13, 113, 14, 114, 15, 115};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The woven sample at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The woven sample at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The woven sample at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The woven sample at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The woven sample at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The woven sample at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The woven sample at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The woven sample at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The woven sample at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The woven sample at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The woven sample at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The woven sample at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The woven sample at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The woven sample at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The woven sample at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The woven sample at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The woven sample at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The woven sample at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The woven sample at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The woven sample at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The woven sample at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The woven sample at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The woven sample at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The woven sample at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The woven sample at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The woven sample at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The woven sample at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The woven sample at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The woven sample at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The woven sample at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The woven sample at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The woven sample at index 31 is different from expected");
}

void test_weave_scanlines_alternating_extremes(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t first[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    alignas(16) const uint8_t second[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    alignas(16) uint8_t result[32];
    weave_scanlines(result, first, second);
    const uint8_t expected[32] = {0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255,
                                  0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The woven sample at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The woven sample at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The woven sample at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The woven sample at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The woven sample at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The woven sample at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The woven sample at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The woven sample at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The woven sample at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The woven sample at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The woven sample at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The woven sample at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The woven sample at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The woven sample at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The woven sample at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The woven sample at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The woven sample at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The woven sample at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The woven sample at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The woven sample at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The woven sample at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The woven sample at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The woven sample at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The woven sample at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The woven sample at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The woven sample at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The woven sample at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The woven sample at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The woven sample at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The woven sample at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The woven sample at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The woven sample at index 31 is different from expected");
}

void test_weave_scanlines_high_half_distinct(void) {
    TEST_IGNORE();
    alignas(16) const uint8_t first[16] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    alignas(16) const uint8_t second[16] = {200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215};
    alignas(16) uint8_t result[32];
    weave_scanlines(result, first, second);
    const uint8_t expected[32] = {10, 200, 11, 201, 12, 202, 13, 203, 14, 204, 15, 205, 16, 206, 17, 207,
                                  18, 208, 19, 209, 20, 210, 21, 211, 22, 212, 23, 213, 24, 214, 25, 215};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The woven sample at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The woven sample at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The woven sample at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The woven sample at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The woven sample at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The woven sample at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The woven sample at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The woven sample at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The woven sample at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The woven sample at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The woven sample at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The woven sample at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The woven sample at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The woven sample at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The woven sample at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The woven sample at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The woven sample at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The woven sample at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The woven sample at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The woven sample at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The woven sample at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The woven sample at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The woven sample at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The woven sample at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The woven sample at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The woven sample at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The woven sample at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The woven sample at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The woven sample at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The woven sample at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The woven sample at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The woven sample at index 31 is different from expected");
}

// TASK: 4
void test_pack_samples_example(void) {
    TEST_IGNORE();
    alignas(16) const int16_t first[8] = {300, -5, 128, 255, 0, 400, 64, 200};
    alignas(16) const int16_t second[8] = {255, 256, -1, 100, 50, 1000, 7, 0};
    alignas(16) uint8_t result[16];
    pack_samples(result, first, second);
    const uint8_t expected[16] = {255, 0, 128, 255, 0, 255, 64, 200, 255, 255, 0, 100, 50, 255, 7, 0};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The packed sample at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The packed sample at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The packed sample at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The packed sample at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The packed sample at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The packed sample at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The packed sample at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The packed sample at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The packed sample at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The packed sample at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The packed sample at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The packed sample at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The packed sample at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The packed sample at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The packed sample at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The packed sample at index 15 is different from expected");
}

void test_pack_samples_all_in_range(void) {
    TEST_IGNORE();
    alignas(16) const int16_t first[8] = {0, 1, 64, 127, 128, 200, 254, 255};
    alignas(16) const int16_t second[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    alignas(16) uint8_t result[16];
    pack_samples(result, first, second);
    const uint8_t expected[16] = {0, 1, 64, 127, 128, 200, 254, 255, 10, 20, 30, 40, 50, 60, 70, 80};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The packed sample at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The packed sample at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The packed sample at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The packed sample at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The packed sample at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The packed sample at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The packed sample at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The packed sample at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The packed sample at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The packed sample at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The packed sample at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The packed sample at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The packed sample at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The packed sample at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The packed sample at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The packed sample at index 15 is different from expected");
}

void test_pack_samples_all_clamp_high(void) {
    TEST_IGNORE();
    alignas(16) const int16_t first[8] = {256, 300, 1000, 32767, 256, 512, 700, 999};
    alignas(16) const int16_t second[8] = {256, 257, 258, 259, 260, 5000, 9000, 32000};
    alignas(16) uint8_t result[16];
    pack_samples(result, first, second);
    const uint8_t expected[16] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The packed sample at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The packed sample at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The packed sample at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The packed sample at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The packed sample at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The packed sample at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The packed sample at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The packed sample at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The packed sample at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The packed sample at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The packed sample at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The packed sample at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The packed sample at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The packed sample at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The packed sample at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The packed sample at index 15 is different from expected");
}

void test_pack_samples_all_clamp_low(void) {
    TEST_IGNORE();
    alignas(16) const int16_t first[8] = {-1, -2, -100, -32768, -5, -50, -500, -9000};
    alignas(16) const int16_t second[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    alignas(16) uint8_t result[16];
    pack_samples(result, first, second);
    const uint8_t expected[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The packed sample at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The packed sample at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The packed sample at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The packed sample at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The packed sample at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The packed sample at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The packed sample at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The packed sample at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The packed sample at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The packed sample at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The packed sample at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The packed sample at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The packed sample at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The packed sample at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The packed sample at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The packed sample at index 15 is different from expected");
}

void test_pack_samples_boundaries(void) {
    TEST_IGNORE();
    alignas(16) const int16_t first[8] = {-1, 0, 1, 254, 255, 256, 128, 200};
    alignas(16) const int16_t second[8] = {0, 255, -1, 256, 127, 128, 300, -300};
    alignas(16) uint8_t result[16];
    pack_samples(result, first, second);
    const uint8_t expected[16] = {0, 0, 1, 254, 255, 255, 128, 200, 0, 255, 0, 255, 127, 128, 255, 0};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The packed sample at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The packed sample at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The packed sample at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The packed sample at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The packed sample at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The packed sample at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The packed sample at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The packed sample at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The packed sample at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The packed sample at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The packed sample at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The packed sample at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The packed sample at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The packed sample at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The packed sample at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The packed sample at index 15 is different from expected");
}

// TASK: 5
void test_split_coordinates_example(void) {
    TEST_IGNORE();
    alignas(16) const float first[4] = {0.0f, 0.5f, 1.0f, 1.5f};
    alignas(16) const float second[4] = {2.0f, 2.5f, 3.0f, 3.5f};
    alignas(16) float xs[4];
    alignas(16) float ys[4];
    split_coordinates(xs, ys, first, second);
    const float expected_xs[4] = {0.0f, 1.0f, 2.0f, 3.0f};
    const float expected_ys[4] = {0.5f, 1.5f, 2.5f, 3.5f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[0], xs[0], "The x coordinate at index 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[1], xs[1], "The x coordinate at index 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[2], xs[2], "The x coordinate at index 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[3], xs[3], "The x coordinate at index 3 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[0], ys[0], "The y coordinate at index 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[1], ys[1], "The y coordinate at index 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[2], ys[2], "The y coordinate at index 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[3], ys[3], "The y coordinate at index 3 is different from expected");
}

void test_split_coordinates_negative(void) {
    TEST_IGNORE();
    alignas(16) const float first[4] = {-1.0f, -2.0f, 3.0f, 4.0f};
    alignas(16) const float second[4] = {-5.0f, 6.0f, -7.0f, 8.0f};
    alignas(16) float xs[4];
    alignas(16) float ys[4];
    split_coordinates(xs, ys, first, second);
    const float expected_xs[4] = {-1.0f, 3.0f, -5.0f, -7.0f};
    const float expected_ys[4] = {-2.0f, 4.0f, 6.0f, 8.0f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[0], xs[0], "The x coordinate at index 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[1], xs[1], "The x coordinate at index 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[2], xs[2], "The x coordinate at index 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[3], xs[3], "The x coordinate at index 3 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[0], ys[0], "The y coordinate at index 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[1], ys[1], "The y coordinate at index 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[2], ys[2], "The y coordinate at index 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[3], ys[3], "The y coordinate at index 3 is different from expected");
}

void test_split_coordinates_distinct_streams(void) {
    TEST_IGNORE();
    alignas(16) const float first[4] = {10.0f, 11.0f, 12.0f, 13.0f};
    alignas(16) const float second[4] = {20.0f, 21.0f, 22.0f, 23.0f};
    alignas(16) float xs[4];
    alignas(16) float ys[4];
    split_coordinates(xs, ys, first, second);
    const float expected_xs[4] = {10.0f, 12.0f, 20.0f, 22.0f};
    const float expected_ys[4] = {11.0f, 13.0f, 21.0f, 23.0f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[0], xs[0], "The x coordinate at index 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[1], xs[1], "The x coordinate at index 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[2], xs[2], "The x coordinate at index 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[3], xs[3], "The x coordinate at index 3 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[0], ys[0], "The y coordinate at index 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[1], ys[1], "The y coordinate at index 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[2], ys[2], "The y coordinate at index 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[3], ys[3], "The y coordinate at index 3 is different from expected");
}

void test_split_coordinates_fractional(void) {
    TEST_IGNORE();
    alignas(16) const float first[4] = {0.25f, 0.5f, 0.75f, 1.25f};
    alignas(16) const float second[4] = {1.5f, 1.75f, 2.0f, 2.5f};
    alignas(16) float xs[4];
    alignas(16) float ys[4];
    split_coordinates(xs, ys, first, second);
    const float expected_xs[4] = {0.25f, 0.75f, 1.5f, 2.0f};
    const float expected_ys[4] = {0.5f, 1.25f, 1.75f, 2.5f};
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[0], xs[0], "The x coordinate at index 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[1], xs[1], "The x coordinate at index 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[2], xs[2], "The x coordinate at index 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[3], xs[3], "The x coordinate at index 3 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[0], ys[0], "The y coordinate at index 0 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[1], ys[1], "The y coordinate at index 1 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[2], ys[2], "The y coordinate at index 2 is different from expected");
    TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[3], ys[3], "The y coordinate at index 3 is different from expected");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_display_order_example_two_blocks);
    RUN_TEST(test_display_order_single_block);
    RUN_TEST(test_display_order_three_blocks);
    RUN_TEST(test_display_order_red_equals_blue_unchanged);
    RUN_TEST(test_fill_region_example_two_blocks);
    RUN_TEST(test_fill_region_single_block);
    RUN_TEST(test_fill_region_three_blocks_transparent_black);
    RUN_TEST(test_fill_region_opaque_white_two_blocks);
    RUN_TEST(test_weave_scanlines_example);
    RUN_TEST(test_weave_scanlines_alternating_extremes);
    RUN_TEST(test_weave_scanlines_high_half_distinct);
    RUN_TEST(test_pack_samples_example);
    RUN_TEST(test_pack_samples_all_in_range);
    RUN_TEST(test_pack_samples_all_clamp_high);
    RUN_TEST(test_pack_samples_all_clamp_low);
    RUN_TEST(test_pack_samples_boundaries);
    RUN_TEST(test_split_coordinates_example);
    RUN_TEST(test_split_coordinates_negative);
    RUN_TEST(test_split_coordinates_distinct_streams);
    RUN_TEST(test_split_coordinates_fractional);
    return UNITY_END();
}
