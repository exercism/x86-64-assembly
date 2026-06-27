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

void setUp(void) {
}

void tearDown(void) {
}

// TASK: 1
void test_named_format_constants(void) {
    int64_t result[8] = {0};
    format_metrics(result);
    const int64_t expected[8] = {4, 18, 32, 61, 4, 46, 45, 35};
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[0], result[0], "The format constant at index 0 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[1], result[1], "The format constant at index 1 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[2], result[2], "The format constant at index 2 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[3], result[3], "The format constant at index 3 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[4], result[4], "The format constant at index 4 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[5], result[5], "The format constant at index 5 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[6], result[6], "The format constant at index 6 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[7], result[7], "The format constant at index 7 is different from expected");
}

// TASK: 2
void test_fill_run_one_line(void) {
    TEST_IGNORE();
    uint8_t result[16] = {0};
    reset_galley(result, 16);
    const uint8_t expected[16] = {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The fill_run byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The fill_run byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The fill_run byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The fill_run byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The fill_run byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The fill_run byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The fill_run byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The fill_run byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The fill_run byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The fill_run byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The fill_run byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The fill_run byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The fill_run byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The fill_run byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The fill_run byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The fill_run byte at index 15 is different from expected");
}

void test_fill_run_short_line(void) {
    TEST_IGNORE();
    uint8_t result[1] = {0};
    reset_galley(result, 1);
    const uint8_t expected[1] = {32};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The fill_run byte at index 0 is different from expected");
}

void test_fill_run_odd_length(void) {
    TEST_IGNORE();
    uint8_t result[13] = {0};
    reset_galley(result, 13);
    const uint8_t expected[13] = {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The fill_run byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The fill_run byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The fill_run byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The fill_run byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The fill_run byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The fill_run byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The fill_run byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The fill_run byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The fill_run byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The fill_run byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The fill_run byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The fill_run byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The fill_run byte at index 12 is different from expected");
}

void test_fill_run_full_column(void) {
    TEST_IGNORE();
    uint8_t result[40] = {0};
    reset_galley(result, 40);
    const uint8_t expected[40] = {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
                                  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The fill_run byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The fill_run byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The fill_run byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The fill_run byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The fill_run byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The fill_run byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The fill_run byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The fill_run byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The fill_run byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The fill_run byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The fill_run byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The fill_run byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The fill_run byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The fill_run byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The fill_run byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The fill_run byte at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The fill_run byte at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The fill_run byte at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The fill_run byte at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The fill_run byte at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The fill_run byte at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The fill_run byte at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The fill_run byte at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The fill_run byte at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The fill_run byte at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The fill_run byte at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The fill_run byte at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The fill_run byte at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The fill_run byte at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The fill_run byte at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The fill_run byte at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The fill_run byte at index 31 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[32], result[32], "The fill_run byte at index 32 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[33], result[33], "The fill_run byte at index 33 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[34], result[34], "The fill_run byte at index 34 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[35], result[35], "The fill_run byte at index 35 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[36], result[36], "The fill_run byte at index 36 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[37], result[37], "The fill_run byte at index 37 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[38], result[38], "The fill_run byte at index 38 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[39], result[39], "The fill_run byte at index 39 is different from expected");
}

void test_fill_run_twice_exact_rule(void) {
    TEST_IGNORE();
    uint8_t result[4] = {0};
    frame_page(result, 4);
    const uint8_t expected[4] = {61, 61, 61, 61};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The fill_run byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The fill_run byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The fill_run byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The fill_run byte at index 3 is different from expected");
}

void test_fill_run_twice_short_line(void) {
    TEST_IGNORE();
    uint8_t result[8] = {0};
    frame_page(result, 8);
    const uint8_t expected[8] = {61, 61, 61, 61, 32, 32, 32, 32};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The fill_run byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The fill_run byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The fill_run byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The fill_run byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The fill_run byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The fill_run byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The fill_run byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The fill_run byte at index 7 is different from expected");
}

void test_fill_run_twice_full_line(void) {
    TEST_IGNORE();
    uint8_t result[40] = {0};
    frame_page(result, 40);
    const uint8_t expected[40] = {61, 61, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
                                  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The fill_run byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The fill_run byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The fill_run byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The fill_run byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The fill_run byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The fill_run byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The fill_run byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The fill_run byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The fill_run byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The fill_run byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The fill_run byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The fill_run byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The fill_run byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The fill_run byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The fill_run byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The fill_run byte at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The fill_run byte at index 16 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[17], result[17], "The fill_run byte at index 17 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[18], result[18], "The fill_run byte at index 18 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[19], result[19], "The fill_run byte at index 19 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[20], result[20], "The fill_run byte at index 20 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[21], result[21], "The fill_run byte at index 21 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[22], result[22], "The fill_run byte at index 22 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[23], result[23], "The fill_run byte at index 23 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[24], result[24], "The fill_run byte at index 24 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[25], result[25], "The fill_run byte at index 25 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[26], result[26], "The fill_run byte at index 26 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[27], result[27], "The fill_run byte at index 27 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[28], result[28], "The fill_run byte at index 28 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[29], result[29], "The fill_run byte at index 29 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[30], result[30], "The fill_run byte at index 30 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[31], result[31], "The fill_run byte at index 31 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[32], result[32], "The fill_run byte at index 32 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[33], result[33], "The fill_run byte at index 33 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[34], result[34], "The fill_run byte at index 34 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[35], result[35], "The fill_run byte at index 35 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[36], result[36], "The fill_run byte at index 36 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[37], result[37], "The fill_run byte at index 37 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[38], result[38], "The fill_run byte at index 38 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[39], result[39], "The fill_run byte at index 39 is different from expected");
}

void test_fill_run_twice_odd_length(void) {
    TEST_IGNORE();
    uint8_t result[13] = {0};
    frame_page(result, 13);
    const uint8_t expected[13] = {61, 61, 61, 61, 32, 32, 32, 32, 32, 32, 32, 32, 32};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The fill_run byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The fill_run byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The fill_run byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The fill_run byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The fill_run byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The fill_run byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The fill_run byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The fill_run byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The fill_run byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The fill_run byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The fill_run byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The fill_run byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The fill_run byte at index 12 is different from expected");
}

void test_fill_run_zero_count_writes_nothing(void) {
    TEST_IGNORE();
    uint8_t page[8] = {0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB};
    reset_galley(page, 0);
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xAB, page[0], "fill_run with a count of 0 must write nothing");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xAB, page[1], "fill_run with a count of 0 must write nothing");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xAB, page[2], "fill_run with a count of 0 must write nothing");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xAB, page[3], "fill_run with a count of 0 must write nothing");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xAB, page[4], "fill_run with a count of 0 must write nothing");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xAB, page[5], "fill_run with a count of 0 must write nothing");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xAB, page[6], "fill_run with a count of 0 must write nothing");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xAB, page[7], "fill_run with a count of 0 must write nothing");
}

