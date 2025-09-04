FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define MAX_ARRAY_SIZE 20
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define INCOMPLETE_SEQUENCE -1

extern int64_t encode(uint8_t *buffer, const uint32_t *integers, size_t integer_count);
extern int64_t decode(uint32_t *buffer, const uint8_t *integers, size_t integer_count);
"""


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    integers = inp["integers"]
    if prop == "encode":
        input_element_type = "uint32_t"
        output_element_type = "uint8_t"
    else:
        input_element_type = "uint8_t"
        output_element_type = "uint32_t"

    str_list = []
    str_list.append(
        f"const {input_element_type} integers[] = {array_literal(integers)};\n"
    )
    str_list.append(f"{output_element_type} actual[MAX_ARRAY_SIZE];\n")

    if isinstance(expected, dict) and "error" in expected:
        str_list.append(
            f"TEST_ASSERT_EQUAL(INCOMPLETE_SEQUENCE, {prop}(actual, integers, ARRAY_SIZE(integers)));\n"
        )
    else:
        str_list.append(
            f"const {output_element_type} expected[] = {array_literal(expected)};\n"
        )
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), {prop}(actual, integers, ARRAY_SIZE(integers)));"
        )
        output_array_type = output_element_type.replace("_t", "_array").upper()
        str_list.append(
            f"TEST_ASSERT_EQUAL_{output_array_type}(expected, actual, ARRAY_SIZE(expected));\n"
        )
    return "".join(str_list)
