#include "vendor/unity.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define BUFFER_SIZE 200
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
} date_t;

extern bool shared_birthday(size_t birthdates_count, const date_t *birthdates);
extern void random_birthdates(date_t *birthdates, size_t group_size);
extern float estimated_probability_of_shared_birthday(size_t group_size);

bool is_leap(uint16_t year) {
    return year % 400 == 0 || ((year % 4 == 0) && (year % 100 != 0));
}

bool is_valid_day(date_t date) {
    switch (date.month) {
        case 2:
            return date.day <= 28;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return date.day <= 31;
        default:
            return date.day <= 30;
    }
}

void setUp(void) {
}

void tearDown(void) {
}

void test_one_birthdate(void) {
    const date_t birthdates[] = {{2000, 1, 1}};
    TEST_ASSERT_EQUAL(false, shared_birthday(ARRAY_SIZE(birthdates), birthdates));
}

void test_two_birthdates_with_same_year_month_and_day(void) {
    TEST_IGNORE();
    const date_t birthdates[] = {{2000, 1, 1}, {2000, 1, 1}};
    TEST_ASSERT_EQUAL(true, shared_birthday(ARRAY_SIZE(birthdates), birthdates));
}

void test_two_birthdates_with_same_year_and_month_but_different_day(void) {
    TEST_IGNORE();
    const date_t birthdates[] = {{2012, 5, 9}, {2012, 5, 17}};
    TEST_ASSERT_EQUAL(false, shared_birthday(ARRAY_SIZE(birthdates), birthdates));
}

void test_two_birthdates_with_same_month_and_day_but_different_year(void) {
    TEST_IGNORE();
    const date_t birthdates[] = {{1999, 10, 23}, {1988, 10, 23}};
    TEST_ASSERT_EQUAL(true, shared_birthday(ARRAY_SIZE(birthdates), birthdates));
}

void test_two_birthdates_with_same_year_but_different_month_and_day(void) {
    TEST_IGNORE();
    const date_t birthdates[] = {{2007, 12, 19}, {2007, 4, 27}};
    TEST_ASSERT_EQUAL(false, shared_birthday(ARRAY_SIZE(birthdates), birthdates));
}

void test_two_birthdates_with_different_year_month_and_day(void) {
    TEST_IGNORE();
    const date_t birthdates[] = {{1997, 8, 4}, {1963, 11, 23}};
    TEST_ASSERT_EQUAL(false, shared_birthday(ARRAY_SIZE(birthdates), birthdates));
}

void test_multiple_birthdates_without_shared_birthday(void) {
    TEST_IGNORE();
    const date_t birthdates[] = {{1966, 7, 29}, {1977, 2, 12}, {2001, 12, 25}, {1980, 11, 10}};
    TEST_ASSERT_EQUAL(false, shared_birthday(ARRAY_SIZE(birthdates), birthdates));
}

void test_multiple_birthdates_with_one_shared_birthday(void) {
    TEST_IGNORE();
    const date_t birthdates[] = {{1966, 7, 29}, {1977, 2, 12}, {2001, 7, 29}, {1980, 11, 10}};
    TEST_ASSERT_EQUAL(true, shared_birthday(ARRAY_SIZE(birthdates), birthdates));
}

void test_multiple_birthdates_with_more_than_one_shared_birthday(void) {
    TEST_IGNORE();
    const date_t birthdates[] = {{1966, 7, 29}, {1977, 2, 12}, {2001, 12, 25}, {1980, 7, 29}, {2019, 2, 12}};
    TEST_ASSERT_EQUAL(true, shared_birthday(ARRAY_SIZE(birthdates), birthdates));
}

void test_generate_requested_number_of_birthdates(void) {
    TEST_IGNORE();
    double month_map[12] = {0};
    double day_map[31] = {0};
    for (size_t i = 0; i < 365; ++i) {
        date_t buffer[BUFFER_SIZE] = {0};
        random_birthdates(buffer, 120);
        for (size_t j = 0; j < 120; ++j) {
            TEST_ASSERT(!is_leap(buffer[j].year));
            TEST_ASSERT_LESS_OR_EQUAL(12, buffer[j].month);
            TEST_ASSERT(is_valid_day(buffer[j]));
            month_map[buffer[j].month - 1]++;
            day_map[buffer[j].day - 1]++;
        }
    }
    double sum_of_month_frequencies = 0;
    for (size_t i = 0; i < 12; ++i) {
        const double squared = (month_map[i] - 3650) * (month_map[i] - 3650);
        sum_of_month_frequencies += squared / 3650;
    }
    TEST_ASSERT_LESS_OR_EQUAL(37367, (uint32_t)(1000 * sum_of_month_frequencies));
    const double day_expected[] = {1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440,
                                   1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1320, 1320, 840};
    double sum_of_day_frequencies = 0;
    for (size_t i = 0; i < 31; ++i) {
        const double squared = (day_map[i] - day_expected[i]) * (day_map[i] - day_expected[i]);
        sum_of_day_frequencies += squared / day_expected[i];
        TEST_ASSERT_LESS_OR_EQUAL(67633, (uint32_t)(1000 * sum_of_day_frequencies));
    }
}

void test_for_one_person(void) {
    TEST_IGNORE();
    TEST_ASSERT_FLOAT_WITHIN(0.1, 0.0, estimated_probability_of_shared_birthday(1));
}

void test_among_ten_people(void) {
    TEST_IGNORE();
    TEST_ASSERT_FLOAT_WITHIN(8.2765, 11.694818, estimated_probability_of_shared_birthday(10));
}

void test_among_twentythree_people(void) {
    TEST_IGNORE();
    TEST_ASSERT_FLOAT_WITHIN(12.88, 50.729723, estimated_probability_of_shared_birthday(23));
}

void test_among_seventy_people(void) {
    TEST_IGNORE();
    TEST_ASSERT_FLOAT_WITHIN(0.83, 99.915958, estimated_probability_of_shared_birthday(70));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_one_birthdate);
    RUN_TEST(test_two_birthdates_with_same_year_month_and_day);
    RUN_TEST(test_two_birthdates_with_same_year_and_month_but_different_day);
    RUN_TEST(test_two_birthdates_with_same_month_and_day_but_different_year);
    RUN_TEST(test_two_birthdates_with_same_year_but_different_month_and_day);
    RUN_TEST(test_two_birthdates_with_different_year_month_and_day);
    RUN_TEST(test_multiple_birthdates_without_shared_birthday);
    RUN_TEST(test_multiple_birthdates_with_one_shared_birthday);
    RUN_TEST(test_multiple_birthdates_with_more_than_one_shared_birthday);
    RUN_TEST(test_generate_requested_number_of_birthdates);
    RUN_TEST(test_for_one_person);
    RUN_TEST(test_among_ten_people);
    RUN_TEST(test_among_twentythree_people);
    RUN_TEST(test_among_seventy_people);
    return UNITY_END();
}
