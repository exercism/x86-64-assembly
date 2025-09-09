#include "vendor/unity.h"

#include <stddef.h>
#include <stdint.h>

typedef enum {
    C2 = 2,
    C3,
    C4,
    C5,
    C6,
    C7,
    C8,
    C9,
    C10,
    CJ,
    CQ,
    CK,
    CA
} card_t;

typedef enum {
    finished = 0,
    loop
} status_t;

typedef struct {
    status_t status;
    uint32_t cards;
    uint32_t tricks;
} result_t;

#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

extern result_t simulate_game(const card_t *playerA, size_t playerA_count, const card_t *playerB, size_t playerB_count);

void setUp(void) {
}

void tearDown(void) {
}

void test_two_cards_one_trick(void) {
    const card_t playerA[] = {C2};
    const card_t playerB[] = {C3};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 2, 1};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_three_cards_one_trick(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, C4};
    const card_t playerB[] = {C3};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 3, 1};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_four_cards_one_trick(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, C4};
    const card_t playerB[] = {C3, C5, C6};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 4, 1};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_the_ace_reigns_supreme(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, CA};
    const card_t playerB[] = {C3, C4, C5, C6, C7};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 7, 1};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_the_king_beats_ace(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, CA};
    const card_t playerB[] = {C3, C4, C5, C6, CK};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 7, 1};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_the_queen_seduces_the_king(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, CA, C7, C8, CQ};
    const card_t playerB[] = {C3, C4, C5, C6, CK};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 10, 1};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_the_jack_betrays_the_queen(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, CA, C7, C8, CQ};
    const card_t playerB[] = {C3, C4, C5, C6, CK, C9, CJ};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 12, 1};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_the_10_just_wants_to_put_on_a_show(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, CA, C7, C8, CQ, C10};
    const card_t playerB[] = {C3, C4, C5, C6, CK, C9, CJ};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 13, 1};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_simple_loop_with_decks_of_3_cards(void) {
    TEST_IGNORE();

    const card_t playerA[] = {CJ, C2, C3};
    const card_t playerB[] = {C4, CJ, C5};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {loop, 8, 3};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_the_story_is_starting_to_get_a_bit_complicated(void) {
    TEST_IGNORE();

    const card_t playerA[] = {
        C2, C6, C6, CJ, C4,  CK, CQ,  C10, CK, CJ, CQ,  C2, C3, CK, C5, C6, CQ, CQ, CA,  CA, C6,  C9,  CK, CA, C8, CK,  C2, CA, C9, CA,  CQ,
        C4, CK, CK, CK, C3,  C5, CK,  C8,  CQ, C3, CQ,  C7, CJ, CK, CJ, C9, CJ, C3, C3,  CK, CK,  CQ,  CA, CK, C7, C10, CA, CQ, C7, C10, CJ,
        C4, C5, CJ, C9, C10, CQ, CJ,  CJ,  CK, C6, C10, CJ, C6, CQ, CJ, C5, CJ, CQ, CQ,  C8, C3,  C8,  CA, C2, C6, C9,  CK, C7, CJ, CK,  CK,
        C8, CK, CQ, C6, C10, CJ, C10, CJ,  CQ, CJ, C10, C3, C8, CK, CA, C6, C9, CK, C2,  CA, CA,  C10, CJ, C6, CA, C4,  CJ, CA, CJ, CJ,  C6,
        C2, CJ, C3, CK, C2,  C5, C9,  CJ,  C9, C6, CK,  CA, C5, CQ, CJ, C2, CQ, CK, CA,  C3, CK,  CJ,  CK, C2, C5, C6,  CQ, CJ, CQ, CQ,  CJ,
        C2, CJ, C9, CQ, C7,  C7, CA,  CQ,  C7, CQ, CJ,  CK, CJ, CA, C7, C7, C8, CQ, C10, CJ, C10, CJ,  CJ, C9, C2, CA,  C2};
    const card_t playerB[] = {
        C7, C2,  C10, CK, C8, C2,  CJ,  C9, CA, C5, C6,  CJ, CQ, C6,  CK,  C6,  C5, CA, C4,  CQ, C7, CJ, C7, C10, C2,  CQ, C8,  C2, C2, CK,
        CJ, CA,  C5,  C5, CA, C4,  CQ,  C6, CQ, CK, C10, C8, CQ, C2,  C10, CJ,  CA, CQ, C8,  CQ, CQ, CJ, CJ, CA,  CA,  C9, C10, CJ, CK, C4,
        CQ, C10, C10, CJ, CK, C10, C2,  CJ, C7, CA, CK,  CK, CJ, CA,  CJ,  C10, C8, CK, CA,  C7, CQ, CQ, CJ, C3,  CQ,  C4, CA,  C3, CA, CQ,
        CQ, CQ,  C5,  C4, CK, CJ,  C10, CA, CQ, CJ, C6,  CJ, CA, C10, CA,  C5,  C8, C3, CK,  C5, C9, CQ, C8, C7,  C7,  CJ, C7,  CQ, CQ, CQ,
        CA, C7,  C8,  C9, CA, CQ,  CA,  CK, C8, CA, CA,  CJ, C8, C4,  C8,  CK,  CJ, CA, C10, CQ, C8, CJ, C8, C6,  C10, CQ, CJ,  CJ, CA, CA,
        CJ, C5,  CQ,  C6, CJ, CK,  CQ,  C8, CK, C4, CQ,  CQ, C6, CJ,  CK,  C4,  C7, CJ, CJ,  C9, C9, CA, CQ, CQ,  CK,  CA, C6,  C5, CK};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 361, 1};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_two_tricks(void) {
    TEST_IGNORE();

    const card_t playerA[] = {CJ};
    const card_t playerB[] = {C3, CJ};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 5, 2};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_more_tricks(void) {
    TEST_IGNORE();

    const card_t playerA[] = {CJ, C2, C4};
    const card_t playerB[] = {C3, CJ, CA};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 12, 4};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_simple_loop_with_decks_of_4_cards(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, C3, CJ, C6};
    const card_t playerB[] = {CK, C5, CJ, C7};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {loop, 16, 4};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_easy_card_combination(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C4, C8, C7, C5, C4, C10, C3, C9, C7, C3, C10, C10, C6, C8, C2, C8, C5, C4, C5, C9, C6, C5, C2, C8, C10, C9};
    const card_t playerB[] = {C6, C9, C4, C7, C2, C2, C3, C6, C7, C3, CA, CA, CA, CA, CK, CK, CK, CK, CQ, CQ, CQ, CQ, CJ, CJ, CJ, CJ};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 40, 4};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_easy_card_combination_inverted_decks(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C3, C3, C5, C7, C3, C2, C10, C7, C6, C7, CA, CA, CA, CA, CK, CK, CK, CK, CQ, CQ, CQ, CQ, CJ, CJ, CJ, CJ};
    const card_t playerB[] = {C5, C10, C8, C2, C6, C7, C2, C4, C9, C2, C6, C10, C10, C5, C4, C8, C4, C8, C6, C9, C8, C5, C9, C3, C4, C9};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 40, 4};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_mirrored_decks(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, CA, C3, CA, C3, CK, C4, CK, C2, CQ, C2, CQ, C10, CJ, C5, CJ, C6, C10, C2, C9, C10, C7, C3, C9, C6, C9};
    const card_t playerB[] = {C6, CA, C4, CA, C7, CK, C4, CK, C7, CQ, C7, CQ, C5, CJ, C8, CJ, C4, C5, C8, C9, C10, C6, C8, C3, C8, C5};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 59, 4};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_opposite_decks(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C4, CA, C9, CA, C4, CK, C9, CK, C6, CQ, C8, CQ, C8, CJ, C10, CJ, C9, C8, C4, C6, C3, C6, C5, C2, C4, C3};
    const card_t playerB[] = {C10, C7, C3, C2, C9, C2, C7, C8, C7, C5, CJ, C7, CJ, C10, CQ, C10, CQ, C3, CK, C5, CK, C6, CA, C2, CA, C5};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 151, 21};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_random_decks_1(void) {
    TEST_IGNORE();

    const card_t playerA[] = {CK, C10, C9, C8, CJ, C8, C6, C9, C7, CA, CK, C5, C4, C4, CJ, C5, CJ, C4, C3, C5, C8, C6, C7, C7, C4, C9};
    const card_t playerB[] = {C6, C3, CK, CA, CQ, C10, CA, C2, CQ, C8, C2, C10, C10, C2, CQ, C3, CK, C9, C7, CA, C3, CQ, C5, CJ, C2, C6};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 542, 76};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_random_decks_2(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C8, CA, C4, C8, C5, CQ, CJ, C2, C6, C2, C9, C7, CK, CA, C8, C10, CK, C8, C10, C9, CK, C6, C7, C3, CK, C9};
    const card_t playerB[] = {C10, C5, C2, C6, CQ, CJ, CA, C9, C5, C5, C3, C7, C3, CJ, CA, C2, CQ, C3, CJ, CQ, C4, C10, C4, C7, C4, C6};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 327, 42};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_kleber_1999(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C4, C8, C9, CJ, CQ, C8, C5, C5, CK, C2, CA, C9, C8, C5, C10, CA, C4, CJ, C3, CK, C6, C9, C2, CQ, CK, C7};
    const card_t playerB[] = {C10, CJ, C3, C2, C4, C10, C4, C7, C5, C3, C6, C6, C7, CA, CJ, CQ, CA, C7, C2, C10, C3, CK, C9, C6, C8, CQ};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 5790, 805};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_collins_2006(void) {
    TEST_IGNORE();

    const card_t playerA[] = {CA, C8, CQ, CK, C9, C10, C3, C7, C4, C2, CQ, C3, C2, C10, C9, CK, CA, C8, C7, C7, C4, C5, CJ, C9, C2, C10};
    const card_t playerB[] = {C4, CJ, CA, CK, C8, C5, C6, C6, CA, C6, C5, CQ, C4, C6, C10, C8, CJ, C2, C5, C7, CQ, CJ, C3, C3, CK, C9};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 6913, 960};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_mann_and_wu_2007(void) {
    TEST_IGNORE();

    const card_t playerA[] = {CK, C2, CK, CK, C3, C3, C6, C10, CK, C6, CA, C2, C5, C5, C7, C9, CJ, CA, CA, C3, C4, CQ, C4, C8, CJ, C6};
    const card_t playerB[] = {C4, C5, C2, CQ, C7, C9, C9, CQ, C7, CJ, C9, C8, C10, C3, C10, CJ, C4, C10, C8, C6, C8, C7, CA, CQ, C5, C2};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 7157, 1007};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_nessler_2012(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C10, C3, C6, C7, CQ, C2, C9, C8, C2, C8, C4, CA, C10, C6, CK, C2, C10, CA, C5, CA, C2, C4, CQ, CJ, CK, C4};
    const card_t playerB[] = {C10, CQ, C4, C6, CJ, C9, C3, CJ, C9, C3, C3, CQ, CK, C5, C9, C5, CK, C6, C5, C7, C8, CJ, CA, C7, C8, C7};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 7207, 1015};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_anderson_2013(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C6, C7, CA, C3, CQ, C3, C5, CJ, C3, C2, CJ, C7, C4, C5, CQ, C10, C5, CA, CJ, C2, CK, C8, C9, C9, CK, C3};
    const card_t playerB[] = {C4, CJ, C6, C9, C8, C5, C10, C7, C9, CQ, C2, C7, C10, C8, C4, C10, CA, C6, C4, CA, C6, C8, CQ, CK, CK, C2};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 7225, 1016};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_rucklidge_2014(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C8, CJ, C2, C9, C4, C4, C5, C8, CQ, C3, C9, C3, C6, C2, C8, CA, CA, CA, C9, C4, C7, C2, C5, CQ, CQ, C3};
    const card_t playerB[] = {CK, C7, C10, C6, C3, CJ, CA, C7, C6, C5, C5, C8, C10, C9, C10, C4, C2, C7, CK, CQ, C10, CK, C6, CJ, CJ, CK};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 7959, 1122};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_nessler_2021(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C7, C2, C3, C4, CK, C9, C6, C10, CA, C8, C9, CQ, C7, CA, C4, C8, CJ, CJ, CA, C4, C3, C2, C5, C6, C6, CJ};
    const card_t playerB[] = {C3, C10, C8, C9, C8, CK, CK, C2, C5, C5, C7, C6, C4, C3, C5, C7, CA, C9, CJ, CK, C2, CQ, C10, CQ, C10, CQ};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 7972, 1106};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_nessler_2022(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, C10, C10, CA, CJ, C3, C8, CQ, C2, C5, C5, C5, C9, C2, C4, C3, C10, CQ, CA, CK, CQ, CJ, CJ, C9, CQ, CK};
    const card_t playerB[] = {C10, C7, C6, C3, C6, CA, C8, C9, C4, C3, CK, CJ, C6, CK, C4, C9, C7, C8, C5, C7, C8, C2, CA, C7, C4, C6};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {finished, 8344, 1164};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

