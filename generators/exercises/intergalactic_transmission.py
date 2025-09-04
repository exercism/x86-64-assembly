FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

#define BUFFER_SIZE 100
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define WRONG_PARITY -1

extern int transmit_sequence(uint8_t *buffer, const uint8_t *message, int message_length);
extern int decode_message(uint8_t *buffer, const uint8_t *message, int message_length);
"""


def describe(case):
    description = case["description"]
    property = case["property"]
    return f"{property} {description}"


def array_literal(digits):
    return ", ".join(digits).replace("'", "")


def gen_func_body(prop, inp, expected):
    message = inp["message"]

    str_list = []
    if len(message) == 0:
        message = "NULL"
        message_length = 0
    else:
        str_list.append("const uint8_t message[] = {\n")
        str_list.append(f"    {array_literal(message)}\n")
        str_list.append("};\n")

        message = "message"
        message_length = "ARRAY_SIZE(message)"

    str_list.append("uint8_t buffer[BUFFER_SIZE];\n")
    call = f"{prop}(buffer, {message}, {message_length})"

    if isinstance(expected, dict):
        str_list.append(f"TEST_ASSERT_EQUAL_INT(WRONG_PARITY, {call});\n")
    elif expected == []:
        str_list.append(f"TEST_ASSERT_EQUAL_INT(0, {call});\n")
    else:
        str_list.append("const uint8_t expected[] = {\n")
        str_list.append(f"    {array_literal(expected)}\n")
        str_list.append("};\n")

        str_list.append(f"TEST_ASSERT_EQUAL_INT(ARRAY_SIZE(expected), {call});\n")
        str_list.append(
            "TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, buffer, ARRAY_SIZE(expected));\n"
        )
    return "".join(str_list)
