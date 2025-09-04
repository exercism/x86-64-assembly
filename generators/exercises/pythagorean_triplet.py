FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define MAX_ARRAY_SIZE 120
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern size_t triplets_with_sum(uint64_t n, uint64_t *a, uint64_t *b, uint64_t *c);
"""


def extra_cases():
    return [
        {
            "description": "triplets for very large number",
            "property": "tripletsWithSum",
            "input": {"n": 238714},
            "expected": [[68145, 71672, 98897]],
        }
    ]


def array_literal(numbers):
    return str(list(numbers)).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    n = inp["n"]
    str_list = []
    if len(expected) > 0:
        str_list.append(
            f"const uint64_t expected_a[] = {array_literal(map(lambda t: t[0], expected))};\n"
        )
        str_list.append(
            f"const uint64_t expected_b[] = {array_literal(map(lambda t: t[1], expected))};\n"
        )
        str_list.append(
            f"const uint64_t expected_c[] = {array_literal(map(lambda t: t[2], expected))};\n"
        )
    str_list.append("uint64_t actual_a[MAX_ARRAY_SIZE];\n")
    str_list.append("uint64_t actual_b[MAX_ARRAY_SIZE];\n")
    str_list.append("uint64_t actual_c[MAX_ARRAY_SIZE];\n")
    str_list.append(
        f"const size_t size = triplets_with_sum({n}, actual_a, actual_b, actual_c);\n"
    )
    if len(expected) > 0:
        str_list.append("TEST_ASSERT_EQUAL_UINT(ARRAY_SIZE(expected_a), size);\n")
        str_list.append(
            'TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_a, actual_a, size, "a");\n'
        )
        str_list.append(
            'TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_b, actual_b, size, "b");\n'
        )
        str_list.append(
            'TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected_c, actual_c, size, "c");\n'
        )
    else:
        str_list.append("TEST_ASSERT_EQUAL_UINT(0U, size);\n")
    return "".join(str_list)
