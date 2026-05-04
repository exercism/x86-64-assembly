from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>

#define BUFFER_SIZE 512
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern void tally(char buffer[], const char rows[]);
"""

FUNC_GEN_TEMPLATE = Template("""
char buffer[BUFFER_SIZE];
alignas(16) const char rows[] = "${rows}";
const char *expected = "${expected}";

${prop}(buffer, rows);

TEST_ASSERT_EQUAL_STRING(expected, buffer);
""")


def gen_func_body(prop, inp, expected):
    rows = '\\n"\n"'.join(inp["rows"])
    expected = '\\n"\n"'.join(expected)
    return FUNC_GEN_TEMPLATE.substitute(rows=rows, expected=expected, prop=prop)
