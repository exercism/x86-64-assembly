#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

typedef void *(*allocator_t)(size_t);
typedef void (*deallocator_t)(void *);

typedef struct node {
    int64_t data;
    struct node *next;
} node_t;

typedef struct {
    node_t *head;
    allocator_t alloc;
    deallocator_t dealloc;
} list_t;

extern list_t *create_list(allocator_t alloc, deallocator_t dealloc);
extern size_t count_list(const list_t *list);
extern void push_list(list_t *list, int64_t data);
extern int64_t peek_list(const list_t *list);
extern int64_t pop_list(list_t *list);
extern void reverse_list(list_t *list);
extern void delete_list(list_t *list);

static size_t alloc_count = 0;

static void *allocator(size_t sz) {
    alloc_count++;
    return malloc(sz);
}

static void deallocator(void *ptr) {
    alloc_count--;
    free(ptr);
}

void setUp(void) {
}

void tearDown(void) {
}

void test_empty_list_has_length_of_zero(void) {
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    TEST_ASSERT_EQUAL(0, count_list(list));
    TEST_ASSERT_EQUAL(1, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_singleton_list_has_length_of_one(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(1, count_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_nonempty_list_has_correct_length(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 3);
    TEST_ASSERT_EQUAL(4, alloc_count);
    TEST_ASSERT_EQUAL(3, count_list(list));
    TEST_ASSERT_EQUAL(4, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_can_pop_from_singleton_list(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(1, pop_list(list));
    TEST_ASSERT_EQUAL(1, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_can_pop_from_nonempty_list(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, pop_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_can_pop_multiple_items(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, pop_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(1, pop_list(list));
    TEST_ASSERT_EQUAL(1, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_pop_updates_the_count(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, count_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, pop_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(1, count_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(1, pop_list(list));
    TEST_ASSERT_EQUAL(1, alloc_count);
    TEST_ASSERT_EQUAL(0, count_list(list));
    TEST_ASSERT_EQUAL(1, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_can_push_to_an_empty_list(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_can_push_to_a_nonempty_list(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 3);
    TEST_ASSERT_EQUAL(4, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_push_updates_count(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 3);
    TEST_ASSERT_EQUAL(4, alloc_count);
    TEST_ASSERT_EQUAL(3, count_list(list));
    TEST_ASSERT_EQUAL(4, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_push_and_pop(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, pop_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 3);
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, count_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(3, pop_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(1, pop_list(list));
    TEST_ASSERT_EQUAL(1, alloc_count);
    TEST_ASSERT_EQUAL(0, count_list(list));
    TEST_ASSERT_EQUAL(1, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_can_peek_on_singleton_list(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(1, peek_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_can_peek_on_nonempty_list(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, peek_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_peek_does_not_change_the_count(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, peek_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, count_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_can_peek_after_a_pop_and_push(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, peek_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, pop_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(1, peek_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 3);
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(3, peek_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_empty_linked_list_to_list_is_empty(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_to_list_with_multiple_values(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 3);
    TEST_ASSERT_EQUAL(4, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(3, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(2, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(1, node->data);
    node = node->next;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_to_list_after_a_pop(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 3);
    TEST_ASSERT_EQUAL(4, alloc_count);
    TEST_ASSERT_EQUAL(3, pop_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 4);
    TEST_ASSERT_EQUAL(4, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(4, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(2, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(1, node->data);
    node = node->next;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_reversed_empty_list_has_same_values(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    reverse_list(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_reversed_singleton_list_is_same_list(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    reverse_list(list);
    TEST_ASSERT_EQUAL(2, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(1, node->data);
    node = node->next;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_reversed_nonempty_list_is_reversed(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 3);
    TEST_ASSERT_EQUAL(4, alloc_count);
    reverse_list(list);
    TEST_ASSERT_EQUAL(4, alloc_count);
    TEST_ASSERT_EQUAL(3, count_list(list));
    TEST_ASSERT_EQUAL(4, alloc_count);
    TEST_ASSERT_EQUAL(1, pop_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, pop_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(3, pop_list(list));
    TEST_ASSERT_EQUAL(1, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_double_reverse(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 3);
    TEST_ASSERT_EQUAL(4, alloc_count);
    reverse_list(list);
    TEST_ASSERT_EQUAL(4, alloc_count);
    reverse_list(list);
    TEST_ASSERT_EQUAL(4, alloc_count);
    TEST_ASSERT_EQUAL(3, pop_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(2, pop_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(1, pop_list(list));
    TEST_ASSERT_EQUAL(1, alloc_count);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_list_has_length_of_zero);
    RUN_TEST(test_singleton_list_has_length_of_one);
    RUN_TEST(test_nonempty_list_has_correct_length);
    RUN_TEST(test_can_pop_from_singleton_list);
    RUN_TEST(test_can_pop_from_nonempty_list);
    RUN_TEST(test_can_pop_multiple_items);
    RUN_TEST(test_pop_updates_the_count);
    RUN_TEST(test_can_push_to_an_empty_list);
    RUN_TEST(test_can_push_to_a_nonempty_list);
    RUN_TEST(test_push_updates_count);
    RUN_TEST(test_push_and_pop);
    RUN_TEST(test_can_peek_on_singleton_list);
    RUN_TEST(test_can_peek_on_nonempty_list);
    RUN_TEST(test_peek_does_not_change_the_count);
    RUN_TEST(test_can_peek_after_a_pop_and_push);
    RUN_TEST(test_empty_linked_list_to_list_is_empty);
    RUN_TEST(test_to_list_with_multiple_values);
    RUN_TEST(test_to_list_after_a_pop);
    RUN_TEST(test_reversed_empty_list_has_same_values);
    RUN_TEST(test_reversed_singleton_list_is_same_list);
    RUN_TEST(test_reversed_nonempty_list_is_reversed);
    RUN_TEST(test_double_reverse);
    return UNITY_END();
}
