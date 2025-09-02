FUNC_PROTO = """\
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

typedef void*(*allocator_t)(size_t);
typedef void(*deallocator_t)(void*);

extern node_t* build_tree(allocator_t allocator, const int64_t *tree_data, size_t data_count);
extern size_t sorted_data(int64_t *buffer, node_t* tree);
extern void delete_tree(node_t *tree, deallocator_t deallocator);
"""


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace("'", "")


def gen_func_body(prop, inp, expected):
    str_list = []
    tree_data = array_literal(inp["treeData"])
    str_list.append(f"const int64_t tree_data[] = {tree_data};\n")
    str_list.append(
        "node_t *tree = build_tree(malloc, tree_data, ARRAY_SIZE(tree_data));\n"
    )

    def recur_checks(exp_node, inp_node):
        nonlocal str_list
        if "data" in exp_node:
            str_list.append(
                f"TEST_ASSERT_EQUAL_INT64({exp_node['data']}, {inp_node}->data);\n"
            )
        if "left" in exp_node:
            if exp_node["left"] is None:
                str_list.append(f"TEST_ASSERT_NULL({inp_node}->left);\n")
            else:
                str_list.append(f"TEST_ASSERT_NOT_NULL({inp_node}->left);\n")
                recur_checks(exp_node["left"], inp_node + "->left")
        if "right" in exp_node:
            if exp_node["right"] is None:
                str_list.append(f"TEST_ASSERT_NULL({inp_node}->right);\n")
            else:
                str_list.append(f"TEST_ASSERT_NOT_NULL({inp_node}->right);\n")
                recur_checks(exp_node["right"], inp_node + "->right")
        return

    if prop == "sorted_data":
        str_list.append("int64_t buffer[BUFFER_SIZE];\n")
        str_list.append(f"const int64_t expected[] = {array_literal(expected)};\n")
        str_list.append(
            f"TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), {prop}(buffer, tree));\n"
        )
        str_list.append(
            "TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));\n"
        )
    else:
        recur_checks(expected, "tree")
    str_list.append("delete_tree(tree, free);\n")
    return "".join(str_list)
