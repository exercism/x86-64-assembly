from string import Template
import math

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define ASSERT_FLOAT(x, y)                              \
    do {                                                \
        float _dt = 0.0001f * ((x) < 0 ? -(x) : (x));   \
        float _tl = _dt > 0.00001f ? _dt : 0.00001f;    \
        TEST_ASSERT_FLOAT_WITHIN(_tl, (x), (y));        \
    } while (0)

#define ASSERT_COMPLEX(xr, xi, yr, yi)                  \
    do {                                                \
        float _abxr = (xr) < 0 ? -(xr) : (xr);          \
        float _abxi = (xi) < 0 ? -(xi) : (xi);          \
        float _dist = _abxr > _abxi ? _abxr : _abxi;    \
        float _dt  = 0.0001f * _dist;                   \
        float _tl  = _dt > 0.00001f ? _dt : 0.00001f;   \
        TEST_ASSERT_FLOAT_WITHIN(_tl, (xr), (yr));      \
        TEST_ASSERT_FLOAT_WITHIN(_tl, (xi), (yi));      \
    } while (0)

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

ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
""")

UNARY_COMPLEX_RESULT_TEMPLATE = Template("""
const complex_t z = ${z};
const complex_t result = ${prop}(z);
const complex_t expected = ${expected};

ASSERT_COMPLEX(expected.real, expected.imag, result.real, result.imag);
""")

UNARY_FLOAT_RESULT_TEMPLATE = Template("""
const complex_t z = ${z};
const float result = ${prop}(z);
const float expected = ${expected};

ASSERT_FLOAT(expected, result);
""")


def extra_cases():
    return [
        {
            "description": "exponential with a large real part: magnitude e^5, both components sizable",
            "property": "exp",
            "input": {"z": [5, 1]},
            "expected": [80.187972, 124.885367],
        },
        {
            "description": "exponential with a large real part: magnitude e^7, second-quadrant angle",
            "property": "exp",
            "input": {"z": [7, 2]},
            "expected": [-456.360420, 997.165709],
        },
        {
            "description": "exponential with a large real part: magnitude e^6, negative angle",
            "property": "exp",
            "input": {"z": [6, -2]},
            "expected": [-167.885616, -366.836764],
        },
        {
            "description": "exponential with a large real part: magnitude e^4, fourth-quadrant angle",
            "property": "exp",
            "input": {"z": [4, -2.5]},
            "expected": [-43.740959, -32.675472],
        },
        {
            "description": "regression: residual angle near pi/2 (failed before sin/cos fix)",
            "property": "exp",
            "input": {"z": [-0.3, 1.5]},
            "expected": [0.052403, 0.738962],
        },
        {
            "description": "regression: residual angle near pi/2, second case",
            "property": "exp",
            "input": {"z": [-0.2, 1.5]},
            "expected": [0.057915, 0.816680],
        },
        {
            "description": "regression: third-quadrant angle, near-zero second component",
            "property": "exp",
            "input": {"z": [-0.1, -3.25]},
            "expected": [-0.899526, 0.097899],
        },
        {
            "description": "regression: residual angle near pi/2, third case",
            "property": "exp",
            "input": {"z": [-0.1, 1.5]},
            "expected": [0.064006, 0.902571],
        },
    ]


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
