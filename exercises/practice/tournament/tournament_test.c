#include "vendor/unity.h"

#include <stdalign.h>

#define BUFFER_SIZE 1024
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern void tally(char buffer[], const char rows[]);

void setUp(void) {
}

void tearDown(void) {
}

void test_just_the_header_if_no_input(void) {
    alignas(16) char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] = "";
    const char *expected = "Team                           | MP |  W |  D |  L |  P";

    tally(buffer, rows);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_a_win_is_three_points_a_loss_is_zero_points(void) {
    TEST_IGNORE();

    alignas(16) char buffer[BUFFER_SIZE];
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

    alignas(16) char buffer[BUFFER_SIZE];
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

    alignas(16) char buffer[BUFFER_SIZE];
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

    alignas(16) char buffer[BUFFER_SIZE];
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

    alignas(16) char buffer[BUFFER_SIZE];
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

    alignas(16) char buffer[BUFFER_SIZE];
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

    alignas(16) char buffer[BUFFER_SIZE];
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

    alignas(16) char buffer[BUFFER_SIZE];
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

    alignas(16) char buffer[BUFFER_SIZE];
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

    alignas(16) char buffer[BUFFER_SIZE];
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

    alignas(16) char buffer[BUFFER_SIZE];
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

void test_team_names_sharing_the_first_letter(void) {
    TEST_IGNORE();

    alignas(16) char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Invincible Iguanas;Primal Panthers;draw\n"
        "Polar Penguins;Thunderous Tigers;loss\n"
        "Heroic Hawks;Howling Hyenas;win\n"
        "Tenacious Turtles;Thunderous Tigers;win";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Heroic Hawks                   |  1 |  1 |  0 |  0 |  3\n"
        "Tenacious Turtles              |  1 |  1 |  0 |  0 |  3\n"
        "Thunderous Tigers              |  2 |  1 |  0 |  1 |  3\n"
        "Invincible Iguanas             |  1 |  0 |  1 |  0 |  1\n"
        "Primal Panthers                |  1 |  0 |  1 |  0 |  1\n"
        "Howling Hyenas                 |  1 |  0 |  0 |  1 |  0\n"
        "Polar Penguins                 |  1 |  0 |  0 |  1 |  0";

    tally(buffer, rows);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_team_composite_names_sharing_the_first_word(void) {
    TEST_IGNORE();

    alignas(16) char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Courageous Cougars;Courageous Californians;win\n"
        "Courageous Californians;Blithering Badgers;win\n"
        "Courageous Cougars;Wild Wolverines;draw\n"
        "Charging Cheetahs;Wild Wolves;loss\n"
        "Thunderous Tigers;Zealous Zebras;win\n"
        "Wild Wolves;Thunderous Tigers;draw";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Courageous Cougars             |  2 |  1 |  1 |  0 |  4\n"
        "Thunderous Tigers              |  2 |  1 |  1 |  0 |  4\n"
        "Wild Wolves                    |  2 |  1 |  1 |  0 |  4\n"
        "Courageous Californians        |  2 |  1 |  0 |  1 |  3\n"
        "Wild Wolverines                |  1 |  0 |  1 |  0 |  1\n"
        "Blithering Badgers             |  1 |  0 |  0 |  1 |  0\n"
        "Charging Cheetahs              |  1 |  0 |  0 |  1 |  0\n"
        "Zealous Zebras                 |  1 |  0 |  0 |  1 |  0";

    tally(buffer, rows);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_team_composite_names_sharing_the_second_word(void) {
    TEST_IGNORE();

    alignas(16) char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Proud Panthers;Primal Panthers;win\n"
        "Heroic Hawks;Blithering Badgers;win\n"
        "Heroic Hedgehogs;Wild Wolves;draw\n"
        "Fierce Falcons;Courageous Cougars;loss\n"
        "Furious Foxes;Flying Falcons;draw\n"
        "Wild Wolves;Flying Falcons;loss\n"
        "Primal Panthers;Heroic Hawks;win\n"
        "Flying Falcons;Proud Panthers;win";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Flying Falcons                 |  3 |  2 |  1 |  0 |  7\n"
        "Courageous Cougars             |  1 |  1 |  0 |  0 |  3\n"
        "Heroic Hawks                   |  2 |  1 |  0 |  1 |  3\n"
        "Primal Panthers                |  2 |  1 |  0 |  1 |  3\n"
        "Proud Panthers                 |  2 |  1 |  0 |  1 |  3\n"
        "Furious Foxes                  |  1 |  0 |  1 |  0 |  1\n"
        "Heroic Hedgehogs               |  1 |  0 |  1 |  0 |  1\n"
        "Wild Wolves                    |  2 |  0 |  1 |  1 |  1\n"
        "Blithering Badgers             |  1 |  0 |  0 |  1 |  0\n"
        "Fierce Falcons                 |  1 |  0 |  0 |  1 |  0";

    tally(buffer, rows);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_many_teams_with_names_sharing_prefixes_and_suffixes(void) {
    TEST_IGNORE();

    alignas(16) char buffer[BUFFER_SIZE];
    alignas(16) const char rows[] =
        "Zealous Zebras;Charging Cheetahs;loss\n"
        "Monolith;Blithering Badgers;win\n"
        "Primal Panthers;Blithering Badgers;win\n"
        "Thunderous Tigers;Howling Hyenas;win\n"
        "Furious Foxes;Wild Wolves;draw\n"
        "Nebula;Tenacious Turtles;loss\n"
        "Heroic Hawks;Wild Wolves;win\n"
        "Blithering Badgers;Devastating Donkeys;loss\n"
        "Swift Iron Wolf Pack;Zealous Zebras;win\n"
        "Charging Cheetahs;Thunderous Tigers;draw\n"
        "Howling Hyenas;Primal Panthers;loss\n"
        "Proud Panthers;Primal Panthers;draw\n"
        "Flying Falcons;Proud Panthers;win\n"
        "Fierce Falcons;Flying Falcons;loss\n"
        "Tenacious Turtles;Heroic Hawks;win\n"
        "Devastating Donkeys;Charging Cheetahs;win\n"
        "Fierce Falcons;Primal Panthers;loss\n"
        "Wild Wolves;Tenacious Turtles;draw\n"
        "Furious Foxes;Blithering Badgers;draw\n"
        "Charging Cheetahs;Primal Panthers;loss\n"
        "Devastating Donkeys;Thunderous Tigers;loss\n"
        "Heroic Hawks;Primal Panthers;win\n"
        "Tenacious Turtles;Primal Panthers;win\n"
        "Blithering Badgers;Zealous Zebras;draw\n"
        "Swift Iron Wolf Pack;Howling Hyenas;win\n"
        "Fierce Falcons;Swift Iron Wolf Pack;draw\n"
        "Flying Falcons;Zealous Zebras;loss\n"
        "Devastating Donkeys;Proud Panthers;draw\n"
        "Primal Panthers;Swift Iron Wolf Pack;win\n"
        "Heroic Hawks;Charging Cheetahs;draw\n"
        "Howling Hyenas;Devastating Donkeys;loss\n"
        "Wild Wolves;Flying Falcons;win\n"
        "Thunderous Tigers;Blithering Badgers;win\n"
        "Proud Panthers;Furious Foxes;draw\n"
        "Fierce Falcons;Tenacious Turtles;loss\n"
        "Primal Panthers;Zealous Zebras;draw\n"
        "Charging Cheetahs;Proud Panthers;draw\n"
        "Tenacious Turtles;Wild Wolves;win\n"
        "Furious Foxes;Heroic Hawks;loss\n"
        "Blithering Badgers;Flying Falcons;win\n"
        "Devastating Donkeys;Swift Iron Wolf Pack;draw\n"
        "Zealous Zebras;Howling Hyenas;draw\n"
        "Primal Panthers;Blithering Badgers;loss\n"
        "Fierce Falcons;Devastating Donkeys;draw\n"
        "Swift Iron Wolf Pack;Thunderous Tigers;loss\n"
        "Flying Falcons;Charging Cheetahs;win\n"
        "Heroic Hawks;Furious Foxes;loss\n"
        "Tenacious Turtles;Devastating Donkeys;draw\n"
        "Monolith;Heroic Hawks;draw\n"
        "Nebula;Blithering Badgers;loss\n"
        "Wild Wolves;Furious Foxes;win\n"
        "Charging Cheetahs;Swift Iron Wolf Pack;loss\n"
        "Howling Hyenas;Thunderous Tigers;draw\n"
        "Proud Panthers;Zealous Zebras;win\n"
        "Primal Panthers;Flying Falcons;loss\n"
        "Fierce Falcons;Primal Panthers;win\n"
        "Tenacious Turtles;Blithering Badgers;draw\n"
        "Heroic Hawks;Devastating Donkeys;win\n"
        "Wild Wolves;Zealous Zebras;loss\n"
        "Monolith;Tenacious Turtles;win\n"
        "Nebula;Furious Foxes;draw";
    const char *expected =
        "Team                           | MP |  W |  D |  L |  P\n"
        "Tenacious Turtles              |  9 |  5 |  3 |  1 | 18\n"
        "Primal Panthers                | 12 |  5 |  2 |  5 | 17\n"
        "Heroic Hawks                   |  8 |  4 |  2 |  2 | 14\n"
        "Thunderous Tigers              |  6 |  4 |  2 |  0 | 14\n"
        "Devastating Donkeys            |  9 |  3 |  4 |  2 | 13\n"
        "Blithering Badgers             | 10 |  3 |  3 |  4 | 12\n"
        "Flying Falcons                 |  7 |  4 |  0 |  3 | 12\n"
        "Swift Iron Wolf Pack           |  7 |  3 |  2 |  2 | 11\n"
        "Zealous Zebras                 |  8 |  2 |  3 |  3 |  9\n"
        "Wild Wolves                    |  7 |  2 |  2 |  3 |  8\n"
        "Furious Foxes                  |  7 |  1 |  4 |  2 |  7\n"
        "Monolith                       |  3 |  2 |  1 |  0 |  7\n"
        "Proud Panthers                 |  6 |  1 |  4 |  1 |  7\n"
        "Charging Cheetahs              |  8 |  1 |  3 |  4 |  6\n"
        "Fierce Falcons                 |  6 |  1 |  2 |  3 |  5\n"
        "Howling Hyenas                 |  6 |  0 |  2 |  4 |  2\n"
        "Nebula                         |  3 |  0 |  1 |  2 |  1";

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
    RUN_TEST(test_team_names_sharing_the_first_letter);
    RUN_TEST(test_team_composite_names_sharing_the_first_word);
    RUN_TEST(test_team_composite_names_sharing_the_second_word);
    RUN_TEST(test_many_teams_with_names_sharing_prefixes_and_suffixes);
    return UNITY_END();
}
