#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 20
#define SLICE_SIZE 20
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define EMPTY_SERIES -1
#define ZERO_LENGTH -2
#define NEGATIVE_LENGTH -3
#define EXCESSIVE_LENGTH -4

extern int64_t slices(char buffer[][SLICE_SIZE], const char *series, size_t slice_length);

void setUp(void) {
}

void tearDown(void) {
}

void test_slices_of_one_from_one(void) {
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    const char *expected[] = {"1"};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), slices(buffer, "1", 1));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_slices_of_one_from_two(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    const char *expected[] = {"1", "2"};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), slices(buffer, "12", 1));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_slices_of_two(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    const char *expected[] = {"35"};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), slices(buffer, "35", 2));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_slices_of_two_overlap(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    const char *expected[] = {"91", "14", "42"};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), slices(buffer, "9142", 2));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_slices_can_include_duplicates(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    const char *expected[] = {"777", "777", "777", "777"};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), slices(buffer, "777777", 3));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_slices_of_a_long_series(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    const char *expected[] = {"91849", "18493", "84939", "49390", "93904", "39042", "90424", "04243"};
    TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), slices(buffer, "918493904243", 5));
    for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
    }
}

void test_slice_length_is_too_large(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    TEST_ASSERT_EQUAL_INT64(EXCESSIVE_LENGTH, slices(buffer, "12345", 6));
}

void test_slice_length_is_way_too_large(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    TEST_ASSERT_EQUAL_INT64(EXCESSIVE_LENGTH, slices(buffer, "12345", 42));
}

void test_slice_length_cannot_be_zero(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    TEST_ASSERT_EQUAL_INT64(ZERO_LENGTH, slices(buffer, "12345", 0));
}

void test_slice_length_cannot_be_negative(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    TEST_ASSERT_EQUAL_INT64(NEGATIVE_LENGTH, slices(buffer, "123", -1));
}

void test_empty_series_is_invalid(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE][SLICE_SIZE];
    TEST_ASSERT_EQUAL_INT64(EMPTY_SERIES, slices(buffer, "", 1));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_slices_of_one_from_one);
    RUN_TEST(test_slices_of_one_from_two);
    RUN_TEST(test_slices_of_two);
    RUN_TEST(test_slices_of_two_overlap);
    RUN_TEST(test_slices_can_include_duplicates);
    RUN_TEST(test_slices_of_a_long_series);
    RUN_TEST(test_slice_length_is_too_large);
    RUN_TEST(test_slice_length_is_way_too_large);
    RUN_TEST(test_slice_length_cannot_be_zero);
    RUN_TEST(test_slice_length_cannot_be_negative);
    RUN_TEST(test_empty_series_is_invalid);
    return UNITY_END();
}
