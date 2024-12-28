#include "vendor/unity.h"

#define BUFFER_SIZE 20

typedef enum {
    FIRST = 1,
    SECOND,
    THIRD,
    FOURTH,
    TEENTH,
    LAST
} week_t;

typedef enum {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
} dayofweek_t;

extern void meetup(char *buffer, int year, int month, week_t week, dayofweek_t dayofweek);

void setUp(void) {
}

void tearDown(void) {
}

void test_when_teenth_monday_is_the_13th_the_first_day_of_the_teenth_week(void) {
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 5, TEENTH, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-05-13", buffer);
}

void test_when_teenth_monday_is_the_19th_the_last_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 8, TEENTH, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-08-19", buffer);
}

void test_when_teenth_monday_is_some_day_in_the_middle_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 9, TEENTH, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-09-16", buffer);
}

void test_when_teenth_tuesday_is_the_19th_the_last_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, TEENTH, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-19", buffer);
}

void test_when_teenth_tuesday_is_some_day_in_the_middle_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, TEENTH, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-16", buffer);
}

void test_when_teenth_tuesday_is_the_13th_the_first_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 8, TEENTH, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-08-13", buffer);
}

void test_when_teenth_wednesday_is_some_day_in_the_middle_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 1, TEENTH, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-01-16", buffer);
}

void test_when_teenth_wednesday_is_the_13th_the_first_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 2, TEENTH, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-02-13", buffer);
}

void test_when_teenth_wednesday_is_the_19th_the_last_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 6, TEENTH, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-06-19", buffer);
}

void test_when_teenth_thursday_is_some_day_in_the_middle_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 5, TEENTH, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-05-16", buffer);
}

void test_when_teenth_thursday_is_the_13th_the_first_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 6, TEENTH, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-06-13", buffer);
}

void test_when_teenth_thursday_is_the_19th_the_last_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 9, TEENTH, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-09-19", buffer);
}

void test_when_teenth_friday_is_the_19th_the_last_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, TEENTH, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-19", buffer);
}

void test_when_teenth_friday_is_some_day_in_the_middle_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 8, TEENTH, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-08-16", buffer);
}

void test_when_teenth_friday_is_the_13th_the_first_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 9, TEENTH, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-09-13", buffer);
}

void test_when_teenth_saturday_is_some_day_in_the_middle_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 2, TEENTH, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-02-16", buffer);
}

void test_when_teenth_saturday_is_the_13th_the_first_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, TEENTH, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-13", buffer);
}

void test_when_teenth_saturday_is_the_19th_the_last_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 10, TEENTH, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-10-19", buffer);
}

void test_when_teenth_sunday_is_the_19th_the_last_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 5, TEENTH, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-05-19", buffer);
}

void test_when_teenth_sunday_is_some_day_in_the_middle_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 6, TEENTH, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-06-16", buffer);
}

void test_when_teenth_sunday_is_the_13th_the_first_day_of_the_teenth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 10, TEENTH, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-10-13", buffer);
}

void test_when_first_monday_is_some_day_in_the_middle_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, FIRST, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-04", buffer);
}

void test_when_first_monday_is_the_1st_the_first_day_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, FIRST, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-01", buffer);
}

void test_when_first_tuesday_is_the_7th_the_last_day_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 5, FIRST, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-05-07", buffer);
}

void test_when_first_tuesday_is_some_day_in_the_middle_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 6, FIRST, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-06-04", buffer);
}

void test_when_first_wednesday_is_some_day_in_the_middle_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 7, FIRST, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-07-03", buffer);
}

void test_when_first_wednesday_is_the_7th_the_last_day_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 8, FIRST, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-08-07", buffer);
}

void test_when_first_thursday_is_some_day_in_the_middle_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 9, FIRST, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-09-05", buffer);
}

void test_when_first_thursday_is_another_day_in_the_middle_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 10, FIRST, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-10-03", buffer);
}

void test_when_first_friday_is_the_1st_the_first_day_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 11, FIRST, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-11-01", buffer);
}

void test_when_first_friday_is_some_day_in_the_middle_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 12, FIRST, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-12-06", buffer);
}

void test_when_first_saturday_is_some_day_in_the_middle_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 1, FIRST, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-01-05", buffer);
}

void test_when_first_saturday_is_another_day_in_the_middle_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 2, FIRST, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-02-02", buffer);
}

