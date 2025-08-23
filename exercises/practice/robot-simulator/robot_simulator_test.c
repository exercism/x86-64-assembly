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

void setUp(void) {
}

void tearDown(void) {
}

void test_at_origin_facing_north(void) {
    robot_t robot = create(0, 0, north);
    const robot_t expected = {0, 0, north};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_at_negative_position_facing_south(void) {
    TEST_IGNORE();
    robot_t robot = create(-1, -1, south);
    const robot_t expected = {-1, -1, south};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_changes_north_to_east(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, north);
    move(&robot, "R");
    const robot_t expected = {0, 0, east};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_changes_east_to_south(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, east);
    move(&robot, "R");
    const robot_t expected = {0, 0, south};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_changes_south_to_west(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, south);
    move(&robot, "R");
    const robot_t expected = {0, 0, west};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_changes_west_to_north(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, west);
    move(&robot, "R");
    const robot_t expected = {0, 0, north};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_changes_north_to_west(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, north);
    move(&robot, "L");
    const robot_t expected = {0, 0, west};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_changes_west_to_south(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, west);
    move(&robot, "L");
    const robot_t expected = {0, 0, south};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_changes_south_to_east(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, south);
    move(&robot, "L");
    const robot_t expected = {0, 0, east};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_changes_east_to_north(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, east);
    move(&robot, "L");
    const robot_t expected = {0, 0, north};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_facing_north_increments_y(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, north);
    move(&robot, "A");
    const robot_t expected = {0, 1, north};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_facing_south_decrements_y(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, south);
    move(&robot, "A");
    const robot_t expected = {0, -1, south};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_facing_east_increments_x(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, east);
    move(&robot, "A");
    const robot_t expected = {1, 0, east};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_facing_west_decrements_x(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, west);
    move(&robot, "A");
    const robot_t expected = {-1, 0, west};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_moving_east_and_north_from_readme(void) {
    TEST_IGNORE();
    robot_t robot = create(7, 3, north);
    move(&robot, "RAALAL");
    const robot_t expected = {9, 4, west};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_moving_west_and_north(void) {
    TEST_IGNORE();
    robot_t robot = create(0, 0, north);
    move(&robot, "LAAARALA");
    const robot_t expected = {-4, 1, west};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_moving_west_and_south(void) {
    TEST_IGNORE();
    robot_t robot = create(2, -7, east);
    move(&robot, "RRAAAAALA");
    const robot_t expected = {-3, -8, south};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

void test_moving_east_and_north(void) {
    TEST_IGNORE();
    robot_t robot = create(8, 4, south);
    move(&robot, "LAAARRRALLLL");
    const robot_t expected = {11, 5, north};
    TEST_ASSERT_EQUAL_INT32(expected.x, robot.x);
    TEST_ASSERT_EQUAL_INT32(expected.y, robot.y);
    TEST_ASSERT_EQUAL_INT(expected.direction, robot.direction);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_at_origin_facing_north);
    RUN_TEST(test_at_negative_position_facing_south);
    RUN_TEST(test_changes_north_to_east);
    RUN_TEST(test_changes_east_to_south);
    RUN_TEST(test_changes_south_to_west);
    RUN_TEST(test_changes_west_to_north);
    RUN_TEST(test_changes_north_to_west);
    RUN_TEST(test_changes_west_to_south);
    RUN_TEST(test_changes_south_to_east);
    RUN_TEST(test_changes_east_to_north);
    RUN_TEST(test_facing_north_increments_y);
    RUN_TEST(test_facing_south_decrements_y);
    RUN_TEST(test_facing_east_increments_x);
    RUN_TEST(test_facing_west_decrements_x);
    RUN_TEST(test_moving_east_and_north_from_readme);
    RUN_TEST(test_moving_west_and_north);
    RUN_TEST(test_moving_west_and_south);
    RUN_TEST(test_moving_east_and_north);
    return UNITY_END();
}
