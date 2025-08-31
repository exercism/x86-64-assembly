FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

typedef enum {
    SUCCESS = 0,
    SYNTAX_ERROR,
    UNKNOWN_OPERATION
} error_t;

typedef int64_t result_t;

extern error_t answer(result_t *result, const char *question);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    str_list.append("result_t result;\n")
    if type(expected) is dict and "error" in expected:
        error = "_".join(str(expected["error"]).upper().split(" "))
        str_list.append(
            f'TEST_ASSERT_EQUAL({error}, answer(&result, "{inp["question"]}"));\n'
        )
    else:
        str_list.append(
            f'TEST_ASSERT_EQUAL(SUCCESS, answer(&result, "{inp["question"]}"));\n'
        )
        str_list.append(f"TEST_ASSERT_EQUAL({expected}, result);\n")
    return "".join(str_list)
