from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

typedef enum {
    C2 = 2,
    C3,
    C4,
    C5,
    C6,
    C7,
    C8,
    C9,
    C10,
    CJ,
    CQ,
    CK,
    CA
} card_t;

typedef enum {
    finished = 0,
    loop
} status_t;

typedef struct {
    status_t status;
    uint32_t cards;
    uint32_t tricks;
} result_t;

#define BUFFER_SIZE 300
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern result_t simulate_game(const card_t *playerA, size_t playerA_count, const card_t *playerB, size_t playerB_count);
"""

FUNC_GEN_TEMPLATE = Template("""
const card_t playerA[] = ${playerA};
const card_t playerB[] = ${playerB};

const result_t actual = ${prop}(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
const result_t expected = ${expected};

TEST_ASSERT_EQUAL(expected.status, actual.status);
TEST_ASSERT_EQUAL(expected.cards, actual.cards);
TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
""")


def str_array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace("'", "")


def gen_func_body(prop, inp, expected):
    exp_string = str_array_literal([v for v in expected.values()])
    playerA = str_array_literal([f"C{c}" for c in inp["playerA"]])
    playerB = str_array_literal([f"C{c}" for c in inp["playerB"]])
    return FUNC_GEN_TEMPLATE.substitute(
        playerA=playerA, playerB=playerB, prop=prop, expected=exp_string
    )
