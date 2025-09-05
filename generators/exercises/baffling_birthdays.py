FUNC_PROTO = """\
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
"""


def gen_random_check(prop):
    return f"""double month_map[12] = {{0}};
    double day_map[31] = {{0}};
    for (size_t i = 0; i < 365; ++i) {{
        date_t buffer[BUFFER_SIZE] = {{0}};
        {prop}(buffer, 120);
        for (size_t j = 0; j < 120; ++j) {{
            TEST_ASSERT(!is_leap(buffer[j].year));
            TEST_ASSERT_LESS_OR_EQUAL(12, buffer[j].month);
            TEST_ASSERT(is_valid_day(buffer[j]));
            month_map[buffer[j].month - 1]++;
            day_map[buffer[j].day - 1]++;
        }}
    }}
    double sum_of_month_frequencies = 0;
    for (size_t i = 0; i < 12; ++i) {{
        const double squared = (month_map[i] - 3650) * (month_map[i] - 3650);
        sum_of_month_frequencies += squared / 3650;
    }}
    TEST_ASSERT_LESS_OR_EQUAL(37367, (uint32_t)(1000 * sum_of_month_frequencies));
    const double day_expected[] = {{1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1440, 1320, 1320, 840}};
    double sum_of_day_frequencies = 0;
    for (size_t i = 0; i < 31; ++i) {{
        const double squared = (day_map[i] - day_expected[i]) * (day_map[i] - day_expected[i]);
        sum_of_day_frequencies += squared / day_expected[i];
        TEST_ASSERT_LESS_OR_EQUAL(67633, (uint32_t)(1000 * sum_of_day_frequencies));
    }}
    """


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


delta = {"0.0": 0.1, "11.694818": 8.2765, "50.729723": 12.88, "99.915958": 0.83}


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
