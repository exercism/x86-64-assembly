FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define MAX_ARRAY_SIZE 100

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern size_t factors(uint64_t dest[], uint64_t value);
"""


def describe(case):
    return case["description"].replace("-", " ")


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    str_list = []
    if expected:
        str_list.append(f"const uint64_t expected[] = {array_literal(expected)};")
        str_list.append("uint64_t actual[MAX_ARRAY_SIZE];")
        str_list.append(f"const size_t size = {prop}(actual, {inp['value']});")
        str_list.append("TEST_ASSERT_EQUAL_UINT(ARRAY_SIZE(expected), size);")
        str_list.append("TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, actual, size);")
        return "\n".join(str_list)
    str_list.append("uint64_t actual[MAX_ARRAY_SIZE];")
    str_list.append(f"const size_t size = {prop}(actual, {inp['value']});")
    str_list.append("TEST_ASSERT_EQUAL_UINT(0u, size);")
    return "\n".join(str_list)
