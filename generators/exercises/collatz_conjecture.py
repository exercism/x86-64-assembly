FUNC_PROTO = """\
#include "vendor/unity.h"

#define ERROR_VALUE -1

extern int steps(int number);
"""


def gen_func_body(prop, inp, expected):
    number = inp["number"]
    if isinstance(expected, dict):
        expected = "ERROR_VALUE"
    return f"TEST_ASSERT_EQUAL_INT({expected}, {prop}({number}));\n"
