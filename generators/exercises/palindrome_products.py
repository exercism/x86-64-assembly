from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 20
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

#define EMPTY_RESULT 0
#define INVALID_INPUT -1

typedef struct {
    size_t count;
    uint64_t factors[BUFFER_SIZE][2];
} factor_t;

extern int64_t largest(factor_t *factors, uint64_t min, uint64_t max);
extern int64_t smallest(factor_t *factors, uint64_t min, uint64_t max);
"""

VALID_RESULT_TEMPLATE = Template("""
factor_t factors = {0};
const int64_t result = ${prop}(&factors, ${min}, ${max});
const uint64_t expected[][2] = ${factors};

TEST_ASSERT_EQUAL_INT64(${value}, result);
TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), factors.count);

for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected[i], factors.factors[i], 2);
}
""")

ERROR_TEMPLATE = Template("""
factor_t factors = {0};
TEST_ASSERT_EQUAL(${error}, ${prop}(&factors, ${min}, ${max}));
""")


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    if "error" in expected:
        return ERROR_TEMPLATE.substitute(
            error="INVALID_INPUT", prop=prop, min=inp["min"], max=inp["max"]
        )
    elif len(expected["factors"]) == 0:
        return ERROR_TEMPLATE.substitute(
            error="EMPTY_RESULT", prop=prop, min=inp["min"], max=inp["max"]
        )
    else:
        return VALID_RESULT_TEMPLATE.substitute(
            factors=array_literal(expected["factors"]),
            value=expected["value"],
            prop=prop,
            min=inp["min"],
            max=inp["max"],
        )
