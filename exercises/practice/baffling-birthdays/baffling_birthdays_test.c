#include "vendor/unity.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define BUFFER_SIZE 1024
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
} date_t;

extern bool shared_birthday(size_t birthdates_count, const date_t *birthdates);
extern void random_birthdates(date_t *birthdates, size_t group_size);
extern float estimated_probability_of_shared_birthday(size_t group_size);

static const unsigned days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const unsigned prev_days[] = {0,
                                     31,
                                     31 + 28,
                                     31 + 28 + 31,
                                     31 + 28 + 31 + 30,
                                     31 + 28 + 31 + 30 + 31,
                                     31 + 28 + 31 + 30 + 31 + 30,
                                     31 + 28 + 31 + 30 + 31 + 30 + 31,
                                     31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
                                     31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
                                     31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
                                     31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30};

inline static bool is_leap(uint16_t year) {
    return year % 400 == 0 || ((year % 4 == 0) && (year % 100 != 0));
}

inline static bool is_valid_day(date_t date) {
    return date.day > 0 && date.day <= days_in_month[date.month - 1];
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

    double year_map[529] = {0};
    double day_map[365] = {0};
    for (size_t i = 0; i < 3650; ++i) {
        date_t buffer[BUFFER_SIZE] = {0};
        random_birthdates(buffer, 1000);
        for (size_t j = 0; j < 1000; ++j) {
            const date_t date = buffer[j];
            TEST_ASSERT_MESSAGE(date.year >= 1600 && date.year < 2129, "A valid year must be >= 1600 and < 2129");
            TEST_ASSERT_MESSAGE(!is_leap(date.year), "A leap year is not valid in a generated birthdate");
            TEST_ASSERT_MESSAGE(date.month >= 1 && date.month <= 12, "A month must be in the range [1, 12], inclusive");
            TEST_ASSERT_MESSAGE(is_valid_day(date), "A day must be in the valid range for its month");
            const unsigned year_day = (unsigned)date.day + prev_days[date.month - 1];
            day_map[year_day - 1]++;
            year_map[date.year - 1600]++;
        }
    }

    double sum_of_year_frequencies = 0.0;
    for (size_t i = 0; i < 529; ++i) {
        const uint16_t year = 1600 + i;
        if (is_leap(year)) continue;
        const double squared = (year_map[i] - 9125) * (year_map[i] - 9125);
        sum_of_year_frequencies += squared / 9125;
    }
    TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(512704, (uint32_t)(1000 * sum_of_year_frequencies),
                                      "Generated years do not follow an uniform distribution in the range [1600, 2129)");

    double sum_of_day_frequencies = 0.0;
    for (size_t i = 0; i < 365; ++i) {
        const double squared = (day_map[i] - 10000) * (day_map[i] - 10000);
        sum_of_day_frequencies += squared / 10000;
    }
    TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(472995, (uint32_t)(1000 * sum_of_day_frequencies),
                                      "Generated birthdays do not follow an uniform distribution across the 365 days of the year");
}

void test_for_one_person(void) {
    TEST_IGNORE();
    TEST_ASSERT_FLOAT_WITHIN(0.05, 0.0, estimated_probability_of_shared_birthday(1));
}

void test_among_ten_people(void) {
    TEST_IGNORE();
    TEST_ASSERT_FLOAT_WITHIN(3.9537, 11.694818, estimated_probability_of_shared_birthday(10));
}

void test_among_twentythree_people(void) {
    TEST_IGNORE();
    TEST_ASSERT_FLOAT_WITHIN(6.1509, 50.729723, estimated_probability_of_shared_birthday(23));
}

void test_among_seventy_people(void) {
    TEST_IGNORE();
    TEST_ASSERT_FLOAT_WITHIN(0.3565, 99.915958, estimated_probability_of_shared_birthday(70));
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
