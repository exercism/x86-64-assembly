FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdbool.h>
#include <stdalign.h>

extern bool is_valid(const char isbn[]);
"""


def gen_func_body(prop, inp, expected):
    result = "true" if expected else "false"
    str_list = []
    str_list.append(f'alignas(16) const char isbn[] = "{inp["isbn"]}";')
    str_list.append(f"TEST_ASSERT_EQUAL({result}, {prop}(isbn));")
    return "\n".join(str_list)
