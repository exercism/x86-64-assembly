// Version: 1.2.0

#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void rotate(const char *text, int shift_key, char *buffer);

void setUp(void) {
}

void tearDown(void) {
}

void test_rotate_a_by_0_same_output_as_input(void) {
    char buffer[BUFFER_SIZE];

    rotate("a", 0, buffer);
    TEST_ASSERT_EQUAL_STRING("a", buffer);
}

void test_rotate_a_by_1(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    rotate("a", 1, buffer);
    TEST_ASSERT_EQUAL_STRING("b", buffer);
}

void test_rotate_a_by_26_same_output_as_input(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    rotate("a", 26, buffer);
    TEST_ASSERT_EQUAL_STRING("a", buffer);
}

void test_rotate_m_by_13(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    rotate("m", 13, buffer);
    TEST_ASSERT_EQUAL_STRING("z", buffer);
}

void test_rotate_n_by_13_with_wrap_around_alphabet(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    rotate("n", 13, buffer);
    TEST_ASSERT_EQUAL_STRING("a", buffer);
}

void test_rotate_capital_letters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    rotate("OMG", 5, buffer);
    TEST_ASSERT_EQUAL_STRING("TRL", buffer);
}

void test_rotate_spaces(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    rotate("O M G", 5, buffer);
    TEST_ASSERT_EQUAL_STRING("T R L", buffer);
}

void test_rotate_numbers(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    rotate("Testing 1 2 3 testing", 4, buffer);
    TEST_ASSERT_EQUAL_STRING("Xiwxmrk 1 2 3 xiwxmrk", buffer);
}

void test_rotate_punctuation(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    rotate("Let's eat, Grandma!", 21, buffer);
    TEST_ASSERT_EQUAL_STRING("Gzo'n zvo, Bmviyhv!", buffer);
}

void test_rotate_all_letters(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    rotate("The quick brown fox jumps over the lazy dog.", 13, buffer);
    TEST_ASSERT_EQUAL_STRING("Gur dhvpx oebja sbk whzcf bire gur ynml qbt.", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_rotate_a_by_0_same_output_as_input);
    RUN_TEST(test_rotate_a_by_1);
    RUN_TEST(test_rotate_a_by_26_same_output_as_input);
    RUN_TEST(test_rotate_m_by_13);
    RUN_TEST(test_rotate_n_by_13_with_wrap_around_alphabet);
    RUN_TEST(test_rotate_capital_letters);
    RUN_TEST(test_rotate_spaces);
    RUN_TEST(test_rotate_numbers);
    RUN_TEST(test_rotate_punctuation);
    RUN_TEST(test_rotate_all_letters);
    return UNITY_END();
}
