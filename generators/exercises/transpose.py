from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 32
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern size_t transpose(char buffer[][BUFFER_SIZE], const char *lines[], size_t num_of_lines);
"""

FUNC_GEN_TEMPLATE = Template("""
char buffer[BUFFER_SIZE][BUFFER_SIZE];
const char *lines[] = ${lines};
const size_t length = ${prop}(buffer, lines, ARRAY_SIZE(lines));
const char *expected[] = ${expected};
TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
for (size_t i = 0; i < length; ++i) {
    TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);
}
""")

NULL_TEMPLATE = Template("""
char buffer[BUFFER_SIZE][BUFFER_SIZE];
const size_t length = ${prop}(buffer, NULL, 0);
TEST_ASSERT_EQUAL_UINT64(0, length);
""")


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace("'", '"')


def gen_func_body(prop, inp, expected):
    if len(expected) == 0:
        return NULL_TEMPLATE.substitute(prop=prop)
    expected = array_literal(expected)
    lines = array_literal(inp["lines"])
    return FUNC_GEN_TEMPLATE.substitute(expected=expected, prop=prop, lines=lines)
