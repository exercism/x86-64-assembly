FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern void mix_tracks(int16_t result[8], const int16_t track_a[8], const int16_t track_b[8]);
extern void remove_bleed(int16_t result[8], const int16_t track[8], const int16_t bleed[8]);
extern void combine_meters(uint8_t result[16], const uint8_t meter_a[16], const uint8_t meter_b[16]);
extern void apply_fade(int16_t result[], const int16_t track[], const int16_t gains[], size_t n);
extern void attenuate_track(int32_t result[], const int16_t samples[], const int32_t divisor[4], size_t n);
"""


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "mix_tracks_example",
            "property": "mix_tracks",
            "input": [
                [10000, 30000, 20000, -30000, -20000, -100, 100, 0],
                [5000, 5000, 20000, -5000, -20000, 100, -100, 0],
            ],
            "expected": [15000, 32767, 32767, -32768, -32768, 0, 0, 0],
        },
        {
            "task_id": 1,
            "description": "mix_tracks_all_zeros",
            "property": "mix_tracks",
            "input": [[0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0]],
            "expected": [0, 0, 0, 0, 0, 0, 0, 0],
        },
        {
            "task_id": 1,
            "description": "mix_tracks_no_saturation",
            "property": "mix_tracks",
            "input": [[1, 2, 3, 4, 5, 6, 7, 8], [10, 20, 30, 40, 50, 60, 70, 80]],
            "expected": [11, 22, 33, 44, 55, 66, 77, 88],
        },
        {
            "task_id": 1,
            "description": "mix_tracks_saturates_positive",
            "property": "mix_tracks",
            "input": [
                [32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767],
                [1, 1, 1, 1, 1, 1, 1, 1],
            ],
            "expected": [32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767],
        },
        {
            "task_id": 1,
            "description": "mix_tracks_saturates_negative",
            "property": "mix_tracks",
            "input": [
                [-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768],
                [-1, -1, -1, -1, -1, -1, -1, -1],
            ],
            "expected": [
                -32768,
                -32768,
                -32768,
                -32768,
                -32768,
                -32768,
                -32768,
                -32768,
            ],
        },
        {
            "task_id": 1,
            "description": "mix_tracks_reaches_max_without_clamping",
            "property": "mix_tracks",
            "input": [
                [16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383],
                [16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384],
            ],
            "expected": [32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767],
        },
        {
            "task_id": 1,
            "description": "mix_tracks_one_track_silent",
            "property": "mix_tracks",
            "input": [[7, 8, 9, 10, 11, 12, 13, 14], [0, 0, 0, 0, 0, 0, 0, 0]],
            "expected": [7, 8, 9, 10, 11, 12, 13, 14],
        },
        {
            "task_id": 1,
            "description": "mix_tracks_mixed_extremes",
            "property": "mix_tracks",
            "input": [
                [32767, -32768, 100, -100, 0, 16384, -16384, 1],
                [1, -1, -100, 100, 0, 16384, -16384, -1],
            ],
            "expected": [32767, -32768, 0, 0, 0, 32767, -32768, 0],
        },
        {
            "task_id": 2,
            "description": "remove_bleed_example",
            "property": "remove_bleed",
            "input": [
                [10000, -30000, 5000, 32767, 0, 200, -200, 15000],
                [2000, 5000, 5000, -5, 0, 300, 300, 5000],
            ],
            "expected": [8000, -32768, 0, 32767, 0, -100, -500, 10000],
        },
        {
            "task_id": 2,
            "description": "remove_bleed_all_zeros",
            "property": "remove_bleed",
            "input": [[0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0, 0, 0]],
            "expected": [0, 0, 0, 0, 0, 0, 0, 0],
        },
        {
            "task_id": 2,
            "description": "remove_bleed_no_saturation",
            "property": "remove_bleed",
            "input": [
                [100, 200, 300, 400, 500, 600, 700, 800],
                [50, 50, 50, 50, 50, 50, 50, 50],
            ],
            "expected": [50, 150, 250, 350, 450, 550, 650, 750],
        },
        {
            "task_id": 2,
            "description": "remove_bleed_saturates_negative",
            "property": "remove_bleed",
            "input": [
                [-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768],
                [1, 1, 1, 1, 1, 1, 1, 1],
            ],
            "expected": [
                -32768,
                -32768,
                -32768,
                -32768,
                -32768,
                -32768,
                -32768,
                -32768,
            ],
        },
        {
            "task_id": 2,
            "description": "remove_bleed_saturates_positive",
            "property": "remove_bleed",
            "input": [
                [32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767],
                [-1, -1, -1, -1, -1, -1, -1, -1],
            ],
            "expected": [32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767],
        },
        {
            "task_id": 2,
            "description": "remove_bleed_cancels_to_zero",
            "property": "remove_bleed",
            "input": [[5, 10, 15, 20, 25, 30, 35, 40], [5, 10, 15, 20, 25, 30, 35, 40]],
            "expected": [0, 0, 0, 0, 0, 0, 0, 0],
        },
        {
            "task_id": 2,
            "description": "remove_bleed_mixed_extremes",
            "property": "remove_bleed",
            "input": [
                [0, 0, -100, 100, 32767, -32768, 1000, -1000],
                [32767, -32768, 100, -100, -1, 1, 500, -500],
            ],
            "expected": [-32767, 32767, -200, 200, 32767, -32768, 500, -500],
        },
        {
            "task_id": 2,
            "description": "remove_bleed_goes_negative",
            "property": "remove_bleed",
            "input": [
                [10, 20, 30, 40, 50, 60, 70, 80],
                [100, 100, 100, 100, 100, 100, 100, 100],
            ],
            "expected": [-90, -80, -70, -60, -50, -40, -30, -20],
        },
        {
            "task_id": 3,
            "description": "combine_meters_example",
            "property": "combine_meters",
            "input": [
                [200, 100, 50, 255, 0, 128, 10, 240, 1, 2, 3, 4, 5, 6, 7, 8],
                [100, 100, 200, 1, 0, 128, 10, 20, 1, 2, 3, 4, 5, 6, 7, 8],
            ],
            "expected": [
                255,
                200,
                250,
                255,
                0,
                255,
                20,
                255,
                2,
                4,
                6,
                8,
                10,
                12,
                14,
                16,
            ],
        },
        {
            "task_id": 3,
            "description": "combine_meters_all_zeros",
            "property": "combine_meters",
            "input": [
                [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            ],
            "expected": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        },
        {
            "task_id": 3,
            "description": "combine_meters_no_saturation",
            "property": "combine_meters",
            "input": [
                [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
                [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            ],
            "expected": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        },
        {
            "task_id": 3,
            "description": "combine_meters_all_saturate",
            "property": "combine_meters",
            "input": [
                [
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                    200,
                ],
                [
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                    100,
                ],
            ],
            "expected": [
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
            ],
        },
        {
            "task_id": 3,
            "description": "combine_meters_reaches_max_without_clamping",
            "property": "combine_meters",
            "input": [
                [
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                ],
                [
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                    127,
                ],
            ],
            "expected": [
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
            ],
        },
        {
            "task_id": 3,
            "description": "combine_meters_just_overflows",
            "property": "combine_meters",
            "input": [
                [
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                ],
                [
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                    128,
                ],
            ],
            "expected": [
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
            ],
        },
        {
            "task_id": 3,
            "description": "combine_meters_one_meter_dark",
            "property": "combine_meters",
            "input": [
                [
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                    255,
                ],
                [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            ],
            "expected": [
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
            ],
        },
        {
            "task_id": 3,
            "description": "combine_meters_mixed",
            "property": "combine_meters",
            "input": [
                [250, 5, 128, 200, 255, 1, 100, 150, 0, 255, 200, 55, 128, 128, 1, 254],
                [10, 250, 128, 55, 0, 254, 100, 150, 0, 1, 55, 200, 127, 128, 254, 1],
            ],
            "expected": [
                255,
                255,
                255,
                255,
                255,
                255,
                200,
                255,
                0,
                255,
                255,
                255,
                255,
                255,
                255,
                255,
            ],
        },
        {
            "task_id": 4,
            "description": "apply_fade_example",
            "property": "apply_fade",
            "input": [
                [20000, 20000, 20000, 20000, -20000, -20000, -20000, -20000],
                [32767, 24576, 16384, 8192, 32767, 24576, 16384, 8192],
                8,
            ],
            "expected": [9999, 7500, 5000, 2500, -10000, -7500, -5000, -2500],
        },
        {
            "task_id": 4,
            "description": "apply_fade_zero_gain",
            "property": "apply_fade",
            "input": [
                [1000, -1000, 2000, -2000, 3000, -3000, 32767, -32768],
                [0, 0, 0, 0, 0, 0, 0, 0],
                8,
            ],
            "expected": [0, 0, 0, 0, 0, 0, 0, 0],
        },
        {
            "task_id": 4,
            "description": "apply_fade_quarter_gain",
            "property": "apply_fade",
            "input": [
                [4, 40, 400, 4000, -4, -40, -400, -4000],
                [16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384],
                8,
            ],
            "expected": [1, 10, 100, 1000, -1, -10, -100, -1000],
        },
        {
            "task_id": 4,
            "description": "apply_fade_rounds_toward_negative_infinity",
            "property": "apply_fade",
            "input": [
                [-7, -7, -7, -7, 7, 7, 7, 7],
                [16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384],
                8,
            ],
            "expected": [-2, -2, -2, -2, 1, 1, 1, 1],
        },
        {
            "task_id": 4,
            "description": "apply_fade_near_half_gain",
            "property": "apply_fade",
            "input": [
                [32767, 16384, 8192, 4096, -32768, -16384, -8192, -4096],
                [32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767],
                8,
            ],
            "expected": [16383, 8191, 4095, 2047, -16384, -8192, -4096, -2048],
        },
        {
            "task_id": 4,
            "description": "apply_fade_small_products_vanish",
            "property": "apply_fade",
            "input": [
                [2, 2, 2, 2, 2, 2, 2, 2],
                [32767, 16384, 8192, 4096, 2048, 1024, 512, 1],
                8,
            ],
            "expected": [0, 0, 0, 0, 0, 0, 0, 0],
        },
        {
            "task_id": 4,
            "description": "apply_fade_two_blocks",
            "property": "apply_fade",
            "input": [
                [
                    16384,
                    -16384,
                    8192,
                    -8192,
                    30000,
                    -30000,
                    10000,
                    -10000,
                    1,
                    -1,
                    100,
                    -100,
                    25000,
                    -25000,
                    5,
                    -5,
                ],
                [
                    16384,
                    16384,
                    32767,
                    32767,
                    8192,
                    8192,
                    16384,
                    16384,
                    32767,
                    32767,
                    32767,
                    32767,
                    24576,
                    24576,
                    16384,
                    16384,
                ],
                16,
            ],
            "expected": [
                4096,
                -4096,
                4095,
                -4096,
                3750,
                -3750,
                2500,
                -2500,
                0,
                -1,
                49,
                -50,
                9375,
                -9375,
                1,
                -2,
            ],
        },
        {
            "task_id": 5,
            "description": "attenuate_track_example",
            "property": "attenuate_track",
            "input": [[300, 150, 90, -120, 100, 50, -50, 7], 3, 8],
            "expected": [100, 50, 30, -40, 33, 16, -16, 2],
        },
        {
            "task_id": 5,
            "description": "attenuate_track_divide_by_one",
            "property": "attenuate_track",
            "input": [[5, -5, 1000, -1000], 1, 4],
            "expected": [5, -5, 1000, -1000],
        },
        {
            "task_id": 5,
            "description": "attenuate_track_exact_quotients",
            "property": "attenuate_track",
            "input": [[100, 250, 1000, -500], 10, 4],
            "expected": [10, 25, 100, -50],
        },
        {
            "task_id": 5,
            "description": "attenuate_track_truncates_toward_zero",
            "property": "attenuate_track",
            "input": [[7, -7, 9, -9], 2, 4],
            "expected": [3, -3, 4, -4],
        },
        {
            "task_id": 5,
            "description": "attenuate_track_fractional_by_seven",
            "property": "attenuate_track",
            "input": [[100, -100, 50, -50, 1, -1, 1000, -1000], 7, 8],
            "expected": [14, -14, 7, -7, 0, 0, 142, -142],
        },
        {
            "task_id": 5,
            "description": "attenuate_track_near_sample_limits",
            "property": "attenuate_track",
            "input": [[32767, -32768, 16384, -16384], 2, 4],
            "expected": [16383, -16384, 8192, -8192],
        },
        {
            "task_id": 5,
            "description": "attenuate_track_by_five",
            "property": "attenuate_track",
            "input": [[12, -12, 5, -5, 17, -17, 100, -100], 5, 8],
            "expected": [2, -2, 1, -1, 3, -3, 20, -20],
        },
        {
            "task_id": 5,
            "description": "attenuate_track_all_silent",
            "property": "attenuate_track",
            "input": [[0, 0, 0, 0], 9, 4],
            "expected": [0, 0, 0, 0],
        },
    ]


def array_literal(numbers):
    return str(list(numbers)).replace("[", "{").replace("]", "}")


def int16_lane_asserts():
    return [
        f'TEST_ASSERT_EQUAL_INT16_MESSAGE(expected[{i}], result[{i}], "The 16-bit sample at lane {i} is different from expected");'
        for i in range(8)
    ]


def uint8_lane_asserts():
    return [
        f'TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[{i}], result[{i}], "The 8-bit value at lane {i} is different from expected");'
        for i in range(16)
    ]


def gen_func_body(prop, inp, expected):
    str_list = []
    if prop == "mix_tracks":
        str_list.append(
            f"alignas(16) const int16_t track_a[8] = {array_literal(inp[0])};"
        )
        str_list.append(
            f"alignas(16) const int16_t track_b[8] = {array_literal(inp[1])};"
        )
        str_list.append("alignas(16) int16_t result[8];")
        str_list.append("mix_tracks(result, track_a, track_b);")
        str_list.append(f"const int16_t expected[8] = {array_literal(expected)};")
        str_list.extend(int16_lane_asserts())
    elif prop == "remove_bleed":
        str_list.append("const char x1 = 'X';")
        str_list.append("(void)x1;")
        str_list.append("alignas(2) int16_t result[8];")
        str_list.append(
            f"alignas(16) const int16_t track[8] = {array_literal(inp[0])};"
        )
        str_list.append("const char x2 = 'X';")
        str_list.append("(void)x2;")
        str_list.append(f"alignas(2) const int16_t bleed[8] = {array_literal(inp[1])};")
        str_list.append("remove_bleed(result, track, bleed);")
        str_list.append(f"const int16_t expected[8] = {array_literal(expected)};")
        str_list.extend(int16_lane_asserts())
    elif prop == "combine_meters":
        str_list.append(
            f"alignas(16) const uint8_t meter_a[16] = {array_literal(inp[0])};"
        )
        str_list.append(
            f"alignas(16) const uint8_t meter_b[16] = {array_literal(inp[1])};"
        )
        str_list.append("alignas(16) uint8_t result[16];")
        str_list.append("combine_meters(result, meter_a, meter_b);")
        str_list.append(f"const uint8_t expected[16] = {array_literal(expected)};")
        str_list.extend(uint8_lane_asserts())
    elif prop == "apply_fade":
        n = inp[2]
        str_list.append(
            f"alignas(16) const int16_t track[{n}] = {array_literal(inp[0])};"
        )
        str_list.append(
            f"alignas(16) const int16_t gains[{n}] = {array_literal(inp[1])};"
        )
        str_list.append(f"alignas(16) int16_t result[{n}];")
        str_list.append(f"apply_fade(result, track, gains, {n});")
        str_list.append(f"const int16_t expected[{n}] = {array_literal(expected)};")
        str_list.append(
            'TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected), "The sequence of scaled samples is different from expected");'
        )
    elif prop == "attenuate_track":
        n = inp[2]
        d = inp[1]
        str_list.append(
            f"alignas(16) const int16_t samples[{n}] = {array_literal(inp[0])};"
        )
        str_list.append(
            f"alignas(16) const int32_t divisor[4] = {array_literal([d, d, d, d])};"
        )
        str_list.append(f"alignas(16) int32_t result[{n}];")
        str_list.append(f"attenuate_track(result, samples, divisor, {n});")
        str_list.append(f"const int32_t expected[{n}] = {array_literal(expected)};")
        str_list.append(
            'TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, result, ARRAY_SIZE(expected), "The sequence of attenuated samples is different from expected");'
        )
    return "\n".join(str_list)
