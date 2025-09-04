FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct {
    uint16_t first;
    uint16_t second;
} domino_t;

extern int can_chain(size_t domino_count, const domino_t *dominoes);
"""


def array_literal(dominoes):
    return str(dominoes).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    dominoes = inp["dominoes"]
    if expected:
        macro = "TEST_ASSERT_TRUE"
    else:
        macro = "TEST_ASSERT_FALSE"

    str_list = []
    if len(dominoes) > 0:
        str_list.append(f"const domino_t dominoes[] = {array_literal(dominoes)};\n")
        str_list.append(f"{macro}({prop}(ARRAY_SIZE(dominoes), dominoes));\n")
    else:
        str_list.append(f"{macro}({prop}(0, NULL));\n")
    return "".join(str_list)
