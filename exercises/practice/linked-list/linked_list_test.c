// Version: 0

#include <stddef.h>
#include "vendor/unity.h"

// constructs a new (empty) list - called during setup
// recommend : don't rely on `malloc`/`calloc`
extern void list_create(void);

// counts the items on a list
extern size_t list_count(void);

// inserts item at back of a list
extern void list_push(int item_data);

// removes item from back of a list
extern int list_pop(void);

// inserts item at front of a list
extern void list_unshift(int item_data);

// removes item from front of a list
extern int list_shift(void);

// deletes a node that holds the matching data
extern void list_delete(int data);

// destroys an entire list - called during teardown
// recommend : clear pointer and values for this run
extern void list_destroy(void);

void setUp(void) {
    list_create();
}

void tearDown(void) {
    list_destroy();
}

void test_pop_gets_element_from_the_list(void) {
    list_push(7);
    TEST_ASSERT_EQUAL(7, list_pop());
}

void test_pushpop_respectively_addremove_at_the_end_of_the_list(void) {
    TEST_IGNORE();
    list_push(11);
    list_push(13);
    TEST_ASSERT_EQUAL(13, list_pop());
    TEST_ASSERT_EQUAL(11, list_pop());
}

void test_shift_gets_an_element_from_the_list(void) {
    TEST_IGNORE();
    list_push(17);
    TEST_ASSERT_EQUAL(17, list_shift());
}

void test_shift_gets_first_element_from_the_list(void) {
    TEST_IGNORE();
    list_push(23);
    list_push(5);
    TEST_ASSERT_EQUAL(23, list_shift());
    TEST_ASSERT_EQUAL(5, list_shift());
}

void test_unshift_adds_element_at_start_of_the_list(void) {
    TEST_IGNORE();
    list_unshift(23);
    list_unshift(5);
    TEST_ASSERT_EQUAL(5, list_shift());
    TEST_ASSERT_EQUAL(23, list_shift());
}

void test_pop_push_shift_and_unshift_can_be_used_in_any_order(void) {
    TEST_IGNORE();
    list_push(1);
    list_push(2);
    TEST_ASSERT_EQUAL(2, list_pop());
    list_push(3);
    TEST_ASSERT_EQUAL(1, list_shift());
    list_unshift(4);
    list_push(5);
    TEST_ASSERT_EQUAL(4, list_shift());
    TEST_ASSERT_EQUAL(5, list_pop());
    TEST_ASSERT_EQUAL(3, list_shift());
}

void test_count_an_empty_list(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL(0, list_count());
}

void test_count_a_list_with_items(void) {
    TEST_IGNORE();
    list_push(37);
    list_push(1);
    TEST_ASSERT_EQUAL(2, list_count());
}

void test_count_is_correct_after_mutation(void) {
    TEST_IGNORE();
    list_push(31);
    TEST_ASSERT_EQUAL(1, list_count());
    list_unshift(43);
    TEST_ASSERT_EQUAL(2, list_count());
    list_shift();
    TEST_ASSERT_EQUAL(1, list_count());
    list_pop();
    TEST_ASSERT_EQUAL(0, list_count());
}

void test_popping_to_empty_doesnt_break_the_list(void) {
    TEST_IGNORE();
    list_push(41);
    list_push(59);
    list_pop();
    list_pop();
    list_push(47);
    TEST_ASSERT_EQUAL(1, list_count());
    TEST_ASSERT_EQUAL(47, list_pop());
}

void test_shifting_to_empty_doesnt_break_the_list(void) {
    TEST_IGNORE();
    list_push(41);
    list_push(59);
    list_shift();
    list_shift();
    list_push(47);
    TEST_ASSERT_EQUAL(1, list_count());
    TEST_ASSERT_EQUAL(47, list_shift());
}

void test_deletes_the_only_element(void) {
    TEST_IGNORE();
    list_push(61);
    list_delete(61);
    TEST_ASSERT_EQUAL(0, list_count());
}

