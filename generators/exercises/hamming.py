FUNC_PROTO = """\
#include "vendor/unity.h"

extern int distance(const char *strand1, const char *strand2);
"""


def gen_func_body(prop, inp, expected):
    strand1 = inp["strand1"]
    strand2 = inp["strand2"]
    if type(expected) is not int:
        expected = -1
    return f'TEST_ASSERT_EQUAL_INT({expected}, {prop}("{strand1}", "{strand2}"));\n'
