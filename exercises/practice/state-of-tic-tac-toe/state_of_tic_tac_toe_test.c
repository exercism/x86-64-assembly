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
        // clang-format off
        "XOO",
        "X  ",
        "X  ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_middle_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "OXO",
        " X ",
        " X ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_right_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "OOX",
        "  X",
        "  X",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_left_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "OXX",
        "OX ",
        "O  ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_middle_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XOX",
        " OX",
        " O ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_right_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XXO",
        " XO",
        "  O",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_top_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XXX",
        "XOO",
        "O  ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_middle_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "O  ",
        "XXX",
        " O ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_bottom_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        " OO",
        "O X",
        "XXX",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_top_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "OOO",
        "XXO",
        "XX ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_middle_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XX ",
        "OOO",
        "X  ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_bottom_row_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XOX",
        " XX",
        "OOO",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_falling_diagonal_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XOO",
        " X ",
        "  X",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_rising_diagonal_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "O X",
        "OX ",
        "X  ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_falling_diagonal_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "OXX",
        "OOX",
        "X O",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_o_won_via_rising_diagonal_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "  O",
        " OX",
        "OXX",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_a_row_and_a_column_victory(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XXX",
        "XOO",
        "XOO",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_finished_game_where_x_won_via_two_diagonal_victories(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XOX",
        "OXO",
        "XOX",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(WIN, gamestate(board));
}

void test_draw(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XOX",
        "XXO",
        "OXO",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(DRAW, gamestate(board));
}

void test_another_draw(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XXO",
        "OXX",
        "XOO",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(DRAW, gamestate(board));
}

void test_ongoing_game_one_move_in(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "   ",
        "X  ",
        "   ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(ONGOING, gamestate(board));
}

void test_ongoing_game_two_moves_in(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "O  ",
        " X ",
        "   ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(ONGOING, gamestate(board));
}

void test_ongoing_game_five_moves_in(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "X  ",
        " XO",
        "OX ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(ONGOING, gamestate(board));
}

void test_invalid_board_x_went_twice(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XX ",
        "   ",
        "   ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(INVALID, gamestate(board));
}

void test_invalid_board_o_started(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "OOX",
        "   ",
        "   ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(INVALID, gamestate(board));
}

void test_invalid_board_x_won_and_o_kept_playing(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XXX",
        "OOO",
        "   ",
        NULL
        // clang-format on
    };
    TEST_ASSERT_EQUAL_INT(INVALID, gamestate(board));
}

void test_invalid_board_players_kept_playing_after_a_win(void) {
    TEST_IGNORE();
    const char *board[] = {
        // clang-format off
        "XXX",
        "OOO",
        "XOX",
        NULL
        // clang-format on
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
