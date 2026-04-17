FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

extern int64_t expected_minutes_in_oven(void);
extern int64_t remaining_minutes_in_oven(int64_t actual_minutes_in_oven);
extern int64_t preparation_time_in_minutes(int64_t number_of_layers);
extern int64_t elapsed_time_in_minutes(int64_t number_of_layers, int64_t actual_minutes_in_oven);
"""


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "expected",
            "property": "expected_minutes_in_oven",
            "input": None,
            "expected": 40,
        },
        {
            "task_id": 2,
            "description": "remaining",
            "property": "remaining_minutes_in_oven",
            "input": 25,
            "expected": 15,
        },
        {
            "task_id": 3,
            "description": "preparation_one",
            "property": "preparation_time_in_minutes",
            "input": 1,
            "expected": 2,
        },
        {
            "task_id": 3,
            "description": "preparation_many",
            "property": "preparation_time_in_minutes",
            "input": 4,
            "expected": 8,
        },
        {
            "task_id": 4,
            "description": "elapsed_one",
            "property": "elapsed_time_in_minutes",
            "input": {"number_of_layers": 1, "actual_minutes_in_oven": 30},
            "expected": 32,
        },
        {
            "task_id": 4,
            "description": "elapsed_many",
            "property": "elapsed_time_in_minutes",
            "input": {"number_of_layers": 4, "actual_minutes_in_oven": 8},
            "expected": 16,
        },
    ]


def gen_func_body(prop, inp, expected):
    if prop == "expected_minutes_in_oven":
        return f"TEST_ASSERT_EQUAL_INT64({expected}, {prop}());\n"
    if prop == "remaining_minutes_in_oven" or prop == "preparation_time_in_minutes":
        message = f"The function was called with argument: {inp}."
        return f'TEST_ASSERT_EQUAL_INT64_MESSAGE({expected}, {prop}({inp}), "{message}");\n'
    message = f"The function was called with arguments: {inp['number_of_layers']}, {inp['actual_minutes_in_oven']}."
    return (
        f"TEST_ASSERT_EQUAL_INT64_MESSAGE({expected}, {prop}"
        f"({inp['number_of_layers']}, {inp['actual_minutes_in_oven']}), "
        f'"{message}");\n'
    )
