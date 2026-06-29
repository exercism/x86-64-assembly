FUNC_PROTO = """\
#include "vendor/unity.h"

// Returns 1 if queen can be created, otherwise 0.
extern int can_create(int row, int column);

// Returns 1 if queens attack, otherwise 0.
extern int can_attack(int white_row, int white_column, int black_row, int black_column);
"""


def gen_func_body(prop, inp, expected):
    if prop == "create":
        pos = inp["queen"]["position"]
        assertion = (
            "TEST_ASSERT_FALSE" if isinstance(expected, dict) else "TEST_ASSERT_TRUE"
        )
        return f"{assertion}(can_create({pos['row']}, {pos['column']}));"
    white = inp["white_queen"]["position"]
    black = inp["black_queen"]["position"]
    assertion = "TEST_ASSERT_TRUE" if expected else "TEST_ASSERT_FALSE"
    return f"{assertion}(can_attack({white['row']}, {white['column']}, {black['row']}, {black['column']}));"
