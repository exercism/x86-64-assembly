FUNC_PROTO = """\
#include "vendor/unity.h"

extern uint64_t square(int square);
extern uint64_t total(void);
"""

def gen_func_body(prop, inp, expected):
    if type(expected) is not int:
        expected = 0
    if prop == "square":
        square = inp["square"]
        s = f"TEST_ASSERT_EQUAL_UINT64(UINT64_C({expected}), {prop}({square}));\n"
    elif prop == "total":
        s = f"TEST_ASSERT_EQUAL_UINT64(UINT64_C({expected}), {prop}());\n"
    return s
