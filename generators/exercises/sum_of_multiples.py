FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern uint64_t sum(uint64_t limit, const uint64_t *factors, size_t factor_count);
"""


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    factors = inp["factors"]
    limit = inp["limit"]
    str_list = []
    if len(factors) > 0:
        str_list.append(f"const uint64_t factors[] = {array_literal(factors)};\n")
        str_list.append(
            f"TEST_ASSERT_EQUAL_UINT64({expected}, {prop}({limit}, factors, ARRAY_SIZE(factors)));\n"
        )
    else:
        str_list.append(
            f"TEST_ASSERT_EQUAL_UINT64({expected}, {prop}({limit}, NULL, 0));\n"
        )
    return "".join(str_list)