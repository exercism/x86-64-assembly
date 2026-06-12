FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>
#include <stdint.h>

extern void rectify_trace(float result[4], const float trace[4]);
extern void reading_scale(int32_t result[4], const float trace[4]);
extern void coarsen_displacements(int32_t result[4], const int32_t counts[4], uint64_t shift);
extern void gate_channels(uint32_t result[4], const uint32_t enable_a[4], const uint32_t enable_b[4], const uint32_t faulty[4]);
extern void toggle_calibration(uint32_t result[4], const uint32_t status[4], const uint32_t toggle[4], const uint32_t locked[4]);
extern void amplify_trace(float result[4], const float trace[4], const int32_t gains[4]);
"""


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "rectify_trace_example",
            "property": "rectify_trace",
            "input": [["1.5f", "-2.25f", "0.0f", "-135.75f"]],
            "expected": ["1.5f", "2.25f", "0.0f", "135.75f"],
        },
        {
            "task_id": 1,
            "description": "rectify_trace_all_negative",
            "property": "rectify_trace",
            "input": [["-0.5f", "-1.0f", "-3.5f", "-1000.25f"]],
            "expected": ["0.5f", "1.0f", "3.5f", "1000.25f"],
        },
        {
            "task_id": 1,
            "description": "rectify_trace_all_positive_unchanged",
            "property": "rectify_trace",
            "input": [["0.5f", "1.0f", "3.5f", "1000.25f"]],
            "expected": ["0.5f", "1.0f", "3.5f", "1000.25f"],
        },
        {
            "task_id": 1,
            "description": "rectify_trace_negative_zero",
            "property": "rectify_trace",
            "input": [["-0.0f", "0.0f", "-0.0f", "0.0f"]],
            "expected": ["0.0f", "0.0f", "0.0f", "0.0f"],
        },
        {
            "task_id": 1,
            "description": "rectify_trace_large_magnitudes",
            "property": "rectify_trace",
            "input": [["-123456.0f", "98765.5f", "-0.015625f", "-7.0f"]],
            "expected": ["123456.0f", "98765.5f", "0.015625f", "7.0f"],
        },
        {
            "task_id": 2,
            "description": "reading_scale_example",
            "property": "reading_scale",
            "input": [["8.0f", "0.25f", "1.0f", "13.5f"]],
            "expected": [3, -2, 0, 3],
        },
        {
            "task_id": 2,
            "description": "reading_scale_powers_of_two",
            "property": "reading_scale",
            "input": [["1.0f", "2.0f", "4.0f", "1024.0f"]],
            "expected": [0, 1, 2, 10],
        },
        {
            "task_id": 2,
            "description": "reading_scale_small_readings",
            "property": "reading_scale",
            "input": [["0.5f", "0.125f", "0.03125f", "0.75f"]],
            "expected": [-1, -3, -5, -1],
        },
        {
            "task_id": 2,
            "description": "reading_scale_ignores_fraction",
            "property": "reading_scale",
            "input": [["1.999f", "2.001f", "15.875f", "16.125f"]],
            "expected": [0, 1, 3, 4],
        },
        {
            "task_id": 2,
            "description": "reading_scale_negative_readings",
            "property": "reading_scale",
            "input": [["-8.0f", "-0.25f", "-1.5f", "-100.0f"]],
            "expected": [3, -2, 0, 6],
        },
        {
            "task_id": 3,
            "description": "coarsen_displacements_example",
            "property": "coarsen_displacements",
            "input": [[1024, -1024, 25, -25], 3],
            "expected": [128, -128, 3, -4],
        },
        {
            "task_id": 3,
            "description": "coarsen_displacements_shift_zero",
            "property": "coarsen_displacements",
            "input": [[7, -7, 2147483647, -2147483648], 0],
            "expected": [7, -7, 2147483647, -2147483648],
        },
        {
            "task_id": 3,
            "description": "coarsen_displacements_rounds_toward_negative_infinity",
            "property": "coarsen_displacements",
            "input": [[-1, -2, -3, -4], 1],
            "expected": [-1, -1, -2, -2],
        },
        {
            "task_id": 3,
            "description": "coarsen_displacements_keeps_sign_with_large_shift",
            "property": "coarsen_displacements",
            "input": [[-2147483648, 2147483647, -1, 1], 31],
            "expected": [-1, 0, -1, 0],
        },
        {
            "task_id": 4,
            "description": "gate_channels_example",
            "property": "gate_channels",
            "input": [
                [0b1100, 0b0001, 0b1111, 0b0000],
                [0b0110, 0b0001, 0b0000, 0b0000],
                [0b0100, 0b0011, 0b1001, 0b1111],
            ],
            "expected": [0b1010, 0b0000, 0b0110, 0b0000],
        },
        {
            "task_id": 4,
            "description": "gate_channels_no_faults",
            "property": "gate_channels",
            "input": [
                [0xF0F0F0F0, 0, 0x12345678, 0xFFFFFFFF],
                [0x0F0F0F0F, 0, 0x87654321, 0],
                [0, 0, 0, 0],
            ],
            "expected": [0xFFFFFFFF, 0, 0x97755779, 0xFFFFFFFF],
        },
        {
            "task_id": 4,
            "description": "gate_channels_all_faulty",
            "property": "gate_channels",
            "input": [
                [0xDEADBEEF, 0xFFFFFFFF, 1, 0x80000000],
                [0xFEEDFACE, 0xFFFFFFFF, 2, 0x00000001],
                [0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF],
            ],
            "expected": [0, 0, 0, 0],
        },
        {
            "task_id": 4,
            "description": "gate_channels_faults_only_silence_enabled_channels",
            "property": "gate_channels",
            "input": [
                [0b1010, 0b1100, 0xFF00, 0],
                [0b0101, 0b1010, 0x00FF, 0],
                [0b0001, 0b0110, 0x0FF0, 0xFFFFFFFF],
            ],
            "expected": [0b1110, 0b1000, 0xF00F, 0],
        },
        {
            "task_id": 5,
            "description": "toggle_calibration_example",
            "property": "toggle_calibration",
            "input": [
                [0b1100, 0b0001, 0b1111, 0b1010],
                [0b0110, 0b0011, 0b1111, 0b1010],
                [0b0010, 0b0001, 0b1100, 0b0000],
            ],
            "expected": _toggle(
                [0b1100, 0b0001, 0b1111, 0b1010],
                [0b0110, 0b0011, 0b1111, 0b1010],
                [0b0010, 0b0001, 0b1100, 0b0000],
            ),
        },
        {
            "task_id": 5,
            "description": "toggle_calibration_nothing_locked_is_a_plain_toggle",
            "property": "toggle_calibration",
            "input": [
                [0xDEADBEEF, 0, 0xFFFFFFFF, 0x12345678],
                [0x10101010, 0xFFFFFFFF, 0x0F0F0F0F, 0x12345678],
                [0, 0, 0, 0],
            ],
            "expected": _toggle(
                [0xDEADBEEF, 0, 0xFFFFFFFF, 0x12345678],
                [0x10101010, 0xFFFFFFFF, 0x0F0F0F0F, 0x12345678],
                [0, 0, 0, 0],
            ),
        },
        {
            "task_id": 5,
            "description": "toggle_calibration_everything_locked_is_identity",
            "property": "toggle_calibration",
            "input": [
                [0xDEADBEEF, 0, 0xFFFFFFFF, 0x0F0F0F0F],
                [0xFFFFFFFF, 0xFFFFFFFF, 0x12345678, 0xF0F0F0F0],
                [0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF],
            ],
            "expected": [0xDEADBEEF, 0, 0xFFFFFFFF, 0x0F0F0F0F],
        },
        {
            "task_id": 5,
            "description": "toggle_calibration_locks_outside_the_toggle_change_nothing",
            "property": "toggle_calibration",
            "input": [
                [0b1010, 0b1100, 0xFF00, 0xCAFE0000],
                [0b0101, 0b0010, 0x00F0, 0x0000BEEF],
                [0b1010, 0b1101, 0xFF0F, 0xFFFF0000],
            ],
            "expected": _toggle(
                [0b1010, 0b1100, 0xFF00, 0xCAFE0000],
                [0b0101, 0b0010, 0x00F0, 0x0000BEEF],
                [0b1010, 0b1101, 0xFF0F, 0xFFFF0000],
            ),
        },
        {
            "task_id": 5,
            "description": "toggle_calibration_only_unlocked_bits_flip",
            "property": "toggle_calibration",
            "input": [
                [0xAAAAAAAA, 0x55555555, 0xFFFF0000, 0],
                [0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF],
                [0x0000FFFF, 0xFFFF0000, 0x00FF00FF, 0xF0F0F0F0],
            ],
            "expected": _toggle(
                [0xAAAAAAAA, 0x55555555, 0xFFFF0000, 0],
                [0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF],
                [0x0000FFFF, 0xFFFF0000, 0x00FF00FF, 0xF0F0F0F0],
            ),
        },
        {
            "task_id": 5,
            "description": "toggle_calibration_twice_restores",
            "property": "toggle_calibration_twice",
            "input": [
                [0xCAFEF00D, 0x0000FFFF, 0xAAAAAAAA, 0x55555555],
                [0x10101010, 0xFFFFFFFF, 0x55555555, 0x55555555],
                [0x00100100, 0x000000FF, 0x44444444, 0],
            ],
            "expected": [0xCAFEF00D, 0x0000FFFF, 0xAAAAAAAA, 0x55555555],
        },
        {
            "task_id": 6,
            "description": "amplify_trace_example",
            "property": "amplify_trace",
            "input": [["1.5f", "-2.0f", "0.25f", "96.0f"], [2, 1, 3, -5]],
            "expected": ["6.0f", "-4.0f", "2.0f", "3.0f"],
        },
        {
            "task_id": 6,
            "description": "amplify_trace_zero_gain_is_identity",
            "property": "amplify_trace",
            "input": [["1.5f", "-2.25f", "1000.0f", "0.0078125f"], [0, 0, 0, 0]],
            "expected": ["1.5f", "-2.25f", "1000.0f", "0.0078125f"],
        },
        {
            "task_id": 6,
            "description": "amplify_trace_doubling_chain",
            "property": "amplify_trace",
            "input": [["1.0f", "1.0f", "1.0f", "1.0f"], [1, 2, 3, 10]],
            "expected": ["2.0f", "4.0f", "8.0f", "1024.0f"],
        },
        {
            "task_id": 6,
            "description": "amplify_trace_negative_gains_divide",
            "property": "amplify_trace",
            "input": [["64.0f", "-8.0f", "1.0f", "0.5f"], [-6, -3, -1, -9]],
            "expected": ["1.0f", "-1.0f", "0.5f", "0.0009765625f"],
        },
        {
            "task_id": 6,
            "description": "amplify_trace_preserves_sign_and_fraction",
            "property": "amplify_trace",
            "input": [["1.25f", "-7.5f", "0.375f", "100.0f"], [3, -2, 5, 1]],
            "expected": ["10.0f", "-1.875f", "12.0f", "200.0f"],
        },
    ]


def _toggle(status, toggle, locked):
    return [st ^ (tg & ~lk & 0xFFFFFFFF) for st, tg, lk in zip(status, toggle, locked)]


def array_literal(numbers):
    return str(list(numbers)).replace("[", "{").replace("]", "}").replace("'", "")


def lane_asserts(assert_kind, message_kind):
    return [
        f'TEST_ASSERT_EQUAL_{assert_kind}_MESSAGE(expected[{i}], result[{i}], "The {message_kind} at lane {i} is different from expected");'
        for i in range(4)
    ]


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "rectify_trace":
        str_list.append(f"alignas(16) const float trace[4] = {array_literal(inp[0])};")
        str_list.append("alignas(16) float result[4];")
        str_list.append("rectify_trace(result, trace);")
        str_list.append(f"const float expected[4] = {array_literal(expected)};")
        str_list.extend(lane_asserts("FLOAT", "32-bit floating-point number"))
    elif prop == "reading_scale":
        str_list.append(f"alignas(16) const float trace[4] = {array_literal(inp[0])};")
        str_list.append("alignas(16) int32_t result[4];")
        str_list.append("reading_scale(result, trace);")
        str_list.append(f"const int32_t expected[4] = {array_literal(expected)};")
        str_list.extend(lane_asserts("INT32", "scale"))
    elif prop == "coarsen_displacements":
        str_list.append(
            f"alignas(16) const int32_t counts[4] = {array_literal(inp[0])};"
        )
        str_list.append("alignas(16) int32_t result[4];")
        str_list.append(f"coarsen_displacements(result, counts, {inp[1]});")
        str_list.append(f"const int32_t expected[4] = {array_literal(expected)};")
        str_list.extend(lane_asserts("INT32", "coarsened count"))
    elif prop == "gate_channels":
        str_list.append(
            f"alignas(16) const uint32_t enable_a[4] = {array_literal(inp[0])};"
        )
        str_list.append(
            f"alignas(16) const uint32_t enable_b[4] = {array_literal(inp[1])};"
        )
        str_list.append(
            f"alignas(16) const uint32_t faulty[4] = {array_literal(inp[2])};"
        )
        str_list.append("alignas(16) uint32_t result[4];")
        str_list.append("gate_channels(result, enable_a, enable_b, faulty);")
        str_list.append(f"const uint32_t expected[4] = {array_literal(expected)};")
        str_list.extend(lane_asserts("UINT32", "gated mask"))
    elif prop == "toggle_calibration":
        str_list.append(
            f"alignas(16) const uint32_t status[4] = {array_literal(inp[0])};"
        )
        str_list.append(
            f"alignas(16) const uint32_t toggle[4] = {array_literal(inp[1])};"
        )
        str_list.append(
            f"alignas(16) const uint32_t locked[4] = {array_literal(inp[2])};"
        )
        str_list.append("alignas(16) uint32_t result[4];")
        str_list.append("toggle_calibration(result, status, toggle, locked);")
        str_list.append(f"const uint32_t expected[4] = {array_literal(expected)};")
        str_list.extend(lane_asserts("UINT32", "status word"))
    elif prop == "toggle_calibration_twice":
        str_list.append(
            f"alignas(16) const uint32_t status[4] = {array_literal(inp[0])};"
        )
        str_list.append(
            f"alignas(16) const uint32_t toggle[4] = {array_literal(inp[1])};"
        )
        str_list.append(
            f"alignas(16) const uint32_t locked[4] = {array_literal(inp[2])};"
        )
        str_list.append("alignas(16) uint32_t once[4];")
        str_list.append("alignas(16) uint32_t result[4];")
        str_list.append("toggle_calibration(once, status, toggle, locked);")
        str_list.append("toggle_calibration(result, once, toggle, locked);")
        str_list.append(f"const uint32_t expected[4] = {array_literal(expected)};")
        str_list.extend(lane_asserts("UINT32", "status word"))
    elif prop == "amplify_trace":
        str_list.append(f"alignas(16) const float trace[4] = {array_literal(inp[0])};")
        str_list.append(
            f"alignas(16) const int32_t gains[4] = {array_literal(inp[1])};"
        )
        str_list.append("alignas(16) float result[4];")
        str_list.append("amplify_trace(result, trace, gains);")
        str_list.append(f"const float expected[4] = {array_literal(expected)};")
        str_list.extend(lane_asserts("FLOAT", "32-bit floating-point number"))
    return "\n".join(str_list)
