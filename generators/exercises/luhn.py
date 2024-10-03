FUNC_PROTO = """\
#include "vendor/unity.h"

extern int valid(const char *str);
"""

def gen_func_body(prop, inp, expected):
    value = inp["value"]
    if expected:
        s = f'TEST_ASSERT_TRUE({prop}("{value}"));\n'
    else:
        s = f'TEST_ASSERT_FALSE({prop}("{value}"));\n'
    return s
