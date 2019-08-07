FUNC_PROTO = """\
#include <stdbool.h>

#include "vendor/unity.h"

extern bool is_paired(const char *str);
"""

def gen_func_body(prop, inp, expected):
    str_list = []
    value = inp["value"].replace("\\", "\\\\")
    str_list.append(f'const char *str = "{value}";\n\n')
    if expected:
        str_list.append(f"TEST_ASSERT_TRUE({prop}(str));\n")
    else:
        str_list.append(f"TEST_ASSERT_FALSE({prop}(str));\n")
    return "".join(str_list)
