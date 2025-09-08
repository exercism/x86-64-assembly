from string import Template

FUNC_PROTO = """\
#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

#define BUFFER_SIZE 15
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

typedef struct {
    size_t row;
    size_t column;
} point_t;

typedef struct {
    size_t num_elements;
    int64_t row[BUFFER_SIZE];
} row_t;

extern size_t saddle_points(point_t *output, const row_t *rows, size_t rows_count);
"""

INPUT_TEMPLATE = Template("""
point_t points[BUFFER_SIZE];
const row_t rows[] = ${input};
""")

NO_INPUT_TEMPLATE = Template("""
point_t points[BUFFER_SIZE];
""")

WITH_SADDLE_POINTS_TEMPLATE = Template("""
${input}
const point_t expected[] = ${expected};

TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), ${prop}(points, rows, ARRAY_SIZE(rows)));

for (size_t i = 0; i < ARRAY_SIZE(expected); ++i) {
    TEST_ASSERT_EQUAL_INT64(expected[i].row, points[i].row);
    TEST_ASSERT_EQUAL_INT64(expected[i].column, points[i].column);
}
""")

WITHOUT_SADDLE_POINTS_TEMPLATE = Template("""
${input}

TEST_ASSERT_EQUAL_UINT64(0, ${prop}(points, ${rows}, ${size}));
""")


def array_literal(numbers):
    return str(numbers).replace("[", "{").replace("]", "}")


def gen_func_body(prop, inp, expected):
    if len(inp["matrix"][0]) == 0:
        return WITHOUT_SADDLE_POINTS_TEMPLATE.substitute(
            input=NO_INPUT_TEMPLATE.substitute(), prop=prop, rows="NULL", size="0"
        )
    elif len(expected) == 0:
        input = array_literal([[len(arr), arr] for arr in inp["matrix"]])
        input_str = INPUT_TEMPLATE.substitute(input=input)
        return WITHOUT_SADDLE_POINTS_TEMPLATE.substitute(
            input=input_str, prop=prop, rows="rows", size="ARRAY_SIZE(rows)"
        )
    else:
        input = array_literal([[len(arr), arr] for arr in inp["matrix"]])
        input_str = INPUT_TEMPLATE.substitute(input=input)
        expected_str = array_literal(
            sorted([[dic["row"], dic["column"]] for dic in expected])
        )
        return WITH_SADDLE_POINTS_TEMPLATE.substitute(
            input=input_str, prop=prop, expected=expected_str
        )
