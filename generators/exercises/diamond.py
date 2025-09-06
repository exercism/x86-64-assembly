from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 52
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern size_t rows(char buffer[][BUFFER_SIZE], char letter);
"""

FUNC_GEN_TEMPLATE = Template("""
char buffer[BUFFER_SIZE][BUFFER_SIZE];
const char *const expected[] = ${expected};

TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), ${prop}(buffer, '${letter}'));

for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
    TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
}
""")


def str_array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace("'", '"')


def gen_func_body(prop, inp, expected):
    return FUNC_GEN_TEMPLATE.substitute(
        expected=str_array_literal(expected), prop=prop, letter=inp["letter"]
    )
