FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdbool.h>
#include <stdalign.h>

extern bool is_valid(const char isbn[]);
"""


def gen_func_body(prop, inp, expected):
    assertion = "TEST_ASSERT_TRUE" if expected else "TEST_ASSERT_FALSE"
    str_list = []
    str_list.append(f'alignas(16) const char isbn[] = "{inp["isbn"]}";')
    str_list.append(f"{assertion}({prop}(isbn));")
    return "\n".join(str_list)
