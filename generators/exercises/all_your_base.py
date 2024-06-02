FUNC_PROTO = """\
#include "vendor/unity.h"

#define BUFFER_SIZE 100
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define BAD_BASE -1
#define BAD_DIGIT -2

extern int rebase(const int* in_digits, int digits_count, int in_base, int* out_array, int out_base);
"""

def gen_func_body(prop, inp, expected):
    str_list = []
    if (len(inp["digits"]) > 0):
        in_digits = str(inp["digits"]).replace("[", "{").replace("]", "}")
        str_list.append(f"int in_digits[] = {in_digits};\n")
        in_size = "ARRAY_SIZE(in_digits)"
    else:
        str_list.append("const int* in_digits = NULL;\n")
        in_size = "0"
    str_list.append("int out_digits[BUFFER_SIZE];\n")
    if type(expected) is list:
        expected = str(expected).replace("[", "{").replace("]", "}")
        str_list.append(f"int expected[] = {expected};\n\n")
        str_list.append(f"TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), {prop}(in_digits, {in_size}, {inp['inputBase']}, out_digits, {inp['outputBase']}));\n")
        str_list.append(f"TEST_ASSERT_EQUAL_INT_ARRAY(expected, out_digits, ARRAY_SIZE(expected));\n");
    else:
        str_list.append("\n")
        if (expected["error"] == "input base must be >= 2" or expected["error"] == "output base must be >= 2"):
            expected = "BAD_BASE"
        elif (expected["error"] == "all digits must satisfy 0 <= d < input base"):
            expected = "BAD_DIGIT"
        str_list.append(f"TEST_ASSERT_EQUAL_INT({expected}, {prop}(in_digits, {in_size}, {inp['inputBase']}, out_digits, {inp['outputBase']}));\n")

    return "".join(str_list)
