FUNC_PROTO = """\
#include <stdbool.h>

#include "vendor/unity.h"

extern bool is_isogram(const char *str);
"""

def gen_func_body(prop, inp, expected):
    phrase = inp["phrase"]
    if expected:
        s = f'TEST_ASSERT_TRUE({prop}("{phrase}"));\n'
    else:
        s = f'TEST_ASSERT_FALSE({prop}("{phrase}"));\n'
    return s
