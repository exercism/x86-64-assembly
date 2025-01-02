// Version: 0

#include "vendor/unity.h"

typedef struct {
   double a;
   double b;
   double c;
} triangle_t;

extern int is_equilateral(triangle_t sides);
extern int is_isosceles(triangle_t sides);
extern int is_scalene(triangle_t sides);

void setUp(void) {
}

void tearDown(void) {
}

void test_equilateral_triangle_all_sides_are_equal(void) {
    triangle_t sides = { 2, 2, 2 } ;
    TEST_ASSERT_EQUAL_INT(1, is_equilateral(sides));
}

void test_equilateral_triangle_any_side_is_unequal(void) {
    TEST_IGNORE();
    triangle_t sides = { 2, 3, 2 } ;
    TEST_ASSERT_EQUAL_INT(0, is_equilateral(sides));
}

void test_equilateral_triangle_no_sides_are_equal(void) {
    TEST_IGNORE();
    triangle_t sides = { 5, 4, 6 } ;
    TEST_ASSERT_EQUAL_INT(0, is_equilateral(sides));
}

void test_equilateral_triangle_all_zero_sides_is_not_a_triangle(void) {
    TEST_IGNORE();
    triangle_t sides = { 0, 0, 0 } ;
    TEST_ASSERT_EQUAL_INT(0, is_equilateral(sides));
}

void test_equilateral_triangle_sides_may_be_floats(void) {
    TEST_IGNORE();
    triangle_t sides = { 0.5, 0.5, 0.5 } ;
    TEST_ASSERT_EQUAL_INT(1, is_equilateral(sides));
}

void test_isosceles_triangle_last_two_sides_are_equal(void) {
    TEST_IGNORE();
    triangle_t sides = { 3, 4, 4 } ;
    TEST_ASSERT_EQUAL_INT(1, is_isosceles(sides));
}

void test_isosceles_triangle_first_two_sides_are_equal(void) {
    TEST_IGNORE();
    triangle_t sides = { 4, 4, 3 } ;
    TEST_ASSERT_EQUAL_INT(1, is_isosceles(sides));
}

void test_isosceles_triangle_first_and_last_sides_are_equal(void) {
    TEST_IGNORE();
    triangle_t sides = { 4, 3, 4 } ;
    TEST_ASSERT_EQUAL_INT(1, is_isosceles(sides));
}

void test_isosceles_triangle_equilateral_triangles_are_also_isosceles(void) {
    TEST_IGNORE();
    triangle_t sides = { 4, 4, 4 } ;
    TEST_ASSERT_EQUAL_INT(1, is_isosceles(sides));
}

void test_isosceles_triangle_no_sides_are_equal(void) {
    TEST_IGNORE();
    triangle_t sides = { 2, 3, 4 } ;
    TEST_ASSERT_EQUAL_INT(0, is_isosceles(sides));
}

void test_isosceles_triangle_first_triangle_inequality_violation(void) {
    TEST_IGNORE();
    triangle_t sides = { 1, 1, 3 } ;
    TEST_ASSERT_EQUAL_INT(0, is_isosceles(sides));
}

void test_isosceles_triangle_second_triangle_inequality_violation(void) {
    TEST_IGNORE();
    triangle_t sides = { 1, 3, 1 } ;
    TEST_ASSERT_EQUAL_INT(0, is_isosceles(sides));
}

void test_isosceles_triangle_third_triangle_inequality_violation(void) {
    TEST_IGNORE();
    triangle_t sides = { 3, 1, 1 } ;
    TEST_ASSERT_EQUAL_INT(0, is_isosceles(sides));
}

void test_isosceles_triangle_sides_may_be_floats(void) {
    TEST_IGNORE();
    triangle_t sides = { 0.5, 0.4, 0.5 } ;
    TEST_ASSERT_EQUAL_INT(1, is_isosceles(sides));
}

void test_scalene_triangle_no_sides_are_equal(void) {
    TEST_IGNORE();
    triangle_t sides = { 5, 4, 6 } ;
    TEST_ASSERT_EQUAL_INT(1, is_scalene(sides));
}

void test_scalene_triangle_all_sides_are_equal(void) {
    TEST_IGNORE();
    triangle_t sides = { 4, 4, 4 } ;
    TEST_ASSERT_EQUAL_INT(0, is_scalene(sides));
}

void test_scalene_triangle_first_and_second_sides_are_equal(void) {
    TEST_IGNORE();
    triangle_t sides = { 4, 4, 3 } ;
    TEST_ASSERT_EQUAL_INT(0, is_scalene(sides));
}

void test_scalene_triangle_first_and_third_sides_are_equal(void) {
    TEST_IGNORE();
    triangle_t sides = { 3, 4, 3 } ;
    TEST_ASSERT_EQUAL_INT(0, is_scalene(sides));
}

void test_scalene_triangle_second_and_third_sides_are_equal(void) {
    TEST_IGNORE();
    triangle_t sides = { 4, 3, 3 } ;
    TEST_ASSERT_EQUAL_INT(0, is_scalene(sides));
}

void test_scalene_triangle_may_not_violate_triangle_inequality(void) {
    TEST_IGNORE();
    triangle_t sides = { 7, 3, 2 } ;
    TEST_ASSERT_EQUAL_INT(0, is_scalene(sides));
}

void test_scalene_triangle_sides_may_be_floats(void) {
    TEST_IGNORE();
    triangle_t sides = { 0.5, 0.4, 0.6 } ;
    TEST_ASSERT_EQUAL_INT(1, is_scalene(sides));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_equilateral_triangle_all_sides_are_equal);
    RUN_TEST(test_equilateral_triangle_any_side_is_unequal);
    RUN_TEST(test_equilateral_triangle_no_sides_are_equal);
    RUN_TEST(test_equilateral_triangle_all_zero_sides_is_not_a_triangle);
    RUN_TEST(test_equilateral_triangle_sides_may_be_floats);
    RUN_TEST(test_isosceles_triangle_last_two_sides_are_equal);
    RUN_TEST(test_isosceles_triangle_first_two_sides_are_equal);
    RUN_TEST(test_isosceles_triangle_first_and_last_sides_are_equal);
    RUN_TEST(test_isosceles_triangle_equilateral_triangles_are_also_isosceles);
    RUN_TEST(test_isosceles_triangle_no_sides_are_equal);
    RUN_TEST(test_isosceles_triangle_first_triangle_inequality_violation);
    RUN_TEST(test_isosceles_triangle_second_triangle_inequality_violation);
    RUN_TEST(test_isosceles_triangle_third_triangle_inequality_violation);
    RUN_TEST(test_isosceles_triangle_sides_may_be_floats);
    RUN_TEST(test_scalene_triangle_no_sides_are_equal);
    RUN_TEST(test_scalene_triangle_all_sides_are_equal);
    RUN_TEST(test_scalene_triangle_first_and_second_sides_are_equal);
    RUN_TEST(test_scalene_triangle_first_and_third_sides_are_equal);
    RUN_TEST(test_scalene_triangle_second_and_third_sides_are_equal);
    RUN_TEST(test_scalene_triangle_may_not_violate_triangle_inequality);
    RUN_TEST(test_scalene_triangle_sides_may_be_floats);
    return UNITY_END();
}
