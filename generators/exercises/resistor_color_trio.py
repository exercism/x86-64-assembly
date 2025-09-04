FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 20

extern void label(char *buffer, const char **colors);
"""

# Test cases from the Julia track.


def extra_cases():
    return [
        {
            "description": "Orange and orange and red",
            "property": "label",
            "input": {"colors": ["orange", "orange", "red"]},
            "expected": {"value": "3.3", "unit": "kiloohms"},
        },
        {
            "description": "Orange and orange and green",
            "property": "label",
            "input": {"colors": ["orange", "orange", "green"]},
            "expected": {"value": "3.3", "unit": "megaohms"},
        },
        {
            "description": "White and white and violet",
            "property": "label",
            "input": {"colors": ["white", "white", "violet"]},
            "expected": {"value": "990", "unit": "megaohms"},
        },
        {
            "description": "White and white and grey",
            "property": "label",
            "input": {"colors": ["white", "white", "grey"]},
            "expected": {"value": "9.9", "unit": "gigaohms"},
        },
    ]


def gen_func_body(prop, inp, expected):
    colors = inp["colors"]
    expected_value = expected["value"]
    expected_unit = expected["unit"]

    str_list = []
    str_list.append("char buffer[BUFFER_SIZE];\n")
    str_list.append("const char *colors[] = {")
    for color in colors:
        str_list.append(f'  "{color}",')
    str_list.append("  NULL")
    str_list.append("};")
    str_list.append(f"{prop}(buffer, colors);")
    str_list.append(
        f'TEST_ASSERT_EQUAL_STRING("{expected_value} {expected_unit}", buffer);\n'
    )
    return "\n".join(str_list)
