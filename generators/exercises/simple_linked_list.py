FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

typedef void*(*allocator_t)(size_t);
typedef void(*deallocator_t)(void*);

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
"""


def push_initialValues(numbers, size):
    str_list = []
    for num in numbers:
        str_list.append(f"push_list(list, {num});")
        size += 1
        str_list.append(f"TEST_ASSERT_EQUAL({size}, alloc_count);")
    return "\n".join(str_list)


def pop_initialValues(ops, expected, size, op):
    str_list = []
    decrement = 0
    if op == "pop":
        decrement = 1
    for num in expected[:ops]:
        str_list.append(f"TEST_ASSERT_EQUAL({num}, {op}_list(list));")
        size -= decrement
        str_list.append(f"TEST_ASSERT_EQUAL({size}, alloc_count);")
    return "\n".join(str_list)


def check_resulting_list(expected, size):
    str_list = []
    str_list.append("node_t *node = list->head;")
    for value in expected:
        str_list.append("TEST_ASSERT_NOT_NULL(node);")
        str_list.append(f"TEST_ASSERT_EQUAL({value}, node->data);")
        str_list.append("node = node->next;")
    str_list.append("TEST_ASSERT_NULL(node);")
    return "\n".join(str_list)


def gen_func_body(_, inp, expected):
    str_list = []
    str_list.append("list_t *list = create_list(allocator, deallocator);")
    str_list.append("TEST_ASSERT_NOT_NULL(list);")
    size = 1
    str_list.append(f"TEST_ASSERT_EQUAL({size}, alloc_count);")
    if len(inp["initialValues"]) > 0:
        str_list.append(push_initialValues(inp["initialValues"], size))
        size += len(inp["initialValues"])
    for op in inp["operations"]:
        if op["operation"] == "push":
            str_list.append(push_initialValues([op["value"]], size))
            size += 1
        elif op["operation"] == "pop":
            str_list.append(pop_initialValues(1, [op["expected"]], size, "pop"))
            size -= 1
        elif op["operation"] == "peek":
            str_list.append(pop_initialValues(1, [op["expected"]], size, "peek"))
        elif op["operation"] == "reverse":
            str_list.append("reverse_list(list);")
            str_list.append(f"TEST_ASSERT_EQUAL({size}, alloc_count);")
        elif op["operation"] == "count":
            str_list.append(f"TEST_ASSERT_EQUAL({size - 1}, count_list(list));")
            str_list.append(f"TEST_ASSERT_EQUAL({size}, alloc_count);")
        elif op["operation"] == "toList":
            str_list.append(check_resulting_list(op["expected"], size))
    str_list.append("delete_list(list);")
    str_list.append("TEST_ASSERT_EQUAL_UINT64(0, alloc_count);")
    return "\n".join(str_list)
