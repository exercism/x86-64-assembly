FUNC_PROTO = """\
#include "vendor/unity.h"

extern int square_of_sum(int number);
extern int sum_of_squares(int number);
extern int difference_of_squares(int number);
"""


def gen_func_body(prop, inp, expected):
    number = inp["number"]
    return f"TEST_ASSERT_EQUAL_INT({expected}, {prop}({number}));\n"
