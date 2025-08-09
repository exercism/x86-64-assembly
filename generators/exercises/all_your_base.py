FUNC_PROTO = """\
#include "stdint.h"
#include "vendor/unity.h"

#define BUFFER_SIZE 100
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define BAD_BASE -1
#define BAD_DIGIT -2

extern int32_t rebase(const int32_t* in_digits, int32_t digits_count, int32_t in_base, int32_t* out_array, int32_t out_base);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    if len(inp["digits"]) > 0:
        in_digits = str(inp["digits"]).replace("[", "{").replace("]", "}")
        str_list.append(f"int32_t in_digits[] = {in_digits};\n")
        in_size = "ARRAY_SIZE(in_digits)"
    else:
        str_list.append("const int32_t* in_digits = NULL;\n")
        in_size = "0"
    str_list.append("int32_t out_digits[BUFFER_SIZE];\n")
    if type(expected) is list:
        expected = str(expected).replace("[", "{").replace("]", "}")
        str_list.append(f"int32_t expected[] = {expected};\n\n")
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), {prop}(in_digits, {in_size}, {inp['inputBase']}, out_digits, {inp['outputBase']}));\n"
        )
        str_list.append(
            "TEST_ASSERT_EQUAL_INT_ARRAY(expected, out_digits, ARRAY_SIZE(expected));\n"
        )
    else:
        str_list.append("\n")
        if (
            expected["error"] == "input base must be >= 2"
            or expected["error"] == "output base must be >= 2"
        ):
            expected = "BAD_BASE"
        elif expected["error"] == "all digits must satisfy 0 <= d < input base":
            expected = "BAD_DIGIT"
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT({expected}, {prop}(in_digits, {in_size}, {inp['inputBase']}, out_digits, {inp['outputBase']}));\n"
        )

    return "".join(str_list)
