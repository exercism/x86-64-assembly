FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdbool.h>
#include <stdint.h>

extern bool is_armstrong_number(uint32_t number);
"""


def describe(case):
    return case["description"].replace("-", " ")


def gen_func_body(prop, inp, expected):
    result = "true" if expected else "false"
    return f"TEST_ASSERT_EQUAL({result}, {prop}({inp['number']}));"