void test_when_first_sunday_is_some_day_in_the_middle_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, FIRST, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-03", buffer);
}

void test_when_first_sunday_is_the_7th_the_last_day_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, FIRST, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-07", buffer);
}

void test_when_second_monday_is_some_day_in_the_middle_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, SECOND, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-11", buffer);
}

void test_when_second_monday_is_the_8th_the_first_day_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, SECOND, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-08", buffer);
}

void test_when_second_tuesday_is_the_14th_the_last_day_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 5, SECOND, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-05-14", buffer);
}

void test_when_second_tuesday_is_some_day_in_the_middle_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 6, SECOND, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-06-11", buffer);
}

void test_when_second_wednesday_is_some_day_in_the_middle_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 7, SECOND, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-07-10", buffer);
}

void test_when_second_wednesday_is_the_14th_the_last_day_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 8, SECOND, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-08-14", buffer);
}

void test_when_second_thursday_is_some_day_in_the_middle_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 9, SECOND, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-09-12", buffer);
}

void test_when_second_thursday_is_another_day_in_the_middle_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 10, SECOND, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-10-10", buffer);
}

void test_when_second_friday_is_the_8th_the_first_day_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 11, SECOND, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-11-08", buffer);
}

void test_when_second_friday_is_some_day_in_the_middle_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 12, SECOND, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-12-13", buffer);
}

void test_when_second_saturday_is_some_day_in_the_middle_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 1, SECOND, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-01-12", buffer);
}

void test_when_second_saturday_is_another_day_in_the_middle_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 2, SECOND, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-02-09", buffer);
}

void test_when_second_sunday_is_some_day_in_the_middle_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, SECOND, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-10", buffer);
}

void test_when_second_sunday_is_the_14th_the_last_day_of_the_second_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, SECOND, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-14", buffer);
}

void test_when_third_monday_is_some_day_in_the_middle_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, THIRD, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-18", buffer);
}

void test_when_third_monday_is_the_15th_the_first_day_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, THIRD, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-15", buffer);
}

void test_when_third_tuesday_is_the_21st_the_last_day_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 5, THIRD, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-05-21", buffer);
}

void test_when_third_tuesday_is_some_day_in_the_middle_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 6, THIRD, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-06-18", buffer);
}

void test_when_third_wednesday_is_some_day_in_the_middle_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 7, THIRD, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-07-17", buffer);
}

void test_when_third_wednesday_is_the_21st_the_last_day_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 8, THIRD, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-08-21", buffer);
}

void test_when_third_thursday_is_some_day_in_the_middle_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 9, THIRD, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-09-19", buffer);
}

void test_when_third_thursday_is_another_day_in_the_middle_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 10, THIRD, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-10-17", buffer);
}

void test_when_third_friday_is_the_15th_the_first_day_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 11, THIRD, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-11-15", buffer);
}

void test_when_third_friday_is_some_day_in_the_middle_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 12, THIRD, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-12-20", buffer);
}

void test_when_third_saturday_is_some_day_in_the_middle_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 1, THIRD, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-01-19", buffer);
}

void test_when_third_saturday_is_another_day_in_the_middle_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 2, THIRD, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-02-16", buffer);
}

void test_when_third_sunday_is_some_day_in_the_middle_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, THIRD, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-17", buffer);
}

void test_when_third_sunday_is_the_21st_the_last_day_of_the_third_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, THIRD, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-21", buffer);
}

void test_when_fourth_monday_is_some_day_in_the_middle_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, FOURTH, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-25", buffer);
}

void test_when_fourth_monday_is_the_22nd_the_first_day_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, FOURTH, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-22", buffer);
}

void test_when_fourth_tuesday_is_the_28th_the_last_day_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 5, FOURTH, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-05-28", buffer);
}

void test_when_fourth_tuesday_is_some_day_in_the_middle_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 6, FOURTH, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-06-25", buffer);
}

void test_when_fourth_wednesday_is_some_day_in_the_middle_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 7, FOURTH, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-07-24", buffer);
}

void test_when_fourth_wednesday_is_the_28th_the_last_day_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 8, FOURTH, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-08-28", buffer);
}

void test_when_fourth_thursday_is_some_day_in_the_middle_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 9, FOURTH, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-09-26", buffer);
}

