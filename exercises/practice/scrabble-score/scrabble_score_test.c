// Version: 0

#include "vendor/unity.h"

extern int score(const char *score);

void setUp(void) {
}

void tearDown(void) {
}

void test_lowercase_letter(void) {
    TEST_ASSERT_EQUAL(1, score("a"));
}

void test_uppercase_letter(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(1, score("A"));
}

void test_valuable_letter(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(4, score("f"));
}

void test_short_word(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(2, score("at"));
}

void test_short_valuable_word(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(12, score("zoo"));
}

void test_medium_word(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(6, score("street"));
}

void test_medium_valuable_word(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(22, score("quirky"));
}

void test_long_mixedcase_word(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(41, score("OxyphenButazone"));
}

void test_englishlike_word(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(8, score("pinata"));
}

void test_empty_input(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(0, score(""));
}

void test_entire_alphabet_available(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(87, score("abcdefghijklmnopqrstuvwxyz"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_lowercase_letter);
    RUN_TEST(test_uppercase_letter);
    RUN_TEST(test_valuable_letter);
    RUN_TEST(test_short_word);
    RUN_TEST(test_short_valuable_word);
    RUN_TEST(test_medium_word);
    RUN_TEST(test_medium_valuable_word);
    RUN_TEST(test_long_mixedcase_word);
    RUN_TEST(test_englishlike_word);
    RUN_TEST(test_empty_input);
    RUN_TEST(test_entire_alphabet_available);
    return UNITY_END();
}
