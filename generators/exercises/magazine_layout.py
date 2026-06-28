FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stdint.h>

extern void format_metrics(int64_t out[8]);
extern void reset_galley(uint8_t page[], int64_t length);
extern void column_offsets(int64_t out[], int64_t margin);
extern void standing_headers(uint8_t out[], int64_t pitch);
extern void frame_page(uint8_t page[], int64_t width);

extern uint64_t reg_before[16];
extern uint64_t reg_after[16];
extern void probe_fill_run(void);
extern void probe_lay_columns(void);
extern void probe_set_header(void);
extern uint64_t counter_is_rcx(void);
"""

REG_NAMES = [
    "rax",
    "rbx",
    "rcx",
    "rdx",
    "rsi",
    "rdi",
    "rbp",
    "rsp",
    "r8",
    "r9",
    "r10",
    "r11",
    "r12",
    "r13",
    "r14",
    "r15",
]

SPACE = 0x20  # ' '
RULE = 0x3D  # '='
RULE_WIDTH = 4

COLUMN_STRIDE = 18
COLUMN_COUNT = 4

PLAIN = 0x2E  # '.'
RULED = 0x2D  # '-'
BOXED = 0x23  # '#'


def _metrics():
    return [COLUMN_COUNT, COLUMN_STRIDE, SPACE, RULE, RULE_WIDTH, PLAIN, RULED, BOXED]


def _galley(length):
    return [SPACE] * length


def _offsets(margin):
    return [margin + i * COLUMN_STRIDE for i in range(COLUMN_COUNT)]


def _headers(pitch):
    out = [0] * (2 * pitch + 1)
    out[0] = PLAIN
    out[pitch] = RULED
    out[2 * pitch] = BOXED
    return out


def _frame(width):
    return [RULE] * RULE_WIDTH + [SPACE] * (width - RULE_WIDTH)


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "named_format_constants",
            "property": "format_metrics",
            "input": [],
            "expected": _metrics(),
        },
        {
            "task_id": 2,
            "description": "fill_run_one_line",
            "property": "reset_galley",
            "input": [16],
            "expected": _galley(16),
        },
        {
            "task_id": 2,
            "description": "fill_run_short_line",
            "property": "reset_galley",
            "input": [1],
            "expected": _galley(1),
        },
        {
            "task_id": 2,
            "description": "fill_run_odd_length",
            "property": "reset_galley",
            "input": [13],
            "expected": _galley(13),
        },
        {
            "task_id": 2,
            "description": "fill_run_full_column",
            "property": "reset_galley",
            "input": [40],
            "expected": _galley(40),
        },
        {
            "task_id": 2,
            "description": "fill_run_twice_exact_rule",
            "property": "frame_page",
            "input": [4],
            "expected": _frame(4),
        },
        {
            "task_id": 2,
            "description": "fill_run_twice_short_line",
            "property": "frame_page",
            "input": [8],
            "expected": _frame(8),
        },
        {
            "task_id": 2,
            "description": "fill_run_twice_full_line",
            "property": "frame_page",
            "input": [40],
            "expected": _frame(40),
        },
        {
            "task_id": 2,
            "description": "fill_run_twice_odd_length",
            "property": "frame_page",
            "input": [13],
            "expected": _frame(13),
        },
        {
            "task_id": 2,
            "description": "fill_run_zero_count_writes_nothing",
            "property": "count_zero",
            "input": [],
            "expected": [],
        },
        {
            "task_id": 2,
            "description": "counter_names_rcx",
            "property": "counter_alias",
            "input": [],
            "expected": [],
        },
        {
            "task_id": 2,
            "description": "fill_run_preserves_other_registers",
            "property": "clobber",
            "input": ["fill_run"],
            "expected": [2],
        },
        {
            "task_id": 3,
            "description": "lay_columns_flush_margin",
            "property": "column_offsets",
            "input": [0],
            "expected": _offsets(0),
        },
        {
            "task_id": 3,
            "description": "lay_columns_indented",
            "property": "column_offsets",
            "input": [3],
            "expected": _offsets(3),
        },
        {
            "task_id": 3,
            "description": "lay_columns_wide_margin",
            "property": "column_offsets",
            "input": [100],
            "expected": _offsets(100),
        },
        {
            "task_id": 3,
            "description": "lay_columns_preserves_other_registers",
            "property": "clobber",
            "input": ["lay_columns"],
            "expected": [8, 9],
        },
        {
            "task_id": 4,
            "description": "set_header_tight_pitch",
            "property": "standing_headers",
            "input": [1],
            "expected": _headers(1),
        },
        {
            "task_id": 4,
            "description": "set_header_section_pitch",
            "property": "standing_headers",
            "input": [4],
            "expected": _headers(4),
        },
        {
            "task_id": 4,
            "description": "set_header_wide_pitch",
            "property": "standing_headers",
            "input": [8],
            "expected": _headers(8),
        },
        {
            "task_id": 4,
            "description": "set_header_preserves_all_registers",
            "property": "clobber",
            "input": ["set_header"],
            "expected": [],
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
    if prop == "format_metrics":
        s.append("int64_t result[8] = {0};")
        s.append("format_metrics(result);")
        s.append(f"const int64_t expected[8] = {array_literal(expected)};")
        s.extend(elem_asserts("INT64", "format constant", 8))
    elif prop == "reset_galley":
        length = inp[0]
        s.append(f"uint8_t result[{length}] = {{0}};")
        s.append(f"reset_galley(result, {length});")
        s.append(f"const uint8_t expected[{length}] = {array_literal(expected)};")
        s.extend(elem_asserts("UINT8", "fill_run byte", length))
    elif prop == "column_offsets":
        margin = inp[0]
        s.append("int64_t result[4] = {0};")
        s.append(f"column_offsets(result, {margin});")
        s.append(f"const int64_t expected[4] = {array_literal(expected)};")
        s.extend(elem_asserts("INT64", "lay_columns offset", 4))
    elif prop == "standing_headers":
        pitch = inp[0]
        n = 2 * pitch + 1
        s.append(f"uint8_t result[{n}] = {{0}};")
        s.append(f"standing_headers(result, {pitch});")
        s.append(f"const uint8_t expected[{n}] = {array_literal(expected)};")
        s.extend(elem_asserts("UINT8", "set_header byte", n))
    elif prop == "frame_page":
        width = inp[0]
        s.append(f"uint8_t result[{width}] = {{0}};")
        s.append(f"frame_page(result, {width});")
        s.append(f"const uint8_t expected[{width}] = {array_literal(expected)};")
        s.extend(elem_asserts("UINT8", "fill_run byte", width))
    elif prop == "clobber":
        macro = inp[0]
        allowed = set(expected) | {7}  # rsp is never part of the contract
        s.append(f"probe_{macro}();")
        for i in range(16):
            if i in allowed:
                continue
            s.append(
                f"TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[{i}], reg_after[{i}], "
                f'"{macro} clobbered {REG_NAMES[i]}, which it must preserve");'
            )
    elif prop == "count_zero":
        s.append("uint8_t page[8] = {0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB};")
        s.append("reset_galley(page, 0);")
        for i in range(8):
            s.append(
                f"TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xAB, page[{i}], "
                f'"fill_run with a count of 0 must write nothing");'
            )
    elif prop == "counter_alias":
        s.append(
            "TEST_ASSERT_EQUAL_HEX64_MESSAGE(0x1234567890ABCDEFULL, counter_is_rcx(), "
            '"COUNTER must be defined to name the rcx register");'
        )
    return "\n".join(s)
