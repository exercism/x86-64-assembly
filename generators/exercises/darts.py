FUNC_PROTO = """\
#include "vendor/unity.h"

extern uint8_t score(double x, double y);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    x = inp["x"]
    y = inp["y"]
    str_list.append(f"uint8_t expected = {expected};\n\n")
    str_list.append(f"TEST_ASSERT_EQUAL_UINT8(expected, {prop}({x}, {y}));\n")
    return "".join(str_list)
