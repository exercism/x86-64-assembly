FUNC_PROTO = """\
#include <stdbool.h>

#include "vendor/unity.h"

extern bool is_pangram(const char *sentence);
"""

def gen_func_body(prop, inp, expected):
    sentence = inp["sentence"].replace('"', "\\\"")
    if expected:
        s = f'TEST_ASSERT_TRUE({prop}("{sentence}"));\n'
    else:
        s = f'TEST_ASSERT_FALSE({prop}("{sentence}"));\n'
    return s
