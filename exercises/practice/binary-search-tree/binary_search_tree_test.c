#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#define BUFFER_SIZE 100
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef struct node node_t;

struct node {
    int64_t data;
    node_t *left;
    node_t *right;
};

typedef void *(*allocator_t)(size_t);
typedef void (*deallocator_t)(void *);

extern node_t *build_tree(allocator_t allocator, const int64_t *tree_data, size_t data_count);
extern size_t sorted_data(int64_t *buffer, node_t *tree);
extern void delete_tree(node_t *tree, deallocator_t deallocator);

void setUp(void) {
}

void tearDown(void) {
}

void test_data_is_retained(void) {
    const int64_t tree_data[] = {4};
    node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));
    TEST_ASSERT_EQUAL_INT64(4, tree->data);
    TEST_ASSERT_NULL(tree->left);
    TEST_ASSERT_NULL(tree->right);
    delete_tree(tree, free);
}

void test_smaller_number_at_left_node(void) {
    TEST_IGNORE();
    const int64_t tree_data[] = {4, 2};
    node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));
    TEST_ASSERT_EQUAL_INT64(4, tree->data);
    TEST_ASSERT_NOT_NULL(tree->left);
    TEST_ASSERT_EQUAL_INT64(2, tree->left->data);
    TEST_ASSERT_NULL(tree->left->left);
    TEST_ASSERT_NULL(tree->left->right);
    TEST_ASSERT_NULL(tree->right);
    delete_tree(tree, free);
}

void test_same_number_at_left_node(void) {
    TEST_IGNORE();
    const int64_t tree_data[] = {4, 4};
    node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));
    TEST_ASSERT_EQUAL_INT64(4, tree->data);
    TEST_ASSERT_NOT_NULL(tree->left);
    TEST_ASSERT_EQUAL_INT64(4, tree->left->data);
    TEST_ASSERT_NULL(tree->left->left);
    TEST_ASSERT_NULL(tree->left->right);
    TEST_ASSERT_NULL(tree->right);
    delete_tree(tree, free);
}

void test_greater_number_at_right_node(void) {
    TEST_IGNORE();
    const int64_t tree_data[] = {4, 5};
    node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));
    TEST_ASSERT_EQUAL_INT64(4, tree->data);
    TEST_ASSERT_NULL(tree->left);
    TEST_ASSERT_NOT_NULL(tree->right);
    TEST_ASSERT_EQUAL_INT64(5, tree->right->data);
    TEST_ASSERT_NULL(tree->right->left);
    TEST_ASSERT_NULL(tree->right->right);
    delete_tree(tree, free);
}

void test_can_create_complex_tree(void) {
    TEST_IGNORE();
    const int64_t tree_data[] = {4, 2, 6, 1, 3, 5, 7};
    node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));
    TEST_ASSERT_EQUAL_INT64(4, tree->data);
    TEST_ASSERT_NOT_NULL(tree->left);
    TEST_ASSERT_EQUAL_INT64(2, tree->left->data);
    TEST_ASSERT_NOT_NULL(tree->left->left);
    TEST_ASSERT_EQUAL_INT64(1, tree->left->left->data);
    TEST_ASSERT_NULL(tree->left->left->left);
    TEST_ASSERT_NULL(tree->left->left->right);
    TEST_ASSERT_NOT_NULL(tree->left->right);
    TEST_ASSERT_EQUAL_INT64(3, tree->left->right->data);
    TEST_ASSERT_NULL(tree->left->right->left);
    TEST_ASSERT_NULL(tree->left->right->right);
    TEST_ASSERT_NOT_NULL(tree->right);
    TEST_ASSERT_EQUAL_INT64(6, tree->right->data);
    TEST_ASSERT_NOT_NULL(tree->right->left);
    TEST_ASSERT_EQUAL_INT64(5, tree->right->left->data);
    TEST_ASSERT_NULL(tree->right->left->left);
    TEST_ASSERT_NULL(tree->right->left->right);
    TEST_ASSERT_NOT_NULL(tree->right->right);
    TEST_ASSERT_EQUAL_INT64(7, tree->right->right->data);
    TEST_ASSERT_NULL(tree->right->right->left);
    TEST_ASSERT_NULL(tree->right->right->right);
    delete_tree(tree, free);
}

void test_can_sort_single_number(void) {
    TEST_IGNORE();
    const int64_t tree_data[] = {2};
    node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));
    int64_t buffer[BUFFER_SIZE];
    const int64_t expected[] = {2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), sorted_data(buffer, tree));
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
    delete_tree(tree, free);
}

void test_can_sort_if_second_number_is_smaller_than_first(void) {
    TEST_IGNORE();
    const int64_t tree_data[] = {2, 1};
    node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));
    int64_t buffer[BUFFER_SIZE];
    const int64_t expected[] = {1, 2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), sorted_data(buffer, tree));
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
    delete_tree(tree, free);
}

void test_can_sort_if_second_number_is_same_as_first(void) {
    TEST_IGNORE();
    const int64_t tree_data[] = {2, 2};
    node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));
    int64_t buffer[BUFFER_SIZE];
    const int64_t expected[] = {2, 2};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), sorted_data(buffer, tree));
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
    delete_tree(tree, free);
}

void test_can_sort_if_second_number_is_greater_than_first(void) {
    TEST_IGNORE();
    const int64_t tree_data[] = {2, 3};
    node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));
    int64_t buffer[BUFFER_SIZE];
    const int64_t expected[] = {2, 3};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), sorted_data(buffer, tree));
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
    delete_tree(tree, free);
}

void test_can_sort_complex_tree(void) {
    TEST_IGNORE();
    const int64_t tree_data[] = {2, 1, 3, 6, 7, 5};
    node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));
    int64_t buffer[BUFFER_SIZE];
    const int64_t expected[] = {1, 2, 3, 5, 6, 7};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), sorted_data(buffer, tree));
    TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));
    delete_tree(tree, free);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_data_is_retained);
    RUN_TEST(test_smaller_number_at_left_node);
    RUN_TEST(test_same_number_at_left_node);
    RUN_TEST(test_greater_number_at_right_node);
    RUN_TEST(test_can_create_complex_tree);
    RUN_TEST(test_can_sort_single_number);
    RUN_TEST(test_can_sort_if_second_number_is_smaller_than_first);
    RUN_TEST(test_can_sort_if_second_number_is_same_as_first);
    RUN_TEST(test_can_sort_if_second_number_is_greater_than_first);
    RUN_TEST(test_can_sort_complex_tree);
    return UNITY_END();
}
