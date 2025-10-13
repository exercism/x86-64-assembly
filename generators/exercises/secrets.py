FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

extern uint8_t extract_higher_bits(uint16_t code);
extern uint8_t extract_lower_bits(uint16_t code);
extern uint8_t extract_redundant_bits(uint16_t code);
extern uint8_t set_message_bits(uint16_t code);
extern uint16_t rotate_private_key(uint16_t code);
extern uint8_t format_private_key(uint16_t code);
extern uint16_t decrypt_message(uint16_t code);
"""


def extra_cases():
    return [
        {
            "description": "higher_bits_0b1010_0100_1100_0101",
            "property": "extract_higher_bits",
            "input": 0b1010_0100_1100_0101,
            "expected": 0b1010_0100,
        },
        {
            "description": "higher_bits_0b0001_1100_0001_1100",
            "property": "extract_higher_bits",
            "input": 0b0001_1100_0001_1100,
            "expected": 0b0001_1100,
        },
        {
            "description": "higher_bits_0b0000_0000_1111_1111",
            "property": "extract_higher_bits",
            "input": 0b0000_0000_1111_1111,
            "expected": 0b0000_0000,
        },
        {
            "description": "higher_bits_0b1111_1111_0000_0000",
            "property": "extract_higher_bits",
            "input": 0b1111_1111_0000_0000,
            "expected": 0b1111_1111,
        },
        {
            "description": "lower_bits_0b1010_0100_1100_0101",
            "property": "extract_lower_bits",
            "input": 0b1010_0100_1100_0101,
            "expected": 0b1100_0101,
        },
        {
            "description": "lower_bits_0b0001_1100_0001_1100",
            "property": "extract_lower_bits",
            "input": 0b0001_1100_0001_1100,
            "expected": 0b0001_1100,
        },
        {
            "description": "lower_bits_0b0000_0000_1111_1111",
            "property": "extract_lower_bits",
            "input": 0b0000_0000_1111_1111,
            "expected": 0b1111_1111,
        },
        {
            "description": "lower_bits_0b1111_1111_0000_0000",
            "property": "extract_lower_bits",
            "input": 0b1111_1111_0000_0000,
            "expected": 0b0000_0000,
        },
        {
            "description": "redundant_bits_0b1010_0100_1100_0101",
            "property": "extract_redundant_bits",
            "input": 0b1010_0100_1100_0101,
            "expected": 0b1000_0100,
        },
        {
            "description": "redundant_bits_0b0001_1100_0001_1100",
            "property": "extract_redundant_bits",
            "input": 0b0001_1100_0001_1100,
            "expected": 0b0001_1100,
        },
        {
            "description": "redundant_bits_0b0000_0000_1111_1111",
            "property": "extract_redundant_bits",
            "input": 0b0000_0000_1111_1111,
            "expected": 0b0000_0000,
        },
        {
            "description": "redundant_bits_0b1111_1111_0000_0000",
            "property": "extract_redundant_bits",
            "input": 0b1111_1111_0000_0000,
            "expected": 0b0000_0000,
        },
        {
            "description": "set_message_bits_0b1010_0100_1100_0101",
            "property": "set_message_bits",
            "input": 0b1010_0100_1100_0101,
            "expected": 0b1110_0101,
        },
        {
            "description": "set_message_bits_0b0001_1100_0001_1100",
            "property": "set_message_bits",
            "input": 0b0001_1100_0001_1100,
            "expected": 0b0001_1100,
        },
        {
            "description": "set_message_bits_0b0000_0000_1111_1111",
            "property": "set_message_bits",
            "input": 0b0000_0000_1111_1111,
            "expected": 0b1111_1111,
        },
        {
            "description": "set_message_bits_0b1111_1111_0000_0000",
            "property": "set_message_bits",
            "input": 0b1111_1111_0000_0000,
            "expected": 0b1111_1111,
        },
        {
            "description": "rotate_private_key_0b1010_0100_1100_0101",
            "property": "rotate_private_key",
            "input": 0b1010_0100_1100_0101,
            "expected": 0b1100_1100_1111_0010,
        },
        {
            "description": "rotate_private_key_0b0001_1100_0001_1100",
            "property": "rotate_private_key",
            "input": 0b0001_1100_0001_1100,
            "expected": 0b1001_1001_1110_0101,
        },
        {
            "description": "rotate_private_key_0b0000_0000_1111_1111",
            "property": "rotate_private_key",
            "input": 0b0000_0000_1111_1111,
            "expected": 0b1011_0011_0011_1100,
        },
        {
            "description": "rotate_private_key_0b1111_1111_0000_0000",
            "property": "rotate_private_key",
            "input": 0b1111_1111_0000_0000,
            "expected": 0b1011_0011_0011_1100,
        },
        {
            "description": "format_private_key_0b1010_0100_1100_0101",
            "property": "format_private_key",
            "input": 0b1010_0100_1100_0101,
            "expected": 0b1100_0001,
        },
        {
            "description": "format_private_key_0b0001_1100_0001_1100",
            "property": "format_private_key",
            "input": 0b0001_1100_0001_1100,
            "expected": 0b1000_0011,
        },
        {
            "description": "format_private_key_0b0000_0000_1111_1111",
            "property": "format_private_key",
            "input": 0b0000_0000_1111_1111,
            "expected": 0b0111_0000,
        },
        {
            "description": "format_private_key_0b1111_1111_0000_0000",
            "property": "format_private_key",
            "input": 0b1111_1111_0000_0000,
            "expected": 0b0111_0000,
        },
        {
            "description": "decrypt_message_0b1010_0100_1100_0101",
            "property": "decrypt_message",
            "input": 0b1010_0100_1100_0101,
            "expected": 0b1100_0001_1110_0101,
        },
        {
            "description": "decrypt_message_0b0001_1100_0001_1100",
            "property": "decrypt_message",
            "input": 0b0001_1100_0001_1100,
            "expected": 0b1000_0011_0001_1100,
        },
        {
            "description": "decrypt_message_0b0000_0000_1111_1111",
            "property": "decrypt_message",
            "input": 0b0000_0000_1111_1111,
            "expected": 0b0111_0000_1111_1111,
        },
        {
            "description": "decrypt_message_0b1111_1111_0000_0000",
            "property": "decrypt_message",
            "input": 0b1111_1111_0000_0000,
            "expected": 0b0111_0000_1111_1111,
        },
    ]


def array_literal(cards):
    return str(cards).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    if prop == "rotate_private_key" or prop == "decrypt_message":
        return f"TEST_ASSERT_EQUAL_UINT16({expected}, {prop}({inp}));\n"
    return f"TEST_ASSERT_EQUAL_UINT8({expected}, {prop}({inp}));\n"
