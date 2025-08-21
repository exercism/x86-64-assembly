
#include "vendor/unity.h"

#include "stdint.h"
#include "stddef.h"

#define BUFFER_SIZE 100
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define NEGATIVE_TARGET -1
#define UNREACHABLE_TARGET -2

extern int64_t find_fewest_coins(uint64_t *buffer, const uint64_t *coins, int64_t target, size_t coins_size);

void setUp(void) {
}

void tearDown(void) {
}

void test_change_for_1_cent(void) {
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {1, 5, 10, 25};
    const uint64_t expected[] = {1};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), find_fewest_coins(buffer, coins, 1, ARRAY_SIZE(coins)));
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_single_coin_change(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {1, 5, 10, 25, 100};
    const uint64_t expected[] = {25};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), find_fewest_coins(buffer, coins, 25, ARRAY_SIZE(coins)));
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_multiple_coin_change(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {1, 5, 10, 25, 100};
    const uint64_t expected[] = {5, 10};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), find_fewest_coins(buffer, coins, 15, ARRAY_SIZE(coins)));
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_change_with_lilliputian_coins(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {1, 4, 15, 20, 50};
    const uint64_t expected[] = {4, 4, 15};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), find_fewest_coins(buffer, coins, 23, ARRAY_SIZE(coins)));
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_change_with_lower_elbonia_coins(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {1, 5, 10, 21, 25};
    const uint64_t expected[] = {21, 21, 21};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), find_fewest_coins(buffer, coins, 63, ARRAY_SIZE(coins)));
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_large_target_values(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {1, 2, 5, 10, 20, 50, 100};
    const uint64_t expected[] = {2, 2, 5, 20, 20, 50, 100, 100, 100, 100, 100, 100, 100, 100, 100};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), find_fewest_coins(buffer, coins, 999, ARRAY_SIZE(coins)));
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_possible_change_without_unit_coins_available(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {2, 5, 10, 20, 50};
    const uint64_t expected[] = {2, 2, 2, 5, 10};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), find_fewest_coins(buffer, coins, 21, ARRAY_SIZE(coins)));
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_another_possible_change_without_unit_coins_available(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {4, 5};
    const uint64_t expected[] = {4, 4, 4, 5, 5, 5};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), find_fewest_coins(buffer, coins, 27, ARRAY_SIZE(coins)));
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_a_greedy_approach_is_not_optimal(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {1, 10, 11};
    const uint64_t expected[] = {10, 10};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), find_fewest_coins(buffer, coins, 20, ARRAY_SIZE(coins)));
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_no_coins_make_0_change(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {1, 5, 10, 21, 25};
    TEST_ASSERT_EQUAL_INT64(0, find_fewest_coins(buffer, coins, 0, ARRAY_SIZE(coins)));
}

void test_error_testing_for_change_smaller_than_the_smallest_of_coins(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {5, 10};
    TEST_ASSERT_EQUAL_INT64(UNREACHABLE_TARGET, find_fewest_coins(buffer, coins, 3, ARRAY_SIZE(coins)));
}

void test_error_if_no_combination_can_add_up_to_target(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {5, 10};
    TEST_ASSERT_EQUAL_INT64(UNREACHABLE_TARGET, find_fewest_coins(buffer, coins, 94, ARRAY_SIZE(coins)));
}

void test_cannot_find_negative_change_values(void) {
    TEST_IGNORE();
    uint64_t buffer[BUFFER_SIZE];
    const uint64_t coins[] = {1, 2, 5};
    TEST_ASSERT_EQUAL_INT64(NEGATIVE_TARGET, find_fewest_coins(buffer, coins, -5, ARRAY_SIZE(coins)));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_change_for_1_cent);
    RUN_TEST(test_single_coin_change);
    RUN_TEST(test_multiple_coin_change);
    RUN_TEST(test_change_with_lilliputian_coins);
    RUN_TEST(test_change_with_lower_elbonia_coins);
    RUN_TEST(test_large_target_values);
    RUN_TEST(test_possible_change_without_unit_coins_available);
    RUN_TEST(test_another_possible_change_without_unit_coins_available);
    RUN_TEST(test_a_greedy_approach_is_not_optimal);
    RUN_TEST(test_no_coins_make_0_change);
    RUN_TEST(test_error_testing_for_change_smaller_than_the_smallest_of_coins);
    RUN_TEST(test_error_if_no_combination_can_add_up_to_target);
    RUN_TEST(test_cannot_find_negative_change_values);
    return UNITY_END();
}