void test_deletes_the_element_with_the_specified_value_from_the_list(void) {
    TEST_IGNORE();
    list_push(71);
    list_push(83);
    list_push(79);
    list_delete(83);
    TEST_ASSERT_EQUAL(2, list_count());
    TEST_ASSERT_EQUAL(79, list_pop());
    TEST_ASSERT_EQUAL(71, list_shift());
}

void test_deletes_the_element_with_the_specified_value_from_the_list_reassigns_tail(void) {
    TEST_IGNORE();
    list_push(71);
    list_push(83);
    list_push(79);
    list_delete(83);
    TEST_ASSERT_EQUAL(2, list_count());
    TEST_ASSERT_EQUAL(79, list_pop());
    TEST_ASSERT_EQUAL(71, list_pop());
}

void test_deletes_the_element_with_the_specified_value_from_the_list_reassigns_head(void) {
    TEST_IGNORE();
    list_push(71);
    list_push(83);
    list_push(79);
    list_delete(83);
    TEST_ASSERT_EQUAL(2, list_count());
    TEST_ASSERT_EQUAL(71, list_shift());
    TEST_ASSERT_EQUAL(79, list_shift());
}

void test_deletes_the_first_of_two_elements(void) {
    TEST_IGNORE();
    list_push(97);
    list_push(101);
    list_delete(97);
    TEST_ASSERT_EQUAL(1, list_count());
    TEST_ASSERT_EQUAL(101, list_pop());
}

void test_deletes_the_second_of_two_elements(void) {
    TEST_IGNORE();
    list_push(97);
    list_push(101);
    list_delete(101);
    TEST_ASSERT_EQUAL(1, list_count());
    TEST_ASSERT_EQUAL(97, list_pop());
}

void test_delete_does_not_modify_the_list_if_the_element_is_not_found(void) {
    TEST_IGNORE();
    list_push(89);
    list_delete(103);
    TEST_ASSERT_EQUAL(1, list_count());
}

void test_deletes_only_the_first_occurrence(void) {
    TEST_IGNORE();
    list_push(73);
    list_push(9);
    list_push(9);
    list_push(107);
    list_delete(9);
    TEST_ASSERT_EQUAL(3, list_count());
    TEST_ASSERT_EQUAL(107, list_pop());
    TEST_ASSERT_EQUAL(9, list_pop());
    TEST_ASSERT_EQUAL(73, list_pop());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pop_gets_element_from_the_list);
    RUN_TEST(test_pushpop_respectively_addremove_at_the_end_of_the_list);
    RUN_TEST(test_shift_gets_an_element_from_the_list);
    RUN_TEST(test_shift_gets_first_element_from_the_list);
    RUN_TEST(test_unshift_adds_element_at_start_of_the_list);
    RUN_TEST(test_pop_push_shift_and_unshift_can_be_used_in_any_order);
    RUN_TEST(test_count_an_empty_list);
    RUN_TEST(test_count_a_list_with_items);
    RUN_TEST(test_count_is_correct_after_mutation);
    RUN_TEST(test_popping_to_empty_doesnt_break_the_list);
    RUN_TEST(test_shifting_to_empty_doesnt_break_the_list);
    RUN_TEST(test_deletes_the_only_element);
    RUN_TEST(test_deletes_the_element_with_the_specified_value_from_the_list);
    RUN_TEST(test_deletes_the_element_with_the_specified_value_from_the_list_reassigns_tail);
    RUN_TEST(test_deletes_the_element_with_the_specified_value_from_the_list_reassigns_head);
    RUN_TEST(test_deletes_the_first_of_two_elements);
    RUN_TEST(test_deletes_the_second_of_two_elements);
    RUN_TEST(test_delete_does_not_modify_the_list_if_the_element_is_not_found);
    RUN_TEST(test_deletes_only_the_first_occurrence);
    return UNITY_END();
}
