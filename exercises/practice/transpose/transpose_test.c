#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 32
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern size_t transpose(char buffer[][BUFFER_SIZE], const char *lines[], size_t num_of_lines);

void setUp(void) {
}

void tearDown(void) {
}

void test_empty_string(void) {
    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const size_t length = transpose(buffer, NULL, 0);
    TEST_ASSERT_EQUAL_UINT64(0, length);
}

void test_two_characters_in_a_row(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"A1"};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"A", "1"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_two_characters_in_a_column(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"A", "1"};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"A1"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_simple(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"ABC", "123"};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"A1", "B2", "C3"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_single_line(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"Single line."};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"S", "i", "n", "g", "l", "e", " ", "l", "i", "n", "e", "."};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_first_line_longer_than_second_line(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"The fourth line.", "The fifth line."};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"TT", "hh", "ee", "  ", "ff", "oi", "uf", "rt", "th", "h ", " l", "li", "in", "ne", "e.", "."};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_second_line_longer_than_first_line(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"The first line.", "The second line."};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"TT", "hh", "ee", "  ", "fs", "ie", "rc", "so", "tn", " d", "l ", "il", "ni", "en", ".e", " ."};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_mixed_line_length(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"The longest line.", "A long line.", "A longer line.", "A line."};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"TAAA", "h   ", "elll", " ooi", "lnnn", "ogge", "n e.", "glr", "ei ",
                              "snl",  "tei",  " .n",  "l e",  "i .",  "n",    "e",    "."};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_square(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"HEART", "EMBER", "ABUSE", "RESIN", "TREND"};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"HEART", "EMBER", "ABUSE", "RESIN", "TREND"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_rectangle(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"FRACTURE", "OUTLINED", "BLOOMING", "SEPTETTE"};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"FOBS", "RULE", "ATOP", "CLOT", "TIME", "UNIT", "RENT", "EDGE"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_triangle(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"T", "EE", "AAA", "SSSS", "EEEEE", "RRRRRR"};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"TEASER", " EASER", "  ASER", "   SER", "    ER", "     R"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_jagged_triangle(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *lines[] = {"11", "2", "3333", "444", "555555", "66666"};
    const size_t length = transpose(buffer, lines, ARRAY_SIZE(lines));
    const char *expected[] = {"123456", "1 3456", "  3456", "  3 56", "    56", "    5"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_string);
    RUN_TEST(test_two_characters_in_a_row);
    RUN_TEST(test_two_characters_in_a_column);
    RUN_TEST(test_simple);
    RUN_TEST(test_single_line);
    RUN_TEST(test_first_line_longer_than_second_line);
    RUN_TEST(test_second_line_longer_than_first_line);
    RUN_TEST(test_mixed_line_length);
    RUN_TEST(test_square);
    RUN_TEST(test_rectangle);
    RUN_TEST(test_triangle);
    RUN_TEST(test_jagged_triangle);
    return UNITY_END();
}
