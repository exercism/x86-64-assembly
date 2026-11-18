FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 40

extern void label(char *buffer, const char **colors);
"""

# Test cases adapted from the Julia track.


def extra_cases():
    return [
        {
            "description": "Orange, orange, red and gold",
            "property": "label",
            "input": {"colors": ["orange", "orange", "red", "gold"]},
            "expected": {"value": 3.3, "unit": "kiloohms", "tolerance": "±5%"},
        },
        {
            "description": "Orange, orange, green and silver",
            "property": "label",
            "input": {"colors": ["orange", "orange", "green", "silver"]},
            "expected": {"value": 3.3, "unit": "megaohms", "tolerance": "±10%"},
        },
        {
            "description": "White, white, violet and green",
            "property": "label",
            "input": {"colors": ["white", "white", "violet", "green"]},
            "expected": {"value": 990, "unit": "megaohms", "tolerance": "±0.5%"},
        },
        {
            "description": "White, white, grey and blue",
            "property": "label",
            "input": {"colors": ["white", "white", "grey", "blue"]},
            "expected": {"value": 9.9, "unit": "gigaohms", "tolerance": "±0.25%"},
        },
    ]


def gen_func_body(prop, inp, expected):
    colors = inp["colors"]
    expected_label = f"{expected['value']} {expected['unit']}"
    if "tolerance" in expected:
        expected_label += f" {expected['tolerance']}"

    str_list = []
    str_list.append("char buffer[BUFFER_SIZE];\n")
    str_list.append("const char *colors[] = {")
    for color in colors:
        str_list.append(f'  "{color}",')
    str_list.append("  NULL")
    str_list.append("};")
    str_list.append("label(buffer, colors);")
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected_label}", buffer);\n')
    return "\n".join(str_list)
