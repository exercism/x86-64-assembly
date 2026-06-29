FUNC_PROTO = """\
#include "vendor/unity.h"

extern int egg_count(int number);
"""


def extra_cases():
    return [
        {
            "description": "negative number",
            "property": "eggCount",
            "input": {
                "number": -1,
            },
            "expected": 32,
        },
    ]


def gen_func_body(prop, inp, expected):
    return f"TEST_ASSERT_EQUAL_INT({expected}, {prop}({inp['number']}));"
