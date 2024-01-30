FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 16

extern void roman(int number, char *buffer);
"""

def gen_func_body(prop, inp, expected):
    str_list = []
    number = inp["number"]
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f'{prop}({number}, buffer);\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
