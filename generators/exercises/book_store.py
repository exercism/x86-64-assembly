FUNC_PROTO = """\
#include "stdint.h"
#include "vendor/unity.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern int64_t total(int64_t count, const int16_t *basket);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    if len(inp["basket"]) > 0:
        basket = str(inp["basket"]).replace("[", "{").replace("]", "}")
        str_list.append(f"int16_t basket[] = {basket};\n")
        count = "ARRAY_SIZE(basket)"
    else:
        str_list.append("const int16_t* basket = NULL;\n")
        count = "0"

    str_list.append(f"TEST_ASSERT_EQUAL_INT({expected}, {prop}({count}, basket));\n")
    return "".join(str_list)
