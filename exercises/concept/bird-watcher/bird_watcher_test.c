#include "vendor/unity.h"

#include <stdint.h>
#include <stdio.h>

#define BUFFER_SIZE 80

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

static void generate_bitstring(char buffer[], uint64_t number) {
    size_t j = 0;
    buffer[j++] = '{';
    for (size_t i = 0; i < 8; ++i) {
        uint8_t byte = number & 255;
        number >>= 8;

        if (!byte) {
            buffer[j++] = '0';
            buffer[j++] = ',';
            buffer[j++] = ' ';
            continue;
        }

        char temp[4] = {0};
        size_t temp_idx = 4;

        while (byte) {
            const uint8_t digit = byte % 10;
            byte /= 10;
            temp[--temp_idx] = digit + '0';
        }

        for (; temp_idx < 4; ++temp_idx) {
            buffer[j++] = temp[temp_idx];
        }

        buffer[j++] = ',';
        buffer[j++] = ' ';
    }

    buffer[j - 2] = '}';
    buffer[j - 1] = 0;
}

void setUp(void) {
}

void tearDown(void) {
}

void test_last_week_default(void) {
    const uint64_t actual = last_week_counts();
    char exp_buffer_last[BUFFER_SIZE] = {0};
    char actual_buffer_last[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_last, 1134726115295744);
    generate_bitstring(actual_buffer_last, actual);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_last, actual_buffer_last, "Counts for last week are different than expected.");
}

void test_current_week_default(void) {
    TEST_IGNORE();
    current_week_t crt = current_week_counts();
    char exp_buffer_current[BUFFER_SIZE] = {0};
    char actual_buffer_current[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_current, 0);
    generate_bitstring(actual_buffer_current, crt.counts);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_current, actual_buffer_current, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(0, crt.length, "The number of counts is different than expected.");
}

void test_save_count_first_day(void) {
    TEST_IGNORE();
    save_count(5);
    const uint64_t actual = last_week_counts();
    char exp_buffer_last[BUFFER_SIZE] = {0};
    char actual_buffer_last[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_last, 1134726115295744);
    generate_bitstring(actual_buffer_last, actual);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_last, actual_buffer_last, "Counts for last week are different than expected.");
    current_week_t crt = current_week_counts();
    char exp_buffer_current[BUFFER_SIZE] = {0};
    char actual_buffer_current[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_current, 5);
    generate_bitstring(actual_buffer_current, crt.counts);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_current, actual_buffer_current, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, crt.length, "The number of counts is different than expected.");
}

void test_today_count_first_entry(void) {
    TEST_IGNORE();
    const uint8_t actual = today_count();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(5, actual, "Today's count is different than expected.");
}

void test_update_today_count_first_entry(void) {
    TEST_IGNORE();
    update_today_count(2);
    const uint8_t actual = today_count();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(7, actual, "Today's count is different than expected.");
}

void test_save_count_finish_week(void) {
    TEST_IGNORE();
    save_count(13);
    save_count(22);
    save_count(8);
    save_count(0);
    save_count(34);
    save_count(42);
    const uint64_t actual = last_week_counts();
    char exp_buffer_last[BUFFER_SIZE] = {0};
    char actual_buffer_last[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_last, 1134726115295744);
    generate_bitstring(actual_buffer_last, actual);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_last, actual_buffer_last, "Counts for last week are different than expected.");
    current_week_t crt = current_week_counts();
    char exp_buffer_current[BUFFER_SIZE] = {0};
    char actual_buffer_current[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_current, 11859332552854791);
    generate_bitstring(actual_buffer_current, crt.counts);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_current, actual_buffer_current, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, crt.length, "The number of counts is different than expected.");
}

void test_today_count_current_week(void) {
    TEST_IGNORE();
    const uint8_t actual = today_count();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(42, actual, "Today's count is different than expected.");
}

void test_update_today_count_current_week(void) {
    TEST_IGNORE();
    update_today_count(14);
    const uint8_t actual = today_count();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(56, actual, "Today's count is different than expected.");
}

void test_save_count_wrap_current_week(void) {
    TEST_IGNORE();
    save_count(12);
    const uint64_t actual = last_week_counts();
    char exp_buffer_last[BUFFER_SIZE] = {0};
    char actual_buffer_last[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_last, 15799982226803975);
    generate_bitstring(actual_buffer_last, actual);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_last, actual_buffer_last, "Counts for last week are different than expected.");
    current_week_t crt = current_week_counts();
    char exp_buffer_current[BUFFER_SIZE] = {0};
    char actual_buffer_current[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_current, 12);
    generate_bitstring(actual_buffer_current, crt.counts);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_current, actual_buffer_current, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, crt.length, "The number of counts is different than expected.");
}

