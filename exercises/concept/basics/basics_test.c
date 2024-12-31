#include "vendor/unity.h"

#include <stdint.h>

extern int64_t expected_minutes_in_oven(void);
extern int64_t remaining_minutes_in_oven(int64_t actual_minutes_in_oven);
extern int64_t preparation_time_in_minutes(int64_t number_of_layers);
extern int64_t elapsed_time_in_minutes(int64_t number_of_layers, int64_t actual_minutes_in_oven);

void setUp(void) {
}

void tearDown(void) {
}

void test_expected(void) {
    TEST_ASSERT_EQUAL_INT64(40, expected_minutes_in_oven());
}

void test_remaining(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(15, remaining_minutes_in_oven(25));
}

void test_preparation_one(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(2, preparation_time_in_minutes(1));
}

void test_preparation_many(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(8, preparation_time_in_minutes(4));
}

void test_elapsed_one(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(32, elapsed_time_in_minutes(1, 30));
}

void test_elapsed_many(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(16, elapsed_time_in_minutes(4, 8));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_expected);
    RUN_TEST(test_remaining);
    RUN_TEST(test_preparation_one);
    RUN_TEST(test_preparation_many);
    RUN_TEST(test_elapsed_one);
    RUN_TEST(test_elapsed_many);
    return UNITY_END();
}
