FUNC_PROTO = """\
#include "vendor/unity.h"

extern int score(const char *score);
"""


def gen_func_body(prop, inp, expected):
    word = inp["word"]
    return f'TEST_ASSERT_EQUAL({expected}, score("{word}"));\n'
