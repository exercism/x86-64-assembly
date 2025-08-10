// Version: 0

#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern uint64_t sum(uint64_t limit, const uint64_t *factors, size_t factor_count);

void setUp(void) {
}

void tearDown(void) {
}

void test_no_multiples_within_limit(void) {
    const uint64_t factors[] = {3, 5};
    TEST_ASSERT_EQUAL_UINT64(0, sum(1, factors, ARRAY_SIZE(factors)));
}

void test_one_factor_has_multiples_within_limit(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {3, 5};
    TEST_ASSERT_EQUAL_UINT64(3, sum(4, factors, ARRAY_SIZE(factors)));
}

void test_more_than_one_multiple_within_limit(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {3};
    TEST_ASSERT_EQUAL_UINT64(9, sum(7, factors, ARRAY_SIZE(factors)));
}

void test_more_than_one_factor_with_multiples_within_limit(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {3, 5};
    TEST_ASSERT_EQUAL_UINT64(23, sum(10, factors, ARRAY_SIZE(factors)));
}

void test_each_multiple_is_only_counted_once(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {3, 5};
    TEST_ASSERT_EQUAL_UINT64(2318, sum(100, factors, ARRAY_SIZE(factors)));
}

void test_a_much_larger_limit(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {3, 5};
    TEST_ASSERT_EQUAL_UINT64(233168, sum(1000, factors, ARRAY_SIZE(factors)));
}

void test_three_factors(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {7, 13, 17};
    TEST_ASSERT_EQUAL_UINT64(51, sum(20, factors, ARRAY_SIZE(factors)));
}

void test_factors_not_relatively_prime(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {4, 6};
    TEST_ASSERT_EQUAL_UINT64(30, sum(15, factors, ARRAY_SIZE(factors)));
}

void test_some_pairs_of_factors_relatively_prime_and_some_not(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {5, 6, 8};
    TEST_ASSERT_EQUAL_UINT64(4419, sum(150, factors, ARRAY_SIZE(factors)));
}

void test_one_factor_is_a_multiple_of_another(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {5, 25};
    TEST_ASSERT_EQUAL_UINT64(275, sum(51, factors, ARRAY_SIZE(factors)));
}

void test_much_larger_factors(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {43, 47};
    TEST_ASSERT_EQUAL_UINT64(2203160, sum(10000, factors, ARRAY_SIZE(factors)));
}

void test_all_numbers_are_multiples_of_1(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {1};
    TEST_ASSERT_EQUAL_UINT64(4950, sum(100, factors, ARRAY_SIZE(factors)));
}

void test_no_factors_means_an_empty_sum(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(0, sum(10000, NULL, 0));
}

void test_the_only_multiple_of_0_is_0(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {0};
    TEST_ASSERT_EQUAL_UINT64(0, sum(1, factors, ARRAY_SIZE(factors)));
}

void test_the_factor_0_does_not_affect_the_sum_of_multiples_of_other_factors(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {3, 0};
    TEST_ASSERT_EQUAL_UINT64(3, sum(4, factors, ARRAY_SIZE(factors)));
}

void test_solutions_using_includeexclude_must_extend_to_cardinality_greater_than_3(void) {
    TEST_IGNORE();
    const uint64_t factors[] = {2, 3, 5, 7, 11};
    TEST_ASSERT_EQUAL_UINT64(39614537, sum(10000, factors, ARRAY_SIZE(factors)));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_no_multiples_within_limit);
    RUN_TEST(test_one_factor_has_multiples_within_limit);
    RUN_TEST(test_more_than_one_multiple_within_limit);
    RUN_TEST(test_more_than_one_factor_with_multiples_within_limit);
    RUN_TEST(test_each_multiple_is_only_counted_once);
    RUN_TEST(test_a_much_larger_limit);
    RUN_TEST(test_three_factors);
    RUN_TEST(test_factors_not_relatively_prime);
    RUN_TEST(test_some_pairs_of_factors_relatively_prime_and_some_not);
    RUN_TEST(test_one_factor_is_a_multiple_of_another);
    RUN_TEST(test_much_larger_factors);
    RUN_TEST(test_all_numbers_are_multiples_of_1);
    RUN_TEST(test_no_factors_means_an_empty_sum);
    RUN_TEST(test_the_only_multiple_of_0_is_0);
    RUN_TEST(test_the_factor_0_does_not_affect_the_sum_of_multiples_of_other_factors);
    RUN_TEST(test_solutions_using_includeexclude_must_extend_to_cardinality_greater_than_3);
    return UNITY_END();
}
