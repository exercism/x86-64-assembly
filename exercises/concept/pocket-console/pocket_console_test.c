#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern int64_t add_bonus(int64_t total, int64_t bonus);
extern int64_t compare_scores(int64_t score_a, int64_t score_b);
extern int64_t validate_score(int64_t score, int64_t min, int64_t max);
extern void top_two(int64_t buffer[2], const int64_t *array, size_t length);

void setUp(void) {
}

void tearDown(void) {
}

// TASK: 1
void test_add_bonus_both_zero(void) {
    TEST_ASSERT_EQUAL_INT64(0, add_bonus(0, 0));
}

void test_add_bonus_small_sum(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(600, add_bonus(500, 100));
}

void test_add_bonus_already_at_max(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(999999, add_bonus(999999, 0));
}

void test_add_bonus_just_over_max(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(999999, add_bonus(999990, 50));
}

void test_add_bonus_reaches_max_exactly(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(999999, add_bonus(999998, 1));
}

void test_add_bonus_one_past_max(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(999999, add_bonus(999998, 2));
}

void test_add_bonus_large_bonus_from_zero(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(999999, add_bonus(0, 999999));
}

void test_add_bonus_far_above_max(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(999999, add_bonus(500000, 5000000));
}

// TASK: 2
void test_compare_scores_both_zero(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(0, compare_scores(0, 0));
}

void test_compare_scores_a_greater_positive(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(1, compare_scores(500, 300));
}

void test_compare_scores_b_greater_positive(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(-1, compare_scores(300, 500));
}

void test_compare_scores_equal_positive(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(0, compare_scores(500, 500));
}

void test_compare_scores_equal_negative(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(0, compare_scores(-100, -100));
}

void test_compare_scores_a_negative_b_positive(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(-1, compare_scores(-100, 100));
}

void test_compare_scores_a_positive_b_negative(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(1, compare_scores(100, -100));
}

void test_compare_scores_off_by_one(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(1, compare_scores(1000000, 999999));
}

// TASK: 3
void test_validate_score_in_default_range(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(450, validate_score(450, 0, 999999));
}

void test_validate_score_below_default_min(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(0, validate_score(-50, 0, 999999));
}

void test_validate_score_above_default_max(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(999999, validate_score(1234567, 0, 999999));
}

void test_validate_score_at_min_boundary(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(0, validate_score(0, 0, 100));
}

void test_validate_score_at_max_boundary(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(100, validate_score(100, 0, 100));
}

void test_validate_score_within_negative_range(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(-150, validate_score(-150, -200, -100));
}

void test_validate_score_above_negative_range(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(-100, validate_score(-50, -200, -100));
}

void test_validate_score_below_offset_range(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(1000, validate_score(500, 1000, 2000));
}

// TASK: 4
void test_top_two_empty_array(void) {
    TEST_IGNORE();
    int64_t buffer[2] = {0};
    top_two(buffer, NULL, 0);
    const int64_t expected[2] = {0, 0};
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_top_two_single_element(void) {
    TEST_IGNORE();
    int64_t buffer[2] = {0};
    const int64_t input[] = {42};
    top_two(buffer, input, ARRAY_SIZE(input));
    const int64_t expected[2] = {42, 0};
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_top_two_example_from_instructions(void) {
    TEST_IGNORE();
    int64_t buffer[2] = {0};
    const int64_t input[] = {10, 30, 20, 50, 40};
    top_two(buffer, input, ARRAY_SIZE(input));
    const int64_t expected[2] = {50, 40};
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_top_two_all_same(void) {
    TEST_IGNORE();
    int64_t buffer[2] = {0};
    const int64_t input[] = {7, 7, 7, 7};
    top_two(buffer, input, ARRAY_SIZE(input));
    const int64_t expected[2] = {7, 7};
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_top_two_sorted_ascending(void) {
    TEST_IGNORE();
    int64_t buffer[2] = {0};
    const int64_t input[] = {1, 2, 3, 4, 5};
    top_two(buffer, input, ARRAY_SIZE(input));
    const int64_t expected[2] = {5, 4};
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_top_two_sorted_descending(void) {
    TEST_IGNORE();
    int64_t buffer[2] = {0};
    const int64_t input[] = {5, 4, 3, 2, 1};
    top_two(buffer, input, ARRAY_SIZE(input));
    const int64_t expected[2] = {5, 4};
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_top_two_all_negative_disregarded(void) {
    TEST_IGNORE();
    int64_t buffer[2] = {0};
    const int64_t input[] = {-10, -5, -3, -7};
    top_two(buffer, input, ARRAY_SIZE(input));
    const int64_t expected[2] = {0, 0};
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_top_two_mixed_signs(void) {
    TEST_IGNORE();
    int64_t buffer[2] = {0};
    const int64_t input[] = {-100, 50, -50, 100};
    top_two(buffer, input, ARRAY_SIZE(input));
    const int64_t expected[2] = {100, 50};
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add_bonus_both_zero);
    RUN_TEST(test_add_bonus_small_sum);
    RUN_TEST(test_add_bonus_already_at_max);
    RUN_TEST(test_add_bonus_just_over_max);
    RUN_TEST(test_add_bonus_reaches_max_exactly);
    RUN_TEST(test_add_bonus_one_past_max);
    RUN_TEST(test_add_bonus_large_bonus_from_zero);
    RUN_TEST(test_add_bonus_far_above_max);
    RUN_TEST(test_compare_scores_both_zero);
    RUN_TEST(test_compare_scores_a_greater_positive);
    RUN_TEST(test_compare_scores_b_greater_positive);
    RUN_TEST(test_compare_scores_equal_positive);
    RUN_TEST(test_compare_scores_equal_negative);
    RUN_TEST(test_compare_scores_a_negative_b_positive);
    RUN_TEST(test_compare_scores_a_positive_b_negative);
    RUN_TEST(test_compare_scores_off_by_one);
    RUN_TEST(test_validate_score_in_default_range);
    RUN_TEST(test_validate_score_below_default_min);
    RUN_TEST(test_validate_score_above_default_max);
    RUN_TEST(test_validate_score_at_min_boundary);
    RUN_TEST(test_validate_score_at_max_boundary);
    RUN_TEST(test_validate_score_within_negative_range);
    RUN_TEST(test_validate_score_above_negative_range);
    RUN_TEST(test_validate_score_below_offset_range);
    RUN_TEST(test_top_two_empty_array);
    RUN_TEST(test_top_two_single_element);
    RUN_TEST(test_top_two_example_from_instructions);
    RUN_TEST(test_top_two_all_same);
    RUN_TEST(test_top_two_sorted_ascending);
    RUN_TEST(test_top_two_sorted_descending);
    RUN_TEST(test_top_two_all_negative_disregarded);
    RUN_TEST(test_top_two_mixed_signs);
    return UNITY_END();
}
