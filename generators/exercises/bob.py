FUNC_PROTO = """\
#include "vendor/unity.h"

extern const char *response(const char *hey_bob);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    value = inp["heyBob"]
    value = value.replace("\n", "\\n").replace("\r", "\\r").replace("\t", "\\t")
    str_list.append(f'char str[] = "{value}";\n')
    str_list.append(f'TEST_ASSERT_EQUAL_STRING("{expected}", {prop}(str));\n')
    return "".join(str_list)