void test_counter_names_rcx(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(0x1234567890ABCDEFULL, counter_is_rcx(), "COUNTER must be defined to name the rcx register");
}

void test_fill_run_preserves_other_registers(void) {
    TEST_IGNORE();
    probe_fill_run();
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[0], reg_after[0], "fill_run clobbered rax, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[1], reg_after[1], "fill_run clobbered rbx, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[3], reg_after[3], "fill_run clobbered rdx, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[4], reg_after[4], "fill_run clobbered rsi, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[5], reg_after[5], "fill_run clobbered rdi, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[6], reg_after[6], "fill_run clobbered rbp, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[8], reg_after[8], "fill_run clobbered r8, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[9], reg_after[9], "fill_run clobbered r9, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[10], reg_after[10], "fill_run clobbered r10, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[11], reg_after[11], "fill_run clobbered r11, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[12], reg_after[12], "fill_run clobbered r12, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[13], reg_after[13], "fill_run clobbered r13, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[14], reg_after[14], "fill_run clobbered r14, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[15], reg_after[15], "fill_run clobbered r15, which it must preserve");
}

// TASK: 3
void test_lay_columns_flush_margin(void) {
    TEST_IGNORE();
    int64_t result[4] = {0};
    column_offsets(result, 0);
    const int64_t expected[4] = {0, 18, 36, 54};
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[0], result[0], "The lay_columns offset at index 0 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[1], result[1], "The lay_columns offset at index 1 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[2], result[2], "The lay_columns offset at index 2 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[3], result[3], "The lay_columns offset at index 3 is different from expected");
}

void test_lay_columns_indented(void) {
    TEST_IGNORE();
    int64_t result[4] = {0};
    column_offsets(result, 3);
    const int64_t expected[4] = {3, 21, 39, 57};
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[0], result[0], "The lay_columns offset at index 0 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[1], result[1], "The lay_columns offset at index 1 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[2], result[2], "The lay_columns offset at index 2 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[3], result[3], "The lay_columns offset at index 3 is different from expected");
}

void test_lay_columns_wide_margin(void) {
    TEST_IGNORE();
    int64_t result[4] = {0};
    column_offsets(result, 100);
    const int64_t expected[4] = {100, 118, 136, 154};
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[0], result[0], "The lay_columns offset at index 0 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[1], result[1], "The lay_columns offset at index 1 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[2], result[2], "The lay_columns offset at index 2 is different from expected");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(expected[3], result[3], "The lay_columns offset at index 3 is different from expected");
}