void test_when_fourth_thursday_is_another_day_in_the_middle_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 10, FOURTH, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-10-24", buffer);
}

void test_when_fourth_friday_is_the_22nd_the_first_day_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 11, FOURTH, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-11-22", buffer);
}

void test_when_fourth_friday_is_some_day_in_the_middle_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 12, FOURTH, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-12-27", buffer);
}

void test_when_fourth_saturday_is_some_day_in_the_middle_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 1, FOURTH, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-01-26", buffer);
}

void test_when_fourth_saturday_is_another_day_in_the_middle_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 2, FOURTH, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-02-23", buffer);
}

void test_when_fourth_sunday_is_some_day_in_the_middle_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, FOURTH, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-24", buffer);
}

void test_when_fourth_sunday_is_the_28th_the_last_day_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, FOURTH, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-28", buffer);
}

void test_last_monday_in_a_month_with_four_mondays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, LAST, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-25", buffer);
}

void test_last_monday_in_a_month_with_five_mondays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, LAST, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-29", buffer);
}

void test_last_tuesday_in_a_month_with_four_tuesdays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 5, LAST, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-05-28", buffer);
}

void test_last_tuesday_in_another_month_with_four_tuesdays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 6, LAST, TUESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-06-25", buffer);
}

void test_last_wednesday_in_a_month_with_five_wednesdays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 7, LAST, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-07-31", buffer);
}

void test_last_wednesday_in_a_month_with_four_wednesdays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 8, LAST, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2013-08-28", buffer);
}

void test_last_thursday_in_a_month_with_four_thursdays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 9, LAST, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-09-26", buffer);
}

void test_last_thursday_in_a_month_with_five_thursdays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 10, LAST, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2013-10-31", buffer);
}

void test_last_friday_in_a_month_with_five_fridays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 11, LAST, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-11-29", buffer);
}

void test_last_friday_in_a_month_with_four_fridays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 12, LAST, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2013-12-27", buffer);
}

void test_last_saturday_in_a_month_with_four_saturdays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 1, LAST, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-01-26", buffer);
}

void test_last_saturday_in_another_month_with_four_saturdays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 2, LAST, SATURDAY);
    TEST_ASSERT_EQUAL_STRING("2013-02-23", buffer);
}

void test_last_sunday_in_a_month_with_five_sundays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 3, LAST, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-03-31", buffer);
}

void test_last_sunday_in_a_month_with_four_sundays(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2013, 4, LAST, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2013-04-28", buffer);
}

void test_when_last_wednesday_in_february_in_a_leap_year_is_the_29th(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2012, 2, LAST, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2012-02-29", buffer);
}

void test_last_wednesday_in_december_that_is_also_the_last_day_of_the_year(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2014, 12, LAST, WEDNESDAY);
    TEST_ASSERT_EQUAL_STRING("2014-12-31", buffer);
}

void test_when_last_sunday_in_february_in_a_nonleap_year_is_not_the_29th(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2015, 2, LAST, SUNDAY);
    TEST_ASSERT_EQUAL_STRING("2015-02-22", buffer);
}

void test_when_first_friday_is_the_7th_the_last_day_of_the_first_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2012, 12, FIRST, FRIDAY);
    TEST_ASSERT_EQUAL_STRING("2012-12-07", buffer);
}

void test_when_last_thursday_in_february_in_a_nonleap_year_is_not_the_29th(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2300, 2, LAST, THURSDAY);
    TEST_ASSERT_EQUAL_STRING("2300-02-22", buffer);
}

