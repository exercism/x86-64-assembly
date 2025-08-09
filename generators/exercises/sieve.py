FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 200
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern uint32_t primes(uint32_t *buffer, uint32_t limit);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    limit = inp["limit"]
    str_list.append("uint32_t buffer[BUFFER_SIZE];\n\n")
    if limit < 2:
        str_list.append(f"TEST_ASSERT_EQUAL_UINT32(0, {prop}(buffer, {limit}));\n")
    else:
        expected = str(expected).replace("[", "{").replace("]", "}")
        str_list.append(f"uint32_t expected[] = {expected};\n\n")
        str_list.append(
            f"TEST_ASSERT_EQUAL_UINT32(ARRAY_SIZE(expected), {prop}(buffer, {limit}));\n"
        )
        str_list.append(
            "TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));\n"
        )
    return "".join(str_list)
