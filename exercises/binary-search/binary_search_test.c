// Version: 1.3.0

#include "vendor/unity.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern int find(int *array, int size, int value);

void setUp(void) {
}

void tearDown(void) {
}

void test_finds_a_value_in_an_array_with_one_element(void) {
    int array[] = {6};

    TEST_ASSERT_EQUAL_INT(0, find(array, ARRAY_SIZE(array), 6));
}

void test_finds_a_value_in_the_middle_of_an_array(void) {
    int array[] = {1, 3, 4, 6, 8, 9, 11};

    TEST_ASSERT_EQUAL_INT(3, find(array, ARRAY_SIZE(array), 6));
}

void test_finds_a_value_at_the_beginning_of_an_array(void) {
    int array[] = {1, 3, 4, 6, 8, 9, 11};

    TEST_ASSERT_EQUAL_INT(0, find(array, ARRAY_SIZE(array), 1));
}

void test_finds_a_value_at_the_end_of_an_array(void) {
    int array[] = {1, 3, 4, 6, 8, 9, 11};

    TEST_ASSERT_EQUAL_INT(6, find(array, ARRAY_SIZE(array), 11));
}

void test_finds_a_value_in_an_array_of_odd_length(void) {
    int array[] = {1, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 634};

    TEST_ASSERT_EQUAL_INT(9, find(array, ARRAY_SIZE(array), 144));
}

void test_finds_a_value_in_an_array_of_even_length(void) {
    int array[] = {1, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377};

    TEST_ASSERT_EQUAL_INT(5, find(array, ARRAY_SIZE(array), 21));
}

void test_identifies_that_a_value_is_not_included_in_the_array(void) {
    int array[] = {1, 3, 4, 6, 8, 9, 11};

    TEST_ASSERT_EQUAL_INT(-1, find(array, ARRAY_SIZE(array), 7));
}

void test_a_value_smaller_than_the_arrays_smallest_value_is_not_found(void) {
    int array[] = {1, 3, 4, 6, 8, 9, 11};

    TEST_ASSERT_EQUAL_INT(-1, find(array, ARRAY_SIZE(array), 0));
}

void test_a_value_larger_than_the_arrays_largest_value_is_not_found(void) {
    int array[] = {1, 3, 4, 6, 8, 9, 11};

    TEST_ASSERT_EQUAL_INT(-1, find(array, ARRAY_SIZE(array), 13));
}

void test_nothing_is_found_in_an_empty_array(void) {
    TEST_ASSERT_EQUAL_INT(-1, find(NULL, 0, 1));
}

void test_nothing_is_found_when_the_left_and_right_bounds_cross(void) {
    int array[] = {1, 2};

    TEST_ASSERT_EQUAL_INT(-1, find(array, ARRAY_SIZE(array), 0));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_finds_a_value_in_an_array_with_one_element);
    RUN_TEST(test_finds_a_value_in_the_middle_of_an_array);
    RUN_TEST(test_finds_a_value_at_the_beginning_of_an_array);
    RUN_TEST(test_finds_a_value_at_the_end_of_an_array);
    RUN_TEST(test_finds_a_value_in_an_array_of_odd_length);
    RUN_TEST(test_finds_a_value_in_an_array_of_even_length);
    RUN_TEST(test_identifies_that_a_value_is_not_included_in_the_array);
    RUN_TEST(test_a_value_smaller_than_the_arrays_smallest_value_is_not_found);
    RUN_TEST(test_a_value_larger_than_the_arrays_largest_value_is_not_found);
    RUN_TEST(test_nothing_is_found_in_an_empty_array);
    RUN_TEST(test_nothing_is_found_when_the_left_and_right_bounds_cross);
    return UNITY_END();
}
