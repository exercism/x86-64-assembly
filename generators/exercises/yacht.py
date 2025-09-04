FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

typedef enum {
    CHOICE = 0,
    ONES,
    TWOS,
    THREES,
    FOURS,
    FIVES,
    SIXES,
    LITTLE_STRAIGHT,
    BIG_STRAIGHT,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    YACHT,
} category_t;

extern int score(category_t category, const uint16_t *dice);
"""


def array_literal(digits):
    return "{" + ", ".join(str(d) for d in digits) + "}"


def gen_func_body(prop, inp, expected):
    category = inp["category"].upper().replace(" ", "_")
    dice = array_literal(inp["dice"])
    str_list = []
    str_list.append(f"const uint16_t dice[] = {dice};\n")
    str_list.append(f"TEST_ASSERT_EQUAL_INT({expected}, {prop}({category}, dice));\n")
    return "".join(str_list)
