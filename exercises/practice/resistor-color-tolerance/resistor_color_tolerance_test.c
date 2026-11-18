#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 40

extern void label(char *buffer, const char **colors);

void setUp(void) {
}

void tearDown(void) {
}

void test_orange_orange_black_and_red(void) {
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"orange", "orange", "black", "red", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("33 ohms ±2%", buffer);
}

void test_blue_gray_brown_and_violet(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"blue", "grey", "brown", "violet", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("680 ohms ±0.1%", buffer);
}

void test_red_black_red_and_green(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"red", "black", "red", "green", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("2 kiloohms ±0.5%", buffer);
}

void test_green_brownm_orange_and_grey(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"green", "brown", "orange", "grey", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("51 kiloohms ±0.05%", buffer);
}

void test_only_one_band(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"black", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("0 ohms", buffer);
}

void test_orange_orange_yellow_black_and_brown(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"orange", "orange", "yellow", "black", "brown", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("334 ohms ±1%", buffer);
}

void test_red_green_yellow_yellow_and_brown(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"red", "green", "yellow", "yellow", "brown", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("2.54 megaohms ±1%", buffer);
}

void test_blue_gray_white_brown_and_brown(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"blue", "grey", "white", "brown", "brown", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("6.89 kiloohms ±1%", buffer);
}

void test_violet_orange_red_and_gray(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"violet", "orange", "red", "grey", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("7.3 kiloohms ±0.05%", buffer);
}

void test_brown_red_orange_green_and_blue(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"brown", "red", "orange", "green", "blue", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("12.3 megaohms ±0.25%", buffer);
}

void test_brown_black_brown_yellow_and_violet(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"brown", "black", "brown", "yellow", "violet", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("1.01 megaohms ±0.1%", buffer);
}

void test_brown_black_red_and_red(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"brown", "black", "red", "red", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("1 kiloohms ±2%", buffer);
}

void test_orange_orange_red_and_gold(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"orange", "orange", "red", "gold", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("3.3 kiloohms ±5%", buffer);
}

void test_orange_orange_green_and_silver(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"orange", "orange", "green", "silver", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("3.3 megaohms ±10%", buffer);
}

void test_white_white_violet_and_green(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"white", "white", "violet", "green", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("990 megaohms ±0.5%", buffer);
}

void test_white_white_grey_and_blue(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    const char *colors[] = {"white", "white", "grey", "blue", NULL};
    label(buffer, colors);
    TEST_ASSERT_EQUAL_STRING("9.9 gigaohms ±0.25%", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_orange_orange_black_and_red);
    RUN_TEST(test_blue_gray_brown_and_violet);
    RUN_TEST(test_red_black_red_and_green);
    RUN_TEST(test_green_brownm_orange_and_grey);
    RUN_TEST(test_only_one_band);
    RUN_TEST(test_orange_orange_yellow_black_and_brown);
    RUN_TEST(test_red_green_yellow_yellow_and_brown);
    RUN_TEST(test_blue_gray_white_brown_and_brown);
    RUN_TEST(test_violet_orange_red_and_gray);
    RUN_TEST(test_brown_red_orange_green_and_blue);
    RUN_TEST(test_brown_black_brown_yellow_and_violet);
    RUN_TEST(test_brown_black_red_and_red);
    RUN_TEST(test_orange_orange_red_and_gold);
    RUN_TEST(test_orange_orange_green_and_silver);
    RUN_TEST(test_white_white_violet_and_green);
    RUN_TEST(test_white_white_grey_and_blue);
    return UNITY_END();
}
