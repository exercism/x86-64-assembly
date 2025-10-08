#include "vendor/unity.h"

#include <stdint.h>

#define BUFFER_SIZE 100

extern void format(char *buffer, const char *name, uint16_t number);

void setUp(void) {
}

void tearDown(void) {
}

void test_format_smallest_nonexceptional_ordinal_numeral_4(void) {
    char buffer[BUFFER_SIZE];
    format(buffer, "Gianna", 4);
    TEST_ASSERT_EQUAL_STRING("Gianna, you are the 4th customer we serve today. Thank you!", buffer);
}

void test_format_greatest_single_digit_nonexceptional_ordinal_numeral_9(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Maarten", 9);
    TEST_ASSERT_EQUAL_STRING("Maarten, you are the 9th customer we serve today. Thank you!", buffer);
}

void test_format_nonexceptional_ordinal_numeral_5(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Petronila", 5);
    TEST_ASSERT_EQUAL_STRING("Petronila, you are the 5th customer we serve today. Thank you!", buffer);
}

void test_format_nonexceptional_ordinal_numeral_6(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Attakullakulla", 6);
    TEST_ASSERT_EQUAL_STRING("Attakullakulla, you are the 6th customer we serve today. Thank you!", buffer);
}

void test_format_nonexceptional_ordinal_numeral_7(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Kate", 7);
    TEST_ASSERT_EQUAL_STRING("Kate, you are the 7th customer we serve today. Thank you!", buffer);
}

void test_format_nonexceptional_ordinal_numeral_8(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Maximiliano", 8);
    TEST_ASSERT_EQUAL_STRING("Maximiliano, you are the 8th customer we serve today. Thank you!", buffer);
}

void test_format_exceptional_ordinal_numeral_1(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Mary", 1);
    TEST_ASSERT_EQUAL_STRING("Mary, you are the 1st customer we serve today. Thank you!", buffer);
}

void test_format_exceptional_ordinal_numeral_2(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Haruto", 2);
    TEST_ASSERT_EQUAL_STRING("Haruto, you are the 2nd customer we serve today. Thank you!", buffer);
}

void test_format_exceptional_ordinal_numeral_3(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Henriette", 3);
    TEST_ASSERT_EQUAL_STRING("Henriette, you are the 3rd customer we serve today. Thank you!", buffer);
}

void test_format_smallest_two_digit_nonexceptional_ordinal_numeral_10(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Alvarez", 10);
    TEST_ASSERT_EQUAL_STRING("Alvarez, you are the 10th customer we serve today. Thank you!", buffer);
}

void test_format_nonexceptional_ordinal_numeral_11(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Jacqueline", 11);
    TEST_ASSERT_EQUAL_STRING("Jacqueline, you are the 11th customer we serve today. Thank you!", buffer);
}

void test_format_nonexceptional_ordinal_numeral_12(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Juan", 12);
    TEST_ASSERT_EQUAL_STRING("Juan, you are the 12th customer we serve today. Thank you!", buffer);
}

void test_format_nonexceptional_ordinal_numeral_13(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Patricia", 13);
    TEST_ASSERT_EQUAL_STRING("Patricia, you are the 13th customer we serve today. Thank you!", buffer);
}

void test_format_exceptional_ordinal_numeral_21(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Washi", 21);
    TEST_ASSERT_EQUAL_STRING("Washi, you are the 21st customer we serve today. Thank you!", buffer);
}

void test_format_exceptional_ordinal_numeral_62(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Nayra", 62);
    TEST_ASSERT_EQUAL_STRING("Nayra, you are the 62nd customer we serve today. Thank you!", buffer);
}

void test_format_exceptional_ordinal_numeral_100(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "John", 100);
    TEST_ASSERT_EQUAL_STRING("John, you are the 100th customer we serve today. Thank you!", buffer);
}

void test_format_exceptional_ordinal_numeral_101(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Zeinab", 101);
    TEST_ASSERT_EQUAL_STRING("Zeinab, you are the 101st customer we serve today. Thank you!", buffer);
}

void test_format_nonexceptional_ordinal_numeral_112(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Knud", 112);
    TEST_ASSERT_EQUAL_STRING("Knud, you are the 112th customer we serve today. Thank you!", buffer);
}

void test_format_exceptional_ordinal_numeral_123(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    format(buffer, "Yma", 123);
    TEST_ASSERT_EQUAL_STRING("Yma, you are the 123rd customer we serve today. Thank you!", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_format_smallest_nonexceptional_ordinal_numeral_4);
    RUN_TEST(test_format_greatest_single_digit_nonexceptional_ordinal_numeral_9);
    RUN_TEST(test_format_nonexceptional_ordinal_numeral_5);
    RUN_TEST(test_format_nonexceptional_ordinal_numeral_6);
    RUN_TEST(test_format_nonexceptional_ordinal_numeral_7);
    RUN_TEST(test_format_nonexceptional_ordinal_numeral_8);
    RUN_TEST(test_format_exceptional_ordinal_numeral_1);
    RUN_TEST(test_format_exceptional_ordinal_numeral_2);
    RUN_TEST(test_format_exceptional_ordinal_numeral_3);
    RUN_TEST(test_format_smallest_two_digit_nonexceptional_ordinal_numeral_10);
    RUN_TEST(test_format_nonexceptional_ordinal_numeral_11);
    RUN_TEST(test_format_nonexceptional_ordinal_numeral_12);
    RUN_TEST(test_format_nonexceptional_ordinal_numeral_13);
    RUN_TEST(test_format_exceptional_ordinal_numeral_21);
    RUN_TEST(test_format_exceptional_ordinal_numeral_62);
    RUN_TEST(test_format_exceptional_ordinal_numeral_100);
    RUN_TEST(test_format_exceptional_ordinal_numeral_101);
    RUN_TEST(test_format_nonexceptional_ordinal_numeral_112);
    RUN_TEST(test_format_exceptional_ordinal_numeral_123);
    return UNITY_END();
}
