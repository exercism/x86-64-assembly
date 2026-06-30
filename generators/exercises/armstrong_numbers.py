FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdbool.h>
#include <stdint.h>

extern bool is_armstrong_number(uint32_t number);
"""


def describe(case):
    return case["description"].replace("-", " ")


def gen_func_body(prop, inp, expected):
    assertion = "TEST_ASSERT_TRUE" if expected else "TEST_ASSERT_FALSE"
    return f"{assertion}({prop}({inp['number']}));"
