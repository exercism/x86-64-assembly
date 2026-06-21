FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdalign.h>
#include <stdint.h>

extern void to_display_order(uint8_t result[], const uint8_t pixels[], uint64_t block_count);
extern void fill_region(uint8_t result[], const uint8_t color[4], uint64_t block_count);
extern void weave_scanlines(uint8_t result[32], const uint8_t first[16], const uint8_t second[16]);
extern void pack_samples(uint8_t result[16], const int16_t first[8], const int16_t second[8]);
extern void split_coordinates(float xs[4], float ys[4], const float first[4], const float second[4]);
"""


def _display_order(pixels):
    out = []
    for base in range(0, len(pixels), 4):
        r, g, b, a = pixels[base : base + 4]
        out.extend([b, g, r, a])
    return out


def _fill(color, block_count):
    return list(color) * (4 * block_count)


def _weave(first, second):
    out = []
    for a, b in zip(first, second):
        out.extend([a, b])
    return out


def _clamp_u8(x):
    return 0 if x < 0 else 255 if x > 255 else x


def _pack(first, second):
    return [_clamp_u8(x) for x in first] + [_clamp_u8(x) for x in second]


def _split(first, second):
    xs = [first[0], first[2], second[0], second[2]]
    ys = [first[1], first[3], second[1], second[3]]
    return [xs, ys]


_B0 = [200, 64, 32, 255, 10, 20, 30, 40, 0, 0, 0, 255, 12, 34, 56, 78]
_B1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
_B2 = [255, 0, 0, 255, 0, 255, 0, 128, 0, 0, 255, 64, 100, 110, 120, 130]
_GRAY = [50, 60, 50, 255, 0, 9, 0, 1, 128, 7, 128, 64, 200, 1, 200, 2]


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "display_order_example_two_blocks",
            "property": "to_display_order",
            "input": [_B0 + _B1],
            "expected": _display_order(_B0 + _B1),
        },
        {
            "task_id": 1,
            "description": "display_order_single_block",
            "property": "to_display_order",
            "input": [_B0],
            "expected": _display_order(_B0),
        },
        {
            "task_id": 1,
            "description": "display_order_three_blocks",
            "property": "to_display_order",
            "input": [_B0 + _B1 + _B2],
            "expected": _display_order(_B0 + _B1 + _B2),
        },
        {
            "task_id": 1,
            "description": "display_order_red_equals_blue_unchanged",
            "property": "to_display_order",
            "input": [_GRAY + _GRAY],
            "expected": _display_order(_GRAY + _GRAY),
        },
        {
            "task_id": 2,
            "description": "fill_region_example_two_blocks",
            "property": "fill_region",
            "input": [[18, 52, 86, 120], 2],
            "expected": _fill([18, 52, 86, 120], 2),
        },
        {
            "task_id": 2,
            "description": "fill_region_single_block",
            "property": "fill_region",
            "input": [[1, 2, 3, 4], 1],
            "expected": _fill([1, 2, 3, 4], 1),
        },
        {
            "task_id": 2,
            "description": "fill_region_three_blocks_transparent_black",
            "property": "fill_region",
            "input": [[0, 0, 0, 0], 3],
            "expected": _fill([0, 0, 0, 0], 3),
        },
        {
            "task_id": 2,
            "description": "fill_region_opaque_white_two_blocks",
            "property": "fill_region",
            "input": [[255, 255, 255, 255], 2],
            "expected": _fill([255, 255, 255, 255], 2),
        },
        {
            "task_id": 3,
            "description": "weave_scanlines_example",
            "property": "weave_scanlines",
            "input": [
                [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
                [
                    100,
                    101,
                    102,
                    103,
                    104,
                    105,
                    106,
                    107,
                    108,
                    109,
                    110,
                    111,
                    112,
                    113,
                    114,
                    115,
                ],
            ],
            "expected": _weave(
                [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
                [
                    100,
                    101,
                    102,
                    103,
                    104,
                    105,
                    106,
                    107,
                    108,
                    109,
                    110,
                    111,
                    112,
                    113,
                    114,
                    115,
                ],
            ),
        },
        {
            "task_id": 3,
            "description": "weave_scanlines_alternating_extremes",
            "property": "weave_scanlines",
            "input": [[0] * 16, [255] * 16],
            "expected": _weave([0] * 16, [255] * 16),
        },
        {
            "task_id": 3,
            "description": "weave_scanlines_high_half_distinct",
            "property": "weave_scanlines",
            "input": [
                [10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25],
                [
                    200,
                    201,
                    202,
                    203,
                    204,
                    205,
                    206,
                    207,
                    208,
                    209,
                    210,
                    211,
                    212,
                    213,
                    214,
                    215,
                ],
            ],
            "expected": _weave(
                [10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25],
                [
                    200,
                    201,
                    202,
                    203,
                    204,
                    205,
                    206,
                    207,
                    208,
                    209,
                    210,
                    211,
                    212,
                    213,
                    214,
                    215,
                ],
            ),
        },
        {
            "task_id": 4,
            "description": "pack_samples_example",
            "property": "pack_samples",
            "input": [
                [300, -5, 128, 255, 0, 400, 64, 200],
                [255, 256, -1, 100, 50, 1000, 7, 0],
            ],
            "expected": _pack(
                [300, -5, 128, 255, 0, 400, 64, 200],
                [255, 256, -1, 100, 50, 1000, 7, 0],
            ),
        },
        {
            "task_id": 4,
            "description": "pack_samples_all_in_range",
            "property": "pack_samples",
            "input": [
                [0, 1, 64, 127, 128, 200, 254, 255],
                [10, 20, 30, 40, 50, 60, 70, 80],
            ],
            "expected": _pack(
                [0, 1, 64, 127, 128, 200, 254, 255],
                [10, 20, 30, 40, 50, 60, 70, 80],
            ),
        },
        {
            "task_id": 4,
            "description": "pack_samples_all_clamp_high",
            "property": "pack_samples",
            "input": [
                [256, 300, 1000, 32767, 256, 512, 700, 999],
                [256, 257, 258, 259, 260, 5000, 9000, 32000],
            ],
            "expected": _pack(
                [256, 300, 1000, 32767, 256, 512, 700, 999],
                [256, 257, 258, 259, 260, 5000, 9000, 32000],
            ),
        },
        {
            "task_id": 4,
            "description": "pack_samples_all_clamp_low",
            "property": "pack_samples",
            "input": [
                [-1, -2, -100, -32768, -5, -50, -500, -9000],
                [-1, -1, -1, -1, -1, -1, -1, -1],
            ],
            "expected": _pack(
                [-1, -2, -100, -32768, -5, -50, -500, -9000],
                [-1, -1, -1, -1, -1, -1, -1, -1],
            ),
        },
        {
            "task_id": 4,
            "description": "pack_samples_boundaries",
            "property": "pack_samples",
            "input": [
                [-1, 0, 1, 254, 255, 256, 128, 200],
                [0, 255, -1, 256, 127, 128, 300, -300],
            ],
            "expected": _pack(
                [-1, 0, 1, 254, 255, 256, 128, 200],
                [0, 255, -1, 256, 127, 128, 300, -300],
            ),
        },
        {
            "task_id": 5,
            "description": "split_coordinates_example",
            "property": "split_coordinates",
            "input": [
                ["0.0f", "0.5f", "1.0f", "1.5f"],
                ["2.0f", "2.5f", "3.0f", "3.5f"],
            ],
            "expected": _split(
                ["0.0f", "0.5f", "1.0f", "1.5f"], ["2.0f", "2.5f", "3.0f", "3.5f"]
            ),
        },
        {
            "task_id": 5,
            "description": "split_coordinates_negative",
            "property": "split_coordinates",
            "input": [
                ["-1.0f", "-2.0f", "3.0f", "4.0f"],
                ["-5.0f", "6.0f", "-7.0f", "8.0f"],
            ],
            "expected": _split(
                ["-1.0f", "-2.0f", "3.0f", "4.0f"],
                ["-5.0f", "6.0f", "-7.0f", "8.0f"],
            ),
        },
        {
            "task_id": 5,
            "description": "split_coordinates_distinct_streams",
            "property": "split_coordinates",
            "input": [
                ["10.0f", "11.0f", "12.0f", "13.0f"],
                ["20.0f", "21.0f", "22.0f", "23.0f"],
            ],
            "expected": _split(
                ["10.0f", "11.0f", "12.0f", "13.0f"],
                ["20.0f", "21.0f", "22.0f", "23.0f"],
            ),
        },
        {
            "task_id": 5,
            "description": "split_coordinates_fractional",
            "property": "split_coordinates",
            "input": [
                ["0.25f", "0.5f", "0.75f", "1.25f"],
                ["1.5f", "1.75f", "2.0f", "2.5f"],
            ],
            "expected": _split(
                ["0.25f", "0.5f", "0.75f", "1.25f"],
                ["1.5f", "1.75f", "2.0f", "2.5f"],
            ),
        },
    ]


def array_literal(numbers):
    return str(list(numbers)).replace("[", "{").replace("]", "}").replace("'", "")


def elem_asserts(assert_kind, message_kind, count):
    return [
        f'TEST_ASSERT_EQUAL_{assert_kind}_MESSAGE(expected[{i}], result[{i}], "The {message_kind} at index {i} is different from expected");'
        for i in range(count)
    ]


def gen_func_body(prop, inp, expected):
    s = []
    if prop == "to_display_order":
        pixels = inp[0]
        n = len(pixels)
        block_count = n // 16
        s.append(f"alignas(16) const uint8_t pixels[{n}] = {array_literal(pixels)};")
        s.append(f"alignas(16) uint8_t result[{n}];")
        s.append(f"to_display_order(result, pixels, {block_count});")
        s.append(f"const uint8_t expected[{n}] = {array_literal(expected)};")
        s.extend(elem_asserts("UINT8", "converted byte", n))
    elif prop == "fill_region":
        color, block_count = inp[0], inp[1]
        n = 16 * block_count
        s.append(f"alignas(16) const uint8_t color[4] = {array_literal(color)};")
        s.append(f"alignas(16) uint8_t result[{n}];")
        s.append(f"fill_region(result, color, {block_count});")
        s.append(f"const uint8_t expected[{n}] = {array_literal(expected)};")
        s.extend(elem_asserts("UINT8", "filled byte", n))
    elif prop == "weave_scanlines":
        s.append(f"alignas(16) const uint8_t first[16] = {array_literal(inp[0])};")
        s.append(f"alignas(16) const uint8_t second[16] = {array_literal(inp[1])};")
        s.append("alignas(16) uint8_t result[32];")
        s.append("weave_scanlines(result, first, second);")
        s.append(f"const uint8_t expected[32] = {array_literal(expected)};")
        s.extend(elem_asserts("UINT8", "woven sample", 32))
    elif prop == "pack_samples":
        s.append(f"alignas(16) const int16_t first[8] = {array_literal(inp[0])};")
        s.append(f"alignas(16) const int16_t second[8] = {array_literal(inp[1])};")
        s.append("alignas(16) uint8_t result[16];")
        s.append("pack_samples(result, first, second);")
        s.append(f"const uint8_t expected[16] = {array_literal(expected)};")
        s.extend(elem_asserts("UINT8", "packed sample", 16))
    elif prop == "split_coordinates":
        first, second = inp[0], inp[1]
        xs_expected, ys_expected = expected[0], expected[1]
        s.append(f"alignas(16) const float first[4] = {array_literal(first)};")
        s.append(f"alignas(16) const float second[4] = {array_literal(second)};")
        s.append("alignas(16) float xs[4];")
        s.append("alignas(16) float ys[4];")
        s.append("split_coordinates(xs, ys, first, second);")
        s.append(f"const float expected_xs[4] = {array_literal(xs_expected)};")
        s.append(f"const float expected_ys[4] = {array_literal(ys_expected)};")
        for i in range(4):
            s.append(
                f'TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_xs[{i}], xs[{i}], "The x coordinate at index {i} is different from expected");'
            )
        for i in range(4):
            s.append(
                f'TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected_ys[{i}], ys[{i}], "The y coordinate at index {i} is different from expected");'
            )
    return "\n".join(s)
