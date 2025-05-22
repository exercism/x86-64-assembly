FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 80

extern void annotate(char *buffer, const char *minefield);
"""

def gen_func_body(prop, inp, expected):
    minefield = inp["minefield"]
    str_list = []

    def describe(name, minefield):
        str_list.append(f'const char *{name} =\n')
        if minefield == []:
            str_list.append(f'    "";\n')
            return

        for index in range(len(minefield)):
            line = minefield[index]
            if index + 1 < len(minefield):
                str_list.append(f'    "{line}\\n"\n')
            else:
                str_list.append(f'    "{line}\\n";\n')

    describe('minefield', minefield)
    describe('expected', expected)

    str_list.append(f'char buffer[BUFFER_SIZE];\n\n')
    str_list.append(f'{prop}(buffer, minefield);\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING(expected, buffer);\n')
    return "".join(str_list)
