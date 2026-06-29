FUNC_PROTO = """\
#include "vendor/unity.h"

extern int square_root(int radicand);
"""


def extra_cases():
    return [
        {
            "description": "max perfect square in range",
            "property": "squareRoot",
            "input": {
                "radicand": 2147395600,
            },
            "expected": 46340,
        },
    ]


def gen_func_body(prop, inp, expected):
    return f"TEST_ASSERT_EQUAL_INT({expected}, {prop}({inp['radicand']}));"
