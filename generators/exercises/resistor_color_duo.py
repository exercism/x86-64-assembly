FUNC_PROTO = """\
#include "vendor/unity.h"

extern int value(const char *first, const char *second, const char *third);
"""


def describe(case):
    return case["description"].replace("-", " ")


def gen_func_body(prop, inp, expected):
    colors = inp["colors"]
    third = f'"{colors[2]}"' if len(colors) > 2 else "NULL"
    str_list = []
    str_list.append(
        f'const int result = {prop}("{colors[0]}", "{colors[1]}", {third});'
    )
    str_list.append(f"TEST_ASSERT_EQUAL_INT({expected}, result);")
    return "\n".join(str_list)
