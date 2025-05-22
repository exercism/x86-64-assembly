// Version: 0

#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 80

extern void annotate(char *buffer, const char *minefield);

void setUp(void) {
}

void tearDown(void) {
}

void test_no_rows(void) {
    const char *minefield =
        "";
    const char *expected =
        "";
    char buffer[BUFFER_SIZE];

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_no_columns(void) {
    TEST_IGNORE();
    const char *minefield =
        "\n";
    const char *expected =
        "\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_no_mines(void) {
    TEST_IGNORE();
    const char *minefield =
        "   \n"
        "   \n"
        "   \n";
    const char *expected =
        "   \n"
        "   \n"
        "   \n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_minefield_with_only_mines(void) {
    TEST_IGNORE();
    const char *minefield =
        "***\n"
        "***\n"
        "***\n";
    const char *expected =
        "***\n"
        "***\n"
        "***\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_mine_surrounded_by_spaces(void) {
    TEST_IGNORE();
    const char *minefield =
        "   \n"
        " * \n"
        "   \n";
    const char *expected =
        "111\n"
        "1*1\n"
        "111\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_space_surrounded_by_mines(void) {
    TEST_IGNORE();
    const char *minefield =
        "***\n"
        "* *\n"
        "***\n";
    const char *expected =
        "***\n"
        "*8*\n"
        "***\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_horizontal_line(void) {
    TEST_IGNORE();
    const char *minefield =
        " * * \n";
    const char *expected =
        "1*2*1\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_horizontal_line_mines_at_edges(void) {
    TEST_IGNORE();
    const char *minefield =
        "*   *\n";
    const char *expected =
        "*1 1*\n";
    char buffer[BUFFER_SIZE];

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_vertical_line(void) {
    TEST_IGNORE();
    const char *minefield =
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

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_vertical_line_mines_at_edges(void) {
    TEST_IGNORE();
    const char *minefield =
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

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_cross(void) {
    TEST_IGNORE();
    const char *minefield =
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

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_large_minefield(void) {
    TEST_IGNORE();
    const char *minefield =
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

    annotate(buffer, minefield);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_no_rows);
    RUN_TEST(test_no_columns);
    RUN_TEST(test_no_mines);
    RUN_TEST(test_minefield_with_only_mines);
    RUN_TEST(test_mine_surrounded_by_spaces);
    RUN_TEST(test_space_surrounded_by_mines);
    RUN_TEST(test_horizontal_line);
    RUN_TEST(test_horizontal_line_mines_at_edges);
    RUN_TEST(test_vertical_line);
    RUN_TEST(test_vertical_line_mines_at_edges);
    RUN_TEST(test_cross);
    RUN_TEST(test_large_minefield);
    return UNITY_END();
}
