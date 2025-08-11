FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 60

extern void commands(char *buffer, int number);
"""


def gen_func_body(prop, inp, expected):
    number = inp["number"]
    expected = ", ".join(expected)
    str_list = []
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f"commands(buffer, {number});\n")
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
