#include "vendor/unity.h"

#include <stdbool.h>
#include <stddef.h>

#define BUFFER_SIZE 16

#define ARRAY_SIZE(x) ((int)(sizeof(x) / sizeof((x)[0])))

extern int append(const int *list1, const int list1_size, const int *list2, const int list2_size, int *result);
extern int filter(const int *list, const int list_size, bool (*filter_predicate)(int), int *result);
extern int map(const int *list, const int list_size, int (*map_transform)(int), int *result);
extern int foldl(const int *list, const int list_size, int initial, int (*fold_accumulate)(int, int));
extern int foldr(const int *list, const int list_size, int initial, int (*fold_accumulate)(int, int));
extern int reverse(const int *list, const int list_size, int *result);

static bool is_odd(int x) {
    return x % 2 == 1;
}

static int plus_one(int x) {
    return x + 1;
}

static int multiply(int acc, int el) {
    return el * acc;
}

static int add(int acc, int el) {
    return el + acc;
}

static int divide(int acc, int el) {
    return acc == 0 ? 0 : el / acc;
}

void setUp(void) {
}

void tearDown(void) {
}

void test_append_empty_lists(void) {
    int buffer[BUFFER_SIZE];
    TEST_ASSERT_EQUAL_INT(0, append(NULL, 0, NULL, 0, buffer));
}

void test_append_list_to_empty_list(void) {
    TEST_IGNORE();
    const int list2[] = {1, 2, 3, 4};
    int buffer[BUFFER_SIZE];
    const int expected[] = {1, 2, 3, 4};
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), append(NULL, 0, list2, ARRAY_SIZE(list2), buffer));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_append_empty_list_to_list(void) {
    TEST_IGNORE();
    const int list1[] = {1, 2, 3, 4};
    int buffer[BUFFER_SIZE];
    const int expected[] = {1, 2, 3, 4};
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), append(list1, ARRAY_SIZE(list1), NULL, 0, buffer));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_append_nonempty_lists(void) {
    TEST_IGNORE();
    const int list1[] = {1, 2};
    const int list2[] = {2, 3, 4, 5};
    int buffer[BUFFER_SIZE];
    const int expected[] = {1, 2, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), append(list1, ARRAY_SIZE(list1), list2, ARRAY_SIZE(list2), buffer));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_filter_empty_list(void) {
    TEST_IGNORE();
    int buffer[BUFFER_SIZE];
    TEST_ASSERT_EQUAL_INT(0, filter(NULL, 0, is_odd, buffer));
}

void test_filter_nonempty_list(void) {
    TEST_IGNORE();
    const int list[] = {1, 2, 3, 5};
    int buffer[BUFFER_SIZE];
    const int expected[] = {1, 3, 5};
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), filter(list, ARRAY_SIZE(list), is_odd, buffer));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_map_empty_list(void) {
    TEST_IGNORE();
    int buffer[BUFFER_SIZE];
    TEST_ASSERT_EQUAL_INT(0, map(NULL, 0, plus_one, buffer));
}

void test_map_nonempty_list(void) {
    TEST_IGNORE();
    const int list[] = {1, 3, 5, 7};
    int buffer[BUFFER_SIZE];
    const int expected[] = {2, 4, 6, 8};
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), map(list, ARRAY_SIZE(list), plus_one, buffer));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, buffer, ARRAY_SIZE(expected));
}

void test_foldl_empty_list(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(2, foldl(NULL, 0, 2, multiply));
}

void test_foldl_direction_independent_function_applied_to_nonempty_list(void) {
    TEST_IGNORE();
    const int list[] = {1, 2, 3, 4};
    TEST_ASSERT_EQUAL_INT(15, foldl(list, ARRAY_SIZE(list), 5, add));
}

void test_foldl_direction_dependent_function_applied_to_nonempty_list(void) {
    TEST_IGNORE();
    const int list[] = {2, 5};
    TEST_ASSERT_EQUAL_INT(0, foldl(list, ARRAY_SIZE(list), 5, divide));
}

void test_foldr_empty_list(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT(2, foldr(NULL, 0, 2, multiply));
}

void test_foldr_direction_independent_function_applied_to_nonempty_list(void) {
    TEST_IGNORE();
    const int list[] = {1, 2, 3, 4};
    TEST_ASSERT_EQUAL_INT(15, foldr(list, ARRAY_SIZE(list), 5, add));
}

void test_foldr_direction_dependent_function_applied_to_nonempty_list(void) {
    TEST_IGNORE();
    const int list[] = {2, 5};
    TEST_ASSERT_EQUAL_INT(2, foldr(list, ARRAY_SIZE(list), 5, divide));
}

void test_reverse_empty_list(void) {
    TEST_IGNORE();
    int buffer[BUFFER_SIZE];
    TEST_ASSERT_EQUAL_INT(0, reverse(NULL, 0, buffer));
}

void test_reverse_nonempty_list(void) {
    TEST_IGNORE();
    const int list[] = {1, 3, 5, 7};
    int buffer[BUFFER_SIZE];
    const int expected[] = {7, 5, 3, 1};
    TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), reverse(list, ARRAY_SIZE(list), buffer));
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, buffer, ARRAY_SIZE(expected));
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
