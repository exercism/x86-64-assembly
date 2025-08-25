#include "vendor/unity.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t hour;
    uint8_t minute;
} clock_time_t;

extern clock_time_t create(int64_t hour, int64_t minute);
extern clock_time_t add_minutes(int64_t hour, int64_t minute, int64_t value);
extern clock_time_t subtract_minutes(int64_t hour, int64_t minute, int64_t value);
extern bool equal(clock_time_t clock1, clock_time_t clock2);

void setUp(void) {
}

void tearDown(void) {
}

void test_on_the_hour(void) {
    const clock_time_t expected = {8, 0};
    const clock_time_t clock = create(8, 0);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_past_the_hour(void) {
    TEST_IGNORE();
    const clock_time_t expected = {11, 9};
    const clock_time_t clock = create(11, 9);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_midnight_is_zero_hours(void) {
    TEST_IGNORE();
    const clock_time_t expected = {0, 0};
    const clock_time_t clock = create(24, 0);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_hour_rolls_over(void) {
    TEST_IGNORE();
    const clock_time_t expected = {1, 0};
    const clock_time_t clock = create(25, 0);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_hour_rolls_over_continuously(void) {
    TEST_IGNORE();
    const clock_time_t expected = {4, 0};
    const clock_time_t clock = create(100, 0);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_sixty_minutes_is_next_hour(void) {
    TEST_IGNORE();
    const clock_time_t expected = {2, 0};
    const clock_time_t clock = create(1, 60);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_minutes_roll_over(void) {
    TEST_IGNORE();
    const clock_time_t expected = {2, 40};
    const clock_time_t clock = create(0, 160);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_minutes_roll_over_continuously(void) {
    TEST_IGNORE();
    const clock_time_t expected = {4, 43};
    const clock_time_t clock = create(0, 1723);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_hour_and_minutes_roll_over(void) {
    TEST_IGNORE();
    const clock_time_t expected = {3, 40};
    const clock_time_t clock = create(25, 160);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_hour_and_minutes_roll_over_continuously(void) {
    TEST_IGNORE();
    const clock_time_t expected = {11, 1};
    const clock_time_t clock = create(201, 3001);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_hour_and_minutes_roll_over_to_exactly_midnight(void) {
    TEST_IGNORE();
    const clock_time_t expected = {0, 0};
    const clock_time_t clock = create(72, 8640);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_negative_hour(void) {
    TEST_IGNORE();
    const clock_time_t expected = {23, 15};
    const clock_time_t clock = create(-1, 15);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_negative_hour_rolls_over(void) {
    TEST_IGNORE();
    const clock_time_t expected = {23, 0};
    const clock_time_t clock = create(-25, 0);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_negative_hour_rolls_over_continuously(void) {
    TEST_IGNORE();
    const clock_time_t expected = {5, 0};
    const clock_time_t clock = create(-91, 0);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_negative_minutes(void) {
    TEST_IGNORE();
    const clock_time_t expected = {0, 20};
    const clock_time_t clock = create(1, -40);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_negative_minutes_roll_over(void) {
    TEST_IGNORE();
    const clock_time_t expected = {22, 20};
    const clock_time_t clock = create(1, -160);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_negative_minutes_roll_over_continuously(void) {
    TEST_IGNORE();
    const clock_time_t expected = {16, 40};
    const clock_time_t clock = create(1, -4820);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_negative_sixty_minutes_is_previous_hour(void) {
    TEST_IGNORE();
    const clock_time_t expected = {1, 0};
    const clock_time_t clock = create(2, -60);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_negative_hour_and_minutes_both_roll_over(void) {
    TEST_IGNORE();
    const clock_time_t expected = {20, 20};
    const clock_time_t clock = create(-25, -160);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_negative_hour_and_minutes_both_roll_over_continuously(void) {
    TEST_IGNORE();
    const clock_time_t expected = {22, 10};
    const clock_time_t clock = create(-121, -5810);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_add_minutes(void) {
    TEST_IGNORE();
    const clock_time_t expected = {10, 3};
    const clock_time_t clock = add_minutes(10, 0, 3);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_add_no_minutes(void) {
    TEST_IGNORE();
    const clock_time_t expected = {6, 41};
    const clock_time_t clock = add_minutes(6, 41, 0);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_add_to_next_hour(void) {
    TEST_IGNORE();
    const clock_time_t expected = {1, 25};
    const clock_time_t clock = add_minutes(0, 45, 40);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_add_more_than_one_hour(void) {
    TEST_IGNORE();
    const clock_time_t expected = {11, 1};
    const clock_time_t clock = add_minutes(10, 0, 61);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_add_more_than_two_hours_with_carry(void) {
    TEST_IGNORE();
    const clock_time_t expected = {3, 25};
    const clock_time_t clock = add_minutes(0, 45, 160);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_add_across_midnight(void) {
    TEST_IGNORE();
    const clock_time_t expected = {0, 1};
    const clock_time_t clock = add_minutes(23, 59, 2);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_add_more_than_one_day_1500_min__25_hrs(void) {
    TEST_IGNORE();
    const clock_time_t expected = {6, 32};
    const clock_time_t clock = add_minutes(5, 32, 1500);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_add_more_than_two_days(void) {
    TEST_IGNORE();
    const clock_time_t expected = {11, 21};
    const clock_time_t clock = add_minutes(1, 1, 3500);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_subtract_minutes(void) {
    TEST_IGNORE();
    const clock_time_t expected = {10, 0};
    const clock_time_t clock = subtract_minutes(10, 3, 3);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_subtract_to_previous_hour(void) {
    TEST_IGNORE();
    const clock_time_t expected = {9, 33};
    const clock_time_t clock = subtract_minutes(10, 3, 30);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_subtract_more_than_an_hour(void) {
    TEST_IGNORE();
    const clock_time_t expected = {8, 53};
    const clock_time_t clock = subtract_minutes(10, 3, 70);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_subtract_across_midnight(void) {
    TEST_IGNORE();
    const clock_time_t expected = {23, 59};
    const clock_time_t clock = subtract_minutes(0, 3, 4);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_subtract_more_than_two_hours(void) {
    TEST_IGNORE();
    const clock_time_t expected = {21, 20};
    const clock_time_t clock = subtract_minutes(0, 0, 160);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_subtract_more_than_two_hours_with_borrow(void) {
    TEST_IGNORE();
    const clock_time_t expected = {3, 35};
    const clock_time_t clock = subtract_minutes(6, 15, 160);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_subtract_more_than_one_day_1500_min__25_hrs(void) {
    TEST_IGNORE();
    const clock_time_t expected = {4, 32};
    const clock_time_t clock = subtract_minutes(5, 32, 1500);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_subtract_more_than_two_days(void) {
    TEST_IGNORE();
    const clock_time_t expected = {0, 20};
    const clock_time_t clock = subtract_minutes(2, 20, 3000);
    TEST_ASSERT_EQUAL_UINT8(expected.hour, clock.hour);
    TEST_ASSERT_EQUAL_UINT8(expected.minute, clock.minute);
}

void test_clocks_with_same_time(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(15, 37);
    const clock_time_t clock2 = create(15, 37);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_a_minute_apart(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(15, 36);
    const clock_time_t clock2 = create(15, 37);
    TEST_ASSERT_EQUAL(false, equal(clock1, clock2));
}

void test_clocks_an_hour_apart(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(14, 37);
    const clock_time_t clock2 = create(15, 37);
    TEST_ASSERT_EQUAL(false, equal(clock1, clock2));
}

void test_clocks_with_hour_overflow(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(10, 37);
    const clock_time_t clock2 = create(34, 37);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_hour_overflow_by_several_days(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(3, 11);
    const clock_time_t clock2 = create(99, 11);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_negative_hour(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(22, 40);
    const clock_time_t clock2 = create(-2, 40);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_negative_hour_that_wraps(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(17, 3);
    const clock_time_t clock2 = create(-31, 3);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_negative_hour_that_wraps_multiple_times(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(13, 49);
    const clock_time_t clock2 = create(-83, 49);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_minute_overflow(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(0, 1);
    const clock_time_t clock2 = create(0, 1441);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_minute_overflow_by_several_days(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(2, 2);
    const clock_time_t clock2 = create(2, 4322);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_negative_minute(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(2, 40);
    const clock_time_t clock2 = create(3, -20);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_negative_minute_that_wraps(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(4, 10);
    const clock_time_t clock2 = create(5, -1490);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_negative_minute_that_wraps_multiple_times(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(6, 15);
    const clock_time_t clock2 = create(6, -4305);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_negative_hours_and_minutes(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(7, 32);
    const clock_time_t clock2 = create(-12, -268);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_clocks_with_negative_hours_and_minutes_that_wrap(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(18, 7);
    const clock_time_t clock2 = create(-54, -11513);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

void test_full_clock_and_zeroed_clock(void) {
    TEST_IGNORE();
    const clock_time_t clock1 = create(24, 0);
    const clock_time_t clock2 = create(0, 0);
    TEST_ASSERT_EQUAL(true, equal(clock1, clock2));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_on_the_hour);
    RUN_TEST(test_past_the_hour);
    RUN_TEST(test_midnight_is_zero_hours);
    RUN_TEST(test_hour_rolls_over);
    RUN_TEST(test_hour_rolls_over_continuously);
    RUN_TEST(test_sixty_minutes_is_next_hour);
    RUN_TEST(test_minutes_roll_over);
    RUN_TEST(test_minutes_roll_over_continuously);
    RUN_TEST(test_hour_and_minutes_roll_over);
    RUN_TEST(test_hour_and_minutes_roll_over_continuously);
    RUN_TEST(test_hour_and_minutes_roll_over_to_exactly_midnight);
    RUN_TEST(test_negative_hour);
    RUN_TEST(test_negative_hour_rolls_over);
    RUN_TEST(test_negative_hour_rolls_over_continuously);
    RUN_TEST(test_negative_minutes);
    RUN_TEST(test_negative_minutes_roll_over);
    RUN_TEST(test_negative_minutes_roll_over_continuously);
    RUN_TEST(test_negative_sixty_minutes_is_previous_hour);
    RUN_TEST(test_negative_hour_and_minutes_both_roll_over);
    RUN_TEST(test_negative_hour_and_minutes_both_roll_over_continuously);
    RUN_TEST(test_add_minutes);
    RUN_TEST(test_add_no_minutes);
    RUN_TEST(test_add_to_next_hour);
    RUN_TEST(test_add_more_than_one_hour);
    RUN_TEST(test_add_more_than_two_hours_with_carry);
    RUN_TEST(test_add_across_midnight);
    RUN_TEST(test_add_more_than_one_day_1500_min__25_hrs);
    RUN_TEST(test_add_more_than_two_days);
    RUN_TEST(test_subtract_minutes);
    RUN_TEST(test_subtract_to_previous_hour);
    RUN_TEST(test_subtract_more_than_an_hour);
    RUN_TEST(test_subtract_across_midnight);
    RUN_TEST(test_subtract_more_than_two_hours);
    RUN_TEST(test_subtract_more_than_two_hours_with_borrow);
    RUN_TEST(test_subtract_more_than_one_day_1500_min__25_hrs);
    RUN_TEST(test_subtract_more_than_two_days);
    RUN_TEST(test_clocks_with_same_time);
    RUN_TEST(test_clocks_a_minute_apart);
    RUN_TEST(test_clocks_an_hour_apart);
    RUN_TEST(test_clocks_with_hour_overflow);
    RUN_TEST(test_clocks_with_hour_overflow_by_several_days);
    RUN_TEST(test_clocks_with_negative_hour);
    RUN_TEST(test_clocks_with_negative_hour_that_wraps);
    RUN_TEST(test_clocks_with_negative_hour_that_wraps_multiple_times);
    RUN_TEST(test_clocks_with_minute_overflow);
    RUN_TEST(test_clocks_with_minute_overflow_by_several_days);
    RUN_TEST(test_clocks_with_negative_minute);
    RUN_TEST(test_clocks_with_negative_minute_that_wraps);
    RUN_TEST(test_clocks_with_negative_minute_that_wraps_multiple_times);
    RUN_TEST(test_clocks_with_negative_hours_and_minutes);
    RUN_TEST(test_clocks_with_negative_hours_and_minutes_that_wrap);
    RUN_TEST(test_full_clock_and_zeroed_clock);
    return UNITY_END();
}
