from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 10
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern size_t combinations(uint8_t output[][BUFFER_SIZE], uint64_t sum, size_t size, const uint8_t *exclude, size_t exclude_count);
"""

NULL_EXCLUDE_TEMPLATE = Template("""
uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
const uint8_t expected[][BUFFER_SIZE] = ${expected};

TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), ${prop}(buffer, ${sum}, ${size}, NULL, 0));
for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], ${size});
}
""")

WITH_EXCLUDE_TEMPLATE = Template("""
uint8_t buffer[BUFFER_SIZE][BUFFER_SIZE];
const uint8_t expected[][BUFFER_SIZE] = ${expected};
const uint8_t exclude[] = ${exclude};

TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), ${prop}(buffer, ${sum}, ${size}, exclude, ARRAY_SIZE(exclude)));
for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected[i], buffer[i], ${size});
}
""")


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    inp = inp["cage"]
    if len(inp["exclude"]) == 0:
        return NULL_EXCLUDE_TEMPLATE.substitute(
            expected=array_literal(expected),
            prop=prop,
            sum=inp["sum"],
            size=inp["size"],
        )
    else:
        exclude = inp["exclude"]
        return WITH_EXCLUDE_TEMPLATE.substitute(
            expected=array_literal(expected),
            prop=prop,
            sum=inp["sum"],
            size=inp["size"],
            exclude=array_literal(exclude),
        )
