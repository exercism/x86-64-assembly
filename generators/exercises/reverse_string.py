FUNC_PROTO = """\
#include "vendor/unity.h"

extern void reverse(char *str);
"""

def gen_func_body(prop, inp, expected):
    str_list = []
    value = inp["value"]
    str_list.append(f'char str[] = "{value}";\n\n')
    str_list.append(f'{prop}(str);\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", str);\n')
    return "".join(str_list)
