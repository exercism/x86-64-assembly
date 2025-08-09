FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 40

extern void truncate(char *buffer, const char *phrase);
"""


def extra_cases():
    return [
        {
            "description": "ideograms",
            "property": "truncate",
            "input": {"phrase": "二兎を追う者は一兎をも得ず"},
            "expected": "二兎を追う",
        }
    ]


def gen_func_body(prop, inp, expected):
    phrase = inp["phrase"]
    str_list = []
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f'{prop}(buffer, "{phrase}");\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
