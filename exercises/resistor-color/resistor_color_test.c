#include "unity/unity.h"

extern int color_code(const char *color);
extern const char **colors(void);

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

void setUp(void) {
}

void tearDown(void) {
}

void test_black(void) {
    TEST_ASSERT_EQUAL_INT(0, color_code("black"));
}

void test_white(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(9, color_code("white"));
}

void test_orange(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(3, color_code("orange"));
}

void test_colors(void) {
    TEST_IGNORE();
    const char *expected[] = {"black", "brown", "red",    "orange", "yellow",
                              "green", "blue",  "violet", "grey",   "white"};

    TEST_ASSERT_EQUAL_STRING_ARRAY(expected, colors(), ARRAY_SIZE(expected));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_black);
    RUN_TEST(test_white);
    RUN_TEST(test_orange);
    RUN_TEST(test_colors);
    return UNITY_END();
}
