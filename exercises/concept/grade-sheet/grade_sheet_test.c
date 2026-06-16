#include "vendor/unity.h"

#include <stdalign.h>
#include <stdint.h>

extern void flag_above_threshold(uint32_t result[4], const float scores[4], const float thresholds[4]);
extern void flag_perfect(uint32_t result[4], const float scores[4], const float maxima[4]);
extern void assign_ranks(uint32_t result[4], const float scores[4], const float maxima[4]);
extern int32_t count_failures(const uint32_t ranks[], int64_t block_count, const int32_t pass_threshold[4]);
extern int32_t all_passed(const uint32_t failing[], int64_t block_count);

void setUp(void) {
}

void tearDown(void) {
}

// TASK: 1
void test_above_threshold_example(void) {
    alignas(16) const float scores[4] = {72.0f, 55.0f, 90.0f, 40.0f};
    alignas(16) const float thresholds[4] = {60.0f, 60.0f, 60.0f, 60.0f};
    alignas(16) uint32_t result[4];
    flag_above_threshold(result, scores, thresholds);
    const uint32_t expected[4] = {4294967295, 0, 4294967295, 0};
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[0], result[0], "The mask lane at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[1], result[1], "The mask lane at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[2], result[2], "The mask lane at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[3], result[3], "The mask lane at lane 3 is different from expected");
}

void test_above_threshold_equal_is_not_above(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {60.0f, 61.0f, 59.0f, 60.0f};
    alignas(16) const float thresholds[4] = {60.0f, 60.0f, 60.0f, 60.0f};
    alignas(16) uint32_t result[4];
    flag_above_threshold(result, scores, thresholds);
    const uint32_t expected[4] = {0, 4294967295, 0, 0};
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[0], result[0], "The mask lane at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[1], result[1], "The mask lane at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[2], result[2], "The mask lane at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[3], result[3], "The mask lane at lane 3 is different from expected");
}

void test_above_threshold_all_above(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {100.0f, 80.0f, 70.0f, 65.0f};
    alignas(16) const float thresholds[4] = {50.0f, 50.0f, 50.0f, 50.0f};
    alignas(16) uint32_t result[4];
    flag_above_threshold(result, scores, thresholds);
    const uint32_t expected[4] = {4294967295, 4294967295, 4294967295, 4294967295};
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[0], result[0], "The mask lane at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[1], result[1], "The mask lane at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[2], result[2], "The mask lane at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[3], result[3], "The mask lane at lane 3 is different from expected");
}

void test_above_threshold_none_above(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {10.0f, 20.0f, 30.0f, 40.0f};
    alignas(16) const float thresholds[4] = {50.0f, 50.0f, 50.0f, 50.0f};
    alignas(16) uint32_t result[4];
    flag_above_threshold(result, scores, thresholds);
    const uint32_t expected[4] = {0, 0, 0, 0};
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[0], result[0], "The mask lane at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[1], result[1], "The mask lane at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[2], result[2], "The mask lane at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[3], result[3], "The mask lane at lane 3 is different from expected");
}

void test_above_threshold_per_lane(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {50.0f, 50.0f, 50.0f, 50.0f};
    alignas(16) const float thresholds[4] = {40.0f, 50.0f, 60.0f, 49.0f};
    alignas(16) uint32_t result[4];
    flag_above_threshold(result, scores, thresholds);
    const uint32_t expected[4] = {4294967295, 0, 0, 4294967295};
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[0], result[0], "The mask lane at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[1], result[1], "The mask lane at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[2], result[2], "The mask lane at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[3], result[3], "The mask lane at lane 3 is different from expected");
}

// TASK: 2
void test_perfect_example(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {100.0f, 88.0f, 100.0f, 73.0f};
    alignas(16) const float maxima[4] = {100.0f, 100.0f, 100.0f, 100.0f};
    alignas(16) uint32_t result[4];
    flag_perfect(result, scores, maxima);
    const uint32_t expected[4] = {4294967295, 0, 4294967295, 0};
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[0], result[0], "The mask lane at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[1], result[1], "The mask lane at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[2], result[2], "The mask lane at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[3], result[3], "The mask lane at lane 3 is different from expected");
}

