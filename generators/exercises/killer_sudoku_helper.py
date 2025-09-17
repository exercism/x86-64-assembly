from string import Template
from functools import reduce
import operator

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 10
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern size_t combinations(uint16_t output[], uint16_t sum, size_t size, const uint16_t exclude);
"""

NULL_EXCLUDE_TEMPLATE = Template("""
uint16_t buffer[BUFFER_SIZE];
const uint16_t expected[] = ${expected};

TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), ${prop}(buffer, ${sum}, ${size}, 0));
TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
""")

WITH_EXCLUDE_TEMPLATE = Template("""
uint16_t buffer[BUFFER_SIZE];
const uint16_t expected[] = ${expected};
const uint16_t exclude = ${exclude};

TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), ${prop}(buffer, ${sum}, ${size}, exclude));
TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, buffer, ARRAY_SIZE(expected));
""")


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace("'", "")


def gen_func_body(prop, inp, expected):
    inp = inp["cage"]
    if len(inp["exclude"]) == 0:
        expected = sorted(
            [
                format(n, "#018b")
                for n in [
                    reduce(operator.or_, (1 << x for x in lst), 0) for lst in expected
                ]
            ]
        )
        return NULL_EXCLUDE_TEMPLATE.substitute(
            expected=array_literal(expected),
            prop=prop,
            sum=inp["sum"],
            size=inp["size"],
        )
    else:
        expected = sorted(
            [
                format(n, "#018b")
                for n in [
                    reduce(operator.or_, (1 << x for x in lst), 0) for lst in expected
                ]
            ]
        )
        exclude = format(
            reduce(operator.or_, (1 << x for x in inp["exclude"]), 0), "#018b"
        )
        return WITH_EXCLUDE_TEMPLATE.substitute(
            expected=array_literal(expected),
            prop=prop,
            sum=inp["sum"],
            size=inp["size"],
            exclude=array_literal(exclude),
        )
