#include "vendor/unity.h"

extern int value(const char *first, const char *second, const char *third);

void setUp(void) {
}

void tearDown(void) {
}

void test_brown_and_black(void) {
    const int result = value("brown", "black", NULL);
    TEST_ASSERT_EQUAL_INT(10, result);
}

void test_blue_and_grey(void) {
    TEST_IGNORE();
    const int result = value("blue", "grey", NULL);
    TEST_ASSERT_EQUAL_INT(68, result);
}

void test_yellow_and_violet(void) {
    TEST_IGNORE();
    const int result = value("yellow", "violet", NULL);
    TEST_ASSERT_EQUAL_INT(47, result);
}

void test_white_and_red(void) {
    TEST_IGNORE();
    const int result = value("white", "red", NULL);
    TEST_ASSERT_EQUAL_INT(92, result);
}

void test_orange_and_orange(void) {
    TEST_IGNORE();
    const int result = value("orange", "orange", NULL);
    TEST_ASSERT_EQUAL_INT(33, result);
}

void test_ignore_additional_colors(void) {
    TEST_IGNORE();
    const int result = value("green", "brown", "orange");
    TEST_ASSERT_EQUAL_INT(51, result);
}

void test_black_and_brown_one_digit(void) {
    TEST_IGNORE();
    const int result = value("black", "brown", NULL);
    TEST_ASSERT_EQUAL_INT(1, result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_brown_and_black);
    RUN_TEST(test_blue_and_grey);
    RUN_TEST(test_yellow_and_violet);
    RUN_TEST(test_white_and_red);
    RUN_TEST(test_orange_and_orange);
    RUN_TEST(test_ignore_additional_colors);
    RUN_TEST(test_black_and_brown_one_digit);
    return UNITY_END();
}
