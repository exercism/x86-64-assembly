FUNC_PROTO = """\
#include "vendor/unity.h"

typedef enum {
    north,
    east,
    south,
    west
} direction_t;

typedef struct {
    int32_t x;
    int32_t y;
    direction_t direction;
} robot_t;

extern robot_t create(int32_t x, int32_t y, direction_t direction);
extern void move(robot_t *robot, const char *instructions);
"""


def gen_func_body(prop, inp, expected):
    str_list = []
    str_list.append(
        f"robot_t robot = create({inp['position']['x']}, {inp['position']['y']}, {inp['direction']});\n"
    )
    if "instructions" in inp:
        str_list.append(f'{prop}(&robot, "{inp["instructions"]}");\n')
    str_list.append(
        "const robot_t expected = "
        + "{"
        + f"{expected['position']['x']}, {expected['position']['y']}, {expected['direction']}"
        + "};\n"
    )
    str_list.append("TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);\n")
    str_list.append("TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);\n")
    str_list.append("TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);\n")
    return "".join(str_list)
