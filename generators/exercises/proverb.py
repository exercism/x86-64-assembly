FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 400

extern void recite(char *buffer, const char **strings);
"""


def gen_func_body(prop, inp, expected):
    strings = inp["strings"]
    str_list = []
    str_list.append("const char *strings[] = {\n")
    for string in strings:
        str_list.append(f'    "{string}",\n')
    str_list.append("    NULL,\n")
    str_list.append("};\n")
    if len(expected) == 0:
        str_list.append('const char *expected = "";\n')
    else:
        str_list.append("const char *expected =\n")
        for index in range(len(expected)):
            line = expected[index]
            if index + 1 < len(expected):
                str_list.append(f'    "{line}\\n"\n')
            else:
                str_list.append(f'    "{line}\\n";\n')
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f"{prop}(buffer, strings);\n")
    str_list.append("TEST_ASSERT_EQUAL_STRING(expected, buffer);\n")
    return "".join(str_list)
