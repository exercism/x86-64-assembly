FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

typedef struct {
    int64_t numerator;
    int64_t denominator;
} rational_t;

extern rational_t add(rational_t r1, rational_t r2);
extern rational_t sub(rational_t r1, rational_t r2);
extern rational_t mul(rational_t r1, rational_t r2);
extern rational_t div(rational_t r1, rational_t r2);
extern rational_t rational_absolute(rational_t r);
extern rational_t exprational(rational_t r, int64_t n);
extern float expreal(int64_t x, rational_t r);
extern rational_t reduce(rational_t r);
"""

def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")

def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "expreal":
        str_list.append(f"rational_t r = {array_literal(inp["r"])};\n")
        str_list.append(f'const float delta = 0.000001;\n')
        str_list.append(f"const float result = {prop}({inp["x"]}, r);\n")
        str_list.append(f"const float expected = {expected};\n")
        str_list.append(f"TEST_ASSERT_FLOAT_WITHIN(delta, expected, result);\n")
    elif prop == "exprational":
        str_list.append(f"rational_t r = {array_literal(inp["r"])};\n")
        str_list.append(f"const rational_t result = {prop}(r, {inp["n"]});\n")
        str_list.append(f"const rational_t expected = {array_literal(expected)};\n")
        str_list.append(f"TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);\n")
        str_list.append(f"TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);\n")    
    elif prop == "abs" or prop == "reduce":
        if prop == "abs":
            prop = "rational_absolute"
        str_list.append(f"rational_t r = {array_literal(inp["r"])};\n")
        str_list.append(f"const rational_t result = {prop}(r);\n")
        str_list.append(f"const rational_t expected = {array_literal(expected)};\n")
        str_list.append(f"TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);\n")
        str_list.append(f"TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);\n") 
    else:
        str_list.append(f"rational_t r1 = {array_literal(inp["r1"])};\n")
        str_list.append(f"rational_t r2 = {array_literal(inp["r2"])};\n")
        str_list.append(f"const rational_t result = {prop}(r1, r2);\n")
        str_list.append(f"const rational_t expected = {array_literal(expected)};\n")
        str_list.append(f"TEST_ASSERT_EQUAL_INT64(expected.numerator, result.numerator);\n")
        str_list.append(f"TEST_ASSERT_EQUAL_INT64(expected.denominator, result.denominator);\n") 
    return "".join(str_list)