// Version: 1.2.0

#include "vendor/unity.h"

extern void reverse(char *value);

void setUp(void) {
}

void tearDown(void) {
}

void test_an_empty_string(void) {
    char value[] = "";

    reverse(value);
    TEST_ASSERT_EQUAL_STRING("", value);
}

void test_a_word(void) {
    TEST_IGNORE();
    char value[] = "robot";

    reverse(value);
    TEST_ASSERT_EQUAL_STRING("tobor", value);
}

void test_a_capitalized_word(void) {
    TEST_IGNORE();
    char value[] = "Ramen";

    reverse(value);
    TEST_ASSERT_EQUAL_STRING("nemaR", value);
}

void test_a_sentence_with_punctuation(void) {
    TEST_IGNORE();
    char value[] = "I'm hungry!";

    reverse(value);
    TEST_ASSERT_EQUAL_STRING("!yrgnuh m'I", value);
}

void test_a_palindrome(void) {
    TEST_IGNORE();
    char value[] = "racecar";

    reverse(value);
    TEST_ASSERT_EQUAL_STRING("racecar", value);
}

void test_an_evensized_word(void) {
    TEST_IGNORE();
    char value[] = "drawer";

    reverse(value);
    TEST_ASSERT_EQUAL_STRING("reward", value);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_an_empty_string);
    RUN_TEST(test_a_word);
    RUN_TEST(test_a_capitalized_word);
    RUN_TEST(test_a_sentence_with_punctuation);
    RUN_TEST(test_a_palindrome);
    RUN_TEST(test_an_evensized_word);
    return UNITY_END();
}
