// Version: 1.0.0

#include "vendor/unity.h"

extern int is_armstrong_number(int number);

void setUp(void) {
}

void tearDown(void) {
}

void test_zero_is_an_armstrong_number(void) {
    TEST_ASSERT_TRUE(is_armstrong_number(0));
}

void test_single_digit_numbers_are_armstrong_numbers(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(is_armstrong_number(5));
}

void test_there_are_no_two_digit_armstrong_numbers(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(is_armstrong_number(10));
}

void test_three_digit_number_that_is_an_armstrong_number(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(is_armstrong_number(153));
}

void test_three_digit_number_that_is_not_an_armstrong_number(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(is_armstrong_number(100));
}

void test_four_digit_number_that_is_an_armstrong_number(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(is_armstrong_number(9474));
}

void test_four_digit_number_that_is_not_an_armstrong_number(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(is_armstrong_number(9475));
}

void test_seven_digit_number_that_is_an_armstrong_number(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(is_armstrong_number(9926315));
}

void test_seven_digit_number_that_is_not_an_armstrong_number(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(is_armstrong_number(9926314));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_zero_is_an_armstrong_number);
    RUN_TEST(test_single_digit_numbers_are_armstrong_numbers);
    RUN_TEST(test_there_are_no_two_digit_armstrong_numbers);
    RUN_TEST(test_three_digit_number_that_is_an_armstrong_number);
    RUN_TEST(test_three_digit_number_that_is_not_an_armstrong_number);
    RUN_TEST(test_four_digit_number_that_is_an_armstrong_number);
    RUN_TEST(test_four_digit_number_that_is_not_an_armstrong_number);
    RUN_TEST(test_seven_digit_number_that_is_an_armstrong_number);
    RUN_TEST(test_seven_digit_number_that_is_not_an_armstrong_number);
    return UnityEnd();
}