void test_lay_columns_preserves_other_registers(void) {
    TEST_IGNORE();
    probe_lay_columns();
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[0], reg_after[0], "lay_columns clobbered rax, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[1], reg_after[1], "lay_columns clobbered rbx, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[2], reg_after[2], "lay_columns clobbered rcx, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[3], reg_after[3], "lay_columns clobbered rdx, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[4], reg_after[4], "lay_columns clobbered rsi, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[5], reg_after[5], "lay_columns clobbered rdi, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[6], reg_after[6], "lay_columns clobbered rbp, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[10], reg_after[10], "lay_columns clobbered r10, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[11], reg_after[11], "lay_columns clobbered r11, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[12], reg_after[12], "lay_columns clobbered r12, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[13], reg_after[13], "lay_columns clobbered r13, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[14], reg_after[14], "lay_columns clobbered r14, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[15], reg_after[15], "lay_columns clobbered r15, which it must preserve");
}

// TASK: 4
void test_set_header_tight_pitch(void) {
    TEST_IGNORE();
    uint8_t result[3] = {0};
    standing_headers(result, 1);
    const uint8_t expected[3] = {46, 45, 35};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The set_header byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The set_header byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The set_header byte at index 2 is different from expected");
}

void test_set_header_section_pitch(void) {
    TEST_IGNORE();
    uint8_t result[9] = {0};
    standing_headers(result, 4);
    const uint8_t expected[9] = {46, 0, 0, 0, 45, 0, 0, 0, 35};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The set_header byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The set_header byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The set_header byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The set_header byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The set_header byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The set_header byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The set_header byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The set_header byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The set_header byte at index 8 is different from expected");
}

void test_set_header_wide_pitch(void) {
    TEST_IGNORE();
    uint8_t result[17] = {0};
    standing_headers(result, 8);
    const uint8_t expected[17] = {46, 0, 0, 0, 0, 0, 0, 0, 45, 0, 0, 0, 0, 0, 0, 0, 35};
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[0], result[0], "The set_header byte at index 0 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[1], result[1], "The set_header byte at index 1 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[2], result[2], "The set_header byte at index 2 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[3], result[3], "The set_header byte at index 3 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[4], result[4], "The set_header byte at index 4 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[5], result[5], "The set_header byte at index 5 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[6], result[6], "The set_header byte at index 6 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[7], result[7], "The set_header byte at index 7 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[8], result[8], "The set_header byte at index 8 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[9], result[9], "The set_header byte at index 9 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[10], result[10], "The set_header byte at index 10 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[11], result[11], "The set_header byte at index 11 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[12], result[12], "The set_header byte at index 12 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[13], result[13], "The set_header byte at index 13 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[14], result[14], "The set_header byte at index 14 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[15], result[15], "The set_header byte at index 15 is different from expected");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected[16], result[16], "The set_header byte at index 16 is different from expected");
}

void test_set_header_preserves_all_registers(void) {
    TEST_IGNORE();
    probe_set_header();
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[0], reg_after[0], "set_header clobbered rax, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[1], reg_after[1], "set_header clobbered rbx, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[2], reg_after[2], "set_header clobbered rcx, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[3], reg_after[3], "set_header clobbered rdx, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[4], reg_after[4], "set_header clobbered rsi, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[5], reg_after[5], "set_header clobbered rdi, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[6], reg_after[6], "set_header clobbered rbp, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[8], reg_after[8], "set_header clobbered r8, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[9], reg_after[9], "set_header clobbered r9, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[10], reg_after[10], "set_header clobbered r10, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[11], reg_after[11], "set_header clobbered r11, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[12], reg_after[12], "set_header clobbered r12, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[13], reg_after[13], "set_header clobbered r13, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[14], reg_after[14], "set_header clobbered r14, which it must preserve");
    TEST_ASSERT_EQUAL_HEX64_MESSAGE(reg_before[15], reg_after[15], "set_header clobbered r15, which it must preserve");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_named_format_constants);
    RUN_TEST(test_fill_run_one_line);
    RUN_TEST(test_fill_run_short_line);
    RUN_TEST(test_fill_run_odd_length);
    RUN_TEST(test_fill_run_full_column);
    RUN_TEST(test_fill_run_twice_exact_rule);
    RUN_TEST(test_fill_run_twice_short_line);
    RUN_TEST(test_fill_run_twice_full_line);
    RUN_TEST(test_fill_run_twice_odd_length);
    RUN_TEST(test_fill_run_zero_count_writes_nothing);
    RUN_TEST(test_counter_names_rcx);
    RUN_TEST(test_fill_run_preserves_other_registers);
    RUN_TEST(test_lay_columns_flush_margin);
    RUN_TEST(test_lay_columns_indented);
    RUN_TEST(test_lay_columns_wide_margin);
    RUN_TEST(test_lay_columns_preserves_other_registers);
    RUN_TEST(test_set_header_tight_pitch);
    RUN_TEST(test_set_header_section_pitch);
    RUN_TEST(test_set_header_wide_pitch);
    RUN_TEST(test_set_header_preserves_all_registers);
    return UNITY_END();
}
