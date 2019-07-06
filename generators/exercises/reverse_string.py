FUNC_PROTO = """\
#include "vendor/unity.h"

extern void reverse(char *value);
"""

def gen_func_body(prop, inp, expected):
    str_list = []
    value = inp["value"]
    str_list.append(f'char value[] = "{value}";\n\n')
    str_list.append(f'{prop}(value);\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", value);\n')
    return "".join(str_list)
