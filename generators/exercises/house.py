FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 4000

extern void recite(char *buffer, int start_verse, int end_verse);
"""


def gen_func_body(prop, inp, expected):
    start_verse = inp["startVerse"]
    end_verse = inp["endVerse"]
    str_list = []
    str_list.append("const char *expected =\n")
    for index in range(len(expected)):
        line = expected[index]
        if index + 1 < len(expected):
            str_list.append(f'    "{line}\\n"\n')
        else:
            str_list.append(f'    "{line}\\n";\n')
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f"{prop}(buffer, {start_verse}, {end_verse});\n")
    str_list.append("TEST_ASSERT_EQUAL_STRING(expected, buffer);\n")
    return "".join(str_list)
