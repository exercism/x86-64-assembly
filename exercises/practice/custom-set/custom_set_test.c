#include "vendor/unity.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef uint8_t set_id;

extern set_id create_set(size_t input_count, const int8_t *input);
extern bool set_empty(set_id set);
extern bool set_contains(set_id set, int8_t element);
extern bool set_subset(set_id set1, set_id set2);
extern bool set_disjoint(set_id set1, set_id set2);
extern bool set_equal(set_id set1, set_id set2);
extern void set_add(set_id set, int8_t element);
extern set_id set_intersection(set_id set1, set_id set2);
extern set_id set_difference(set_id set1, set_id set2);
extern set_id set_union(set_id set1, set_id set2);
extern void delete_set(set_id set);

void setUp(void) {
}

void tearDown(void) {
}

void test_sets_with_no_elements_are_empty(void) {
    set_id set_result = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_empty(set_result));
    delete_set(set_result);
}

void test_sets_with_elements_are_not_empty(void) {
    TEST_IGNORE();
    const int8_t input[] = {1};
    set_id set_result = create_set(ARRAY_SIZE(input), input);
    TEST_ASSERT_EQUAL(false, set_empty(set_result));
    delete_set(set_result);
}

void test_nothing_is_contained_in_an_empty_set(void) {
    TEST_IGNORE();
    set_id set_result = create_set(0, NULL);
    TEST_ASSERT_EQUAL(false, set_contains(set_result, 1));
    delete_set(set_result);
}

void test_when_the_element_is_in_the_set(void) {
    TEST_IGNORE();
    const int8_t input[] = {1, 2, 3};
    set_id set_result = create_set(ARRAY_SIZE(input), input);
    TEST_ASSERT_EQUAL(true, set_contains(set_result, 1));
    delete_set(set_result);
}

void test_when_the_element_is_not_in_the_set(void) {
    TEST_IGNORE();
    const int8_t input[] = {1, 2, 3};
    set_id set_result = create_set(ARRAY_SIZE(input), input);
    TEST_ASSERT_EQUAL(false, set_contains(set_result, 4));
    delete_set(set_result);
}

