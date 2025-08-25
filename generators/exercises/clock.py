import re

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdbool.h>

typedef struct {
    uint8_t hour;
    uint8_t minute;
} clock_time_t;

extern clock_time_t create(int64_t hour, int64_t minute);
extern clock_time_t add_minutes(int64_t hour, int64_t minute, int64_t value);
extern clock_time_t subtract_minutes(int64_t hour, int64_t minute, int64_t value);
extern bool equal(clock_time_t clock1, clock_time_t clock2);
"""


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "equal":
        expected = str(expected).lower()
        clock1 = list(inp["clock1"].values())
        clock2 = list(inp["clock2"].values())
        str_list.append(
            f"const clock_time_t clock1 = create({clock1[0]}, {clock1[1]});\n"
        )
        str_list.append(
            f"const clock_time_t clock2 = create({clock2[0]}, {clock2[1]});\n"
        )
        str_list.append(f"TEST_ASSERT_EQUAL({expected}, {prop}(clock1, clock2));\n")
    elif prop == "create":
        hour, minute = expected.split(":")
        str_list.append(
            "const clock_time_t expected = "
            + "{"
            + f"{re.sub(r'0(?=\d)', '', hour)}, {re.sub(r'0(?=\d)', '', minute)}"
            + "};\n"
        )
        str_list.append(
            f"const clock_time_t clock = {prop}({inp['hour']}, {inp['minute']});\n"
        )
        str_list.append("TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);\n")
        str_list.append("TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);\n")
    else:
        hour, minute = expected.split(":")
        str_list.append(
            "const clock_time_t expected = "
            + "{"
            + f"{re.sub(r'0(?=\d)', '', hour)}, {re.sub(r'0(?=\d)', '', minute)}"
            + "};\n"
        )
        str_list.append(
            f"const clock_time_t clock = {prop}_minutes({inp['hour']}, {inp['minute']}, {inp['value']});\n"
        )
        str_list.append("TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);\n")
        str_list.append("TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);\n")
    return "".join(str_list)