void test_casella_2024_first_infinite_game_found(void) {
    TEST_IGNORE();

    const card_t playerA[] = {C2, C8, C4, CK, C5, C2, C3, CQ, C6, CK, CQ, CA, CJ, C3, C5, C9, C8, C3, CA, CA, CJ, C4, C4, CJ, C7, C5};
    const card_t playerB[] = {C7, C7, C8, C6, C10, C10, C6, C10, C7, C2, CQ, C6, C3, C2, C4, CK, CQ, C10, CJ, C5, C9, C8, C9, C9, CK, CA};

    const result_t actual = simulate_game(playerA, ARRAY_SIZE(playerA), playerB, ARRAY_SIZE(playerB));
    const result_t expected = {loop, 474, 66};

    TEST_ASSERT_EQUAL(expected.status, actual.status);
    TEST_ASSERT_EQUAL(expected.cards, actual.cards);
    TEST_ASSERT_EQUAL(expected.tricks, actual.tricks);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_two_cards_one_trick);
    RUN_TEST(test_three_cards_one_trick);
    RUN_TEST(test_four_cards_one_trick);
    RUN_TEST(test_the_ace_reigns_supreme);
    RUN_TEST(test_the_king_beats_ace);
    RUN_TEST(test_the_queen_seduces_the_king);
    RUN_TEST(test_the_jack_betrays_the_queen);
    RUN_TEST(test_the_10_just_wants_to_put_on_a_show);
    RUN_TEST(test_simple_loop_with_decks_of_3_cards);
    RUN_TEST(test_the_story_is_starting_to_get_a_bit_complicated);
    RUN_TEST(test_two_tricks);
    RUN_TEST(test_more_tricks);
    RUN_TEST(test_simple_loop_with_decks_of_4_cards);
    RUN_TEST(test_easy_card_combination);
    RUN_TEST(test_easy_card_combination_inverted_decks);
    RUN_TEST(test_mirrored_decks);
    RUN_TEST(test_opposite_decks);
    RUN_TEST(test_random_decks_1);
    RUN_TEST(test_random_decks_2);
    RUN_TEST(test_kleber_1999);
    RUN_TEST(test_collins_2006);
    RUN_TEST(test_mann_and_wu_2007);
    RUN_TEST(test_nessler_2012);
    RUN_TEST(test_anderson_2013);
    RUN_TEST(test_rucklidge_2014);
    RUN_TEST(test_nessler_2021);
    RUN_TEST(test_nessler_2022);
    RUN_TEST(test_casella_2024_first_infinite_game_found);
    return UNITY_END();
}
