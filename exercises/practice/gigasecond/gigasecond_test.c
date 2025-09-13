#include "vendor/unity.h"

#include <stddef.h>

#define BUFFER_SIZE 20

extern void add_seconds(char buffer[], const char *moment);

void setUp(void) {
}

void tearDown(void) {
}

void test_date_only_specification_of_time(void) {
    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "2011-04-25");

    TEST_ASSERT_EQUAL_STRING("2043-01-01T01:46:40", buffer);
}

void test_second_test_for_date_only_specification_of_time(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "1977-06-13");

    TEST_ASSERT_EQUAL_STRING("2009-02-19T01:46:40", buffer);
}

void test_third_test_for_date_only_specification_of_time(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "1959-07-19");

    TEST_ASSERT_EQUAL_STRING("1991-03-27T01:46:40", buffer);
}

void test_full_time_specified(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "2015-01-24T22:00:00");

    TEST_ASSERT_EQUAL_STRING("2046-10-02T23:46:40", buffer);
}

void test_full_time_with_day_rollover(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "2015-01-24T23:59:59");

    TEST_ASSERT_EQUAL_STRING("2046-10-03T01:46:39", buffer);
}

void test_ends_in_leap_year_divisible_by_400(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "2369-02-13");

    TEST_ASSERT_EQUAL_STRING("2400-10-22T01:46:40", buffer);
}

void test_ends_in_non_leap_year_divisible_by_100(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "2068-12-21");

    TEST_ASSERT_EQUAL_STRING("2100-08-30T01:46:40", buffer);
}

void test_ends_in_leap_year_divisible_by_4(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "1981-02-25");

    TEST_ASSERT_EQUAL_STRING("2012-11-03T01:46:40", buffer);
}

void test_starts_in_leap_year_divisible_by_400(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "2000-10-14");

    TEST_ASSERT_EQUAL_STRING("2032-06-22T01:46:40", buffer);
}

void test_starts_in_non_leap_year_divisible_by_100(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "1900-04-02");

    TEST_ASSERT_EQUAL_STRING("1931-12-10T01:46:40", buffer);
}

void test_starts_in_leap_year_divisible_by_4(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "1996-07-19");

    TEST_ASSERT_EQUAL_STRING("2028-03-27T01:46:40", buffer);
}

void test_ends_in_leap_year_before_end_of_february(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "1944-05-28");

    TEST_ASSERT_EQUAL_STRING("1976-02-04T01:46:40", buffer);
}

void test_starts_in_leap_year_before_end_of_february(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "1972-01-17");

    TEST_ASSERT_EQUAL_STRING("2003-09-25T01:46:40", buffer);
}

void test_full_time_with_year_rollover(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    add_seconds(buffer, "2099-12-31T23:59:59");

    TEST_ASSERT_EQUAL_STRING("2131-09-10T01:46:39", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_date_only_specification_of_time);
    RUN_TEST(test_second_test_for_date_only_specification_of_time);
    RUN_TEST(test_third_test_for_date_only_specification_of_time);
    RUN_TEST(test_full_time_specified);
    RUN_TEST(test_full_time_with_day_rollover);
    RUN_TEST(test_ends_in_leap_year_divisible_by_400);
    RUN_TEST(test_ends_in_non_leap_year_divisible_by_100);
    RUN_TEST(test_ends_in_leap_year_divisible_by_4);
    RUN_TEST(test_starts_in_leap_year_divisible_by_400);
    RUN_TEST(test_starts_in_non_leap_year_divisible_by_100);
    RUN_TEST(test_starts_in_leap_year_divisible_by_4);
    RUN_TEST(test_ends_in_leap_year_before_end_of_february);
    RUN_TEST(test_starts_in_leap_year_before_end_of_february);
    RUN_TEST(test_full_time_with_year_rollover);
    return UNITY_END();
}
