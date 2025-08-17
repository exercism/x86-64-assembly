#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 20

extern void label(char *buffer, const char **colors);

void setUp(void) {
}

void tearDown(void) {
}

void test_orange_and_orange_and_black(void) {
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"orange", "orange", "black", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("33 ohms", buffer);
}

void test_blue_and_grey_and_brown(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"blue", "grey", "brown", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("680 ohms", buffer);
}

void test_red_and_black_and_red(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"red", "black", "red", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("2 kiloohms", buffer);
}

void test_green_and_brown_and_orange(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"green", "brown", "orange", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("51 kiloohms", buffer);
}

void test_yellow_and_violet_and_yellow(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"yellow", "violet", "yellow", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("470 kiloohms", buffer);
}

void test_blue_and_violet_and_blue(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"blue", "violet", "blue", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("67 megaohms", buffer);
}

void test_minimum_possible_value(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"black", "black", "black", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("0 ohms", buffer);
}

void test_maximum_possible_value(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"white", "white", "white", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("99 gigaohms", buffer);
}

void test_first_two_colors_make_an_invalid_octal_number(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"black", "grey", "black", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("8 ohms", buffer);
}

void test_ignore_extra_colors(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"blue", "green", "yellow", "orange", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("650 kiloohms", buffer);
}

void test_orange_and_orange_and_red(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"orange", "orange", "red", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("3.3 kiloohms", buffer);
}

void test_orange_and_orange_and_green(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"orange", "orange", "green", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("3.3 megaohms", buffer);
}

void test_white_and_white_and_violet(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"white", "white", "violet", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("990 megaohms", buffer);
}

void test_white_and_white_and_grey(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"white", "white", "grey", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("9.9 gigaohms", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_orange_and_orange_and_black);
    RUN_TEST(test_blue_and_grey_and_brown);
    RUN_TEST(test_red_and_black_and_red);
    RUN_TEST(test_green_and_brown_and_orange);
    RUN_TEST(test_yellow_and_violet_and_yellow);
    RUN_TEST(test_blue_and_violet_and_blue);
    RUN_TEST(test_minimum_possible_value);
    RUN_TEST(test_maximum_possible_value);
    RUN_TEST(test_first_two_colors_make_an_invalid_octal_number);
    RUN_TEST(test_ignore_extra_colors);
    RUN_TEST(test_orange_and_orange_and_red);
    RUN_TEST(test_orange_and_orange_and_green);
    RUN_TEST(test_white_and_white_and_violet);
    RUN_TEST(test_white_and_white_and_grey);
    return UNITY_END();
}