void test_when_fourth_monday_is_the_23nd_the_second_day_of_the_fourth_week(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    meetup(buffer, 2468, 1, FOURTH, MONDAY);
    TEST_ASSERT_EQUAL_STRING("2468-01-23", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_when_teenth_monday_is_the_13th_the_first_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_monday_is_the_19th_the_last_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_monday_is_some_day_in_the_middle_of_the_teenth_week);
    RUN_TEST(test_when_teenth_tuesday_is_the_19th_the_last_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_tuesday_is_some_day_in_the_middle_of_the_teenth_week);
    RUN_TEST(test_when_teenth_tuesday_is_the_13th_the_first_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_wednesday_is_some_day_in_the_middle_of_the_teenth_week);
    RUN_TEST(test_when_teenth_wednesday_is_the_13th_the_first_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_wednesday_is_the_19th_the_last_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_thursday_is_some_day_in_the_middle_of_the_teenth_week);
    RUN_TEST(test_when_teenth_thursday_is_the_13th_the_first_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_thursday_is_the_19th_the_last_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_friday_is_the_19th_the_last_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_friday_is_some_day_in_the_middle_of_the_teenth_week);
    RUN_TEST(test_when_teenth_friday_is_the_13th_the_first_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_saturday_is_some_day_in_the_middle_of_the_teenth_week);
    RUN_TEST(test_when_teenth_saturday_is_the_13th_the_first_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_saturday_is_the_19th_the_last_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_sunday_is_the_19th_the_last_day_of_the_teenth_week);
    RUN_TEST(test_when_teenth_sunday_is_some_day_in_the_middle_of_the_teenth_week);
    RUN_TEST(test_when_teenth_sunday_is_the_13th_the_first_day_of_the_teenth_week);
    RUN_TEST(test_when_first_monday_is_some_day_in_the_middle_of_the_first_week);
    RUN_TEST(test_when_first_monday_is_the_1st_the_first_day_of_the_first_week);
    RUN_TEST(test_when_first_tuesday_is_the_7th_the_last_day_of_the_first_week);
    RUN_TEST(test_when_first_tuesday_is_some_day_in_the_middle_of_the_first_week);
    RUN_TEST(test_when_first_wednesday_is_some_day_in_the_middle_of_the_first_week);
    RUN_TEST(test_when_first_wednesday_is_the_7th_the_last_day_of_the_first_week);
    RUN_TEST(test_when_first_thursday_is_some_day_in_the_middle_of_the_first_week);
    RUN_TEST(test_when_first_thursday_is_another_day_in_the_middle_of_the_first_week);
    RUN_TEST(test_when_first_friday_is_the_1st_the_first_day_of_the_first_week);
    RUN_TEST(test_when_first_friday_is_some_day_in_the_middle_of_the_first_week);
    RUN_TEST(test_when_first_saturday_is_some_day_in_the_middle_of_the_first_week);
    RUN_TEST(test_when_first_saturday_is_another_day_in_the_middle_of_the_first_week);
    RUN_TEST(test_when_first_sunday_is_some_day_in_the_middle_of_the_first_week);
    RUN_TEST(test_when_first_sunday_is_the_7th_the_last_day_of_the_first_week);
    RUN_TEST(test_when_second_monday_is_some_day_in_the_middle_of_the_second_week);
    RUN_TEST(test_when_second_monday_is_the_8th_the_first_day_of_the_second_week);
    RUN_TEST(test_when_second_tuesday_is_the_14th_the_last_day_of_the_second_week);
    RUN_TEST(test_when_second_tuesday_is_some_day_in_the_middle_of_the_second_week);
    RUN_TEST(test_when_second_wednesday_is_some_day_in_the_middle_of_the_second_week);
    RUN_TEST(test_when_second_wednesday_is_the_14th_the_last_day_of_the_second_week);
    RUN_TEST(test_when_second_thursday_is_some_day_in_the_middle_of_the_second_week);
    RUN_TEST(test_when_second_thursday_is_another_day_in_the_middle_of_the_second_week);
    RUN_TEST(test_when_second_friday_is_the_8th_the_first_day_of_the_second_week);
    RUN_TEST(test_when_second_friday_is_some_day_in_the_middle_of_the_second_week);
    RUN_TEST(test_when_second_saturday_is_some_day_in_the_middle_of_the_second_week);
    RUN_TEST(test_when_second_saturday_is_another_day_in_the_middle_of_the_second_week);
    RUN_TEST(test_when_second_sunday_is_some_day_in_the_middle_of_the_second_week);
    RUN_TEST(test_when_second_sunday_is_the_14th_the_last_day_of_the_second_week);
    RUN_TEST(test_when_third_monday_is_some_day_in_the_middle_of_the_third_week);
    RUN_TEST(test_when_third_monday_is_the_15th_the_first_day_of_the_third_week);
    RUN_TEST(test_when_third_tuesday_is_the_21st_the_last_day_of_the_third_week);
    RUN_TEST(test_when_third_tuesday_is_some_day_in_the_middle_of_the_third_week);
    RUN_TEST(test_when_third_wednesday_is_some_day_in_the_middle_of_the_third_week);
    RUN_TEST(test_when_third_wednesday_is_the_21st_the_last_day_of_the_third_week);
    RUN_TEST(test_when_third_thursday_is_some_day_in_the_middle_of_the_third_week);
    RUN_TEST(test_when_third_thursday_is_another_day_in_the_middle_of_the_third_week);
    RUN_TEST(test_when_third_friday_is_the_15th_the_first_day_of_the_third_week);
    RUN_TEST(test_when_third_friday_is_some_day_in_the_middle_of_the_third_week);
    RUN_TEST(test_when_third_saturday_is_some_day_in_the_middle_of_the_third_week);
    RUN_TEST(test_when_third_saturday_is_another_day_in_the_middle_of_the_third_week);
    RUN_TEST(test_when_third_sunday_is_some_day_in_the_middle_of_the_third_week);
    RUN_TEST(test_when_third_sunday_is_the_21st_the_last_day_of_the_third_week);
    RUN_TEST(test_when_fourth_monday_is_some_day_in_the_middle_of_the_fourth_week);
    RUN_TEST(test_when_fourth_monday_is_the_22nd_the_first_day_of_the_fourth_week);
    RUN_TEST(test_when_fourth_tuesday_is_the_28th_the_last_day_of_the_fourth_week);
    RUN_TEST(test_when_fourth_tuesday_is_some_day_in_the_middle_of_the_fourth_week);
    RUN_TEST(test_when_fourth_wednesday_is_some_day_in_the_middle_of_the_fourth_week);
    RUN_TEST(test_when_fourth_wednesday_is_the_28th_the_last_day_of_the_fourth_week);
    RUN_TEST(test_when_fourth_thursday_is_some_day_in_the_middle_of_the_fourth_week);
    RUN_TEST(test_when_fourth_thursday_is_another_day_in_the_middle_of_the_fourth_week);
    RUN_TEST(test_when_fourth_friday_is_the_22nd_the_first_day_of_the_fourth_week);
    RUN_TEST(test_when_fourth_friday_is_some_day_in_the_middle_of_the_fourth_week);
    RUN_TEST(test_when_fourth_saturday_is_some_day_in_the_middle_of_the_fourth_week);
    RUN_TEST(test_when_fourth_saturday_is_another_day_in_the_middle_of_the_fourth_week);
    RUN_TEST(test_when_fourth_sunday_is_some_day_in_the_middle_of_the_fourth_week);
    RUN_TEST(test_when_fourth_sunday_is_the_28th_the_last_day_of_the_fourth_week);
    RUN_TEST(test_last_monday_in_a_month_with_four_mondays);
    RUN_TEST(test_last_monday_in_a_month_with_five_mondays);
    RUN_TEST(test_last_tuesday_in_a_month_with_four_tuesdays);
    RUN_TEST(test_last_tuesday_in_another_month_with_four_tuesdays);
    RUN_TEST(test_last_wednesday_in_a_month_with_five_wednesdays);
    RUN_TEST(test_last_wednesday_in_a_month_with_four_wednesdays);
    RUN_TEST(test_last_thursday_in_a_month_with_four_thursdays);
    RUN_TEST(test_last_thursday_in_a_month_with_five_thursdays);
    RUN_TEST(test_last_friday_in_a_month_with_five_fridays);
    RUN_TEST(test_last_friday_in_a_month_with_four_fridays);
    RUN_TEST(test_last_saturday_in_a_month_with_four_saturdays);
    RUN_TEST(test_last_saturday_in_another_month_with_four_saturdays);
    RUN_TEST(test_last_sunday_in_a_month_with_five_sundays);
    RUN_TEST(test_last_sunday_in_a_month_with_four_sundays);
    RUN_TEST(test_when_last_wednesday_in_february_in_a_leap_year_is_the_29th);
    RUN_TEST(test_last_wednesday_in_december_that_is_also_the_last_day_of_the_year);
    RUN_TEST(test_when_last_sunday_in_february_in_a_nonleap_year_is_not_the_29th);
    RUN_TEST(test_when_first_friday_is_the_7th_the_last_day_of_the_first_week);
    RUN_TEST(test_when_last_thursday_in_february_in_a_nonleap_year_is_not_the_29th);
    RUN_TEST(test_when_fourth_monday_is_the_23nd_the_second_day_of_the_fourth_week);
    return UNITY_END();
}