void test_empty_set_is_a_subset_of_another_empty_set(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    set_id set_2 = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_subset(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_empty_set_is_a_subset_of_nonempty_set(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    const int8_t input_2[] = {1};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(true, set_subset(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_nonempty_set_is_not_a_subset_of_empty_set(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    set_id set_2 = create_set(0, NULL);
    TEST_ASSERT_EQUAL(false, set_subset(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_set_is_a_subset_of_set_with_exact_same_elements(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2, 3};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {1, 2, 3};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(true, set_subset(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_set_is_a_subset_of_larger_set_with_same_elements(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2, 3};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {4, 1, 2, 3};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(true, set_subset(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_set_is_not_a_subset_of_set_that_does_not_contain_its_elements(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2, 3};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {4, 1, 3};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(false, set_subset(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_the_empty_set_is_disjoint_with_itself(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    set_id set_2 = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_disjoint(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_empty_set_is_disjoint_with_nonempty_set(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    const int8_t input_2[] = {1};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(true, set_disjoint(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_nonempty_set_is_disjoint_with_empty_set(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    set_id set_2 = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_disjoint(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_sets_are_not_disjoint_if_they_share_an_element(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {2, 3};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(false, set_disjoint(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_sets_are_disjoint_if_they_share_no_elements(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {3, 4};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(true, set_disjoint(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_empty_sets_are_equal(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    set_id set_2 = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_equal(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_empty_set_is_not_equal_to_nonempty_set(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    const int8_t input_2[] = {1, 2, 3};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(false, set_equal(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_nonempty_set_is_not_equal_to_empty_set(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2, 3};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    set_id set_2 = create_set(0, NULL);
    TEST_ASSERT_EQUAL(false, set_equal(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_sets_with_the_same_elements_are_equal(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {2, 1};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(true, set_equal(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_sets_with_different_elements_are_not_equal(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2, 3};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {1, 2, 4};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(false, set_equal(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_set_is_not_equal_to_larger_set_with_same_elements(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2, 3};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {1, 2, 3, 4};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(false, set_equal(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_set_is_equal_to_a_set_constructed_from_an_array_with_duplicates(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {1, 1};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    TEST_ASSERT_EQUAL(true, set_equal(set_1, set_2));
    delete_set(set_1);
    delete_set(set_2);
}

void test_add_to_empty_set(void) {
    TEST_IGNORE();
    set_id set_result = create_set(0, NULL);
    set_add(set_result, 3);
    const int8_t expected_elements[] = {3};
    set_id set_expected = create_set(ARRAY_SIZE(expected_elements), expected_elements);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
}

void test_add_to_nonempty_set(void) {
    TEST_IGNORE();
    const int8_t input[] = {1, 2, 4};
    set_id set_result = create_set(ARRAY_SIZE(input), input);
    set_add(set_result, 3);
    const int8_t expected_elements[] = {1, 2, 3, 4};
    set_id set_expected = create_set(ARRAY_SIZE(expected_elements), expected_elements);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
}

void test_adding_an_existing_element_does_not_change_the_set(void) {
    TEST_IGNORE();
    const int8_t input[] = {1, 2, 3};
    set_id set_result = create_set(ARRAY_SIZE(input), input);
    set_add(set_result, 3);
    const int8_t expected_elements[] = {1, 2, 3};
    set_id set_expected = create_set(ARRAY_SIZE(expected_elements), expected_elements);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
}

void test_intersection_of_two_empty_sets_is_an_empty_set(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    set_id set_2 = create_set(0, NULL);
    set_id set_result = set_intersection(set_1, set_2);
    set_id set_expected = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_intersection_of_an_empty_set_and_nonempty_set_is_an_empty_set(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    const int8_t input_2[] = {3, 2, 5};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    set_id set_result = set_intersection(set_1, set_2);
    set_id set_expected = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_intersection_of_a_nonempty_set_and_an_empty_set_is_an_empty_set(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2, 3, 4};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    set_id set_2 = create_set(0, NULL);
    set_id set_result = set_intersection(set_1, set_2);
    set_id set_expected = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_intersection_of_two_sets_with_no_shared_elements_is_an_empty_set(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2, 3};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {4, 5, 6};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    set_id set_result = set_intersection(set_1, set_2);
    set_id set_expected = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_intersection_of_two_sets_with_shared_elements_is_a_set_of_the_shared_elements(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2, 3, 4};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {3, 2, 5};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    set_id set_result = set_intersection(set_1, set_2);
    const int8_t expected_elements[] = {2, 3};
    set_id set_expected = create_set(ARRAY_SIZE(expected_elements), expected_elements);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_difference_of_two_empty_sets_is_an_empty_set(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    set_id set_2 = create_set(0, NULL);
    set_id set_result = set_difference(set_1, set_2);
    set_id set_expected = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_difference_of_empty_set_and_nonempty_set_is_an_empty_set(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    const int8_t input_2[] = {3, 2, 5};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    set_id set_result = set_difference(set_1, set_2);
    set_id set_expected = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_difference_of_a_nonempty_set_and_an_empty_set_is_the_nonempty_set(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 2, 3, 4};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    set_id set_2 = create_set(0, NULL);
    set_id set_result = set_difference(set_1, set_2);
    const int8_t expected_elements[] = {1, 2, 3, 4};
    set_id set_expected = create_set(ARRAY_SIZE(expected_elements), expected_elements);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_difference_of_two_nonempty_sets_is_a_set_of_elements_that_are_only_in_the_first_set(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {3, 2, 1};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {2, 4};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    set_id set_result = set_difference(set_1, set_2);
    const int8_t expected_elements[] = {1, 3};
    set_id set_expected = create_set(ARRAY_SIZE(expected_elements), expected_elements);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_difference_removes_all_duplicates_in_the_first_set(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 1};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {1};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    set_id set_result = set_difference(set_1, set_2);
    set_id set_expected = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_union_of_empty_sets_is_an_empty_set(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    set_id set_2 = create_set(0, NULL);
    set_id set_result = set_union(set_1, set_2);
    set_id set_expected = create_set(0, NULL);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_union_of_an_empty_set_and_nonempty_set_is_the_nonempty_set(void) {
    TEST_IGNORE();
    set_id set_1 = create_set(0, NULL);
    const int8_t input_2[] = {2};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    set_id set_result = set_union(set_1, set_2);
    const int8_t expected_elements[] = {2};
    set_id set_expected = create_set(ARRAY_SIZE(expected_elements), expected_elements);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_union_of_a_nonempty_set_and_empty_set_is_the_nonempty_set(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 3};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    set_id set_2 = create_set(0, NULL);
    set_id set_result = set_union(set_1, set_2);
    const int8_t expected_elements[] = {1, 3};
    set_id set_expected = create_set(ARRAY_SIZE(expected_elements), expected_elements);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

void test_union_of_nonempty_sets_contains_all_unique_elements(void) {
    TEST_IGNORE();
    const int8_t input_1[] = {1, 3};
    set_id set_1 = create_set(ARRAY_SIZE(input_1), input_1);
    const int8_t input_2[] = {2, 3};
    set_id set_2 = create_set(ARRAY_SIZE(input_2), input_2);
    set_id set_result = set_union(set_1, set_2);
    const int8_t expected_elements[] = {3, 2, 1};
    set_id set_expected = create_set(ARRAY_SIZE(expected_elements), expected_elements);
    TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));
    delete_set(set_expected);
    delete_set(set_result);
    delete_set(set_1);
    delete_set(set_2);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sets_with_no_elements_are_empty);
    RUN_TEST(test_sets_with_elements_are_not_empty);
    RUN_TEST(test_nothing_is_contained_in_an_empty_set);
    RUN_TEST(test_when_the_element_is_in_the_set);
    RUN_TEST(test_when_the_element_is_not_in_the_set);
    RUN_TEST(test_empty_set_is_a_subset_of_another_empty_set);
    RUN_TEST(test_empty_set_is_a_subset_of_nonempty_set);
    RUN_TEST(test_nonempty_set_is_not_a_subset_of_empty_set);
    RUN_TEST(test_set_is_a_subset_of_set_with_exact_same_elements);
    RUN_TEST(test_set_is_a_subset_of_larger_set_with_same_elements);
    RUN_TEST(test_set_is_not_a_subset_of_set_that_does_not_contain_its_elements);
    RUN_TEST(test_the_empty_set_is_disjoint_with_itself);
    RUN_TEST(test_empty_set_is_disjoint_with_nonempty_set);
    RUN_TEST(test_nonempty_set_is_disjoint_with_empty_set);
    RUN_TEST(test_sets_are_not_disjoint_if_they_share_an_element);
    RUN_TEST(test_sets_are_disjoint_if_they_share_no_elements);
    RUN_TEST(test_empty_sets_are_equal);
    RUN_TEST(test_empty_set_is_not_equal_to_nonempty_set);
    RUN_TEST(test_nonempty_set_is_not_equal_to_empty_set);
    RUN_TEST(test_sets_with_the_same_elements_are_equal);
    RUN_TEST(test_sets_with_different_elements_are_not_equal);
    RUN_TEST(test_set_is_not_equal_to_larger_set_with_same_elements);
    RUN_TEST(test_set_is_equal_to_a_set_constructed_from_an_array_with_duplicates);
    RUN_TEST(test_add_to_empty_set);
    RUN_TEST(test_add_to_nonempty_set);
    RUN_TEST(test_adding_an_existing_element_does_not_change_the_set);
    RUN_TEST(test_intersection_of_two_empty_sets_is_an_empty_set);
    RUN_TEST(test_intersection_of_an_empty_set_and_nonempty_set_is_an_empty_set);
    RUN_TEST(test_intersection_of_a_nonempty_set_and_an_empty_set_is_an_empty_set);
    RUN_TEST(test_intersection_of_two_sets_with_no_shared_elements_is_an_empty_set);
    RUN_TEST(test_intersection_of_two_sets_with_shared_elements_is_a_set_of_the_shared_elements);
    RUN_TEST(test_difference_of_two_empty_sets_is_an_empty_set);
    RUN_TEST(test_difference_of_empty_set_and_nonempty_set_is_an_empty_set);
    RUN_TEST(test_difference_of_a_nonempty_set_and_an_empty_set_is_the_nonempty_set);
    RUN_TEST(test_difference_of_two_nonempty_sets_is_a_set_of_elements_that_are_only_in_the_first_set);
    RUN_TEST(test_difference_removes_all_duplicates_in_the_first_set);
    RUN_TEST(test_union_of_empty_sets_is_an_empty_set);
    RUN_TEST(test_union_of_an_empty_set_and_nonempty_set_is_the_nonempty_set);
    RUN_TEST(test_union_of_a_nonempty_set_and_empty_set_is_the_nonempty_set);
    RUN_TEST(test_union_of_nonempty_sets_contains_all_unique_elements);
    return UNITY_END();
}
