FUNC_PROTO = """\
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
"""


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace("'", "")


def create_set(node_set, node_id="input", set_id=""):
    str_list = []
    if len(node_set) == 0:
        str_list.append(f"set_id set{set_id} = create_set(0, NULL);")
    else:
        str_list.append(f"const int8_t {node_id}[] = {array_literal(node_set)};")
        str_list.append(
            f"set_id set{set_id} = create_set(ARRAY_SIZE({node_id}), {node_id});"
        )
    return "\n".join(str_list)


def gen_func_body(prop, inp, expected):
    str_list = []
    if "set" in inp:
        str_list.append(create_set(inp["set"], "input", "_result"))
        if prop == "empty":
            str_list.append(
                f"TEST_ASSERT_EQUAL({str(expected).lower()}, set_{prop}(set_result));"
            )
        elif prop == "contains":
            str_list.append(
                f"TEST_ASSERT_EQUAL({str(expected).lower()}, set_{prop}(set_result, {inp['element']}));"
            )
        else:
            str_list.append(f"set_{prop}(set_result, {inp['element']});")
            str_list.append(create_set(expected, "expected_elements", "_expected"))
            str_list.append(
                "TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));"
            )
            str_list.append("delete_set(set_expected);")
        str_list.append("delete_set(set_result);")
    else:
        id = 1
        for key, value in inp.items():
            if key.startswith("set"):
                str_list.append(create_set(value, f"input_{id}", f"_{id}"))
                id += 1
        if prop == "subset" or prop == "disjoint" or prop == "equal":
            str_list.append(
                f"TEST_ASSERT_EQUAL({str(expected).lower()}, set_{prop}(set_1, set_2));"
            )
        else:
            str_list.append(f"set_id set_result = set_{prop}(set_1, set_2);")
            str_list.append(create_set(expected, "expected_elements", "_expected"))
            str_list.append(
                "TEST_ASSERT_EQUAL(true, set_equal(set_result, set_expected));"
            )
            str_list.append("delete_set(set_expected);")
            str_list.append("delete_set(set_result);")
        str_list.append("delete_set(set_1);")
        str_list.append("delete_set(set_2);")
    return "\n".join(str_list)
