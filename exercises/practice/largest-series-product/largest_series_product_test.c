#include "vendor/unity.h"

#include <stdint.h>

#define INVALID_CHARACTER -1
#define NEGATIVE_SPAN -2
#define INSUFFICIENT_DIGITS -3

extern int64_t largest_product(int span, const char *digits);

void setUp(void) {
}

void tearDown(void) {
}

void test_finds_the_largest_product_if_span_equals_length(void) {
    TEST_ASSERT_EQUAL_INT64(18, largest_product(2, "29"));
}

void test_can_find_the_largest_product_of_2_with_numbers_in_order(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(72, largest_product(2, "0123456789"));
}

void test_can_find_the_largest_product_of_2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(48, largest_product(2, "576802143"));
}

void test_can_find_the_largest_product_of_3_with_numbers_in_order(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(504, largest_product(3, "0123456789"));
}

void test_can_find_the_largest_product_of_3(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(270, largest_product(3, "1027839564"));
}

void test_can_find_the_largest_product_of_5_with_numbers_in_order(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(15120, largest_product(5, "0123456789"));
}

void test_can_get_the_largest_product_of_a_big_number(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(23520, largest_product(6, "73167176531330624919225119674426574742355349194934"));
}

void test_reports_zero_if_the_only_digits_are_zero(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(0, largest_product(2, "0000"));
}

void test_reports_zero_if_all_spans_include_zero(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(0, largest_product(3, "99099"));
}

void test_rejects_span_longer_than_string_length(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(INSUFFICIENT_DIGITS, largest_product(4, "123"));
}

void test_reports_1_for_empty_string_and_empty_product_0_span(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(1, largest_product(0, ""));
}

void test_reports_1_for_nonempty_string_and_empty_product_0_span(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(1, largest_product(0, "123"));
}

void test_rejects_empty_string_and_nonzero_span(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(INSUFFICIENT_DIGITS, largest_product(1, ""));
}

void test_rejects_invalid_character_in_digits(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(INVALID_CHARACTER, largest_product(2, "1234a5"));
}

void test_rejects_negative_span(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(NEGATIVE_SPAN, largest_product(-1, "12345"));
}

void test_large_span(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT64(131681894400, largest_product(17, "98765432123456789"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_finds_the_largest_product_if_span_equals_length);
    RUN_TEST(test_can_find_the_largest_product_of_2_with_numbers_in_order);
    RUN_TEST(test_can_find_the_largest_product_of_2);
    RUN_TEST(test_can_find_the_largest_product_of_3_with_numbers_in_order);
    RUN_TEST(test_can_find_the_largest_product_of_3);
    RUN_TEST(test_can_find_the_largest_product_of_5_with_numbers_in_order);
    RUN_TEST(test_can_get_the_largest_product_of_a_big_number);
    RUN_TEST(test_reports_zero_if_the_only_digits_are_zero);
    RUN_TEST(test_reports_zero_if_all_spans_include_zero);
    RUN_TEST(test_rejects_span_longer_than_string_length);
    RUN_TEST(test_reports_1_for_empty_string_and_empty_product_0_span);
    RUN_TEST(test_reports_1_for_nonempty_string_and_empty_product_0_span);
    RUN_TEST(test_rejects_empty_string_and_nonzero_span);
    RUN_TEST(test_rejects_invalid_character_in_digits);
    RUN_TEST(test_rejects_negative_span);
    RUN_TEST(test_large_span);
    return UNITY_END();
}

