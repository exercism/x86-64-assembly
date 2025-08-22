FUNC_PROTO = """\
#include "vendor/unity.h"

#include "stdint.h"
#include "stddef.h"

#define BUFFER_SIZE 20
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern int32_t latest(size_t scores_count, const int32_t *scores);
extern int32_t personal_best(size_t scores_count, const int32_t *scores);
extern size_t personal_top_three(int32_t *buffer, const int32_t *scores, size_t scores_count);
"""


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    if prop == "scores":
        return ""
    if prop == "latest_after_top_three":
        return ""
    if prop == "scores_after_top_three":
        return ""
    if prop == "latest_after_best":
        return ""
    if prop == "scores_after_best":
        return ""
    str_list = []
    if prop == "personal_top_three":
        str_list.append("int32_t buffer[BUFFER_SIZE];\n")
        str_list.append(f"const int32_t scores[] = {array_literal(inp['scores'])};\n")
        str_list.append(f"const int32_t expected[] = {array_literal(expected)};\n")
        str_list.append(
            f"TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), {prop}(buffer, scores, ARRAY_SIZE(scores)));\n"
        )
        str_list.append(
            "TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));\n"
        )
    else:
        str_list.append(f"const int32_t scores[] = {array_literal(inp['scores'])};\n")
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT32({expected}, {prop}(ARRAY_SIZE(scores), scores));\n"
        )
    return "".join(str_list)
