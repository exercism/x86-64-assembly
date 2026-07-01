FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>

#define BUFFER_SIZE 256

extern void encode(char buffer[], const char phrase[]);
extern void decode(char buffer[], const char phrase[]);
"""


def extra_cases():
    return [
        {
            "description": "encode boundary characters",
            "property": "encode",
            "input": {"phrase": "/09:@AMNZ[`amnz{"},
            "expected": "09znm aznma",
        }
    ]


def gen_func_body(prop, inp, expected):
    str_list = []
    phrase = inp["phrase"]
    str_list.append(f'alignas(16) const char phrase[] = "{phrase}";')
    str_list.append("char buffer[BUFFER_SIZE];\n\n")
    str_list.append(f"{prop}(buffer, phrase);\n")
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);\n')
    return "".join(str_list)
