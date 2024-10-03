// Version: 0

#include "vendor/unity.h"

extern int valid(const char *str);

void setUp(void) {
}

void tearDown(void) {
}

void test_single_digit_strings_can_not_be_valid(void) {
    TEST_ASSERT_FALSE(valid("1"));
}

void test_a_single_zero_is_invalid(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid("0"));
}

void test_a_simple_valid_sin_that_remains_valid_if_reversed(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(valid("059"));
}

void test_a_simple_valid_sin_that_becomes_invalid_if_reversed(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(valid("59"));
}

void test_a_valid_canadian_sin(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(valid("055 444 285"));
}

void test_invalid_canadian_sin(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid("055 444 286"));
}

void test_invalid_credit_card(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid("8273 1232 7352 0569"));
}

void test_invalid_long_number_with_an_even_remainder(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid("1 2345 6789 1234 5678 9012"));
}

void test_invalid_long_number_with_a_remainder_divisible_by_5(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid("1 2345 6789 1234 5678 9013"));
}

void test_valid_number_with_an_even_number_of_digits(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(valid("095 245 88"));
}

void test_valid_number_with_an_odd_number_of_spaces(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(valid("234 567 891 234"));
}

void test_valid_strings_with_a_nondigit_added_at_the_end_become_invalid(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid("059a"));
}

void test_valid_strings_with_punctuation_included_become_invalid(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid("055-444-285"));
}

void test_valid_strings_with_symbols_included_become_invalid(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid("055# 444$ 285"));
}

void test_single_zero_with_space_is_invalid(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid(" 0"));
}

void test_more_than_a_single_zero_is_valid(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(valid("0000 0"));
}

void test_input_digit_9_is_correctly_converted_to_output_digit_9(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(valid("091"));
}

void test_very_long_input_is_valid(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(valid("9999999999 9999999999 9999999999 9999999999"));
}

void test_valid_luhn_with_an_odd_number_of_digits_and_non_zero_first_digit(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(valid("109"));
}

void test_using_ascii_value_for_nondoubled_nondigit_isnt_allowed(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid("055b 444 285"));
}

void test_using_ascii_value_for_doubled_nondigit_isnt_allowed(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid(":9"));
}

void test_nonnumeric_nonspace_char_in_the_middle_with_a_sum_thats_divisible_by_10_isnt_allowed(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(valid("59%59"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_single_digit_strings_can_not_be_valid);
    RUN_TEST(test_a_single_zero_is_invalid);
    RUN_TEST(test_a_simple_valid_sin_that_remains_valid_if_reversed);
    RUN_TEST(test_a_simple_valid_sin_that_becomes_invalid_if_reversed);
    RUN_TEST(test_a_valid_canadian_sin);
    RUN_TEST(test_invalid_canadian_sin);
    RUN_TEST(test_invalid_credit_card);
    RUN_TEST(test_invalid_long_number_with_an_even_remainder);
    RUN_TEST(test_invalid_long_number_with_a_remainder_divisible_by_5);
    RUN_TEST(test_valid_number_with_an_even_number_of_digits);
    RUN_TEST(test_valid_number_with_an_odd_number_of_spaces);
    RUN_TEST(test_valid_strings_with_a_nondigit_added_at_the_end_become_invalid);
    RUN_TEST(test_valid_strings_with_punctuation_included_become_invalid);
    RUN_TEST(test_valid_strings_with_symbols_included_become_invalid);
    RUN_TEST(test_single_zero_with_space_is_invalid);
    RUN_TEST(test_more_than_a_single_zero_is_valid);
    RUN_TEST(test_input_digit_9_is_correctly_converted_to_output_digit_9);
    RUN_TEST(test_very_long_input_is_valid);
    RUN_TEST(test_valid_luhn_with_an_odd_number_of_digits_and_non_zero_first_digit);
    RUN_TEST(test_using_ascii_value_for_nondoubled_nondigit_isnt_allowed);
    RUN_TEST(test_using_ascii_value_for_doubled_nondigit_isnt_allowed);
    RUN_TEST(test_nonnumeric_nonspace_char_in_the_middle_with_a_sum_thats_divisible_by_10_isnt_allowed);
    return UNITY_END();
}
