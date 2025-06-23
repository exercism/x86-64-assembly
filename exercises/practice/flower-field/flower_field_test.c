#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 80

extern void annotate(char *buffer, const char *garden);

void setUp(void) {
}

void tearDown(void) {
}

void test_no_rows(void) {
    const char *garden = "";
    const char *expected = "";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_no_columns(void) {
    TEST_IGNORE();
    const char *garden = "\n";
    const char *expected = "\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_no_flowers(void) {
    TEST_IGNORE();
    const char *garden =
        "   \n"
        "   \n"
        "   \n";
    const char *expected =
        "   \n"
        "   \n"
        "   \n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_garden_full_of_flowers(void) {
    TEST_IGNORE();
    const char *garden =
        "***\n"
        "***\n"
        "***\n";
    const char *expected =
        "***\n"
        "***\n"
        "***\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_flower_surrounded_by_spaces(void) {
    TEST_IGNORE();
    const char *garden =
        "   \n"
        " * \n"
        "   \n";
    const char *expected =
        "111\n"
        "1*1\n"
        "111\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_space_surrounded_by_flowers(void) {
    TEST_IGNORE();
    const char *garden =
        "***\n"
        "* *\n"
        "***\n";
    const char *expected =
        "***\n"
        "*8*\n"
        "***\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_horizontal_line(void) {
    TEST_IGNORE();
    const char *garden = " * * \n";
    const char *expected = "1*2*1\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_horizontal_line_flowers_at_edges(void) {
    TEST_IGNORE();
    const char *garden = "*   *\n";
    const char *expected = "*1 1*\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_vertical_line(void) {
    TEST_IGNORE();
    const char *garden =
        " \n"
        "*\n"
        " \n"
        "*\n"
        " \n";
    const char *expected =
        "1\n"
        "*\n"
        "2\n"
        "*\n"
        "1\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_vertical_line_flowers_at_edges(void) {
    TEST_IGNORE();
    const char *garden =
        "*\n"
        " \n"
        " \n"
        " \n"
        "*\n";
    const char *expected =
        "*\n"
        "1\n"
        " \n"
        "1\n"
        "*\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_cross(void) {
    TEST_IGNORE();
    const char *garden =
        "  *  \n"
        "  *  \n"
        "*****\n"
        "  *  \n"
        "  *  \n";
    const char *expected =
        " 2*2 \n"
        "25*52\n"
        "*****\n"
        "25*52\n"
        " 2*2 \n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_large_garden(void) {
    TEST_IGNORE();
    const char *garden =
        " *  * \n"
        "  *   \n"
        "    * \n"
        "   * *\n"
        " *  * \n"
        "      \n";
    const char *expected =
        "1*22*1\n"
        "12*322\n"
        " 123*2\n"
        "112*4*\n"
        "1*22*2\n"
        "111111\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, garden);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_no_rows);
    RUN_TEST(test_no_columns);
    RUN_TEST(test_no_flowers);
    RUN_TEST(test_garden_full_of_flowers);
    RUN_TEST(test_flower_surrounded_by_spaces);
    RUN_TEST(test_space_surrounded_by_flowers);
    RUN_TEST(test_horizontal_line);
    RUN_TEST(test_horizontal_line_flowers_at_edges);
    RUN_TEST(test_vertical_line);
    RUN_TEST(test_vertical_line_flowers_at_edges);
    RUN_TEST(test_cross);
    RUN_TEST(test_large_garden);
    return UNITY_END();
}