void test_today_count_new_week(void) {
    TEST_IGNORE();
    const uint8_t actual = today_count();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(12, actual, "Today's count is different than expected.");
}

void test_update_today_count_new_week(void) {
    TEST_IGNORE();
    update_today_count(29);
    const uint8_t actual = today_count();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(41, actual, "Today's count is different than expected.");
}

void test_continuous_save_count(void) {
    TEST_IGNORE();
    save_count(45);
    save_count(12);
    save_count(3);
    save_count(9);
    save_count(0);
    save_count(2);
    save_count(4);
    save_count(8);
    save_count(7);
    save_count(2);
    save_count(3);
    save_count(4);
    save_count(26);
    save_count(32);
    save_count(5);
    save_count(6);
    save_count(1);
    save_count(19);
    const uint64_t actual = last_week_counts();
    char exp_buffer_last[BUFFER_SIZE] = {0};
    char actual_buffer_last[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_last, 7322760359905284);
    generate_bitstring(actual_buffer_last, actual);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_last, actual_buffer_last, "Counts for last week are different than expected.");
    current_week_t crt = current_week_counts();
    char exp_buffer_current[BUFFER_SIZE] = {0};
    char actual_buffer_current[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_current, 81621550368);
    generate_bitstring(actual_buffer_current, crt.counts);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_current, actual_buffer_current, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, crt.length, "The number of counts is different than expected.");
}

void test_save_count_finish_week_again(void) {
    TEST_IGNORE();
    save_count(1);
    save_count(7);
    const uint64_t actual = last_week_counts();
    char exp_buffer_last[BUFFER_SIZE] = {0};
    char actual_buffer_last[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_last, 7322760359905284);
    generate_bitstring(actual_buffer_last, actual);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_last, actual_buffer_last, "Counts for last week are different than expected.");
    current_week_t crt = current_week_counts();
    char exp_buffer_current[BUFFER_SIZE] = {0};
    char actual_buffer_current[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_current, 1971505970152736);
    generate_bitstring(actual_buffer_current, crt.counts);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_current, actual_buffer_current, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, crt.length, "The number of counts is different than expected.");
}

void test_update_week_count_one(void) {
    TEST_IGNORE();
    update_week_counts(321276659632387);
    const uint64_t actual = last_week_counts();
    char exp_buffer_last[BUFFER_SIZE] = {0};
    char actual_buffer_last[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_last, 1971505970152736);
    generate_bitstring(actual_buffer_last, actual);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_last, actual_buffer_last, "Counts for last week are different than expected.");
    current_week_t crt = current_week_counts();
    char exp_buffer_current[BUFFER_SIZE] = {0};
    char actual_buffer_current[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_current, 321276659632387);
    generate_bitstring(actual_buffer_current, crt.counts);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_current, actual_buffer_current, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, crt.length, "The number of counts is different than expected.");
}

void test_update_week_count_two(void) {
    TEST_IGNORE();
    update_week_counts(6796120059876119);
    const uint64_t actual = last_week_counts();
    char exp_buffer_last[BUFFER_SIZE] = {0};
    char actual_buffer_last[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_last, 321276659632387);
    generate_bitstring(actual_buffer_last, actual);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_last, actual_buffer_last, "Counts for last week are different than expected.");
    current_week_t crt = current_week_counts();
    char exp_buffer_current[BUFFER_SIZE] = {0};
    char actual_buffer_current[BUFFER_SIZE] = {0};
    generate_bitstring(exp_buffer_current, 6796120059876119);
    generate_bitstring(actual_buffer_current, crt.counts);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(exp_buffer_current, actual_buffer_current, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, crt.length, "The number of counts is different than expected.");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_last_week_default);
    RUN_TEST(test_current_week_default);
    RUN_TEST(test_save_count_first_day);
    RUN_TEST(test_today_count_first_entry);
    RUN_TEST(test_update_today_count_first_entry);
    RUN_TEST(test_save_count_finish_week);
    RUN_TEST(test_today_count_current_week);
    RUN_TEST(test_update_today_count_current_week);
    RUN_TEST(test_save_count_wrap_current_week);
    RUN_TEST(test_today_count_new_week);
    RUN_TEST(test_update_today_count_new_week);
    RUN_TEST(test_continuous_save_count);
    RUN_TEST(test_save_count_finish_week_again);
    RUN_TEST(test_update_week_count_one);
    RUN_TEST(test_update_week_count_two);
    return UNITY_END();
}
