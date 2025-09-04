FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

#define DEFICIENT 1
#define PERFECT 2
#define ABUNDANT 3
#define INVALID -1

extern int classify(int64_t number);
"""


def extra_cases():
    return [
        {
            "description": "large negative is rejected",
            "property": "classify",
            "input": {"number": -7001002003},
            "expected": {
                "error": "Classification is only possible for positive integers."
            },
        }
    ]


def gen_func_body(prop, inp, expected):
    number = inp["number"]
    if isinstance(expected, dict):
        expected = "INVALID"
    expected = expected.upper()
    return f"TEST_ASSERT_EQUAL_INT({expected}, {prop}({number}));\n"