void test_perfect_none(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {99.0f, 87.0f, 50.0f, 72.0f};
    alignas(16) const float maxima[4] = {100.0f, 100.0f, 100.0f, 100.0f};
    alignas(16) uint32_t result[4];
    flag_perfect(result, scores, maxima);
    const uint32_t expected[4] = {0, 0, 0, 0};
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[0], result[0], "The mask lane at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[1], result[1], "The mask lane at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[2], result[2], "The mask lane at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[3], result[3], "The mask lane at lane 3 is different from expected");
}

void test_perfect_all(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {20.0f, 50.0f, 100.0f, 73.0f};
    alignas(16) const float maxima[4] = {20.0f, 50.0f, 100.0f, 73.0f};
    alignas(16) uint32_t result[4];
    flag_perfect(result, scores, maxima);
    const uint32_t expected[4] = {4294967295, 4294967295, 4294967295, 4294967295};
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[0], result[0], "The mask lane at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[1], result[1], "The mask lane at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[2], result[2], "The mask lane at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[3], result[3], "The mask lane at lane 3 is different from expected");
}

void test_perfect_per_lane_maxima(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {20.0f, 50.0f, 60.0f, 80.0f};
    alignas(16) const float maxima[4] = {20.0f, 40.0f, 60.0f, 100.0f};
    alignas(16) uint32_t result[4];
    flag_perfect(result, scores, maxima);
    const uint32_t expected[4] = {4294967295, 0, 4294967295, 0};
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[0], result[0], "The mask lane at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[1], result[1], "The mask lane at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[2], result[2], "The mask lane at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected[3], result[3], "The mask lane at lane 3 is different from expected");
}

// TASK: 3
void test_assign_ranks_example(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {40.0f, 75.0f, 100.0f, 60.0f};
    alignas(16) const float maxima[4] = {100.0f, 100.0f, 100.0f, 100.0f};
    alignas(16) uint32_t result[4];
    assign_ranks(result, scores, maxima);
    const uint32_t expected[4] = {1, 2, 3, 2};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The rank at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The rank at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The rank at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The rank at lane 3 is different from expected");
}

void test_assign_ranks_all_low(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {50.0f, 30.0f, 10.0f, 0.0f};
    alignas(16) const float maxima[4] = {100.0f, 100.0f, 100.0f, 100.0f};
    alignas(16) uint32_t result[4];
    assign_ranks(result, scores, maxima);
    const uint32_t expected[4] = {1, 1, 1, 1};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The rank at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The rank at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The rank at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The rank at lane 3 is different from expected");
}

void test_assign_ranks_all_perfect(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {100.0f, 100.0f, 100.0f, 100.0f};
    alignas(16) const float maxima[4] = {100.0f, 100.0f, 100.0f, 100.0f};
    alignas(16) uint32_t result[4];
    assign_ranks(result, scores, maxima);
    const uint32_t expected[4] = {3, 3, 3, 3};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The rank at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The rank at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The rank at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The rank at lane 3 is different from expected");
}

void test_assign_ranks_perfect_overrides_threshold(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {55.0f, 100.0f, 50.0f, 90.0f};
    alignas(16) const float maxima[4] = {200.0f, 100.0f, 50.0f, 90.0f};
    alignas(16) uint32_t result[4];
    assign_ranks(result, scores, maxima);
    const uint32_t expected[4] = {2, 3, 3, 3};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The rank at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The rank at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The rank at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The rank at lane 3 is different from expected");
}

void test_assign_ranks_threshold_boundary(void) {
    TEST_IGNORE();
    alignas(16) const float scores[4] = {50.0f, 51.0f, 49.0f, 100.0f};
    alignas(16) const float maxima[4] = {100.0f, 100.0f, 100.0f, 100.0f};
    alignas(16) uint32_t result[4];
    assign_ranks(result, scores, maxima);
    const uint32_t expected[4] = {1, 2, 1, 3};
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[0], result[0], "The rank at lane 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[1], result[1], "The rank at lane 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[2], result[2], "The rank at lane 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected[3], result[3], "The rank at lane 3 is different from expected");
}

