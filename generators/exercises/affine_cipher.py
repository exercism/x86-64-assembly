FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 256

extern void encode(char *buffer, const char *phrase, unsigned a, unsigned b);
extern void decode(char *buffer, const char *phrase, unsigned a, unsigned b);
"""


def extra_cases():
    return [
        {
            "description": "encode boundary characters",
            "property": "encode",
            "input": {"phrase": "/09:@AMNZ[`amnz{", "key": {"a": 25, "b": 12}},
            "expected": "09maz nmazn",
        }
    ]


def gen_func_body(prop, inp, expected):
    str_list = []
    if isinstance(expected, dict):
        expected = ""
    phrase = inp["phrase"]
    a = inp["key"]["a"]
    b = inp["key"]["b"]
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f'{prop}(buffer, "{phrase}", {a}, {b});\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
