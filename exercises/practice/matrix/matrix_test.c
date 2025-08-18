#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define BUFFER_SIZE 10

extern size_t row(int32_t *buffer, const char *input, size_t index);
extern size_t column(int32_t *buffer, const char *input, size_t index);

void setUp(void) {
}

void tearDown(void) {
}

void test_extract_row_from_one_number_matrix(void) {
    int32_t buffer[BUFFER_SIZE];

    const int32_t expected[] = {1};
    const size_t length = row(buffer, "1", 1);
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_can_extract_row(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];

    const int32_t expected[] = {3, 4};
    const size_t length = row(buffer, "1 2\n3 4", 2);
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_extract_row_where_numbers_have_different_widths(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];

    const int32_t expected[] = {10, 20};
    const size_t length = row(buffer, "1 2\n10 20", 2);
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_can_extract_row_from_nonsquare_matrix_with_no_corresponding_column(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];

    const int32_t expected[] = {8, 7, 6};
    const size_t length = row(buffer, "1 2 3\n4 5 6\n7 8 9\n8 7 6", 4);
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_extract_column_from_one_number_matrix(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];

    const int32_t expected[] = {1};
    const size_t length = column(buffer, "1", 1);
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_can_extract_column(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];

    const int32_t expected[] = {3, 6, 9};
    const size_t length = column(buffer, "1 2 3\n4 5 6\n7 8 9", 3);
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_can_extract_column_from_nonsquare_matrix_with_no_corresponding_row(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];

    const int32_t expected[] = {4, 8, 6};
    const size_t length = column(buffer, "1 2 3 4\n5 6 7 8\n9 8 7 6", 4);
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_extract_column_where_numbers_have_different_widths(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];

    const int32_t expected[] = {1903, 3, 4};
    const size_t length = column(buffer, "89 1903 3\n18 3 1\n9 4 800", 2);
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_row_with_negative_numbers(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];

    const int32_t expected[] = {-57, 9, -42};
    const size_t length = row(buffer, "1 2 4\n-57 9 -42\n10 0 65", 2);
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_column_with_negative_numbers(void) {
    TEST_IGNORE();
    int32_t buffer[BUFFER_SIZE];

    const int32_t expected[] = {-4, -42, -465};
    const size_t length = column(buffer, "1 2 -4\n-57 9 -42\n10 0 -465", 3);
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_extract_row_from_one_number_matrix);
    RUN_TEST(test_can_extract_row);
    RUN_TEST(test_extract_row_where_numbers_have_different_widths);
    RUN_TEST(test_can_extract_row_from_nonsquare_matrix_with_no_corresponding_column);
    RUN_TEST(test_extract_column_from_one_number_matrix);
    RUN_TEST(test_can_extract_column);
    RUN_TEST(test_can_extract_column_from_nonsquare_matrix_with_no_corresponding_row);
    RUN_TEST(test_extract_column_where_numbers_have_different_widths);
    RUN_TEST(test_row_with_negative_numbers);
    RUN_TEST(test_column_with_negative_numbers);
    return UNITY_END();
}
