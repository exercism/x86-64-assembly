// Version: 1.0.0

#include "vendor/unity.h"

// Returns 1 if queen can be created, otherwise 0.
extern int can_create(int row, int column);

// Returns 1 if queens attack, otherwise 0.
extern int can_attack(int white_row, int white_column, int black_row, int black_column);

void setUp(void) {
}

void tearDown(void) {
}

void test_queen_with_a_valid_position(void) {
    TEST_ASSERT_TRUE(can_create(2, 2));
}

void test_queen_must_have_positive_row(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(can_create(-2, 2));
}

void test_queen_must_have_row_on_board(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(can_create(8, 4));
}

void test_queen_must_have_positive_column(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(can_create(2, -2));
}

void test_queen_must_have_column_on_board(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(can_create(4, 8));
}

void test_cannot_attack(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(can_attack(2, 4, 6, 6));
}

void test_can_attack_on_same_row(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(can_attack(2, 4, 2, 6));
}

void test_can_attack_on_same_column(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(can_attack(4, 5, 2, 5));
}

void test_can_attack_on_first_diagonal(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(can_attack(2, 2, 0, 4));
}

void test_can_attack_on_second_diagonal(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(can_attack(2, 2, 3, 1));
}

void test_can_attack_on_third_diagonal(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(can_attack(2, 2, 1, 1));
}

void test_can_attack_on_fourth_diagonal(void) {
    TEST_IGNORE();
    TEST_ASSERT_TRUE(can_attack(1, 7, 0, 6));
}

void test_cannot_attack_if_falling_diagonals_are_only_the_same_when_reflected_across_the_longest_falling_diagonal(void) {
    TEST_IGNORE();
    TEST_ASSERT_FALSE(can_attack(4, 1, 2, 5));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_queen_with_a_valid_position);
    RUN_TEST(test_queen_must_have_positive_row);
    RUN_TEST(test_queen_must_have_row_on_board);
    RUN_TEST(test_queen_must_have_positive_column);
    RUN_TEST(test_queen_must_have_column_on_board);
    RUN_TEST(test_cannot_attack);
    RUN_TEST(test_can_attack_on_same_row);
    RUN_TEST(test_can_attack_on_same_column);
    RUN_TEST(test_can_attack_on_first_diagonal);
    RUN_TEST(test_can_attack_on_second_diagonal);
    RUN_TEST(test_can_attack_on_third_diagonal);
    RUN_TEST(test_can_attack_on_fourth_diagonal);
    RUN_TEST(test_cannot_attack_if_falling_diagonals_are_only_the_same_when_reflected_across_the_longest_falling_diagonal);
    return UNITY_END();
}
