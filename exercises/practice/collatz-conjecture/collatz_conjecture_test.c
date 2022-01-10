// Version: 0

#include "vendor/unity.h"

#define ERROR_VALUE -1

extern int steps(int number);

void setUp(void) {
}

void tearDown(void) {
}

void test_zero_steps_for_one(void) {
    TEST_ASSERT_EQUAL_INT(0, steps(1));
}

void test_divide_if_even(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(4, steps(16));
}

void test_even_and_odd_steps(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(9, steps(12));
}

void test_large_number_of_even_and_odd_steps(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(152, steps(1000000));
}

void test_zero_is_an_error(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(ERROR_VALUE, steps(0));
}

void test_negative_value_is_an_error(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(ERROR_VALUE, steps(-15));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_zero_steps_for_one);
    RUN_TEST(test_divide_if_even);
    RUN_TEST(test_even_and_odd_steps);
    RUN_TEST(test_large_number_of_even_and_odd_steps);
    RUN_TEST(test_zero_is_an_error);
    RUN_TEST(test_negative_value_is_an_error);
    return UNITY_END();
}
