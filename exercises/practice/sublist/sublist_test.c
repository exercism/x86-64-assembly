#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef enum {
    UNEQUAL = 0,
    EQUAL,
    SUBLIST,
    SUPERLIST,
} relation_t;

extern relation_t sublist(const int64_t *list_one, size_t list_one_count, const int64_t *list_two, size_t list_two_count);

void setUp(void) {
}

void tearDown(void) {
}

void test_empty_lists(void) {
    TEST_ASSERT_EQUAL_INT(EQUAL, sublist(NULL, 0, NULL, 0));
}

void test_empty_list_within_non_empty_list(void) {
    TEST_IGNORE();
    const int64_t list_two[] = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(SUBLIST, sublist(NULL, 0, list_two, ARRAY_SIZE(list_two)));
}

void test_non_empty_list_contains_empty_list(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(SUPERLIST, sublist(list_one, ARRAY_SIZE(list_one), NULL, 0));
}

void test_list_equals_itself(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {1, 2, 3};
    const int64_t list_two[] = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(EQUAL, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_different_lists(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {1, 2, 3};
    const int64_t list_two[] = {2, 3, 4};
    TEST_ASSERT_EQUAL_INT(UNEQUAL, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_false_start(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {1, 2, 5};
    const int64_t list_two[] = {0, 1, 2, 3, 1, 2, 5, 6};
    TEST_ASSERT_EQUAL_INT(SUBLIST, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_consecutive(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {1, 1, 2};
    const int64_t list_two[] = {0, 1, 1, 1, 2, 1, 2};
    TEST_ASSERT_EQUAL_INT(SUBLIST, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_sublist_at_start(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {0, 1, 2};
    const int64_t list_two[] = {0, 1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(SUBLIST, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_sublist_in_middle(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {2, 3, 4};
    const int64_t list_two[] = {0, 1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(SUBLIST, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_sublist_at_end(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {3, 4, 5};
    const int64_t list_two[] = {0, 1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(SUBLIST, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_at_start_of_superlist(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {0, 1, 2, 3, 4, 5};
    const int64_t list_two[] = {0, 1, 2};
    TEST_ASSERT_EQUAL_INT(SUPERLIST, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_in_middle_of_superlist(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {0, 1, 2, 3, 4, 5};
    const int64_t list_two[] = {2, 3};
    TEST_ASSERT_EQUAL_INT(SUPERLIST, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_at_end_of_superlist(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {0, 1, 2, 3, 4, 5};
    const int64_t list_two[] = {3, 4, 5};
    TEST_ASSERT_EQUAL_INT(SUPERLIST, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_first_list_missing_element_from_second_list(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {1, 3};
    const int64_t list_two[] = {1, 2, 3};
    TEST_ASSERT_EQUAL_INT(UNEQUAL, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_second_list_missing_element_from_first_list(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {1, 2, 3};
    const int64_t list_two[] = {1, 3};
    TEST_ASSERT_EQUAL_INT(UNEQUAL, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_first_list_missing_additional_digits_from_second_list(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {1, 2};
    const int64_t list_two[] = {1, 22};
    TEST_ASSERT_EQUAL_INT(UNEQUAL, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_order_matters_to_a_list(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {1, 2, 3};
    const int64_t list_two[] = {3, 2, 1};
    TEST_ASSERT_EQUAL_INT(UNEQUAL, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

void test_same_digits_but_different_numbers(void) {
    TEST_IGNORE();
    const int64_t list_one[] = {1, 0, 1};
    const int64_t list_two[] = {10, 1};
    TEST_ASSERT_EQUAL_INT(UNEQUAL, sublist(list_one, ARRAY_SIZE(list_one), list_two, ARRAY_SIZE(list_two)));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_lists);
    RUN_TEST(test_empty_list_within_non_empty_list);
    RUN_TEST(test_non_empty_list_contains_empty_list);
    RUN_TEST(test_list_equals_itself);
    RUN_TEST(test_different_lists);
    RUN_TEST(test_false_start);
    RUN_TEST(test_consecutive);
    RUN_TEST(test_sublist_at_start);
    RUN_TEST(test_sublist_in_middle);
    RUN_TEST(test_sublist_at_end);
    RUN_TEST(test_at_start_of_superlist);
    RUN_TEST(test_in_middle_of_superlist);
    RUN_TEST(test_at_end_of_superlist);
    RUN_TEST(test_first_list_missing_element_from_second_list);
    RUN_TEST(test_second_list_missing_element_from_first_list);
    RUN_TEST(test_first_list_missing_additional_digits_from_second_list);
    RUN_TEST(test_order_matters_to_a_list);
    RUN_TEST(test_same_digits_but_different_numbers);
    return UNITY_END();
}
