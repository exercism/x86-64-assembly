FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

#define BUFFER_SIZE 50

extern char front_door_response(const char *line);
extern void front_door_password(char *letters);
extern char back_door_response(const char *line);
extern void back_door_password(char *buffer, char *letters);
"""


def extra_cases():
    return [
        {
            "description": "front_door_response_S1",
            "property": "front_door_response",
            "input": "Sunshine warming my toes,",
            "expected": "S",
        },
        {
            "description": "front_door_response_U1",
            "property": "front_door_response",
            "input": "Underwater fun with my friends.",
            "expected": "U",
        },
        {
            "description": "front_door_response_M1",
            "property": "front_door_response",
            "input": "Making homemade ice cream on the porch,",
            "expected": "M",
        },
        {
            "description": "front_door_response_M2",
            "property": "front_door_response",
            "input": "Many long nights catching fireflies.",
            "expected": "M",
        },
        {
            "description": "front_door_response_E1",
            "property": "front_door_response",
            "input": "Early morning walks to the creek,",
            "expected": "E",
        },
        {
            "description": "front_door_response_R1",
            "property": "front_door_response",
            "input": "Reveling in the freedom of lazy days.",
            "expected": "R",
        },
        {
            "description": "front_door_response_S2",
            "property": "front_door_response",
            "input": "Serene, calming quality",
            "expected": "S",
        },
        {
            "description": "front_door_response_O1",
            "property": "front_door_response",
            "input": "Organized, you always have it together",
            "expected": "O",
        },
        {
            "description": "front_door_response_P1",
            "property": "front_door_response",
            "input": "Picturesque, strikingly beautiful",
            "expected": "P",
        },
        {
            "description": "front_door_response_H1",
            "property": "front_door_response",
            "input": "Honest, so genuine",
            "expected": "H",
        },
        {
            "description": "front_door_response_I1",
            "property": "front_door_response",
            "input": "Imaginative, a creative mind",
            "expected": "I",
        },
        {
            "description": "front_door_response_A1",
            "property": "front_door_response",
            "input": "Alluring, so attractive",
            "expected": "A",
        },
        {
            "description": "front_door_response_C1",
            "property": "front_door_response",
            "input": "Compilers intensily bestow",
            "expected": "C",
        },
        {
            "description": "front_door_response_O2",
            "property": "front_door_response",
            "input": "On commencing without ego",
            "expected": "O",
        },
        {
            "description": "front_door_response_D1",
            "property": "front_door_response",
            "input": "Different processes ajar",
            "expected": "D",
        },
        {
            "description": "front_door_response_E2",
            "property": "front_door_response",
            "input": "Exit with zero quick",
            "expected": "E",
        },
        {
            "description": "front_door_password_SUMMER",
            "property": "front_door_password",
            "input": "SUMMER",
            "expected": "Summer",
        },
        {
            "description": "front_door_password_sophia",
            "property": "front_door_password",
            "input": "sophia",
            "expected": "Sophia",
        },
        {
            "description": "front_door_password_Code",
            "property": "front_door_password",
            "input": "Code",
            "expected": "Code",
        },
        {
            "description": "back_door_response_w1",
            "property": "back_door_response",
            "input": "Compilers intensily bestow",
            "expected": "w",
        },
        {
            "description": "back_door_response_o1",
            "property": "back_door_response",
            "input": "On commencing without ego",
            "expected": "o",
        },
        {
            "description": "back_door_response_r1",
            "property": "back_door_response",
            "input": "Different processes ajar",
            "expected": "r",
        },
        {
            "description": "back_door_response_k1",
            "property": "back_door_response",
            "input": "Exit with zero quick",
            "expected": "k",
        },
        {
            "description": "back_door_response_H1",
            "property": "back_door_response",
            "input": "Stands so HIGH   ",
            "expected": "H",
        },
        {
            "description": "back_door_response_o2",
            "property": "back_door_response",
            "input": "\tHuge ... hooves ... too!",
            "expected": "o",
        },
        {
            "description": "back_door_response_r2",
            "property": "back_door_response",
            "input": "Impatiently waits for... \t \t",
            "expected": "r",
        },
        {
            "description": "back_door_response_s1",
            "property": "back_door_response",
            "input": "    Reins and harness    ",
            "expected": "s",
        },
        {
            "description": "back_door_response_E1",
            "property": "back_door_response",
            "input": "Eager to LEAVE!!!",
            "expected": "E",
        },
        {
            "description": "back_door_password_work",
            "property": "back_door_password",
            "input": "work",
            "expected": "Work, please.",
        },
        {
            "description": "back_door_password_horse",
            "property": "back_door_password",
            "input": "horse",
            "expected": "Horse, please.",
        },
    ]


def string_literal(string):
    return string.replace("'", "")


def char_literal(char):
    return char.replace()


def unroll_args(args):
    if isinstance(args, (int, float)):
        return str(args)
    if isinstance(args, dict):
        return str([*args.values()]).replace("[", "").replace("]", "")
    return str(args).replace("[", "").replace("]", "")


def gen_func_body(prop, inp, expected):
    if prop == "front_door_response" or prop == "back_door_response":
        message = f"Passed line: {inp}"
        return (
            "TEST_ASSERT_EQUAL_INT8_MESSAGE("
            + f"'{expected}'"
            + f', {prop}("{inp}"), "{message}");\n'
        )
    str_list = []
    if prop == "front_door_password":
        message = f"Combined letters are: {string_literal(inp)}"
        str_list.append(f'char letters[] = "{string_literal(inp)}";')
        str_list.append(f"{prop}(letters);")
        str_list.append(
            f'TEST_ASSERT_EQUAL_STRING_MESSAGE("{expected}", letters, "{message}");'
        )
    else:
        str_list.append("char buffer[BUFFER_SIZE];")
        message = f"Combined letters are: {string_literal(inp)}"
        str_list.append(f'char letters[] = "{string_literal(inp)}";')
        str_list.append(f"{prop}(buffer, letters);")
        str_list.append(
            f'TEST_ASSERT_EQUAL_STRING_MESSAGE("{expected}", buffer, "{message}");'
        )
    return "\n".join(str_list)
