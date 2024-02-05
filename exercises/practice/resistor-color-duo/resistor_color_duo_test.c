// Version: 1.0.0

#include "vendor/unity.h"

extern int value(const char *first, const char *second, const char *third);

void setUp(void) {
}

void tearDown(void) {
}

void test_brown_and_black(void) {
    TEST_ASSERT_EQUAL_INT(10, value("brown", "black", NULL));
}

void test_blue_and_grey(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(68, value("blue", "grey", NULL));
}

void test_yellow_and_violet(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(47, value("yellow", "violet", NULL));
}

void test_white_and_red(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(92, value("white", "red", NULL));
}

void test_orange_and_orange(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(33, value("orange", "orange", NULL));
}

void test_ignore_additional_colors(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(51, value("green", "brown", "orange"));
}

void test_black_and_brown_one_digit(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(1, value("black", "brown", NULL));
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
