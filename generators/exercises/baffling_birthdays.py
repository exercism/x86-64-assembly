FUNC_PROTO = """\
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

static const unsigned days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static const unsigned prev_days[] = {
    0,
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
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30
};

inline static bool is_leap(uint16_t year) {
    return year % 400 == 0 || ((year % 4 == 0) && (year % 100 != 0));
}

inline static bool is_valid_day(date_t date) {
    return date.day > 0 && date.day <= days_in_month[date.month - 1];
}
"""


def gen_random_check(prop):
    return f"""
    double year_map[529] = {{0}};
    double day_map[365] = {{0}};
    for (size_t i = 0; i < 3650; ++i) {{
        date_t buffer[BUFFER_SIZE] = {{0}};
        {prop}(buffer, 1000);
        for (size_t j = 0; j < 1000; ++j) {{
            const date_t date = buffer[j];
            TEST_ASSERT_MESSAGE(date.year >= 1600 && date.year < 2129, "A valid year must be >= 1600 and < 2129");
            TEST_ASSERT_MESSAGE(!is_leap(date.year), "A leap year is not valid in a generated birthdate");
            TEST_ASSERT_MESSAGE(date.month >= 1 && date.month <= 12, "A month must be in the range [1, 12], inclusive");
            TEST_ASSERT_MESSAGE(is_valid_day(date), "A day must be in the valid range for its month");
            const unsigned year_day = (unsigned)date.day + prev_days[date.month - 1];
            day_map[year_day - 1]++;
            year_map[date.year - 1600]++;
        }}
    }}

    double sum_of_year_frequencies = 0.0;
    for (size_t i = 0; i < 529; ++i) {{
        const uint16_t year = 1600 + i;
        if (is_leap(year)) continue;
        const double squared = (year_map[i] - 9125) * (year_map[i] - 9125);
        sum_of_year_frequencies += squared / 9125;
    }}
    TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(512704, (uint32_t)(1000 * sum_of_year_frequencies),
        "Generated years do not follow an uniform distribution in the range [1600, 2129)");

    double sum_of_day_frequencies = 0.0;
    for (size_t i = 0; i < 365; ++i) {{
        const double squared = (day_map[i] - 10000) * (day_map[i] - 10000);
        sum_of_day_frequencies += squared / 10000;
    }}
    TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(472995, (uint32_t)(1000 * sum_of_day_frequencies),
        "Generated birthdays do not follow an uniform distribution across the 365 days of the year");
    """


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


delta = {"0.0": 0.05, "11.694818": 3.9537, "50.729723": 6.1509, "99.915958": 0.3565}


def gen_func_body(prop, inp, expected):
    global flag
    str_list = []
    if prop == "shared_birthday":
        birth_dates = [[int(d) for d in bd.split("-")] for bd in inp["birthdates"]]
        str_list.append(f"const date_t birthdates[] = {array_literal(birth_dates)};")
        str_list.append(
            f"TEST_ASSERT_EQUAL({str(expected).lower()}, {prop}(ARRAY_SIZE(birthdates), birthdates));"
        )
    elif prop == "random_birthdates":
        str_list.append(gen_random_check(prop))
    else:
        str_list.append(
            f"TEST_ASSERT_FLOAT_WITHIN({delta[str(expected)]}, {expected}, {prop}({inp['groupSize']}));"
        )

    return "\n".join(str_list)
