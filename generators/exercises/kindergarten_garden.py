FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 80

extern void plants(char *buffer, const char *diagram, const char *student);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    diagram = inp["diagram"].replace("\n", "\\n")
    student = inp["student"]
    expected = ", ".join(expected)
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f'{prop}(buffer, "{diagram}", "{student}");\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
