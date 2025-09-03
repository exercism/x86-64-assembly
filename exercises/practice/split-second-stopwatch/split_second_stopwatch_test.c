#include "vendor/unity.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 20
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef enum {
    ready = 0,
    running,
    stopped
} state_t;

typedef enum {
    success = 0,
    already_running,
    not_running,
    not_stopped
} error_t;

extern void new(void);
extern error_t start(void);
extern error_t stop(void);
extern error_t reset(void);
extern state_t state(void);
extern error_t lap(void);
extern const char *current_lap(void);
extern size_t previous_laps(const char *buffer[]);
extern void advance_time(const char *by);
extern const char *total(void);

void setUp(void) {
}

void tearDown(void) {
}

void test_new_stopwatch_starts_in_ready_state(void) {
    new();
    TEST_ASSERT_EQUAL(ready, state());
}

void test_new_stopwatchs_current_lap_has_no_elapsed_time(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL_STRING("00:00:00", current_lap());
}

void test_new_stopwatchs_total_has_no_elapsed_time(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL_STRING("00:00:00", total());
}

void test_new_stopwatch_does_not_have_previous_laps(void) {
    TEST_IGNORE();
    new();
    const char *buffer_1[BUFFER_SIZE];
    TEST_ASSERT_EQUAL_UINT64(0, previous_laps(buffer_1));
}

void test_start_from_ready_state_changes_state_to_running(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    TEST_ASSERT_EQUAL(running, state());
}

void test_start_does_not_change_previous_laps(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    const char *buffer_1[BUFFER_SIZE];
    TEST_ASSERT_EQUAL_UINT64(0, previous_laps(buffer_1));
}

void test_start_initiates_time_tracking_for_current_lap(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:00:05");
    TEST_ASSERT_EQUAL_STRING("00:00:05", current_lap());
}

void test_start_initiates_time_tracking_for_total(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:00:23");
    TEST_ASSERT_EQUAL_STRING("00:00:23", total());
}

void test_start_cannot_be_called_from_running_state(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    TEST_ASSERT_EQUAL(already_running, start());
}

void test_stop_from_running_state_changes_state_to_stopped(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    TEST_ASSERT_EQUAL(success, stop());
    TEST_ASSERT_EQUAL(stopped, state());
}

void test_stop_pauses_time_tracking_for_current_lap(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:00:05");
    TEST_ASSERT_EQUAL(success, stop());
    advance_time("00:00:08");
    TEST_ASSERT_EQUAL_STRING("00:00:05", current_lap());
}

void test_stop_pauses_time_tracking_for_total(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:00:13");
    TEST_ASSERT_EQUAL(success, stop());
    advance_time("00:00:44");
    TEST_ASSERT_EQUAL_STRING("00:00:13", total());
}

void test_stop_cannot_be_called_from_ready_state(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(not_running, stop());
}

void test_stop_cannot_be_called_from_stopped_state(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    TEST_ASSERT_EQUAL(success, stop());
    TEST_ASSERT_EQUAL(not_running, stop());
}

void test_start_from_stopped_state_changes_state_to_running(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    TEST_ASSERT_EQUAL(success, stop());
    TEST_ASSERT_EQUAL(success, start());
    TEST_ASSERT_EQUAL(running, state());
}

void test_start_from_stopped_state_resumes_time_tracking_for_current_lap(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:01:20");
    TEST_ASSERT_EQUAL(success, stop());
    advance_time("00:00:20");
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:00:08");
    TEST_ASSERT_EQUAL_STRING("00:01:28", current_lap());
}

void test_start_from_stopped_state_resumes_time_tracking_for_total(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:00:23");
    TEST_ASSERT_EQUAL(success, stop());
    advance_time("00:00:44");
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:00:09");
    TEST_ASSERT_EQUAL_STRING("00:00:32", total());
}

