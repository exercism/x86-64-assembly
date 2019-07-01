FUNC_PROTO = """\
#include <stdbool.h>

#include "vendor/unity.h"

extern bool is_paired(const char *value);
"""

def gen_func_body(prop, inp, expected):
    str_list = []
    value = inp["value"].replace("\\", "\\\\")
    str_list.append(f'const char *value = "{value}";\n\n')
    if expected:
        str_list.append(f"TEST_ASSERT_TRUE({prop}(value));\n")
    else:
        str_list.append(f"TEST_ASSERT_FALSE({prop}(value));\n")
    return "".join(str_list)
