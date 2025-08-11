FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

#define BUFFER_SIZE 240

extern void say(char *buffer, int64_t number);
"""


def extra_cases():
    return [
        {
            "description": "additional big number",
            "property": "say",
            "input": {"number": 19011016013},
            "expected": "nineteen billion eleven million sixteen thousand thirteen",
        },
        {
            "description": "different big number",
            "property": "say",
            "input": {"number": 812000070017},
            "expected": "eight hundred twelve billion seventy thousand seventeen",
        },
        {
            "description": "alternative big number",
            "property": "say",
            "input": {"number": 60010015018},
            "expected": "sixty billion ten million fifteen thousand eighteen",
        },
    ]


def gen_func_body(prop, inp, expected):
    number = inp["number"]
    if isinstance(expected, dict):
        expected = ""
    str_list = []
    str_list.append("char buffer[BUFFER_SIZE];\n")
    str_list.append(f"{prop}(buffer, {number});\n")
    if len(expected) <= 120:
        str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    else:
        str_list.append("TEST_ASSERT_EQUAL_STRING(\n")
        str_list.append(f'    "{expected}",\n')
        str_list.append("    buffer);\n")
    return "".join(str_list)
