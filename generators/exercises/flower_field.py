FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 80

extern void annotate(char *buffer, const char *garden);
"""


def gen_func_body(prop, inp, expected):
    garden = inp["garden"]
    str_list = []

    def describe(name, garden):
        str_list.append(f"const char *{name} =\n")
        if garden == []:
            str_list.append('    "";\n')
            return

        for index in range(len(garden)):
            line = garden[index]
            if index + 1 < len(garden):
                str_list.append(f'    "{line}\\n"\n')
            else:
                str_list.append(f'    "{line}\\n";\n')

    describe("garden", garden)
    describe("expected", expected)

    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f"{prop}(buffer, garden);\n")
    str_list.append("TEST_ASSERT_EQUAL_STRING(expected, buffer);\n")
    return "".join(str_list)