void test_lap_adds_current_lap_to_previous_laps(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:01:38");
    TEST_ASSERT_EQUAL(success, lap());
    const char *buffer_1[BUFFER_SIZE];
    const char *const expected_1[] = {"00:01:38"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected_1), previous_laps(buffer_1));
    for (size_t i = 0; i < ARRAY_SIZE(expected_1); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected_1[i], buffer_1[i]);
    }
    advance_time("00:00:44");
    TEST_ASSERT_EQUAL(success, lap());
    const char *buffer_2[BUFFER_SIZE];
    const char *const expected_2[] = {"00:01:38", "00:00:44"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected_2), previous_laps(buffer_2));
    for (size_t i = 0; i < ARRAY_SIZE(expected_2); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected_2[i], buffer_2[i]);
    }
}

void test_lap_resets_current_lap_and_resumes_time_tracking(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:08:22");
    TEST_ASSERT_EQUAL(success, lap());
    TEST_ASSERT_EQUAL_STRING("00:00:00", current_lap());
    advance_time("00:00:15");
    TEST_ASSERT_EQUAL_STRING("00:00:15", current_lap());
}

void test_lap_continues_time_tracking_for_total(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:00:22");
    TEST_ASSERT_EQUAL(success, lap());
    advance_time("00:00:33");
    TEST_ASSERT_EQUAL_STRING("00:00:55", total());
}

void test_lap_cannot_be_called_from_ready_state(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(not_running, lap());
}

void test_lap_cannot_be_called_from_stopped_state(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    TEST_ASSERT_EQUAL(success, stop());
    TEST_ASSERT_EQUAL(not_running, lap());
}

void test_stop_does_not_change_previous_laps(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:11:22");
    TEST_ASSERT_EQUAL(success, lap());
    const char *buffer_1[BUFFER_SIZE];
    const char *const expected_1[] = {"00:11:22"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected_1), previous_laps(buffer_1));
    for (size_t i = 0; i < ARRAY_SIZE(expected_1); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected_1[i], buffer_1[i]);
    }
    TEST_ASSERT_EQUAL(success, stop());
    const char *buffer_2[BUFFER_SIZE];
    const char *const expected_2[] = {"00:11:22"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected_2), previous_laps(buffer_2));
    for (size_t i = 0; i < ARRAY_SIZE(expected_2); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected_2[i], buffer_2[i]);
    }
}

void test_reset_from_stopped_state_changes_state_to_ready(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    TEST_ASSERT_EQUAL(success, stop());
    TEST_ASSERT_EQUAL(success, reset());
    TEST_ASSERT_EQUAL(ready, state());
}

void test_reset_resets_current_lap(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:00:10");
    TEST_ASSERT_EQUAL(success, stop());
    TEST_ASSERT_EQUAL(success, reset());
    TEST_ASSERT_EQUAL_STRING("00:00:00", current_lap());
}

void test_reset_clears_previous_laps(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("00:00:10");
    TEST_ASSERT_EQUAL(success, lap());
    advance_time("00:00:20");
    TEST_ASSERT_EQUAL(success, lap());
    const char *buffer_1[BUFFER_SIZE];
    const char *const expected_1[] = {"00:00:10", "00:00:20"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected_1), previous_laps(buffer_1));
    for (size_t i = 0; i < ARRAY_SIZE(expected_1); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected_1[i], buffer_1[i]);
    }
    TEST_ASSERT_EQUAL(success, stop());
    TEST_ASSERT_EQUAL(success, reset());
    const char *buffer_2[BUFFER_SIZE];
    TEST_ASSERT_EQUAL_UINT64(0, previous_laps(buffer_2));
}

void test_reset_cannot_be_called_from_ready_state(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(not_stopped, reset());
}

void test_reset_cannot_be_called_from_running_state(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    TEST_ASSERT_EQUAL(not_stopped, reset());
}

