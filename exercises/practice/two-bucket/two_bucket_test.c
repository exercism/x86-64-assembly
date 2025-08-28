#include "vendor/unity.h"

#define SUCCESS 0
#define UNREACHABLE_GOAL 1

typedef enum {
    ONE = 1,
    TWO
} bucket_id;

typedef struct {
    size_t moves;
    bucket_id goal_bucket;
    size_t other_bucket;
} bucket_result_t;

extern int measure(bucket_result_t *result, size_t bucket_one, size_t bucket_two, size_t goal, bucket_id start_bucket);

void setUp(void) {
}

void tearDown(void) {
}

void test_measure_using_bucket_one_of_size_3_and_bucket_two_of_size_5__start_with_bucket_one(void) {
    bucket_result_t result = {0};
    TEST_ASSERT_EQUAL(SUCCESS, measure(&result, 3, 5, 1, ONE));
    TEST_ASSERT_EQUAL(4, result.moves);
    TEST_ASSERT_EQUAL(ONE, result.goal_bucket);
    TEST_ASSERT_EQUAL(5, result.other_bucket);
}

void test_measure_using_bucket_one_of_size_3_and_bucket_two_of_size_5__start_with_bucket_two(void) {
    TEST_IGNORE();
    bucket_result_t result = {0};
    TEST_ASSERT_EQUAL(SUCCESS, measure(&result, 3, 5, 1, TWO));
    TEST_ASSERT_EQUAL(8, result.moves);
    TEST_ASSERT_EQUAL(TWO, result.goal_bucket);
    TEST_ASSERT_EQUAL(3, result.other_bucket);
}

void test_measure_using_bucket_one_of_size_7_and_bucket_two_of_size_11__start_with_bucket_one(void) {
    TEST_IGNORE();
    bucket_result_t result = {0};
    TEST_ASSERT_EQUAL(SUCCESS, measure(&result, 7, 11, 2, ONE));
    TEST_ASSERT_EQUAL(14, result.moves);
    TEST_ASSERT_EQUAL(ONE, result.goal_bucket);
    TEST_ASSERT_EQUAL(11, result.other_bucket);
}

void test_measure_using_bucket_one_of_size_7_and_bucket_two_of_size_11__start_with_bucket_two(void) {
    TEST_IGNORE();
    bucket_result_t result = {0};
    TEST_ASSERT_EQUAL(SUCCESS, measure(&result, 7, 11, 2, TWO));
    TEST_ASSERT_EQUAL(18, result.moves);
    TEST_ASSERT_EQUAL(TWO, result.goal_bucket);
    TEST_ASSERT_EQUAL(7, result.other_bucket);
}

void test_measure_one_step_using_bucket_one_of_size_1_and_bucket_two_of_size_3__start_with_bucket_two(void) {
    TEST_IGNORE();
    bucket_result_t result = {0};
    TEST_ASSERT_EQUAL(SUCCESS, measure(&result, 1, 3, 3, TWO));
    TEST_ASSERT_EQUAL(1, result.moves);
    TEST_ASSERT_EQUAL(TWO, result.goal_bucket);
    TEST_ASSERT_EQUAL(0, result.other_bucket);
}

void test_measure_using_bucket_one_of_size_2_and_bucket_two_of_size_3__start_with_bucket_one_and_end_with_bucket_two(void) {
    TEST_IGNORE();
    bucket_result_t result = {0};
    TEST_ASSERT_EQUAL(SUCCESS, measure(&result, 2, 3, 3, ONE));
    TEST_ASSERT_EQUAL(2, result.moves);
    TEST_ASSERT_EQUAL(TWO, result.goal_bucket);
    TEST_ASSERT_EQUAL(2, result.other_bucket);
}

void test_not_possible_to_reach_the_goal(void) {
    TEST_IGNORE();
    bucket_result_t result = {0};
    TEST_ASSERT_EQUAL(UNREACHABLE_GOAL, measure(&result, 6, 15, 5, ONE));
}

void test_with_the_same_buckets_but_a_different_goal_then_it_is_possible(void) {
    TEST_IGNORE();
    bucket_result_t result = {0};
    TEST_ASSERT_EQUAL(SUCCESS, measure(&result, 6, 15, 9, ONE));
    TEST_ASSERT_EQUAL(10, result.moves);
    TEST_ASSERT_EQUAL(TWO, result.goal_bucket);
    TEST_ASSERT_EQUAL(0, result.other_bucket);
}

void test_goal_larger_than_both_buckets_is_impossible(void) {
    TEST_IGNORE();
    bucket_result_t result = {0};
    TEST_ASSERT_EQUAL(UNREACHABLE_GOAL, measure(&result, 5, 7, 8, ONE));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_measure_using_bucket_one_of_size_3_and_bucket_two_of_size_5__start_with_bucket_one);
    RUN_TEST(test_measure_using_bucket_one_of_size_3_and_bucket_two_of_size_5__start_with_bucket_two);
    RUN_TEST(test_measure_using_bucket_one_of_size_7_and_bucket_two_of_size_11__start_with_bucket_one);
    RUN_TEST(test_measure_using_bucket_one_of_size_7_and_bucket_two_of_size_11__start_with_bucket_two);
    RUN_TEST(test_measure_one_step_using_bucket_one_of_size_1_and_bucket_two_of_size_3__start_with_bucket_two);
    RUN_TEST(test_measure_using_bucket_one_of_size_2_and_bucket_two_of_size_3__start_with_bucket_one_and_end_with_bucket_two);
    RUN_TEST(test_not_possible_to_reach_the_goal);
    RUN_TEST(test_with_the_same_buckets_but_a_different_goal_then_it_is_possible);
    RUN_TEST(test_goal_larger_than_both_buckets_is_impossible);
    return UNITY_END();
}
