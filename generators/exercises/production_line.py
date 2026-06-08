FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>
#include <stddef.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern void sum_yields(const float line_a[4], const float line_b[4], float result[4]);
extern void scaled_deviation(const double measured[], const double target[], const double sensitivity[], double result[]);
extern void calibrate_batch(const float raw[], const double reference[2], const double offset[2], double result[2]);
extern void normalize_scores(double scores[], const double gains[], const double scale[2], size_t n);
"""


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "sum_yields_example",
            "property": "sum_yields",
            "input": [[10.0, 20.0, 30.0, 40.0], [5.0, 15.0, 25.0, 35.0]],
            "expected": [15.0, 35.0, 55.0, 75.0],
        },
        {
            "task_id": 1,
            "description": "sum_yields_all_zeros",
            "property": "sum_yields",
            "input": [[0.0, 0.0, 0.0, 0.0], [0.0, 0.0, 0.0, 0.0]],
            "expected": [0.0, 0.0, 0.0, 0.0],
        },
        {
            "task_id": 1,
            "description": "sum_yields_cancels_to_zero",
            "property": "sum_yields",
            "input": [[-1.0, -2.0, -3.0, -4.0], [1.0, 2.0, 3.0, 4.0]],
            "expected": [0.0, 0.0, 0.0, 0.0],
        },
        {
            "task_id": 1,
            "description": "sum_yields_mixed_signs",
            "property": "sum_yields",
            "input": [[1.5, -2.5, 3.5, -4.5], [-0.5, 2.5, -1.5, 4.5]],
            "expected": [1.0, 0.0, 2.0, 0.0],
        },
        {
            "task_id": 1,
            "description": "sum_yields_fractional",
            "property": "sum_yields",
            "input": [[0.5, 0.25, 0.125, 0.75], [0.5, 0.75, 0.875, 0.25]],
            "expected": [1.0, 1.0, 1.0, 1.0],
        },
        {
            "task_id": 1,
            "description": "sum_yields_large_values",
            "property": "sum_yields",
            "input": [
                [1000000.0, 2000000.0, 3000000.0, 4000000.0],
                [500000.0, 500000.0, 500000.0, 500000.0],
            ],
            "expected": [1500000.0, 2500000.0, 3500000.0, 4500000.0],
        },
        {
            "task_id": 1,
            "description": "sum_yields_one_operand_zero",
            "property": "sum_yields",
            "input": [[7.0, 8.0, 9.0, 10.0], [0.0, 0.0, 0.0, 0.0]],
            "expected": [7.0, 8.0, 9.0, 10.0],
        },
        {
            "task_id": 1,
            "description": "sum_yields_both_negative",
            "property": "sum_yields",
            "input": [[-10.0, -20.0, -30.0, -40.0], [-5.0, -15.0, -25.0, -35.0]],
            "expected": [-15.0, -35.0, -55.0, -75.0],
        },
        {
            "task_id": 2,
            "description": "scaled_deviation_example",
            "property": "scaled_deviation",
            "input": [[10.5, 20.5], [10.0, 20.0], [2.0, 4.0]],
            "expected": [1.0, 2.0],
        },
        {
            "task_id": 2,
            "description": "scaled_deviation_zero_deviation",
            "property": "scaled_deviation",
            "input": [[5.0, 5.0], [5.0, 5.0], [2.0, 2.0]],
            "expected": [0.0, 0.0],
        },
        {
            "task_id": 2,
            "description": "scaled_deviation_negative_deviation",
            "property": "scaled_deviation",
            "input": [[1.0, 2.0], [3.0, 5.0], [1.0, 1.0]],
            "expected": [-2.0, -3.0],
        },
        {
            "task_id": 2,
            "description": "scaled_deviation_zero_sensitivity",
            "property": "scaled_deviation",
            "input": [[100.0, 200.0], [50.0, 50.0], [0.0, 0.0]],
            "expected": [0.0, 0.0],
        },
        {
            "task_id": 2,
            "description": "scaled_deviation_fractional_sensitivity",
            "property": "scaled_deviation",
            "input": [[4.0, 8.0], [2.0, 4.0], [0.5, 0.25]],
            "expected": [1.0, 1.0],
        },
        {
            "task_id": 2,
            "description": "scaled_deviation_negative_target",
            "property": "scaled_deviation",
            "input": [[0.0, 0.0], [-3.0, -7.0], [1.0, 1.0]],
            "expected": [3.0, 7.0],
        },
        {
            "task_id": 2,
            "description": "scaled_deviation_negative_sensitivity",
            "property": "scaled_deviation",
            "input": [[10.0, 10.0], [5.0, 5.0], [-2.0, -3.0]],
            "expected": [-10.0, -15.0],
        },
        {
            "task_id": 2,
            "description": "scaled_deviation_larger_values",
            "property": "scaled_deviation",
            "input": [[1000.0, 2000.0], [1000.0, 1500.0], [3.0, 2.0]],
            "expected": [0.0, 1000.0],
        },
        {
            "task_id": 3,
            "description": "calibrate_batch_example",
            "property": "calibrate_batch",
            "input": [[10.0, 20.0, 25.0, 50.0], [100.0, 100.0], [5.0, 10.0]],
            "expected": [10.0, 5.0, 2.5, 1.25],
        },
        {
            "task_id": 3,
            "description": "calibrate_batch_uniform",
            "property": "calibrate_batch",
            "input": [[6.0, 6.0, 6.0, 6.0], [12.0, 12.0], [2.0, 2.0]],
            "expected": [1.5, 1.5, 1.5, 1.5],
        },
        {
            "task_id": 3,
            "description": "calibrate_batch_different_offset_per_lane",
            "property": "calibrate_batch",
            "input": [[10.0, 10.0, 10.0, 10.0], [20.0, 20.0], [5.0, 8.0]],
            "expected": [2.0, 5.0, 2.0, 5.0],
        },
        {
            "task_id": 3,
            "description": "calibrate_batch_negative_raw",
            "property": "calibrate_batch",
            "input": [[-2.0, -4.0, -8.0, -16.0], [16.0, 16.0], [0.0, 0.0]],
            "expected": [-4.0, -2.0, -1.0, -0.5],
        },
        {
            "task_id": 3,
            "description": "calibrate_batch_different_reference_per_lane",
            "property": "calibrate_batch",
            "input": [[10.0, 10.0, 10.0, 10.0], [100.0, 50.0], [0.0, 0.0]],
            "expected": [5.0, 2.5, 5.0, 2.5],
        },
        {
            "task_id": 3,
            "description": "calibrate_batch_fractional_raw",
            "property": "calibrate_batch",
            "input": [[0.5, 1.0, 2.0, 4.0], [4.0, 4.0], [0.0, 0.0]],
            "expected": [4.0, 2.0, 1.0, 0.5],
        },
        {
            "task_id": 3,
            "description": "calibrate_batch_offset_exceeds_raw",
            "property": "calibrate_batch",
            "input": [[2.0, 2.0, 6.0, 8.0], [8.0, 8.0], [10.0, 10.0]],
            "expected": [-0.5, -0.5, -1.0, -2.0],
        },
        {
            "task_id": 3,
            "description": "calibrate_batch_mixed_reference_offset",
            "property": "calibrate_batch",
            "input": [[3.0, 5.0, 9.0, 17.0], [2.0, 4.0], [1.0, 1.0]],
            "expected": [0.5, 0.5, 0.125, 0.125],
        },
        {
            "task_id": 4,
            "description": "normalize_scores_example",
            "property": "normalize_scores",
            "input": [[10.0, 20.0, 30.0, 40.0], [2.0, 1.5, 1.0, 0.5], [2.0, 4.0], 4],
            "expected": [10.0, 7.5, 15.0, 5.0],
        },
        {
            "task_id": 4,
            "description": "normalize_scores_single_iteration",
            "property": "normalize_scores",
            "input": [[8.0, 16.0], [2.0, 2.0], [4.0, 8.0], 2],
            "expected": [4.0, 4.0],
        },
        {
            "task_id": 4,
            "description": "normalize_scores_identity",
            "property": "normalize_scores",
            "input": [[1.0, 2.0, 3.0, 4.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0], 4],
            "expected": [1.0, 2.0, 3.0, 4.0],
        },
        {
            "task_id": 4,
            "description": "normalize_scores_three_iterations",
            "property": "normalize_scores",
            "input": [
                [2.0, 4.0, 6.0, 8.0, 10.0, 12.0],
                [1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                [2.0, 4.0],
                6,
            ],
            "expected": [1.0, 1.0, 3.0, 2.0, 5.0, 3.0],
        },
        {
            "task_id": 4,
            "description": "normalize_scores_negative_scores",
            "property": "normalize_scores",
            "input": [[-4.0, -8.0, -12.0, -16.0], [1.0, 1.0, 1.0, 1.0], [2.0, 4.0], 4],
            "expected": [-2.0, -2.0, -6.0, -4.0],
        },
        {
            "task_id": 4,
            "description": "normalize_scores_negative_gains",
            "property": "normalize_scores",
            "input": [[10.0, 10.0], [-2.0, -4.0], [1.0, 1.0], 2],
            "expected": [-20.0, -40.0],
        },
        {
            "task_id": 4,
            "description": "normalize_scores_fractional_gains",
            "property": "normalize_scores",
            "input": [[8.0, 8.0, 8.0, 8.0], [0.5, 0.25, 0.125, 0.5], [1.0, 1.0], 4],
            "expected": [4.0, 2.0, 1.0, 4.0],
        },
        {
            "task_id": 4,
            "description": "normalize_scores_negative_scale",
            "property": "normalize_scores",
            "input": [[6.0, 8.0], [2.0, 2.0], [-3.0, -4.0], 2],
            "expected": [-4.0, -4.0],
        },
    ]


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "sum_yields":
        str_list.append(f"alignas(16) const float line_a[4] = {array_literal(inp[0])};")
        str_list.append(f"alignas(16) const float line_b[4] = {array_literal(inp[1])};")
        str_list.append("alignas(16) float result[4];")
        str_list.append(f"{prop}(line_a, line_b, result);")
        str_list.append(f"const float expected[4] = {array_literal(expected)};")
        str_list.append(
            'TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[0], result[0], "The 32-bit floating-point number at lane 0 is different from expected");'
        )
        str_list.append(
            'TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[1], result[1], "The 32-bit floating-point number at lane 1 is different from expected");'
        )
        str_list.append(
            'TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[2], result[2], "The 32-bit floating-point number at lane 2 is different from expected");'
        )
        str_list.append(
            'TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected[3], result[3], "The 32-bit floating-point number at lane 3 is different from expected");'
        )
    elif prop == "scaled_deviation":
        str_list.append(
            f"alignas(16) const double measured[2] = {array_literal(inp[0])};"
        )
        str_list.append("alignas(16) const char x1 = 'X';")
        str_list.append("(void)x1;")
        str_list.append(f"alignas(8) const double target[2] = {array_literal(inp[1])};")
        str_list.append("alignas(16) const char x2 = 'X';")
        str_list.append("(void)x2;")
        str_list.append(
            f"alignas(8) const double sensitivity[2] = {array_literal(inp[2])};"
        )
        str_list.append("alignas(16) const char x3 = 'X';")
        str_list.append("(void)x3;")
        str_list.append("alignas(8) double result[2];")
        str_list.append(f"{prop}(measured, target, sensitivity, result);")
        str_list.append(f"const double expected[2] = {array_literal(expected)};")
        str_list.append(
            'TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0], "The 64-bit floating-point number at lane 0 is different from expected");'
        )
        str_list.append(
            'TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1], "The 64-bit floating-point number at lane 1 is different from expected");'
        )
    elif prop == "calibrate_batch":
        str_list.append("alignas(16) const char x = 'X';")
        str_list.append("(void)x;")
        str_list.append(f"alignas(4) const float raw[] = {array_literal(inp[0])};")
        str_list.append(
            f"alignas(16) const double reference[2] = {array_literal(inp[1])};"
        )
        str_list.append(
            f"alignas(16) const double offset[2] = {array_literal(inp[2])};"
        )
        str_list.append("alignas(16) double result[4];")
        str_list.append(f"{prop}(raw, reference, offset, result);")
        str_list.append(f"const double expected[] = {array_literal(expected)};")
        str_list.append(
            'TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[0], result[0], "The 64-bit floating-point number at lane 0 of the first row is different from expected");'
        )
        str_list.append(
            'TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[1], result[1], "The 64-bit floating-point number at lane 1 of the first row is different from expected");'
        )
        str_list.append(
            'TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[2], result[2], "The 64-bit floating-point number at lane 0 of the second row is different from expected");'
        )
        str_list.append(
            'TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected[3], result[3], "The 64-bit floating-point number at lane 1 of the second row is different from expected");'
        )
    elif prop == "normalize_scores":
        str_list.append(f"alignas(16) double scores[] = {array_literal(inp[0])};")
        str_list.append(f"alignas(16) const double gains[] = {array_literal(inp[1])};")
        str_list.append(f"alignas(16) const double scale[2] = {array_literal(inp[2])};")
        str_list.append(f"{prop}(scores, gains, scale, {inp[3]});")
        str_list.append(f"const double expected[] = {array_literal(expected)};")
        str_list.append(
            'TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, scores, ARRAY_SIZE(expected), "The sequence of 64-bit floating-point numbers is different from expected");'
        )
    return "\n".join(str_list)
