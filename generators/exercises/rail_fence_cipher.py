FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 64

extern void encode(char message[], size_t rails);
extern void decode(char message[], size_t rails);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    msg = inp["msg"]
    rails = inp["rails"]
    str_list.append(f'char message[BUFFER_SIZE] = "{msg}";')
    str_list.append(f"{prop}(message, {rails});")
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", message);')
    return "\n".join(str_list)
