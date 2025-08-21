FUNC_PROTO = """\

#include "vendor/unity.h"

#include "stdint.h"
#include "stddef.h"

#define BUFFER_SIZE 100
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define NEGATIVE_TARGET -1
#define UNREACHABLE_TARGET -2

extern int64_t find_fewest_coins(uint64_t *buffer, const uint64_t *coins, int64_t target, size_t coins_size);
"""


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    str_list = []
    coins = array_literal(inp["coins"])
    target = inp["target"]
    str_list.append("uint64_t buffer[BUFFER_SIZE];\n")
    str_list.append(f"const uint64_t coins[] = {coins};\n")
    if target < 0:
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT64(NEGATIVE_TARGET, {prop}(buffer, coins, {target}, ARRAY_SIZE(coins)));\n"
        )
    elif "error" in expected:
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT64(UNREACHABLE_TARGET, {prop}(buffer, coins, {target}, ARRAY_SIZE(coins)));\n"
        )
    elif len(expected) == 0:
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT64(0, {prop}(buffer, coins, {target},ARRAY_SIZE(coins)));\n"
        )
    else:
        str_list.append(f"const uint64_t expected[] = {array_literal(expected)};\n")
        str_list.append(
            f"TEST_ASSERT_EQUAL_INT64(ARRAY_SIZE(expected), {prop}(buffer, coins, {target}, ARRAY_SIZE(coins)));\n"
        )
        str_list.append(
            "TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));\n"
        )
    return "".join(str_list)
