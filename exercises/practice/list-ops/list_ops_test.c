// Version: 0

#include "vendor/unity.h"

#include <stdbool.h>
#include <stddef.h>

#define MAX_ARRAY_SIZE 16

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern int append(const int *first_array, const int first_array_size, const int *second_array, const int second_array_size,
                  int *result_array);
extern int filter(const int *array, const int array_size, bool (*filter_predicate)(int), int *result_array);
extern int map(const int *array, const int array_size, int (*map_transform)(int), int *result_array);
extern int foldl(const int *array, const int array_size, int initial, int (*fold_accumulate)(int, int));
extern int foldr(const int *array, const int array_size, int initial, int (*fold_accumulate)(int, int));
extern int reverse(const int *array, const int array_size, int *result_array);

static bool filter_odd(int x) {
    return x % 2 == 1;
}

static int map_increment(int x) {
    return x + 1;
}

static int fold_multiply(int acc, int el) {
    return el * acc;
}

static int fold_add(int acc, int el) {
    return el + acc;
}

static int fold_divide(int acc, int el) {
    return acc == 0 ? 0 : el / acc;
}

void setUp(void) {
}

void tearDown(void) {
}

void test_append_empty_lists(void) {
    int actual[MAX_ARRAY_SIZE];
    int size = append(NULL, 0, NULL, 0, actual);
    TEST_ASSERT_EQUAL_INT(0, size);
}

void test_append_list_to_empty_list(void) {
    TEST_IGNORE();
    int second_array[] = {1, 2, 3, 4};
    int expected[] = {1, 2, 3, 4};
    int actual[MAX_ARRAY_SIZE];
    int size = append(NULL, 0, second_array, ARRAY_SIZE(second_array), actual);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, size);
}

void test_append_empty_list_to_list(void) {
    TEST_IGNORE();
    int first_array[] = {1, 2, 3, 4};
    int expected[] = {1, 2, 3, 4};
    int actual[MAX_ARRAY_SIZE];
    int size = append(first_array, ARRAY_SIZE(first_array), NULL, 0, actual);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, size);
}

void test_append_nonempty_lists(void) {
    TEST_IGNORE();
    int first_array[] = {1, 2};
    int second_array[] = {2, 3, 4, 5};
    int expected[] = {1, 2, 2, 3, 4, 5};
    int actual[MAX_ARRAY_SIZE];
    int size = append(first_array, ARRAY_SIZE(first_array), second_array, ARRAY_SIZE(second_array), actual);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, size);
}

void test_filter_empty_list(void) {
    TEST_IGNORE();
    int actual[MAX_ARRAY_SIZE];
    int size = filter(NULL, 0, filter_odd, actual);
    TEST_ASSERT_EQUAL_INT(0, size);
}

void test_filter_nonempty_list(void) {
    TEST_IGNORE();
    int array[] = {1, 2, 3, 5};
    int expected[] = {1, 3, 5};
    int actual[MAX_ARRAY_SIZE];
    int size = filter(array, ARRAY_SIZE(array), filter_odd, actual);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, size);
}

void test_map_empty_list(void) {
    TEST_IGNORE();
    int actual[MAX_ARRAY_SIZE];
    int size = map(NULL, 0, map_increment, actual);
    TEST_ASSERT_EQUAL_INT(0, size);
}

void test_map_nonempty_list(void) {
    TEST_IGNORE();
    int array[] = {1, 3, 5, 7};
    int expected[] = {2, 4, 6, 8};
    int actual[MAX_ARRAY_SIZE];
    int size = map(array, ARRAY_SIZE(array), map_increment, actual);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, size);
}

void test_foldl_empty_list(void) {
    TEST_IGNORE();
    int initial = 2;
    int expected = 2;
    int actual = foldl(NULL, 0, initial, fold_multiply);
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

void test_foldl_direction_independent_function_applied_to_nonempty_list(void) {
    TEST_IGNORE();
    int array[] = {1, 2, 3, 4};
    int initial = 5;
    int expected = 15;
    int actual = foldl(array, ARRAY_SIZE(array), initial, fold_add);
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

void test_foldl_direction_dependent_function_applied_to_nonempty_list(void) {
    TEST_IGNORE();
    int array[] = {2, 5};
    int initial = 5;
    int expected = 0;
    int actual = foldl(array, ARRAY_SIZE(array), initial, fold_divide);
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

void test_foldr_empty_list(void) {
    TEST_IGNORE();
    int initial = 2;
    int expected = 2;
    int actual = foldr(NULL, 0, initial, fold_multiply);
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

void test_foldr_direction_independent_function_applied_to_nonempty_list(void) {
    TEST_IGNORE();
    int array[] = {1, 2, 3, 4};
    int initial = 5;
    int expected = 15;
    int actual = foldr(array, ARRAY_SIZE(array), initial, fold_add);
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

void test_foldr_direction_dependent_function_applied_to_nonempty_list(void) {
    TEST_IGNORE();
    int array[] = {2, 5};
    int initial = 5;
    int expected = 2;
    int actual = foldr(array, ARRAY_SIZE(array), initial, fold_divide);
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

void test_reverse_empty_list(void) {
    TEST_IGNORE();
    int actual[MAX_ARRAY_SIZE];
    int size = reverse(NULL, 0, actual);
    TEST_ASSERT_EQUAL_INT(0, size);
}

void test_reverse_nonempty_list(void) {
    TEST_IGNORE();
    int array[] = {1, 3, 5, 7};
    int expected[] = {7, 5, 3, 1};
    int actual[MAX_ARRAY_SIZE];
    int size = reverse(array, ARRAY_SIZE(array), actual);
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, size);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_append_empty_lists);
    RUN_TEST(test_append_list_to_empty_list);
    RUN_TEST(test_append_empty_list_to_list);
    RUN_TEST(test_append_nonempty_lists);
    RUN_TEST(test_filter_empty_list);
    RUN_TEST(test_filter_nonempty_list);
    RUN_TEST(test_map_empty_list);
    RUN_TEST(test_map_nonempty_list);
    RUN_TEST(test_foldl_empty_list);
    RUN_TEST(test_foldl_direction_independent_function_applied_to_nonempty_list);
    RUN_TEST(test_foldl_direction_dependent_function_applied_to_nonempty_list);
    RUN_TEST(test_foldr_empty_list);
    RUN_TEST(test_foldr_direction_independent_function_applied_to_nonempty_list);
    RUN_TEST(test_foldr_direction_dependent_function_applied_to_nonempty_list);
    RUN_TEST(test_reverse_empty_list);
    RUN_TEST(test_reverse_nonempty_list);
    return UNITY_END();
}
