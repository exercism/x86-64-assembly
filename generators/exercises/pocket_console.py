FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern int64_t add_bonus(int64_t total, int64_t bonus);
extern int64_t compare_scores(int64_t score_a, int64_t score_b);
extern int64_t validate_score(int64_t score, int64_t min, int64_t max);
extern void top_two(int64_t buffer[2], const int64_t *array, size_t length);
"""


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "add_bonus_both_zero",
            "property": "add_bonus",
            "input": [0, 0],
            "expected": 0,
        },
        {
            "task_id": 1,
            "description": "add_bonus_small_sum",
            "property": "add_bonus",
            "input": [500, 100],
            "expected": 600,
        },
        {
            "task_id": 1,
            "description": "add_bonus_already_at_max",
            "property": "add_bonus",
            "input": [999999, 0],
            "expected": 999999,
        },
        {
            "task_id": 1,
            "description": "add_bonus_just_over_max",
            "property": "add_bonus",
            "input": [999990, 50],
            "expected": 999999,
        },
        {
            "task_id": 1,
            "description": "add_bonus_reaches_max_exactly",
            "property": "add_bonus",
            "input": [999998, 1],
            "expected": 999999,
        },
        {
            "task_id": 1,
            "description": "add_bonus_one_past_max",
            "property": "add_bonus",
            "input": [999998, 2],
            "expected": 999999,
        },
        {
            "task_id": 1,
            "description": "add_bonus_large_bonus_from_zero",
            "property": "add_bonus",
            "input": [0, 999999],
            "expected": 999999,
        },
        {
            "task_id": 1,
            "description": "add_bonus_far_above_max",
            "property": "add_bonus",
            "input": [500000, 5000000],
            "expected": 999999,
        },
        {
            "task_id": 2,
            "description": "compare_scores_both_zero",
            "property": "compare_scores",
            "input": [0, 0],
            "expected": 0,
        },
        {
            "task_id": 2,
            "description": "compare_scores_a_greater_positive",
            "property": "compare_scores",
            "input": [500, 300],
            "expected": 1,
        },
        {
            "task_id": 2,
            "description": "compare_scores_b_greater_positive",
            "property": "compare_scores",
            "input": [300, 500],
            "expected": -1,
        },
        {
            "task_id": 2,
            "description": "compare_scores_equal_positive",
            "property": "compare_scores",
            "input": [500, 500],
            "expected": 0,
        },
        {
            "task_id": 2,
            "description": "compare_scores_equal_negative",
            "property": "compare_scores",
            "input": [-100, -100],
            "expected": 0,
        },
        {
            "task_id": 2,
            "description": "compare_scores_a_negative_b_positive",
            "property": "compare_scores",
            "input": [-100, 100],
            "expected": -1,
        },
        {
            "task_id": 2,
            "description": "compare_scores_a_positive_b_negative",
            "property": "compare_scores",
            "input": [100, -100],
            "expected": 1,
        },
        {
            "task_id": 2,
            "description": "compare_scores_off_by_one",
            "property": "compare_scores",
            "input": [1000000, 999999],
            "expected": 1,
        },
        {
            "task_id": 3,
            "description": "validate_score_in_default_range",
            "property": "validate_score",
            "input": [450, 0, 999999],
            "expected": 450,
        },
        {
            "task_id": 3,
            "description": "validate_score_below_default_min",
            "property": "validate_score",
            "input": [-50, 0, 999999],
            "expected": 0,
        },
        {
            "task_id": 3,
            "description": "validate_score_above_default_max",
            "property": "validate_score",
            "input": [1234567, 0, 999999],
            "expected": 999999,
        },
        {
            "task_id": 3,
            "description": "validate_score_at_min_boundary",
            "property": "validate_score",
            "input": [0, 0, 100],
            "expected": 0,
        },
        {
            "task_id": 3,
            "description": "validate_score_at_max_boundary",
            "property": "validate_score",
            "input": [100, 0, 100],
            "expected": 100,
        },
        {
            "task_id": 3,
            "description": "validate_score_within_negative_range",
            "property": "validate_score",
            "input": [-150, -200, -100],
            "expected": -150,
        },
        {
            "task_id": 3,
            "description": "validate_score_above_negative_range",
            "property": "validate_score",
            "input": [-50, -200, -100],
            "expected": -100,
        },
        {
            "task_id": 3,
            "description": "validate_score_below_offset_range",
            "property": "validate_score",
            "input": [500, 1000, 2000],
            "expected": 1000,
        },
        {
            "task_id": 4,
            "description": "top_two_empty_array",
            "property": "top_two",
            "input": [[], 0],
            "expected": [0, 0],
        },
        {
            "task_id": 4,
            "description": "top_two_single_element",
            "property": "top_two",
            "input": [[42], 1],
            "expected": [42, 0],
        },
        {
            "task_id": 4,
            "description": "top_two_example_from_instructions",
            "property": "top_two",
            "input": [[10, 30, 20, 50, 40], 5],
            "expected": [50, 40],
        },
        {
            "task_id": 4,
            "description": "top_two_all_same",
            "property": "top_two",
            "input": [[7, 7, 7, 7], 4],
            "expected": [7, 7],
        },
        {
            "task_id": 4,
            "description": "top_two_sorted_ascending",
            "property": "top_two",
            "input": [[1, 2, 3, 4, 5], 5],
            "expected": [5, 4],
        },
        {
            "task_id": 4,
            "description": "top_two_sorted_descending",
            "property": "top_two",
            "input": [[5, 4, 3, 2, 1], 5],
            "expected": [5, 4],
        },
        {
            "task_id": 4,
            "description": "top_two_all_negative_disregarded",
            "property": "top_two",
            "input": [[-10, -5, -3, -7], 4],
            "expected": [0, 0],
        },
        {
            "task_id": 4,
            "description": "top_two_mixed_signs",
            "property": "top_two",
            "input": [[-100, 50, -50, 100], 4],
            "expected": [100, 50],
        },
    ]


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}").replace("'", "")


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "top_two":
        str_list.append("int64_t buffer[2] = {0};")
        if inp[0]:
            str_list.append(f"const int64_t input[] = {array_literal(inp[0])};")
            str_list.append(f"{prop}(buffer, input, ARRAY_SIZE(input));")
        else:
            str_list.append(f"{prop}(buffer, NULL, 0);")
        str_list.append(f"const int64_t expected[2] = {array_literal(expected)};")
        str_list.append(
            "TEST_ASSERT_EQUAL_INT64_ARRAY(expected, buffer, ARRAY_SIZE(expected));"
        )
    else:
        args = ", ".join([str(arg) for arg in inp])
        str_list.append(f"TEST_ASSERT_EQUAL_INT64({expected}, {prop}({args}));")
    return "\n".join(str_list)
