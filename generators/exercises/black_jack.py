FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t card_t;

typedef struct {
    uint64_t fst;
    uint64_t snd;
} card_pair_t;

static const card_t C2 = 2;
static const card_t C3 = 3;
static const card_t C4 = 4;
static const card_t C5 = 5;
static const card_t C6 = 6;
static const card_t C7 = 7;
static const card_t C8 = 8;
static const card_t C9 = 9;
static const card_t C10 = 10;
static const card_t CJ = 11;
static const card_t CQ = 12;
static const card_t CK = 13;
static const card_t CA = 14;

extern uint64_t value_of_card(card_t card);
extern card_pair_t higher_card(card_t card_one, card_t card_two);
extern uint64_t value_of_ace(card_t card_one, card_t card_two);
extern bool is_blackjack(card_t card_one, card_t card_two);
extern bool can_split_pairs(card_t card_one, card_t card_two);
extern bool can_double_down(card_t card_one, card_t card_two);
"""


def extra_cases():
    return [
        {
            "description": "value_of_card_2",
            "property": "value_of_card",
            "input": "C2",
            "expected": 2,
        },
        {
            "description": "value_of_card_5",
            "property": "value_of_card",
            "input": "C5",
            "expected": 5,
        },
        {
            "description": "value_of_card_A",
            "property": "value_of_card",
            "input": "CA",
            "expected": 1,
        },
        {
            "description": "value_of_card_J",
            "property": "value_of_card",
            "input": "CJ",
            "expected": 10,
        },
        {
            "description": "value_of_card_8",
            "property": "value_of_card",
            "input": "C8",
            "expected": 8,
        },
        {
            "description": "value_of_card_K",
            "property": "value_of_card",
            "input": "CK",
            "expected": 10,
        },
        {
            "description": "value_of_card_Q",
            "property": "value_of_card",
            "input": "CQ",
            "expected": 10,
        },
        {
            "description": "higher_card_4_8",
            "property": "higher_card",
            "input": ["C4", "C8"],
            "expected": ["C8"],
        },
        {
            "description": "higher_card_A_A",
            "property": "higher_card",
            "input": ["CA", "CA"],
            "expected": ["CA", "CA"],
        },
        {
            "description": "higher_card_6_J",
            "property": "higher_card",
            "input": ["C6", "CJ"],
            "expected": ["CJ"],
        },
        {
            "description": "higher_card_10_J",
            "property": "higher_card",
            "input": ["C10", "CJ"],
            "expected": ["C10", "CJ"],
        },
        {
            "description": "higher_card_3_A",
            "property": "higher_card",
            "input": ["C3", "CA"],
            "expected": ["C3"],
        },
        {
            "description": "higher_card_5_5",
            "property": "higher_card",
            "input": ["C5", "C5"],
            "expected": ["C5", "C5"],
        },
        {
            "description": "value_of_ace_2_3",
            "property": "value_of_ace",
            "input": ["C2", "C3"],
            "expected": 11,
        },
        {
            "description": "value_of_ace_A_Q",
            "property": "value_of_ace",
            "input": ["CA", "CQ"],
            "expected": 1,
        },
        {
            "description": "value_of_ace_5_5",
            "property": "value_of_ace",
            "input": ["C5", "C5"],
            "expected": 11,
        },
        {
            "description": "value_of_ace_A_2",
            "property": "value_of_ace",
            "input": ["CA", "C2"],
            "expected": 11,
        },
        {
            "description": "value_of_ace_7_3",
            "property": "value_of_ace",
            "input": ["C7", "C3"],
            "expected": 11,
        },
        {
            "description": "value_of_ace_7_4",
            "property": "value_of_ace",
            "input": ["C7", "C4"],
            "expected": 1,
        },
        {
            "description": "is_blackjack_A_K",
            "property": "is_blackjack",
            "input": ["CA", "CK"],
            "expected": True,
        },
        {
            "description": "is_blackjack_A_A",
            "property": "is_blackjack",
            "input": ["CA", "CA"],
            "expected": False,
        },
        {
            "description": "is_blackjack_4_7",
            "property": "is_blackjack",
            "input": ["C4", "C7"],
            "expected": False,
        },
        {
            "description": "is_blackjack_Q_K",
            "property": "is_blackjack",
            "input": ["CQ", "CK"],
            "expected": False,
        },
        {
            "description": "is_blackjack_A_10",
            "property": "is_blackjack",
            "input": ["CA", "C10"],
            "expected": True,
        },
        {
            "description": "is_blackjack_J_A",
            "property": "is_blackjack",
            "input": ["CJ", "CA"],
            "expected": True,
        },
        {
            "description": "can_split_Q_K",
            "property": "can_split_pairs",
            "input": ["CQ", "CK"],
            "expected": True,
        },
        {
            "description": "can_split_10_A",
            "property": "can_split_pairs",
            "input": ["C10", "CA"],
            "expected": False,
        },
        {
            "description": "can_split_A_A",
            "property": "can_split_pairs",
            "input": ["CA", "CA"],
            "expected": True,
        },
        {
            "description": "can_split_6_6",
            "property": "can_split_pairs",
            "input": ["C6", "C6"],
            "expected": True,
        },
        {
            "description": "can_split_9_10",
            "property": "can_split_pairs",
            "input": ["C9", "C10"],
            "expected": False,
        },
        {
            "description": "can_double_down_A_9",
            "property": "can_double_down",
            "input": ["CA", "C9"],
            "expected": True,
        },
        {
            "description": "can_double_down_K_J",
            "property": "can_double_down",
            "input": ["CK", "CJ"],
            "expected": False,
        },
        {
            "description": "can_double_down_4_3",
            "property": "can_double_down",
            "input": ["C4", "C3"],
            "expected": False,
        },
        {
            "description": "can_double_down_4_5",
            "property": "can_double_down",
            "input": ["C4", "C5"],
            "expected": True,
        },
        {
            "description": "can_double_down_A_A",
            "property": "can_double_down",
            "input": ["CA", "CA"],
            "expected": False,
        },
        {
            "description": "can_double_down_K_A",
            "property": "can_double_down",
            "input": ["CK", "CA"],
            "expected": True,
        },
    ]


def array_literal(cards):
    return str(cards).replace("[", "{").replace("]", "}").replace("'", "")


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "value_of_card":
        return f"TEST_ASSERT_EQUAL_UINT64({expected}, {prop}({inp}));\n"
    if prop == "value_of_ace":
        return f"TEST_ASSERT_EQUAL_UINT64({expected}, {prop}({inp[0]}, {inp[1]}));\n"
    if prop == "higher_card":
        if len(expected) < 2:
            expected.append("0")
        str_list = []
        str_list.append(f"const card_pair_t expected = {array_literal(expected)};")
        str_list.append(f"const card_pair_t actual = {prop}({inp[0]}, {inp[1]});")
        str_list.append(
            "TEST_ASSERT((actual.fst == expected.snd && actual.snd == expected.fst) || (actual.fst == expected.fst && actual.snd == expected.snd));"
        )
        return "\n".join(str_list)
    if expected:
        return f"TEST_ASSERT({prop}({inp[0]}, {inp[1]}));\n"
    return f"TEST_ASSERT(!{prop}({inp[0]}, {inp[1]}));\n"
