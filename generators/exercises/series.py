FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

#define BUFFER_SIZE 20
#define SLICE_SIZE 20
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define EMPTY_SERIES -1
#define ZERO_LENGTH -2
#define NEGATIVE_LENGTH -3
#define EXCESSIVE_LENGTH -4

extern int64_t slices(char buffer[][SLICE_SIZE], const char *series, int64_t slice_length);
"""


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace("'", '"')


def gen_func_body(prop, inp, expected):
    series = inp["series"]
    slice_length = inp["sliceLength"]
    str_list = []
    str_list.append("char buffer[BUFFER_SIZE][SLICE_SIZE];")
    if len(series) == 0:
        str_list.append(
            f'TEST_ASSERT_EQUAL_INT64(EMPTY_SERIES, {prop}(buffer, "{series}", {slice_length}));'
        )
    elif slice_length == 0:
        str_list.append(
            f'TEST_ASSERT_EQUAL_INT64(ZERO_LENGTH, {prop}(buffer, "{series}", {slice_length}));'
        )
    elif slice_length < 0:
        str_list.append(
            f'TEST_ASSERT_EQUAL_INT64(NEGATIVE_LENGTH, {prop}(buffer, "{series}", {slice_length}));'
        )
    elif slice_length > len(series):
        str_list.append(
            f'TEST_ASSERT_EQUAL_INT64(EXCESSIVE_LENGTH, {prop}(buffer, "{series}", {slice_length}));'
        )
    else:
        str_list.append(
            f"const char expected[][SLICE_SIZE] = {array_literal(expected)};"
        )
        str_list.append(
            f'TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), {prop}(buffer, "{series}", {slice_length}));'
        )
        str_list.append("for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) " + "{")
        str_list.append("TEST_ASSERT_EQUAL_STRING(expected[i], buffer[i]);")
        str_list.append("}")
    return "\n".join(str_list)
