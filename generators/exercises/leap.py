FUNC_PROTO = """\
#include <stdbool.h>

#include "vendor/unity.h"

extern bool leap_year(int year);
"""

def gen_func_body(prop, inp, expected):
    year = inp["year"]
    if expected:
        s = f"TEST_ASSERT_TRUE({prop}({year}));\n"
    else:
        s = f"TEST_ASSERT_FALSE({prop}({year}));\n"
    return s
