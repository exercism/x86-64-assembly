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
"""


def extra_cases():
    return [
        {
            "description": "can_create_list",
            "property": "run",
            "input": {},
            "expected": [],
        },
        {
            "description": "can_push",
            "property": "run",
            "input": [{"operation": "push", "values": [16]}],
            "expected": [16],
        },
        {
            "description": "push_updates_head",
            "property": "run",
            "input": [{"operation": "push", "values": [99, -123]}],
            "expected": [-123, 99],
        },
        {
            "description": "can_pop",
            "property": "run",
            "input": [
                {"operation": "push", "values": [-123]},
                {"operation": "pop", "ops": 1, "expected": [-123]},
            ],
            "expected": [],
        },
        {
            "description": "pop_multiple_values",
            "property": "run",
            "input": [
                {"operation": "push", "values": [-123, 234, 456, 789]},
                {"operation": "pop", "ops": 3, "expected": [789, 456, 234]},
            ],
            "expected": [-123],
        },
        {
            "description": "multiple_operations",
            "property": "run",
            "input": [
                {"operation": "push", "values": [24, -15, 28, 576]},
                {"operation": "pop", "ops": 2, "expected": [576, 28]},
                {"operation": "push", "values": [1245, 9829, -65555, 234]},
                {"operation": "pop", "ops": 3, "expected": [234, -65555, 9829]},
                {"operation": "push", "values": [-777, 0, 19]},
                {"operation": "pop", "ops": 1, "expected": [19]},
                {"operation": "pop", "ops": 1, "expected": [0]},
                {"operation": "push", "values": [1]},
                {"operation": "pop", "ops": 2, "expected": [1, -777]},
            ],
            "expected": [1245, -15, 24],
        },
        {
            "description": "reverse_list",
            "property": "run",
            "input": [
                {"operation": "push", "values": [0, 45, -71, 4567890, 8000, 27]},
                {"operation": "reverse"},
            ],
            "expected": [0, 45, -71, 4567890, 8000, 27],
        },
        {
            "description": "reverse_of_a_reverse_is_original_list",
            "property": "run",
            "input": [
                {
                    "operation": "push",
                    "values": [8, 2198, -33, 24, 10, 175532, -6534, 892838],
                },
                {"operation": "reverse"},
                {"operation": "reverse"},
            ],
            "expected": [892838, -6534, 175532, 10, 24, -33, 2198, 8],
        },
    ]


def push_values(numbers, size):
    str_list = []
    for num in numbers:
        str_list.append(f"push_list(list, {num});")
        size += 1
        str_list.append(f"TEST_ASSERT_EQUAL({size}, alloc_count);")
    return "\n".join(str_list)


def pop_values(ops, expected, size):
    str_list = []
    for num in expected[:ops]:
        str_list.append(f"TEST_ASSERT_EQUAL({num}, pop_list(list));")
        size -= 1
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
    for op in inp:
        if op["operation"] == "push":
            str_list.append(push_values(op["values"], size))
            size += len(op["values"])
        elif op["operation"] == "pop":
            str_list.append(pop_values(op["ops"], op["expected"], size))
            size -= op["ops"]
        else:
            str_list.append("reverse_list(list);")
            str_list.append(f"TEST_ASSERT_EQUAL({size}, alloc_count);")
    str_list.append(check_resulting_list(expected, size))
    str_list.append("delete_list(list);")
    str_list.append("TEST_ASSERT_EQUAL_UINT64(0, alloc_count);")
    return "\n".join(str_list)