void test_supports_very_long_laps(void) {
    TEST_IGNORE();
    new();
    TEST_ASSERT_EQUAL(success, start());
    advance_time("01:23:45");
    TEST_ASSERT_EQUAL_STRING("01:23:45", current_lap());
    TEST_ASSERT_EQUAL(success, lap());
    const char *buffer_2[BUFFER_SIZE];
    const char *const expected_2[] = {"01:23:45"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected_2), previous_laps(buffer_2));
    for (size_t i = 0; i < ARRAY_SIZE(expected_2); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected_2[i], buffer_2[i]);
    }
    advance_time("04:01:40");
    TEST_ASSERT_EQUAL_STRING("04:01:40", current_lap());
    TEST_ASSERT_EQUAL_STRING("05:25:25", total());
    TEST_ASSERT_EQUAL(success, lap());
    const char *buffer_5[BUFFER_SIZE];
    const char *const expected_5[] = {"01:23:45", "04:01:40"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected_5), previous_laps(buffer_5));
    for (size_t i = 0; i < ARRAY_SIZE(expected_5); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected_5[i], buffer_5[i]);
    }
    advance_time("08:43:05");
    TEST_ASSERT_EQUAL_STRING("08:43:05", current_lap());
    TEST_ASSERT_EQUAL_STRING("14:08:30", total());
    TEST_ASSERT_EQUAL(success, lap());
    const char *buffer_8[BUFFER_SIZE];
    const char *const expected_8[] = {"01:23:45", "04:01:40", "08:43:05"};
    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected_8), previous_laps(buffer_8));
    for (size_t i = 0; i < ARRAY_SIZE(expected_8); ++i) {
        TEST_ASSERT_EQUAL_STRING(expected_8[i], buffer_8[i]);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_stopwatch_starts_in_ready_state);
    RUN_TEST(test_new_stopwatchs_current_lap_has_no_elapsed_time);
    RUN_TEST(test_new_stopwatchs_total_has_no_elapsed_time);
    RUN_TEST(test_new_stopwatch_does_not_have_previous_laps);
    RUN_TEST(test_start_from_ready_state_changes_state_to_running);
    RUN_TEST(test_start_does_not_change_previous_laps);
    RUN_TEST(test_start_initiates_time_tracking_for_current_lap);
    RUN_TEST(test_start_initiates_time_tracking_for_total);
    RUN_TEST(test_start_cannot_be_called_from_running_state);
    RUN_TEST(test_stop_from_running_state_changes_state_to_stopped);
    RUN_TEST(test_stop_pauses_time_tracking_for_current_lap);
    RUN_TEST(test_stop_pauses_time_tracking_for_total);
    RUN_TEST(test_stop_cannot_be_called_from_ready_state);
    RUN_TEST(test_stop_cannot_be_called_from_stopped_state);
    RUN_TEST(test_start_from_stopped_state_changes_state_to_running);
    RUN_TEST(test_start_from_stopped_state_resumes_time_tracking_for_current_lap);
    RUN_TEST(test_start_from_stopped_state_resumes_time_tracking_for_total);
    RUN_TEST(test_lap_adds_current_lap_to_previous_laps);
    RUN_TEST(test_lap_resets_current_lap_and_resumes_time_tracking);
    RUN_TEST(test_lap_continues_time_tracking_for_total);
    RUN_TEST(test_lap_cannot_be_called_from_ready_state);
    RUN_TEST(test_lap_cannot_be_called_from_stopped_state);
    RUN_TEST(test_stop_does_not_change_previous_laps);
    RUN_TEST(test_reset_from_stopped_state_changes_state_to_ready);
    RUN_TEST(test_reset_resets_current_lap);
    RUN_TEST(test_reset_clears_previous_laps);
    RUN_TEST(test_reset_cannot_be_called_from_ready_state);
    RUN_TEST(test_reset_cannot_be_called_from_running_state);
    RUN_TEST(test_supports_very_long_laps);
    return UNITY_END();
}
