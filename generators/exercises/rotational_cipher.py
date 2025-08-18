FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void rotate(const char *text, int shift_key, char *buffer);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    text = inp["text"]
    shift_key = inp["shiftKey"]
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f'{prop}("{text}", {shift_key}, buffer);\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
