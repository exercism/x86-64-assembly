FUNC_PROTO = """\
#include "vendor/unity.h"

enum planet {
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE
};

extern float age(enum planet planet, int seconds);
"""


def gen_func_body(prop, inp, expected):
    planet = inp["planet"].upper()
    seconds = inp["seconds"]
    return f"TEST_ASSERT_FLOAT_WITHIN(0.01, {expected}, {prop}({planet}, {seconds}));\n"
