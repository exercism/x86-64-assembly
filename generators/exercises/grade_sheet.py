FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>
#include <stdint.h>

extern void flag_above_threshold(uint32_t result[4], const float scores[4], const float thresholds[4]);
extern void flag_perfect(uint32_t result[4], const float scores[4], const float maxima[4]);
extern void assign_ranks(uint32_t result[4], const float scores[4], const float maxima[4]);
extern int32_t count_failures(const uint32_t ranks[], int64_t block_count, const int32_t pass_threshold[4]);
extern int32_t all_passed(const uint32_t failing[], int64_t block_count);
"""

ALL_ONES = 0xFFFFFFFF
NONE = 0x00000000

# The passing threshold baked into assign_ranks. Must match the exemplar's rodata.
RANK_THRESHOLD = 50.0


def _above(scores, thresholds):
    return [ALL_ONES if s > t else NONE for s, t in zip(scores, thresholds)]


def _perfect(scores, maxima):
    return [ALL_ONES if s == m else NONE for s, m in zip(scores, maxima)]


def _ranks(scores, maxima):
    out = []
    for s, m in zip(scores, maxima):
        if s == m:
            out.append(3)
        elif s > RANK_THRESHOLD:
            out.append(2)
        else:
            out.append(1)
    return out


def _count(ranks, threshold):
    return sum(1 for r in ranks if r < threshold)


def _all_passed(failing):
    return 1 if all(f == NONE for f in failing) else 0


def extra_cases():
    return [
        # TASK 1: flag_above_threshold
        {
            "task_id": 1,
            "description": "above_threshold_example",
            "property": "flag_above_threshold",
            "input": [[72.0, 55.0, 90.0, 40.0], [60.0, 60.0, 60.0, 60.0]],
            "expected": _above([72.0, 55.0, 90.0, 40.0], [60.0, 60.0, 60.0, 60.0]),
        },
        {
            "task_id": 1,
            "description": "above_threshold_equal_is_not_above",
            "property": "flag_above_threshold",
            "input": [[60.0, 61.0, 59.0, 60.0], [60.0, 60.0, 60.0, 60.0]],
            "expected": _above([60.0, 61.0, 59.0, 60.0], [60.0, 60.0, 60.0, 60.0]),
        },
        {
            "task_id": 1,
            "description": "above_threshold_all_above",
            "property": "flag_above_threshold",
            "input": [[100.0, 80.0, 70.0, 65.0], [50.0, 50.0, 50.0, 50.0]],
            "expected": _above([100.0, 80.0, 70.0, 65.0], [50.0, 50.0, 50.0, 50.0]),
        },
        {
            "task_id": 1,
            "description": "above_threshold_none_above",
            "property": "flag_above_threshold",
            "input": [[10.0, 20.0, 30.0, 40.0], [50.0, 50.0, 50.0, 50.0]],
            "expected": _above([10.0, 20.0, 30.0, 40.0], [50.0, 50.0, 50.0, 50.0]),
        },
        {
            "task_id": 1,
            "description": "above_threshold_per_lane",
            "property": "flag_above_threshold",
            "input": [[50.0, 50.0, 50.0, 50.0], [40.0, 50.0, 60.0, 49.0]],
            "expected": _above([50.0, 50.0, 50.0, 50.0], [40.0, 50.0, 60.0, 49.0]),
        },
        # TASK 2: flag_perfect
        {
            "task_id": 2,
            "description": "perfect_example",
            "property": "flag_perfect",
            "input": [[100.0, 88.0, 100.0, 73.0], [100.0, 100.0, 100.0, 100.0]],
            "expected": _perfect(
                [100.0, 88.0, 100.0, 73.0], [100.0, 100.0, 100.0, 100.0]
            ),
        },
        {
            "task_id": 2,
            "description": "perfect_none",
            "property": "flag_perfect",
            "input": [[99.0, 87.0, 50.0, 72.0], [100.0, 100.0, 100.0, 100.0]],
            "expected": _perfect(
                [99.0, 87.0, 50.0, 72.0], [100.0, 100.0, 100.0, 100.0]
            ),
        },
        {
            "task_id": 2,
            "description": "perfect_all",
            "property": "flag_perfect",
            "input": [[20.0, 50.0, 100.0, 73.0], [20.0, 50.0, 100.0, 73.0]],
            "expected": _perfect([20.0, 50.0, 100.0, 73.0], [20.0, 50.0, 100.0, 73.0]),
        },
        {
            "task_id": 2,
            "description": "perfect_per_lane_maxima",
            "property": "flag_perfect",
            "input": [[20.0, 50.0, 60.0, 80.0], [20.0, 40.0, 60.0, 100.0]],
            "expected": _perfect([20.0, 50.0, 60.0, 80.0], [20.0, 40.0, 60.0, 100.0]),
        },
        # TASK 3: assign_ranks (threshold 50.0, perfect == maximum)
        {
            "task_id": 3,
            "description": "assign_ranks_example",
            "property": "assign_ranks",
            "input": [[40.0, 75.0, 100.0, 60.0], [100.0, 100.0, 100.0, 100.0]],
            "expected": _ranks([40.0, 75.0, 100.0, 60.0], [100.0, 100.0, 100.0, 100.0]),
        },
        {
            "task_id": 3,
            "description": "assign_ranks_all_low",
            "property": "assign_ranks",
            "input": [[50.0, 30.0, 10.0, 0.0], [100.0, 100.0, 100.0, 100.0]],
            "expected": _ranks([50.0, 30.0, 10.0, 0.0], [100.0, 100.0, 100.0, 100.0]),
        },
        {
            "task_id": 3,
            "description": "assign_ranks_all_perfect",
            "property": "assign_ranks",
            "input": [[100.0, 100.0, 100.0, 100.0], [100.0, 100.0, 100.0, 100.0]],
            "expected": _ranks(
                [100.0, 100.0, 100.0, 100.0], [100.0, 100.0, 100.0, 100.0]
            ),
        },
        {
            "task_id": 3,
            "description": "assign_ranks_perfect_overrides_threshold",
            "property": "assign_ranks",
            "input": [[55.0, 100.0, 50.0, 90.0], [200.0, 100.0, 50.0, 90.0]],
            "expected": _ranks([55.0, 100.0, 50.0, 90.0], [200.0, 100.0, 50.0, 90.0]),
        },
        {
            "task_id": 3,
            "description": "assign_ranks_threshold_boundary",
            "property": "assign_ranks",
            "input": [[50.0, 51.0, 49.0, 100.0], [100.0, 100.0, 100.0, 100.0]],
            "expected": _ranks([50.0, 51.0, 49.0, 100.0], [100.0, 100.0, 100.0, 100.0]),
        },
        # TASK 4: count_failures (ranks across blocks, threshold replicated across 4 lanes)
        {
            "task_id": 4,
            "description": "count_failures_example",
            "property": "count_failures",
            "input": [[1, 2, 3, 1, 2, 2, 1, 3], 2],
            "expected": _count([1, 2, 3, 1, 2, 2, 1, 3], 2),
        },
        {
            "task_id": 4,
            "description": "count_failures_none_below",
            "property": "count_failures",
            "input": [[2, 3, 2, 3, 3, 2, 3, 2], 2],
            "expected": _count([2, 3, 2, 3, 3, 2, 3, 2], 2),
        },
        {
            "task_id": 4,
            "description": "count_failures_all_below_single_block",
            "property": "count_failures",
            "input": [[1, 1, 1, 1], 2],
            "expected": _count([1, 1, 1, 1], 2),
        },
        {
            "task_id": 4,
            "description": "count_failures_higher_threshold",
            "property": "count_failures",
            "input": [[1, 2, 3, 1, 2, 2, 1, 3], 3],
            "expected": _count([1, 2, 3, 1, 2, 2, 1, 3], 3),
        },
        {
            "task_id": 4,
            "description": "count_failures_three_blocks",
            "property": "count_failures",
            "input": [[1, 2, 3, 1, 3, 3, 3, 3, 1, 1, 2, 3], 2],
            "expected": _count([1, 2, 3, 1, 3, 3, 3, 3, 1, 1, 2, 3], 2),
        },
        # TASK 5: all_passed (failing masks across blocks)
        {
            "task_id": 5,
            "description": "all_passed_example",
            "property": "all_passed",
            "input": [[NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE]],
            "expected": _all_passed([NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE]),
        },
        {
            "task_id": 5,
            "description": "all_passed_one_failure",
            "property": "all_passed",
            "input": [[NONE, NONE, NONE, NONE, NONE, ALL_ONES, NONE, NONE]],
            "expected": _all_passed(
                [NONE, NONE, NONE, NONE, NONE, ALL_ONES, NONE, NONE]
            ),
        },
        {
            "task_id": 5,
            "description": "all_passed_single_block_clear",
            "property": "all_passed",
            "input": [[NONE, NONE, NONE, NONE]],
            "expected": _all_passed([NONE, NONE, NONE, NONE]),
        },
        {
            "task_id": 5,
            "description": "all_passed_first_block_failure",
            "property": "all_passed",
            "input": [[ALL_ONES, NONE, NONE, NONE, NONE, NONE, NONE, NONE]],
            "expected": _all_passed(
                [ALL_ONES, NONE, NONE, NONE, NONE, NONE, NONE, NONE]
            ),
        },
        {
            "task_id": 5,
            "description": "all_passed_last_lane_failure",
            "property": "all_passed",
            "input": [[NONE, NONE, NONE, NONE, NONE, NONE, NONE, ALL_ONES]],
            "expected": _all_passed(
                [NONE, NONE, NONE, NONE, NONE, NONE, NONE, ALL_ONES]
            ),
        },
    ]


def int_array_literal(numbers):
    return str(list(numbers)).replace("[", "{").replace("]", "}").replace("'", "")


def float_array_literal(numbers):
    return "{" + ", ".join(f"{float(n)}f" for n in numbers) + "}"


def lane_asserts(assert_kind, message_kind):
    return [
        f'TEST_ASSERT_EQUAL_{assert_kind}_MESSAGE(expected[{i}], result[{i}], "The {message_kind} at lane {i} is different from expected");'
        for i in range(4)
    ]


def gen_func_body(prop, inp, expected):
    s = []
    if prop == "flag_above_threshold":
        s.append(f"alignas(16) const float scores[4] = {float_array_literal(inp[0])};")
        s.append(
            f"alignas(16) const float thresholds[4] = {float_array_literal(inp[1])};"
        )
        s.append("alignas(16) uint32_t result[4];")
        s.append("flag_above_threshold(result, scores, thresholds);")
        s.append(f"const uint32_t expected[4] = {int_array_literal(expected)};")
        s.extend(lane_asserts("HEX32", "mask lane"))
    elif prop == "flag_perfect":
        s.append(f"alignas(16) const float scores[4] = {float_array_literal(inp[0])};")
        s.append(f"alignas(16) const float maxima[4] = {float_array_literal(inp[1])};")
        s.append("alignas(16) uint32_t result[4];")
        s.append("flag_perfect(result, scores, maxima);")
        s.append(f"const uint32_t expected[4] = {int_array_literal(expected)};")
        s.extend(lane_asserts("HEX32", "mask lane"))
    elif prop == "assign_ranks":
        s.append(f"alignas(16) const float scores[4] = {float_array_literal(inp[0])};")
        s.append(f"alignas(16) const float maxima[4] = {float_array_literal(inp[1])};")
        s.append("alignas(16) uint32_t result[4];")
        s.append("assign_ranks(result, scores, maxima);")
        s.append(f"const uint32_t expected[4] = {int_array_literal(expected)};")
        s.extend(lane_asserts("UINT32", "rank"))
    elif prop == "count_failures":
        ranks, threshold = inp[0], inp[1]
        block_count = len(ranks) // 4
        s.append(
            f"alignas(16) const uint32_t ranks[{len(ranks)}] = {int_array_literal(ranks)};"
        )
        s.append(
            f"alignas(16) const int32_t pass_threshold[4] = {int_array_literal([threshold] * 4)};"
        )
        s.append(
            f'TEST_ASSERT_EQUAL_INT32_MESSAGE({expected}, count_failures(ranks, {block_count}, pass_threshold), "The number of failing ranks is different from expected");'
        )
    elif prop == "all_passed":
        failing = inp[0]
        block_count = len(failing) // 4
        s.append(
            f"alignas(16) const uint32_t failing[{len(failing)}] = {int_array_literal(failing)};"
        )
        s.append(
            f'TEST_ASSERT_EQUAL_INT32_MESSAGE({expected}, all_passed(failing, {block_count}), "The all-passed answer is different from expected");'
        )
    return "\n".join(s)