// TASK: 4
void test_count_failures_example(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t ranks[8] = {1, 2, 3, 1, 2, 2, 1, 3};
    alignas(16) const int32_t pass_threshold[4] = {2, 2, 2, 2};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(3, count_failures(ranks, 2, pass_threshold), "The number of failing ranks is different from expected");
}

void test_count_failures_none_below(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t ranks[8] = {2, 3, 2, 3, 3, 2, 3, 2};
    alignas(16) const int32_t pass_threshold[4] = {2, 2, 2, 2};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(0, count_failures(ranks, 2, pass_threshold), "The number of failing ranks is different from expected");
}

void test_count_failures_all_below_single_block(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t ranks[4] = {1, 1, 1, 1};
    alignas(16) const int32_t pass_threshold[4] = {2, 2, 2, 2};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(4, count_failures(ranks, 1, pass_threshold), "The number of failing ranks is different from expected");
}

void test_count_failures_higher_threshold(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t ranks[8] = {1, 2, 3, 1, 2, 2, 1, 3};
    alignas(16) const int32_t pass_threshold[4] = {3, 3, 3, 3};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(6, count_failures(ranks, 2, pass_threshold), "The number of failing ranks is different from expected");
}

void test_count_failures_three_blocks(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t ranks[12] = {1, 2, 3, 1, 3, 3, 3, 3, 1, 1, 2, 3};
    alignas(16) const int32_t pass_threshold[4] = {2, 2, 2, 2};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(4, count_failures(ranks, 3, pass_threshold), "The number of failing ranks is different from expected");
}

// TASK: 5
void test_all_passed_example(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t failing[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(1, all_passed(failing, 2), "The all-passed answer is different from expected");
}

void test_all_passed_one_failure(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t failing[8] = {0, 0, 0, 0, 0, 4294967295, 0, 0};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(0, all_passed(failing, 2), "The all-passed answer is different from expected");
}

void test_all_passed_single_block_clear(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t failing[4] = {0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(1, all_passed(failing, 1), "The all-passed answer is different from expected");
}

void test_all_passed_first_block_failure(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t failing[8] = {4294967295, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(0, all_passed(failing, 2), "The all-passed answer is different from expected");
}

void test_all_passed_last_lane_failure(void) {
    TEST_IGNORE();
    alignas(16) const uint32_t failing[8] = {0, 0, 0, 0, 0, 0, 0, 4294967295};
    TEST_ASSERT_EQUAL_INT32_MESSAGE(0, all_passed(failing, 2), "The all-passed answer is different from expected");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_above_threshold_example);
    RUN_TEST(test_above_threshold_equal_is_not_above);
    RUN_TEST(test_above_threshold_all_above);
    RUN_TEST(test_above_threshold_none_above);
    RUN_TEST(test_above_threshold_per_lane);
    RUN_TEST(test_perfect_example);
    RUN_TEST(test_perfect_none);
    RUN_TEST(test_perfect_all);
    RUN_TEST(test_perfect_per_lane_maxima);
    RUN_TEST(test_assign_ranks_example);
    RUN_TEST(test_assign_ranks_all_low);
    RUN_TEST(test_assign_ranks_all_perfect);
    RUN_TEST(test_assign_ranks_perfect_overrides_threshold);
    RUN_TEST(test_assign_ranks_threshold_boundary);
    RUN_TEST(test_count_failures_example);
    RUN_TEST(test_count_failures_none_below);
    RUN_TEST(test_count_failures_all_below_single_block);
    RUN_TEST(test_count_failures_higher_threshold);
    RUN_TEST(test_count_failures_three_blocks);
    RUN_TEST(test_all_passed_example);
    RUN_TEST(test_all_passed_one_failure);
    RUN_TEST(test_all_passed_single_block_clear);
    RUN_TEST(test_all_passed_first_block_failure);
    RUN_TEST(test_all_passed_last_lane_failure);
    return UNITY_END();
}
