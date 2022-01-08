FUNC_PROTO = """\
#include "vendor/unity.h"

extern int steps(int number);
"""

def gen_func_body(prop, inp, expected):
    number = inp["number"]
    return f"TEST_ASSERT_EQUAL_INT({expected}, {prop}({number}));\n"