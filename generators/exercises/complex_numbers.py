from string import Template
import math

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

typedef struct {
    float real;
    float imag;
} complex_t;

extern float complex_real(complex_t z);
extern float complex_imaginary(complex_t z);
extern complex_t complex_mul(complex_t z1, complex_t z2);
extern complex_t complex_add(complex_t z1, complex_t z2);
extern complex_t complex_sub(complex_t z1, complex_t z2);
extern complex_t complex_div(complex_t z1, complex_t z2);
extern float complex_abs(complex_t z);
extern complex_t complex_conjugate(complex_t z);
extern complex_t complex_exp(complex_t z);
extern complex_t complex_real_add(complex_t z1, float z2);
extern complex_t real_complex_add(float z1, complex_t z2);
extern complex_t complex_real_sub(complex_t z1, float z2);
extern complex_t real_complex_sub(float z1, complex_t z2);
extern complex_t complex_real_mul(complex_t z1, float z2);
extern complex_t real_complex_mul(float z1, complex_t z2);
extern complex_t complex_real_div(complex_t z1, float z2);
extern complex_t real_complex_div(float z1, complex_t z2);
"""

BINARY_COMPLEX_RESULT_TEMPLATE = Template("""
const ${type1} z1 = ${z1};
const ${type2} z2 = ${z2};
const complex_t result = ${prop}(z1, z2);
const complex_t expected = ${expected};

TEST_ASSERT_FLOAT_WITHIN(0.0001, expected.real, result.real);
TEST_ASSERT_FLOAT_WITHIN(0.0001, expected.imag, result.imag);
""")

UNARY_COMPLEX_RESULT_TEMPLATE = Template("""
const complex_t z = ${z};
const complex_t result = ${prop}(z);
const complex_t expected = ${expected};

TEST_ASSERT_FLOAT_WITHIN(0.0001, expected.real, result.real);
TEST_ASSERT_FLOAT_WITHIN(0.0001, expected.imag, result.imag);
""")

UNARY_FLOAT_RESULT_TEMPLATE = Template("""
const complex_t z = ${z};
const float result = ${prop}(z);

TEST_ASSERT_FLOAT_WITHIN(0.0001, ${expected}, result);
""")


def get_type(x):
    if isinstance(x, list):
        return "complex_t"
    else:
        return "float"


def struct_literal(numbers):
    return (
        str(numbers)
        .replace("[", "{")
        .replace("]", "}")
        .replace("pi", f"{math.pi}")
        .replace("ln(2)", f"{math.log(2)}")
        .replace("e", f"{math.e}")
        .replace("'", "")
    )


def gen_func_body(prop, inp, expected):
    if "z" in inp and isinstance(expected, list):
        return UNARY_COMPLEX_RESULT_TEMPLATE.substitute(
            prop=f"complex_{prop}",
            z=struct_literal(inp["z"]),
            expected=struct_literal(expected),
        )
    elif isinstance(expected, list):
        type1 = get_type(inp["z1"])
        type2 = get_type(inp["z2"])
        if type1 == "complex_t" and type2 == "complex_t":
            prop = f"complex_{prop}"
        elif type1 == "complex_t":
            prop = f"complex_real_{prop}"
        else:
            prop = f"real_complex_{prop}"
        return BINARY_COMPLEX_RESULT_TEMPLATE.substitute(
            prop=prop,
            z1=struct_literal(inp["z1"]),
            type1=type1,
            z2=struct_literal(inp["z2"]),
            type2=type2,
            expected=struct_literal(expected),
        )
    else:
        return UNARY_FLOAT_RESULT_TEMPLATE.substitute(
            prop=f"complex_{prop}", z=struct_literal(inp["z"]), expected=expected
        )
