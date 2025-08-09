FUNC_PROTO = """\
#include "vendor/unity.h"

extern int leap_year(int year);
"""


def gen_func_body(prop, inp, expected):
    year = inp["year"]
    if expected:
        s = f"TEST_ASSERT_TRUE({prop}({year}));\n"
    else:
        s = f"TEST_ASSERT_FALSE({prop}({year}));\n"
    return s
