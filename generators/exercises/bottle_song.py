FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 4000

extern void recite(char *buffer, int start_bottles, int take_down);
"""


def gen_func_body(prop, inp, expected):
    start_bottles = inp["startBottles"]
    take_down = inp["takeDown"]
    str_list = []
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f"recite(buffer, {start_bottles}, {take_down});\n")
    str_list.append("const char expected[] =\n")
    for index in range(len(expected)):
        line = expected[index]
        if index + 1 < len(expected):
            str_list.append(f'    "{line}\\n"\n')
        else:
            str_list.append(f'    "{line}\\n";\n')
    str_list.append("TEST_ASSERT_EQUAL_STRING(expected, buffer);\n")
    return "".join(str_list)
