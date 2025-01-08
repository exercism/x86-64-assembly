#include "vendor/unity.h"

#include <stddef.h>

enum state {
    ONGOING,
    DRAW,
    WIN,
    INVALID
};

extern int gamestate(const char **board);

void setUp(void) {
}

void tearDown(void) {
}

void test_finished_game_where_x_won_via_left_column_victory(void) {
    const char *board[] = {
      "XOO",
      "X  ",
      "X  ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_middle_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "OXO",
      " X ",
      " X ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_right_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "OOX",
      "  X",
      "  X",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_left_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "OXX",
      "OX ",
      "O  ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_middle_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XOX",
      " OX",
      " O ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_right_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XXO",
      " XO",
      "  O",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_top_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XXX",
      "XOO",
      "O  ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_middle_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "O  ",
      "XXX",
      " O ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_bottom_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      " OO",
      "O X",
      "XXX",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_top_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "OOO",
      "XXO",
      "XX ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_middle_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XX ",
      "OOO",
      "X  ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_bottom_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XOX",
      " XX",
      "OOO",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_falling_diagonal_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XOO",
      " X ",
      "  X",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_rising_diagonal_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "O X",
      "OX ",
      "X  ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_falling_diagonal_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "OXX",
      "OOX",
      "X O",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_rising_diagonal_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "  O",
      " OX",
      "OXX",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_a_row_and_a_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XXX",
      "XOO",
      "XOO",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_two_diagonal_victories(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XOX",
      "OXO",
      "XOX",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_draw(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XOX",
      "XXO",
      "OXO",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(DRAW, gamestate(board));
}

void test_another_draw(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XXO",
      "OXX",
      "XOO",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(DRAW, gamestate(board));
}

void test_ongoing_game_one_move_in(void) {
    TEST_IGNORE();
    const char *board[] = {
      "   ",
      "X  ",
      "   ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(ONGOING, gamestate(board));
}

void test_ongoing_game_two_moves_in(void) {
    TEST_IGNORE();
    const char *board[] = {
      "O  ",
      " X ",
      "   ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(ONGOING, gamestate(board));
}

void test_ongoing_game_five_moves_in(void) {
    TEST_IGNORE();
    const char *board[] = {
      "X  ",
      " XO",
      "OX ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(ONGOING, gamestate(board));
}

void test_invalid_board_x_went_twice(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XX ",
      "   ",
      "   ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(INVALID, gamestate(board));
}

void test_invalid_board_o_started(void) {
    TEST_IGNORE();
    const char *board[] = {
      "OOX",
      "   ",
      "   ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(INVALID, gamestate(board));
}

void test_invalid_board_x_won_and_o_kept_playing(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XXX",
      "OOO",
      "   ",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(INVALID, gamestate(board));
}

void test_invalid_board_players_kept_playing_after_a_win(void) {
    TEST_IGNORE();
    const char *board[] = {
      "XXX",
      "OOO",
      "XOX",
      NULL
    };
    TEST_ASSERT_EQUAL_INT(INVALID, gamestate(board));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_finished_game_where_x_won_via_left_column_victory);
    RUN_TEST(test_finished_game_where_x_won_via_middle_column_victory);
    RUN_TEST(test_finished_game_where_x_won_via_right_column_victory);
    RUN_TEST(test_finished_game_where_o_won_via_left_column_victory);
    RUN_TEST(test_finished_game_where_o_won_via_middle_column_victory);
    RUN_TEST(test_finished_game_where_o_won_via_right_column_victory);
    RUN_TEST(test_finished_game_where_x_won_via_top_row_victory);
    RUN_TEST(test_finished_game_where_x_won_via_middle_row_victory);
    RUN_TEST(test_finished_game_where_x_won_via_bottom_row_victory);
    RUN_TEST(test_finished_game_where_o_won_via_top_row_victory);
    RUN_TEST(test_finished_game_where_o_won_via_middle_row_victory);
    RUN_TEST(test_finished_game_where_o_won_via_bottom_row_victory);
    RUN_TEST(test_finished_game_where_x_won_via_falling_diagonal_victory);
    RUN_TEST(test_finished_game_where_x_won_via_rising_diagonal_victory);
    RUN_TEST(test_finished_game_where_o_won_via_falling_diagonal_victory);
    RUN_TEST(test_finished_game_where_o_won_via_rising_diagonal_victory);
    RUN_TEST(test_finished_game_where_x_won_via_a_row_and_a_column_victory);
    RUN_TEST(test_finished_game_where_x_won_via_two_diagonal_victories);
    RUN_TEST(test_draw);
    RUN_TEST(test_another_draw);
    RUN_TEST(test_ongoing_game_one_move_in);
    RUN_TEST(test_ongoing_game_two_moves_in);
    RUN_TEST(test_ongoing_game_five_moves_in);
    RUN_TEST(test_invalid_board_x_went_twice);
    RUN_TEST(test_invalid_board_o_started);
    RUN_TEST(test_invalid_board_x_won_and_o_kept_playing);
    RUN_TEST(test_invalid_board_players_kept_playing_after_a_win);
    return UNITY_END();
}
