FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

typedef struct {
    uint64_t counts;
    uint64_t length;
} current_week_t;

extern uint64_t last_week_counts(void);
extern current_week_t current_week_counts(void);
extern void save_count(uint8_t count);
extern uint8_t today_count(void);
extern void update_today_count(uint8_t count);
extern void update_week_counts(uint64_t week_count);
"""


def extra_cases():
    return [
        {
            "description": "last_week_default",
            "property": "last_weeks_counts",
            "input": None,
            "expected": 0
            | (2 << 8)
            | (5 << 16)
            | (3 << 24)
            | (7 << 32)
            | (8 << 40)
            | (4 << 48),
        },
        {
            "description": "current_week_default",
            "property": "current_week_counts",
            "input": None,
            "expected": [0, 0],
        },
        {
            "description": "save_count_first_day",
            "property": "save_count",
            "input": [5],
            "expected": {
                "last_week": 0
                | (2 << 8)
                | (5 << 16)
                | (3 << 24)
                | (7 << 32)
                | (8 << 40)
                | (4 << 48),
                "current_week": [5, 1],
            },
        },
        {
            "description": "today_count_first_entry",
            "property": "today_count",
            "input": None,
            "expected": 5,
        },
        {
            "description": "update_today_count_first_entry",
            "property": "update_today_count",
            "input": 2,
            "expected": 7,
        },
        {
            "description": "save_count_finish_week",
            "property": "save_count",
            "input": [13, 22, 8, 0, 34, 42],
            "expected": {
                "last_week": 0
                | (2 << 8)
                | (5 << 16)
                | (3 << 24)
                | (7 << 32)
                | (8 << 40)
                | (4 << 48),
                "current_week": [
                    7
                    | (13 << 8)
                    | (22 << 16)
                    | (8 << 24)
                    | (0 << 32)
                    | (34 << 40)
                    | (42 << 48),
                    7,
                ],
            },
        },
        {
            "description": "today_count_current_week",
            "property": "today_count",
            "input": None,
            "expected": 42,
        },
        {
            "description": "update_today_count_current_week",
            "property": "update_today_count",
            "input": 14,
            "expected": 56,
        },
        {
            "description": "save_count_wrap_current_week",
            "property": "save_count",
            "input": [12],
            "expected": {
                "last_week": 7
                | (13 << 8)
                | (22 << 16)
                | (8 << 24)
                | (0 << 32)
                | (34 << 40)
                | (56 << 48),
                "current_week": [12, 1],
            },
        },
        {
            "description": "today_count_new_week",
            "property": "today_count",
            "input": None,
            "expected": 12,
        },
        {
            "description": "update_today_count_new_week",
            "property": "update_today_count",
            "input": 29,
            "expected": 41,
        },
        {
            "description": "continuous_save_count",
            "property": "save_count",
            "input": [45, 12, 3, 9, 0, 2, 4, 8, 7, 2, 3, 4, 26, 32, 5, 6, 1, 19],
            "expected": {
                "last_week": 4
                | (8 << 8)
                | (7 << 16)
                | (2 << 24)
                | (3 << 32)
                | (4 << 40)
                | (26 << 48),
                "current_week": [32 | (5 << 8) | (6 << 16) | (1 << 24) | (19 << 32), 5],
            },
        },
        {
            "description": "save_count_finish_week_again",
            "property": "save_count",
            "input": [1, 7],
            "expected": {
                "last_week": 4
                | (8 << 8)
                | (7 << 16)
                | (2 << 24)
                | (3 << 32)
                | (4 << 40)
                | (26 << 48),
                "current_week": [
                    32
                    | (5 << 8)
                    | (6 << 16)
                    | (1 << 24)
                    | (19 << 32)
                    | (1 << 40)
                    | (7 << 48),
                    7,
                ],
            },
        },
        {
            "description": "update_week_count_one",
            "property": "update_week_counts",
            "input": 3
            | (9 << 8)
            | (44 << 16)
            | (13 << 24)
            | (51 << 32)
            | (36 << 40)
            | (1 << 48),
            "expected": {
                "last_week": 32
                | (5 << 8)
                | (6 << 16)
                | (1 << 24)
                | (19 << 32)
                | (1 << 40)
                | (7 << 48),
                "current_week": [
                    3
                    | (9 << 8)
                    | (44 << 16)
                    | (13 << 24)
                    | (51 << 32)
                    | (36 << 40)
                    | (1 << 48),
                    7,
                ],
            },
        },
        {
            "description": "update_week_count_two",
            "property": "update_week_counts",
            "input": 23
            | (19 << 8)
            | (5 << 16)
            | (2 << 24)
            | (9 << 32)
            | (37 << 40)
            | (24 << 48),
            "expected": {
                "last_week": 3
                | (9 << 8)
                | (44 << 16)
                | (13 << 24)
                | (51 << 32)
                | (36 << 40)
                | (1 << 48),
                "current_week": [
                    23
                    | (19 << 8)
                    | (5 << 16)
                    | (2 << 24)
                    | (9 << 32)
                    | (37 << 40)
                    | (24 << 48),
                    7,
                ],
            },
        },
    ]


def array_literal(cards):
    return str(cards).replace("[", "{").replace("]", "}")


def check_current_week(prop, expected):
    str_list = []
    str_list.append(f"current_week_t crt = {prop}();")
    str_list.append(
        f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({expected[0]}, crt.counts, "Counts for the week are different than expected.");'
    )
    str_list.append(
        f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({expected[1]}, crt.length, "The number of counts is different than expected.");'
    )
    return "\n".join(str_list)


def check_last_week(prop, expected):
    return f'TEST_ASSERT_EQUAL_UINT64_MESSAGE({expected}, {prop}(), "Counts for last week are different than expected.");\n'


def gen_func_body(prop, inp, expected):
    if prop == "last_week_counts":
        return check_last_week(prop, expected)
    if prop == "current_week_counts":
        return check_current_week(prop, expected)
    str_list = []
    if prop == "save_count":
        for val in inp:
            str_list.append(f"{prop}({val});")
        str_list.append(check_last_week("last_week_counts", expected["last_week"]))
        str_list.append(
            check_current_week("current_week_counts", expected["current_week"])
        )
        return "\n".join(str_list)
    if prop == "update_week_counts":
        str_list.append(f"{prop}({inp});")
        str_list.append(check_last_week("last_week_counts", expected["last_week"]))
        str_list.append(
            check_current_week("current_week_counts", expected["current_week"])
        )
        return "\n".join(str_list)
    if prop == "update_today_count":
        str_list.append(f"{prop}({inp});")
    str_list.append(
        f'TEST_ASSERT_EQUAL_UINT8_MESSAGE({expected}, today_count(), "Today\'s count is different than expected.");'
    )
    return "\n".join(str_list)
