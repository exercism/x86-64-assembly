#include "vendor/unity.h"

#include <stdint.h>

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

void setUp(void) {
}

void tearDown(void) {
}

void test_last_week_default(void) {
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(1134726115295744, today_count(), "Today's count is different than expected.");
}

void test_current_week_default(void) {
    TEST_IGNORE();
    current_week_t crt = current_week_counts();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(0, crt.counts, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(0, crt.length, "The number of counts is different than expected.");
}

void test_save_count_first_day(void) {
    TEST_IGNORE();
    save_count(5);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1134726115295744, last_week_counts(), "Counts for last week are different than expected.");

    current_week_t crt = current_week_counts();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, crt.counts, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, crt.length, "The number of counts is different than expected.");
}

void test_today_count_first_entry(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(5, today_count(), "Today's count is different than expected.");
}

void test_update_today_count_first_entry(void) {
    TEST_IGNORE();
    update_today_count(2);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(7, today_count(), "Today's count is different than expected.");
}

void test_save_count_finish_week(void) {
    TEST_IGNORE();
    save_count(13);
    save_count(22);
    save_count(8);
    save_count(0);
    save_count(34);
    save_count(42);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1134726115295744, last_week_counts(), "Counts for last week are different than expected.");

    current_week_t crt = current_week_counts();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(11859332552854791, crt.counts, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, crt.length, "The number of counts is different than expected.");
}

void test_today_count_current_week(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(42, today_count(), "Today's count is different than expected.");
}

void test_update_today_count_current_week(void) {
    TEST_IGNORE();
    update_today_count(14);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(56, today_count(), "Today's count is different than expected.");
}

void test_save_count_wrap_current_week(void) {
    TEST_IGNORE();
    save_count(12);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(15799982226803975, last_week_counts(), "Counts for last week are different than expected.");

    current_week_t crt = current_week_counts();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(12, crt.counts, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, crt.length, "The number of counts is different than expected.");
}

void test_today_count_new_week(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(12, today_count(), "Today's count is different than expected.");
}

void test_update_today_count_new_week(void) {
    TEST_IGNORE();
    update_today_count(29);
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(41, today_count(), "Today's count is different than expected.");
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
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7322760359905284, last_week_counts(), "Counts for last week are different than expected.");

    current_week_t crt = current_week_counts();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(81621550368, crt.counts, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, crt.length, "The number of counts is different than expected.");
}

void test_save_count_finish_week_again(void) {
    TEST_IGNORE();
    save_count(1);
    save_count(7);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7322760359905284, last_week_counts(), "Counts for last week are different than expected.");

    current_week_t crt = current_week_counts();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1971505970152736, crt.counts, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, crt.length, "The number of counts is different than expected.");
}

void test_update_week_count_one(void) {
    TEST_IGNORE();
    update_week_counts(321276659632387);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1971505970152736, last_week_counts(), "Counts for last week are different than expected.");

    current_week_t crt = current_week_counts();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(321276659632387, crt.counts, "Counts for the week are different than expected.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, crt.length, "The number of counts is different than expected.");
}

void test_update_week_count_two(void) {
    TEST_IGNORE();
    update_week_counts(6796120059876119);
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(321276659632387, last_week_counts(), "Counts for last week are different than expected.");

    current_week_t crt = current_week_counts();
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(6796120059876119, crt.counts, "Counts for the week are different than expected.");
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
