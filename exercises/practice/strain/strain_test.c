#include "vendor/unity.h"

#include <stddef.h>
#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef bool (*predicate_t)(const void *);

extern size_t keep(void *elems, size_t elem_size, size_t num_elems, predicate_t fn);
extern size_t discard(void *elems, size_t elem_size, size_t num_elems, predicate_t fn);

static bool always(const void *x) {
    (void)x;
    return true;
}

static bool never(const void *x) {
    (void)x;
    return false;
}

static bool is_even(const void *x) {
    const int *y = x;
    return (*y & 1) == 0;
}

static bool is_odd(const void *x) {
    const int *y = x;
    return (*y & 1) == 1;
}

static bool starts_with_z(const void *x) {
    const char *const *y = x;
    for (int i = 0; *(*y + i); ++i) {
        if (*(*y + i) == 'z') return true;
    }
    return false;
}

static bool contains_5(const void *x) {
    const int *y = x;
    for (int i = 0; i < 3; ++i) {
        if (y[i] == 5) return true;
    }
    return false;
}

void setUp(void) {
}

void tearDown(void) {
}

void test_keep_on_empty_list_returns_empty_list(void) {
    void *ptr = NULL;
    size_t elem_size = sizeof(int);
    size_t num_elems = 0;
    const size_t size = keep(ptr, elem_size, num_elems, always);
    TEST_ASSERT_EQUAL_UINT64(0, size);
}

void test_keeps_everything(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(int);
    size_t num_elems = 0;
    int input[] = {1, 3, 5};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = keep(ptr, elem_size, num_elems, always);
    const int result[] = {1, 3, 5};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(result, input, ARRAY_SIZE(result));
}

void test_keeps_nothing(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(int);
    size_t num_elems = 0;
    int input[] = {1, 3, 5};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = keep(ptr, elem_size, num_elems, never);
    TEST_ASSERT_EQUAL_UINT64(0, size);
}

void test_keeps_first_and_last(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(int);
    size_t num_elems = 0;
    int input[] = {1, 2, 3};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = keep(ptr, elem_size, num_elems, is_odd);
    const int result[] = {1, 3};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(result, input, ARRAY_SIZE(result));
}

void test_keeps_neither_first_nor_last(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(int);
    size_t num_elems = 0;
    int input[] = {1, 2, 3};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = keep(ptr, elem_size, num_elems, is_even);
    const int result[] = {2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(result, input, ARRAY_SIZE(result));
}

void test_keeps_strings(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(const char *);
    size_t num_elems = 0;
    const char *input[] = {"apple", "zebra", "banana", "zombies", "cherimoya", "zealot"};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = keep(ptr, elem_size, num_elems, starts_with_z);
    const char *result[] = {"zebra", "zombies", "zealot"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);
    TEST_ASSERT_EQUAL_STRING_ARRAY(result, input, ARRAY_SIZE(result));
}

void test_keeps_lists(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = 3 * sizeof(const int);
    size_t num_elems = 0;
    const int input[][3] = {{1, 2, 3}, {5, 5, 5}, {5, 1, 2}, {2, 1, 2}, {1, 5, 2}, {2, 2, 1}, {1, 2, 5}};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = keep(ptr, elem_size, num_elems, contains_5);
    const int result[][3] = {{5, 5, 5}, {5, 1, 2}, {1, 5, 2}, {1, 2, 5}};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);
    for (size_t i = 0; i < ARRAY_SIZE(result); ++i) {
        TEST_ASSERT_EQUAL_INT_ARRAY(result[i], input[i], 3);
    }
}

void test_discard_on_empty_list_returns_empty_list(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(int);
    size_t num_elems = 0;
    const size_t size = discard(ptr, elem_size, num_elems, always);
    TEST_ASSERT_EQUAL_UINT64(0, size);
}

void test_discards_everything(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(int);
    size_t num_elems = 0;
    int input[] = {1, 3, 5};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = discard(ptr, elem_size, num_elems, always);
    TEST_ASSERT_EQUAL_UINT64(0, size);
}

void test_discards_nothing(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(int);
    size_t num_elems = 0;
    int input[] = {1, 3, 5};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = discard(ptr, elem_size, num_elems, never);
    const int result[] = {1, 3, 5};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(result, input, ARRAY_SIZE(result));
}

void test_discards_first_and_last(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(int);
    size_t num_elems = 0;
    int input[] = {1, 2, 3};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = discard(ptr, elem_size, num_elems, is_odd);
    const int result[] = {2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(result, input, ARRAY_SIZE(result));
}

void test_discards_neither_first_nor_last(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(int);
    size_t num_elems = 0;
    int input[] = {1, 2, 3};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = discard(ptr, elem_size, num_elems, is_even);
    const int result[] = {1, 3};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);
    TEST_ASSERT_EQUAL_INT_ARRAY(result, input, ARRAY_SIZE(result));
}

void test_discards_strings(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = sizeof(const char *);
    size_t num_elems = 0;
    const char *input[] = {"apple", "zebra", "banana", "zombies", "cherimoya", "zealot"};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = discard(ptr, elem_size, num_elems, starts_with_z);
    const char *result[] = {"apple", "banana", "cherimoya"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);
    TEST_ASSERT_EQUAL_STRING_ARRAY(result, input, ARRAY_SIZE(result));
}

void test_discards_lists(void) {
    TEST_IGNORE();
    void *ptr = NULL;
    size_t elem_size = 3 * sizeof(const int);
    size_t num_elems = 0;
    const int input[][3] = {{1, 2, 3}, {5, 5, 5}, {5, 1, 2}, {2, 1, 2}, {1, 5, 2}, {2, 2, 1}, {1, 2, 5}};
    ptr = (void *)input;
    num_elems = ARRAY_SIZE(input);
    const size_t size = discard(ptr, elem_size, num_elems, contains_5);
    const int result[][3] = {{1, 2, 3}, {2, 1, 2}, {2, 2, 1}};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(result), size);
    for (size_t i = 0; i < ARRAY_SIZE(result); ++i) {
        TEST_ASSERT_EQUAL_INT_ARRAY(result[i], input[i], 3);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_keep_on_empty_list_returns_empty_list);
    RUN_TEST(test_keeps_everything);
    RUN_TEST(test_keeps_nothing);
    RUN_TEST(test_keeps_first_and_last);
    RUN_TEST(test_keeps_neither_first_nor_last);
    RUN_TEST(test_keeps_strings);
    RUN_TEST(test_keeps_lists);
    RUN_TEST(test_discard_on_empty_list_returns_empty_list);
    RUN_TEST(test_discards_everything);
    RUN_TEST(test_discards_nothing);
    RUN_TEST(test_discards_first_and_last);
    RUN_TEST(test_discards_neither_first_nor_last);
    RUN_TEST(test_discards_strings);
    RUN_TEST(test_discards_lists);
    return UNITY_END();
}
