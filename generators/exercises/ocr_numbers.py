from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 20
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef enum {
    success = 0,
    invalid_lines,
    invalid_columns
} error_t;

extern error_t convert(char buffer[], const char *const rows[], size_t num_of_rows);
"""

VALID_RESULT_TEMPLATE = Template("""
char buffer[BUFFER_SIZE];
const char *const rows[] = ${rows};

TEST_ASSERT_EQUAL(success, ${prop}(buffer, rows, ARRAY_SIZE(rows)));
TEST_ASSERT_EQUAL_STRING("${expected}", buffer);
""")

ERROR_TEMPLATE = Template("""
char buffer[BUFFER_SIZE];
const char *const rows[] = ${rows};

TEST_ASSERT_EQUAL(${error}, ${prop}(buffer, rows, ARRAY_SIZE(rows)));
""")


def str_array_literal(numbers):
    return (
        str(numbers)
        .replace("[", "{")
        .replace("]", "}")
        .replace("'", '"')
        .replace(",", ",\n\n")
    )


def gen_func_body(prop, inp, expected):
    if isinstance(expected, dict) and "error" in expected:
        if expected["error"] == "Number of input lines is not a multiple of four":
            return ERROR_TEMPLATE.substitute(
                rows=str_array_literal(inp["rows"]), error="invalid_lines", prop=prop
            )
        else:
            return ERROR_TEMPLATE.substitute(
                rows=str_array_literal(inp["rows"]), error="invalid_columns", prop=prop
            )
    else:
        return VALID_RESULT_TEMPLATE.substitute(
            rows=str_array_literal(inp["rows"]), prop=prop, expected=expected
        )
