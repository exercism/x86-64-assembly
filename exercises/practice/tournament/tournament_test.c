#include "vendor/unity.h"

#include <stdalign.h>

#define BUFFER_SIZE 512
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern void tally(char buffer[], const char rows[]);

void setUp(void) {
}

void tearDown(void) {
}

void test_just_the_header_if_no_input(void) {
    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] = "";
    const char *expected = "Team                           | MP |  W |  D |  L |  P";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_a_win_is_three_points_a_loss_is_zero_points(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] = "Allegoric Alaskans;Blithering Badgers;win";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Allegoric Alaskans             |  1 |  1 |  0 |  0 |  3\n"
        "Blithering Badgers             |  1 |  0 |  0 |  1 |  0";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_a_win_can_also_be_expressed_as_a_loss(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] = "Blithering Badgers;Allegoric Alaskans;loss";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Allegoric Alaskans             |  1 |  1 |  0 |  0 |  3\n"
        "Blithering Badgers             |  1 |  0 |  0 |  1 |  0";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_a_different_team_can_win(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] = "Blithering Badgers;Allegoric Alaskans;win";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Blithering Badgers             |  1 |  1 |  0 |  0 |  3\n"
        "Allegoric Alaskans             |  1 |  0 |  0 |  1 |  0";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_a_draw_is_one_point_each(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] = "Allegoric Alaskans;Blithering Badgers;draw";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Allegoric Alaskans             |  1 |  0 |  1 |  0 |  1\n"
        "Blithering Badgers             |  1 |  0 |  1 |  0 |  1";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_there_can_be_more_than_one_match(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Allegoric Alaskans;Blithering Badgers;win\n"
        "Allegoric Alaskans;Blithering Badgers;win";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Allegoric Alaskans             |  2 |  2 |  0 |  0 |  6\n"
        "Blithering Badgers             |  2 |  0 |  0 |  2 |  0";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_there_can_be_more_than_one_winner(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Allegoric Alaskans;Blithering Badgers;loss\n"
        "Allegoric Alaskans;Blithering Badgers;win";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Allegoric Alaskans             |  2 |  1 |  0 |  1 |  3\n"
        "Blithering Badgers             |  2 |  1 |  0 |  1 |  3";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_there_can_be_more_than_two_teams(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Allegoric Alaskans;Blithering Badgers;win\n"
        "Blithering Badgers;Courageous Californians;win\n"
        "Courageous Californians;Allegoric Alaskans;loss";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Allegoric Alaskans             |  2 |  2 |  0 |  0 |  6\n"
        "Blithering Badgers             |  2 |  1 |  0 |  1 |  3\n"
        "Courageous Californians        |  2 |  0 |  0 |  2 |  0";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_typical_input(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Allegoric Alaskans;Blithering Badgers;win\n"
        "Devastating Donkeys;Courageous Californians;draw\n"
        "Devastating Donkeys;Allegoric Alaskans;win\n"
        "Courageous Californians;Blithering Badgers;loss\n"
        "Blithering Badgers;Devastating Donkeys;loss\n"
        "Allegoric Alaskans;Courageous Californians;win";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Devastating Donkeys            |  3 |  2 |  1 |  0 |  7\n"
        "Allegoric Alaskans             |  3 |  2 |  0 |  1 |  6\n"
        "Blithering Badgers             |  3 |  1 |  0 |  2 |  3\n"
        "Courageous Californians        |  3 |  0 |  1 |  2 |  1";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_incomplete_competition_not_all_pairs_have_played(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Allegoric Alaskans;Blithering Badgers;loss\n"
        "Devastating Donkeys;Allegoric Alaskans;loss\n"
        "Courageous Californians;Blithering Badgers;draw\n"
        "Allegoric Alaskans;Courageous Californians;win";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Allegoric Alaskans             |  3 |  2 |  0 |  1 |  6\n"
        "Blithering Badgers             |  2 |  1 |  1 |  0 |  4\n"
        "Courageous Californians        |  2 |  0 |  1 |  1 |  1\n"
        "Devastating Donkeys            |  1 |  0 |  0 |  1 |  0";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_ties_broken_alphabetically(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Courageous Californians;Devastating Donkeys;win\n"
        "Allegoric Alaskans;Blithering Badgers;win\n"
        "Devastating Donkeys;Allegoric Alaskans;loss\n"
        "Courageous Californians;Blithering Badgers;win\n"
        "Blithering Badgers;Devastating Donkeys;draw\n"
        "Allegoric Alaskans;Courageous Californians;draw";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Allegoric Alaskans             |  3 |  2 |  1 |  0 |  7\n"
        "Courageous Californians        |  3 |  2 |  1 |  0 |  7\n"
        "Blithering Badgers             |  3 |  0 |  1 |  2 |  1\n"
        "Devastating Donkeys            |  3 |  0 |  1 |  2 |  1";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_ensure_points_sorted_numerically(void) {
    TEST_IGNORE();

    char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Devastating Donkeys;Blithering Badgers;win\n"
        "Devastating Donkeys;Blithering Badgers;win\n"
        "Devastating Donkeys;Blithering Badgers;win\n"
        "Devastating Donkeys;Blithering Badgers;win\n"
        "Blithering Badgers;Devastating Donkeys;win";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Devastating Donkeys            |  5 |  4 |  0 |  1 | 12\n"
        "Blithering Badgers             |  5 |  1 |  0 |  4 |  3";

    tally(buffer, rows);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_just_the_header_if_no_input);
    RUN_TEST(test_a_win_is_three_points_a_loss_is_zero_points);
    RUN_TEST(test_a_win_can_also_be_expressed_as_a_loss);
    RUN_TEST(test_a_different_team_can_win);
    RUN_TEST(test_a_draw_is_one_point_each);
    RUN_TEST(test_there_can_be_more_than_one_match);
    RUN_TEST(test_there_can_be_more_than_one_winner);
    RUN_TEST(test_there_can_be_more_than_two_teams);
    RUN_TEST(test_typical_input);
    RUN_TEST(test_incomplete_competition_not_all_pairs_have_played);
    RUN_TEST(test_ties_broken_alphabetically);
    RUN_TEST(test_ensure_points_sorted_numerically);
    return UNITY_END();
}
