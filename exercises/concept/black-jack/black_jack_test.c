#include "vendor/unity.h"

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t card_t;

typedef struct {
    uint64_t fst;
    uint64_t snd;
} card_pair_t;

static const card_t C2 = 2;
static const card_t C3 = 3;
static const card_t C4 = 4;
static const card_t C5 = 5;
static const card_t C6 = 6;
static const card_t C7 = 7;
static const card_t C8 = 8;
static const card_t C9 = 9;
static const card_t C10 = 10;
static const card_t CJ = 11;
static const card_t CQ = 12;
static const card_t CK = 13;
static const card_t CA = 14;

extern uint64_t value_of_card(card_t card);
extern card_pair_t higher_card(card_t card_one, card_t card_two);
extern uint64_t value_of_ace(card_t card_one, card_t card_two);
extern bool is_blackjack(card_t card_one, card_t card_two);
extern bool can_split_pairs(card_t card_one, card_t card_two);
extern bool can_double_down(card_t card_one, card_t card_two);

void setUp(void) {
}

void tearDown(void) {
}

void test_value_of_card_2(void) {
    TEST_ASSERT_EQUAL_UINT64(2, value_of_card(C2));
}

void test_value_of_card_5(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(5, value_of_card(C5));
}

void test_value_of_card_a(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(1, value_of_card(CA));
}

void test_value_of_card_j(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(10, value_of_card(CJ));
}

void test_value_of_card_8(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(8, value_of_card(C8));
}

void test_value_of_card_k(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(10, value_of_card(CK));
}

void test_value_of_card_q(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(10, value_of_card(CQ));
}

void test_higher_card_4_8(void) {
    TEST_IGNORE();
    const card_pair_t expected = {C8, 0};
    const card_pair_t actual = higher_card(C4, C8);
    TEST_ASSERT((actual.fst == expected.snd && actual.snd == expected.fst) || (actual.fst == expected.fst && actual.snd == expected.snd));
}

void test_higher_card_a_a(void) {
    TEST_IGNORE();
    const card_pair_t expected = {CA, CA};
    const card_pair_t actual = higher_card(CA, CA);
    TEST_ASSERT((actual.fst == expected.snd && actual.snd == expected.fst) || (actual.fst == expected.fst && actual.snd == expected.snd));
}

void test_higher_card_6_j(void) {
    TEST_IGNORE();
    const card_pair_t expected = {CJ, 0};
    const card_pair_t actual = higher_card(C6, CJ);
    TEST_ASSERT((actual.fst == expected.snd && actual.snd == expected.fst) || (actual.fst == expected.fst && actual.snd == expected.snd));
}

void test_higher_card_10_j(void) {
    TEST_IGNORE();
    const card_pair_t expected = {C10, CJ};
    const card_pair_t actual = higher_card(C10, CJ);
    TEST_ASSERT((actual.fst == expected.snd && actual.snd == expected.fst) || (actual.fst == expected.fst && actual.snd == expected.snd));
}

void test_higher_card_3_a(void) {
    TEST_IGNORE();
    const card_pair_t expected = {C3, 0};
    const card_pair_t actual = higher_card(C3, CA);
    TEST_ASSERT((actual.fst == expected.snd && actual.snd == expected.fst) || (actual.fst == expected.fst && actual.snd == expected.snd));
}

void test_higher_card_5_5(void) {
    TEST_IGNORE();
    const card_pair_t expected = {C5, C5};
    const card_pair_t actual = higher_card(C5, C5);
    TEST_ASSERT((actual.fst == expected.snd && actual.snd == expected.fst) || (actual.fst == expected.fst && actual.snd == expected.snd));
}

void test_value_of_ace_2_3(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(11, value_of_ace(C2, C3));
}

void test_value_of_ace_a_q(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(1, value_of_ace(CA, CQ));
}

void test_value_of_ace_5_5(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(11, value_of_ace(C5, C5));
}

void test_value_of_ace_a_2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(1, value_of_ace(CA, C2));
}

void test_value_of_ace_7_3(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(11, value_of_ace(C7, C3));
}

void test_value_of_ace_7_4(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_UINT64(1, value_of_ace(C7, C4));
}

void test_is_blackjack_a_k(void) {
    TEST_IGNORE();
    TEST_ASSERT(is_blackjack(CA, CK));
}

