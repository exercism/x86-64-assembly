#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void clean(char *buffer, const char *phrase);

void setUp(void) {
}

void tearDown(void) {
}

void test_cleans_the_number(void) {
    char buffer[BUFFER_SIZE];

    clean(buffer, "(223) 456-7890");
    TEST_ASSERT_EQUAL_STRING("2234567890", buffer);
}

void test_cleans_numbers_with_dots(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "223.456.7890");
    TEST_ASSERT_EQUAL_STRING("2234567890", buffer);
}

void test_cleans_numbers_with_multiple_spaces(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "223 456   7890   ");
    TEST_ASSERT_EQUAL_STRING("2234567890", buffer);
}

void test_invalid_when_9_digits(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "123456789");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_when_11_digits_does_not_start_with_a_1(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "22234567890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_valid_when_11_digits_and_starting_with_1(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "12234567890");
    TEST_ASSERT_EQUAL_STRING("2234567890", buffer);
}

void test_valid_when_11_digits_and_starting_with_1_even_with_punctuation(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "+1 (223) 456-7890");
    TEST_ASSERT_EQUAL_STRING("2234567890", buffer);
}

void test_invalid_when_more_than_11_digits(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "321234567890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_with_letters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "523-abc-7890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_with_punctuations(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "523-@:!-7890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_if_area_code_starts_with_0(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "(023) 456-7890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_if_area_code_starts_with_1(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "(123) 456-7890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_if_exchange_code_starts_with_0(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "(223) 056-7890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_if_exchange_code_starts_with_1(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "(223) 156-7890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_if_area_code_starts_with_0_on_valid_11digit_number(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "1 (023) 456-7890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_if_area_code_starts_with_1_on_valid_11digit_number(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "1 (123) 456-7890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_if_exchange_code_starts_with_0_on_valid_11digit_number(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "1 (223) 056-7890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

void test_invalid_if_exchange_code_starts_with_1_on_valid_11digit_number(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    clean(buffer, "1 (223) 156-7890");
    TEST_ASSERT_EQUAL_STRING("", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_cleans_the_number);
    RUN_TEST(test_cleans_numbers_with_dots);
    RUN_TEST(test_cleans_numbers_with_multiple_spaces);
    RUN_TEST(test_invalid_when_9_digits);
    RUN_TEST(test_invalid_when_11_digits_does_not_start_with_a_1);
    RUN_TEST(test_valid_when_11_digits_and_starting_with_1);
    RUN_TEST(test_valid_when_11_digits_and_starting_with_1_even_with_punctuation);
    RUN_TEST(test_invalid_when_more_than_11_digits);
    RUN_TEST(test_invalid_with_letters);
    RUN_TEST(test_invalid_with_punctuations);
    RUN_TEST(test_invalid_if_area_code_starts_with_0);
    RUN_TEST(test_invalid_if_area_code_starts_with_1);
    RUN_TEST(test_invalid_if_exchange_code_starts_with_0);
    RUN_TEST(test_invalid_if_exchange_code_starts_with_1);
    RUN_TEST(test_invalid_if_area_code_starts_with_0_on_valid_11digit_number);
    RUN_TEST(test_invalid_if_area_code_starts_with_1_on_valid_11digit_number);
    RUN_TEST(test_invalid_if_exchange_code_starts_with_0_on_valid_11digit_number);
    RUN_TEST(test_invalid_if_exchange_code_starts_with_1_on_valid_11digit_number);
    return UNITY_END();
}
