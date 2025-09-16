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
extern void push_list(list_t *list, int64_t data);
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

void test_can_create_list(void) {
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_can_push(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 16);
    TEST_ASSERT_EQUAL(2, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(16, node->data);
    node = node->next;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_push_updates_head(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 99);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, -123);
    TEST_ASSERT_EQUAL(3, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(-123, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(99, node->data);
    node = node->next;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_can_pop(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, -123);
    TEST_ASSERT_EQUAL(2, alloc_count);
    TEST_ASSERT_EQUAL(-123, pop_list(list));
    TEST_ASSERT_EQUAL(1, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_pop_multiple_values(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, -123);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 234);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 456);
    TEST_ASSERT_EQUAL(4, alloc_count);
    push_list(list, 789);
    TEST_ASSERT_EQUAL(5, alloc_count);
    TEST_ASSERT_EQUAL(789, pop_list(list));
    TEST_ASSERT_EQUAL(4, alloc_count);
    TEST_ASSERT_EQUAL(456, pop_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    TEST_ASSERT_EQUAL(234, pop_list(list));
    TEST_ASSERT_EQUAL(2, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(-123, node->data);
    node = node->next;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_multiple_operations(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 24);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, -15);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 28);
    TEST_ASSERT_EQUAL(4, alloc_count);
    push_list(list, 576);
    TEST_ASSERT_EQUAL(5, alloc_count);
    TEST_ASSERT_EQUAL(576, pop_list(list));
    TEST_ASSERT_EQUAL(4, alloc_count);
    TEST_ASSERT_EQUAL(28, pop_list(list));
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, 1245);
    TEST_ASSERT_EQUAL(4, alloc_count);
    push_list(list, 9829);
    TEST_ASSERT_EQUAL(5, alloc_count);
    push_list(list, -65555);
    TEST_ASSERT_EQUAL(6, alloc_count);
    push_list(list, 234);
    TEST_ASSERT_EQUAL(7, alloc_count);
    TEST_ASSERT_EQUAL(234, pop_list(list));
    TEST_ASSERT_EQUAL(6, alloc_count);
    TEST_ASSERT_EQUAL(-65555, pop_list(list));
    TEST_ASSERT_EQUAL(5, alloc_count);
    TEST_ASSERT_EQUAL(9829, pop_list(list));
    TEST_ASSERT_EQUAL(4, alloc_count);
    push_list(list, -777);
    TEST_ASSERT_EQUAL(5, alloc_count);
    push_list(list, 0);
    TEST_ASSERT_EQUAL(6, alloc_count);
    push_list(list, 19);
    TEST_ASSERT_EQUAL(7, alloc_count);
    TEST_ASSERT_EQUAL(19, pop_list(list));
    TEST_ASSERT_EQUAL(6, alloc_count);
    TEST_ASSERT_EQUAL(0, pop_list(list));
    TEST_ASSERT_EQUAL(5, alloc_count);
    push_list(list, 1);
    TEST_ASSERT_EQUAL(6, alloc_count);
    TEST_ASSERT_EQUAL(1, pop_list(list));
    TEST_ASSERT_EQUAL(5, alloc_count);
    TEST_ASSERT_EQUAL(-777, pop_list(list));
    TEST_ASSERT_EQUAL(4, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(1245, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(-15, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(24, node->data);
    node = node->next;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_reverse_list(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 0);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 45);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, -71);
    TEST_ASSERT_EQUAL(4, alloc_count);
    push_list(list, 4567890);
    TEST_ASSERT_EQUAL(5, alloc_count);
    push_list(list, 8000);
    TEST_ASSERT_EQUAL(6, alloc_count);
    push_list(list, 27);
    TEST_ASSERT_EQUAL(7, alloc_count);
    reverse_list(list);
    TEST_ASSERT_EQUAL(7, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(0, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(45, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(-71, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(4567890, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(8000, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(27, node->data);
    node = node->next;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

void test_reverse_of_a_reverse_is_original_list(void) {
    TEST_IGNORE();
    list_t *list = create_list(allocator, deallocator);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL(1, alloc_count);
    push_list(list, 8);
    TEST_ASSERT_EQUAL(2, alloc_count);
    push_list(list, 2198);
    TEST_ASSERT_EQUAL(3, alloc_count);
    push_list(list, -33);
    TEST_ASSERT_EQUAL(4, alloc_count);
    push_list(list, 24);
    TEST_ASSERT_EQUAL(5, alloc_count);
    push_list(list, 10);
    TEST_ASSERT_EQUAL(6, alloc_count);
    push_list(list, 175532);
    TEST_ASSERT_EQUAL(7, alloc_count);
    push_list(list, -6534);
    TEST_ASSERT_EQUAL(8, alloc_count);
    push_list(list, 892838);
    TEST_ASSERT_EQUAL(9, alloc_count);
    reverse_list(list);
    TEST_ASSERT_EQUAL(9, alloc_count);
    reverse_list(list);
    TEST_ASSERT_EQUAL(9, alloc_count);
    node_t *node = list->head;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(892838, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(-6534, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(175532, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(10, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(24, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(-33, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(2198, node->data);
    node = node->next;
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL(8, node->data);
    node = node->next;
    TEST_ASSERT_NULL(node);
    delete_list(list);
    TEST_ASSERT_EQUAL_UINT64(0, alloc_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_can_create_list);
    RUN_TEST(test_can_push);
    RUN_TEST(test_push_updates_head);
    RUN_TEST(test_can_pop);
    RUN_TEST(test_pop_multiple_values);
    RUN_TEST(test_multiple_operations);
    RUN_TEST(test_reverse_list);
    RUN_TEST(test_reverse_of_a_reverse_is_original_list);
    return UNITY_END();
}
