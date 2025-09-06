#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 52
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern size_t rows(char buffer[][BUFFER_SIZE], char letter);

void setUp(void) {
}

void tearDown(void) {
}

void test_degenerate_case_with_a_single_a_row(void) {
    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *const expected[] = {"A"};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), rows(buffer, 'A'));

    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_degenerate_case_with_no_row_containing_3_distinct_groups_of_spaces(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *const expected[] = {" A ",

                                    "B B",

                                    " A "};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), rows(buffer, 'B'));

    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_smallest_nondegenerate_case_with_odd_diamond_side_length(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *const expected[] = {"  A  ",

                                    " B B ",

                                    "C   C",

                                    " B B ",

                                    "  A  "};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), rows(buffer, 'C'));

    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_smallest_nondegenerate_case_with_even_diamond_side_length(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *const expected[] = {"   A   ",

                                    "  B B  ",

                                    " C   C ",

                                    "D     D",

                                    " C   C ",

                                    "  B B  ",

                                    "   A   "};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), rows(buffer, 'D'));

    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_largest_possible_diamond(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE][BUFFER_SIZE];
    const char *const expected[] = {"                         A                         ",

                                    "                        B B                        ",

                                    "                       C   C                       ",

                                    "                      D     D                      ",

                                    "                     E       E                     ",

                                    "                    F         F                    ",

                                    "                   G           G                   ",

                                    "                  H             H                  ",

                                    "                 I               I                 ",

                                    "                J                 J                ",

                                    "               K                   K               ",

                                    "              L                     L              ",

                                    "             M                       M             ",

                                    "            N                         N            ",

                                    "           O                           O           ",

                                    "          P                             P          ",

                                    "         Q                               Q         ",

                                    "        R                                 R        ",

                                    "       S                                   S       ",

                                    "      T                                     T      ",

                                    "     U                                       U     ",

                                    "    V                                         V    ",

                                    "   W                                           W   ",

                                    "  X                                             X  ",

                                    " Y                                               Y ",

                                    "Z                                                 Z",

                                    " Y                                               Y ",

                                    "  X                                             X  ",

                                    "   W                                           W   ",

                                    "    V                                         V    ",

                                    "     U                                       U     ",

                                    "      T                                     T      ",

                                    "       S                                   S       ",

                                    "        R                                 R        ",

                                    "         Q                               Q         ",

                                    "          P                             P          ",

                                    "           O                           O           ",

                                    "            N                         N            ",

                                    "             M                       M             ",

                                    "              L                     L              ",

                                    "               K                   K               ",

                                    "                J                 J                ",

                                    "                 I               I                 ",

                                    "                  H             H                  ",

                                    "                   G           G                   ",

                                    "                    F         F                    ",

                                    "                     E       E                     ",

                                    "                      D     D                      ",

                                    "                       C   C                       ",

                                    "                        B B                        ",

                                    "                         A                         "};

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), rows(buffer, 'Z'));

    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_degenerate_case_with_a_single_a_row);
    RUN_TEST(test_degenerate_case_with_no_row_containing_3_distinct_groups_of_spaces);
    RUN_TEST(test_smallest_nondegenerate_case_with_odd_diamond_side_length);
    RUN_TEST(test_smallest_nondegenerate_case_with_even_diamond_side_length);
    RUN_TEST(test_largest_possible_diamond);
    return UNITY_END();
}
