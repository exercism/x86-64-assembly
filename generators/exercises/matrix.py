FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define BUFFER_SIZE 10

extern size_t row(int32_t *buffer, const char *input, size_t index);
extern size_t column(int32_t *buffer, const char *input, size_t index);
"""

def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")

def gen_func_body(prop, inp, expected):
    input_string = str(inp["string"]).replace("\n", "\\n")
    index = inp["index"]
    str_list = []
    str_list.append("int32_t buffer[BUFFER_SIZE];\n\n")
    str_list.append(f'const int32_t expected[] = {array_literal(expected)};\n')
    str_list.append(f'const size_t length = {prop}(buffer, "{input_string}", {index});\n')
    str_list.append(f'TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);\n')
    str_list.append(f'TEST_ASSERT_EQUAL_INT32_ARRAY(expected, buffer, ARRAY_SIZE(expected));\n')
    return "".join(str_list)

