FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void two_fer(const char *name, char *buffer);
"""

def gen_func_body(prop, inp, expected):
    str_list = []
    name = inp["name"]
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    if name:
        str_list.append(f'{prop}("{name}", buffer);\n')
    else:
        str_list.append(f"{prop}(NULL, buffer);\n")
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
