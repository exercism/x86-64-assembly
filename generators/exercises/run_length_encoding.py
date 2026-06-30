FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>

#define BUFFER_SIZE 256

extern void encode(char buffer[], const char string[]);
extern void decode(char buffer[], const char string[]);
"""


def extra_cases():
    return [
        {
            "description": "consistency with punctuation",
            "property": "consistency",
            "input": {"string": "\\t\\t///::::\\xB0@@@[[```{{{{"},
            "expected": "\\t\\t///::::\\xB0@@@[[```{{{{",
        }
    ]


def describe(case):
    return f"{case['property']} {case['description']}"


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "consistency":
        str_list.append("alignas(16) char buffer1[BUFFER_SIZE];")
        str_list.append("alignas(16) char buffer2[BUFFER_SIZE];")
        str_list.append(f'encode(buffer1, "{inp["string"]}");')
        str_list.append("decode(buffer2, buffer1);")
        str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer2);')
        return "\n".join(str_list)
    str_list.append("alignas(16) char buffer[BUFFER_SIZE];")
    str_list.append(f'{prop}(buffer, "{inp["string"]}");')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", buffer);')
    return "\n".join(str_list)
