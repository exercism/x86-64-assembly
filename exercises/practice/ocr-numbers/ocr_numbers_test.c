#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 20
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef enum {
    success = 0,
    invalid_lines,
    invalid_columns
} error_t;

extern error_t convert(char buffer[], const char *const rows[], size_t num_of_rows);

void setUp(void) {
}

void tearDown(void) {
}

void test_recognizes_0(void) {
    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        " _ ",
        "| |",
        "|_|",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("0", buffer);
}

void test_recognizes_1(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        "   ",
        "  |",
        "  |",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("1", buffer);
}

void test_unreadable_but_correctly_sized_inputs_return_(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        "   ",
        "  _",
        "  |",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("?", buffer);
}

void test_input_with_a_number_of_lines_that_is_not_a_multiple_of_four_raises_an_error(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        " _ ",
        "| |",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(invalid_lines, convert(buffer, rows, ARRAY_SIZE(rows)));
}

void test_input_with_a_number_of_columns_that_is_not_a_multiple_of_three_raises_an_error(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        "    ",
        "   |",
        "   |",
        "    ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(invalid_columns, convert(buffer, rows, ARRAY_SIZE(rows)));
}

void test_recognizes_110101100(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        "       _     _        _  _ ",
        "  |  || |  || |  |  || || |",
        "  |  ||_|  ||_|  |  ||_||_|",
        "                           ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("110101100", buffer);
}

void test_garbled_numbers_in_a_string_are_replaced_with_(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        "       _     _           _ ",
        "  |  || |  || |     || || |",
        "  |  | _|  ||_|  |  ||_||_|",
        "                           ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("11?10?1?0", buffer);
}

void test_recognizes_2(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        " _ ",
        " _|",
        "|_ ",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("2", buffer);
}

void test_recognizes_3(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        " _ ",
        " _|",
        " _|",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("3", buffer);
}

void test_recognizes_4(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        "   ",
        "|_|",
        "  |",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("4", buffer);
}

void test_recognizes_5(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        " _ ",
        "|_ ",
        " _|",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("5", buffer);
}

void test_recognizes_6(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        " _ ",
        "|_ ",
        "|_|",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("6", buffer);
}

void test_recognizes_7(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        " _ ",
        "  |",
        "  |",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("7", buffer);
}

void test_recognizes_8(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        " _ ",
        "|_|",
        "|_|",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("8", buffer);
}

void test_recognizes_9(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        " _ ",
        "|_|",
        " _|",
        "   ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("9", buffer);
}

void test_recognizes_string_of_decimal_numbers(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        "    _  _     _  _  _  _  _  _ ",
        "  | _| _||_||_ |_   ||_||_|| |",
        "  ||_  _|  | _||_|  ||_| _||_|",
        "                              ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("1234567890", buffer);
}

void test_numbers_separated_by_empty_lines_are_recognized_lines_are_joined_by_commas(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    const char *const rows[] = {
        // clang-format off
        "    _  _ ",
        "  | _| _|",
        "  ||_  _|",
        "         ",
        "    _  _ ",
        "|_||_ |_ ",
        "  | _||_|",
        "         ",
        " _  _  _ ",
        "  ||_||_|",
        "  ||_| _|",
        "         ",
        // clang-format on
    };

    TEST_ASSERT_EQUAL(success, convert(buffer, rows, ARRAY_SIZE(rows)));
    TEST_ASSERT_EQUAL_STRING("123,456,789", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_recognizes_0);
    RUN_TEST(test_recognizes_1);
    RUN_TEST(test_unreadable_but_correctly_sized_inputs_return_);
    RUN_TEST(test_input_with_a_number_of_lines_that_is_not_a_multiple_of_four_raises_an_error);
    RUN_TEST(test_input_with_a_number_of_columns_that_is_not_a_multiple_of_three_raises_an_error);
    RUN_TEST(test_recognizes_110101100);
    RUN_TEST(test_garbled_numbers_in_a_string_are_replaced_with_);
    RUN_TEST(test_recognizes_2);
    RUN_TEST(test_recognizes_3);
    RUN_TEST(test_recognizes_4);
    RUN_TEST(test_recognizes_5);
    RUN_TEST(test_recognizes_6);
    RUN_TEST(test_recognizes_7);
    RUN_TEST(test_recognizes_8);
    RUN_TEST(test_recognizes_9);
    RUN_TEST(test_recognizes_string_of_decimal_numbers);
    RUN_TEST(test_numbers_separated_by_empty_lines_are_recognized_lines_are_joined_by_commas);
    return UNITY_END();
}
