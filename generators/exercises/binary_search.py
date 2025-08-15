FUNC_PROTO = """\
#include "vendor/unity.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern int find(int *array, int size, int value);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    array = str(inp["array"]).replace("[", "{").replace("]", "}")
    value = inp["value"]
    if type(expected) is not int:
        expected = -1
    if inp["array"]:
        str_list.append(f"int array[] = {array};\n\n")
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT({expected}, {prop}(array, ARRAY_SIZE(array), {value}));\n"
        )
    else:
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT({expected}, {prop}(NULL, 0, {value}));\n"
        )
    return "".join(str_list)
