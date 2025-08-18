FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

#define INVALID_NUMBER -1

extern int64_t prime(uint64_t number);
"""


def extra_cases():
    return [
        {
            "description": "seventh prime",
            "property": "prime",
            "input": {"number": 7},
            "expected": 17,
        },
        {
            "description": "very big prime",
            "property": "prime",
            "input": {"number": 65537},
            "expected": 821647,
        },
    ]


def gen_func_body(prop, inp, expected):
    number = inp["number"]
    if isinstance(expected, dict) and "error" in expected:
        return f"TEST_ASSERT_EQUAL_INT64(INVALID_NUMBER, {prop}({number}));\n"
    else:
        return f"TEST_ASSERT_EQUAL_INT64({expected}, {prop}({number}));\n"