void test_is_blackjack_a_a(void) {
    TEST_IGNORE();
    TEST_ASSERT(!is_blackjack(CA, CA));
}

void test_is_blackjack_4_7(void) {
    TEST_IGNORE();
    TEST_ASSERT(!is_blackjack(C4, C7));
}

void test_is_blackjack_q_k(void) {
    TEST_IGNORE();
    TEST_ASSERT(!is_blackjack(CQ, CK));
}

void test_is_blackjack_a_10(void) {
    TEST_IGNORE();
    TEST_ASSERT(is_blackjack(CA, C10));
}

void test_is_blackjack_j_a(void) {
    TEST_IGNORE();
    TEST_ASSERT(is_blackjack(CJ, CA));
}

void test_can_split_q_k(void) {
    TEST_IGNORE();
    TEST_ASSERT(can_split_pairs(CQ, CK));
}

void test_can_split_10_a(void) {
    TEST_IGNORE();
    TEST_ASSERT(!can_split_pairs(C10, CA));
}

void test_can_split_a_a(void) {
    TEST_IGNORE();
    TEST_ASSERT(can_split_pairs(CA, CA));
}

void test_can_split_6_6(void) {
    TEST_IGNORE();
    TEST_ASSERT(can_split_pairs(C6, C6));
}

void test_can_split_9_10(void) {
    TEST_IGNORE();
    TEST_ASSERT(!can_split_pairs(C9, C10));
}

void test_can_double_down_a_9(void) {
    TEST_IGNORE();
    TEST_ASSERT(can_double_down(CA, C9));
}

void test_can_double_down_k_j(void) {
    TEST_IGNORE();
    TEST_ASSERT(!can_double_down(CK, CJ));
}

void test_can_double_down_4_3(void) {
    TEST_IGNORE();
    TEST_ASSERT(!can_double_down(C4, C3));
}

void test_can_double_down_4_5(void) {
    TEST_IGNORE();
    TEST_ASSERT(can_double_down(C4, C5));
}

void test_can_double_down_a_a(void) {
    TEST_IGNORE();
    TEST_ASSERT(!can_double_down(CA, CA));
}

void test_can_double_down_k_a(void) {
    TEST_IGNORE();
    TEST_ASSERT(can_double_down(CK, CA));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_value_of_card_2);
    RUN_TEST(test_value_of_card_5);
    RUN_TEST(test_value_of_card_a);
    RUN_TEST(test_value_of_card_j);
    RUN_TEST(test_value_of_card_8);
    RUN_TEST(test_value_of_card_k);
    RUN_TEST(test_value_of_card_q);
    RUN_TEST(test_higher_card_4_8);
    RUN_TEST(test_higher_card_a_a);
    RUN_TEST(test_higher_card_6_j);
    RUN_TEST(test_higher_card_10_j);
    RUN_TEST(test_higher_card_3_a);
    RUN_TEST(test_higher_card_5_5);
    RUN_TEST(test_value_of_ace_2_3);
    RUN_TEST(test_value_of_ace_a_q);
    RUN_TEST(test_value_of_ace_5_5);
    RUN_TEST(test_value_of_ace_a_2);
    RUN_TEST(test_value_of_ace_7_3);
    RUN_TEST(test_value_of_ace_7_4);
    RUN_TEST(test_is_blackjack_a_k);
    RUN_TEST(test_is_blackjack_a_a);
    RUN_TEST(test_is_blackjack_4_7);
    RUN_TEST(test_is_blackjack_q_k);
    RUN_TEST(test_is_blackjack_a_10);
    RUN_TEST(test_is_blackjack_j_a);
    RUN_TEST(test_can_split_q_k);
    RUN_TEST(test_can_split_10_a);
    RUN_TEST(test_can_split_a_a);
    RUN_TEST(test_can_split_6_6);
    RUN_TEST(test_can_split_9_10);
    RUN_TEST(test_can_double_down_a_9);
    RUN_TEST(test_can_double_down_k_j);
    RUN_TEST(test_can_double_down_4_3);
    RUN_TEST(test_can_double_down_4_5);
    RUN_TEST(test_can_double_down_a_a);
    RUN_TEST(test_can_double_down_k_a);
    return UNITY_END();
}
