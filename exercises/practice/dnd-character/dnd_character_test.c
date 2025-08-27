#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t strength;
    uint8_t dexterity;
    uint8_t constitution;
    uint8_t intelligence;
    uint8_t wisdom;
    uint8_t charisma;
    uint16_t hitpoints;
} dnd_character_t;

extern int8_t modifier(uint8_t score);
extern uint8_t ability(void);
extern dnd_character_t make_dnd_character(void);

void check_valid_score(uint8_t score) {
    TEST_ASSERT(score >= 3 && score <= 18);
}

void setUp(void) {
}

void tearDown(void) {
}

void test_ability_modifier_for_score_3_is_4(void) {
    TEST_ASSERT_EQUAL_INT8(-4, modifier(3));
}

void test_ability_modifier_for_score_4_is_3(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(-3, modifier(4));
}

void test_ability_modifier_for_score_5_is_3(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(-3, modifier(5));
}

void test_ability_modifier_for_score_6_is_2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(-2, modifier(6));
}

void test_ability_modifier_for_score_7_is_2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(-2, modifier(7));
}

void test_ability_modifier_for_score_8_is_1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(-1, modifier(8));
}

void test_ability_modifier_for_score_9_is_1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(-1, modifier(9));
}

void test_ability_modifier_for_score_10_is_0(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(0, modifier(10));
}

void test_ability_modifier_for_score_11_is_0(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(0, modifier(11));
}

void test_ability_modifier_for_score_12_is_1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(1, modifier(12));
}

void test_ability_modifier_for_score_13_is_1(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(1, modifier(13));
}

void test_ability_modifier_for_score_14_is_2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(2, modifier(14));
}

void test_ability_modifier_for_score_15_is_2(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(2, modifier(15));
}

void test_ability_modifier_for_score_16_is_3(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(3, modifier(16));
}

void test_ability_modifier_for_score_17_is_3(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(3, modifier(17));
}

void test_ability_modifier_for_score_18_is_4(void) {
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_INT8(4, modifier(18));
}

void test_random_ability_is_within_range(void) {
    TEST_IGNORE();
    const double expected[16] = {100, 400, 1000, 2100, 3800, 6200, 9100, 12200, 14800, 16700, 17200, 16000, 13100, 9400, 5400, 2100};

    double results[16] = {0};
    for (size_t i = 0; i < 129600; ++i) {
        const uint8_t value = ability();
        check_valid_score(value);
        results[value - 3]++;
    }

    double sum_of_frequencies = 0;
    for (size_t i = 0; i < 16; ++i) {
        const double squared = (results[i] - expected[i]) * (results[i] - expected[i]);
        sum_of_frequencies += squared / expected[i];
    }

    TEST_ASSERT_LESS_OR_EQUAL(44263, (uint32_t)(1000 * sum_of_frequencies));
}

void test_random_character_is_valid(void) {
    TEST_IGNORE();
    const dnd_character_t Wulfgar = make_dnd_character();
    check_valid_score(Wulfgar.strength);
    TEST_ASSERT_EQUAL(10 + modifier(Wulfgar.constitution), Wulfgar.hitpoints);

    const dnd_character_t Artemis_Entreri = make_dnd_character();
    check_valid_score(Artemis_Entreri.dexterity);
    TEST_ASSERT_EQUAL(10 + modifier(Artemis_Entreri.constitution), Artemis_Entreri.hitpoints);

    const dnd_character_t Drizzt_Do_Urden = make_dnd_character();
    check_valid_score(Drizzt_Do_Urden.constitution);
    TEST_ASSERT_EQUAL(10 + modifier(Drizzt_Do_Urden.constitution), Drizzt_Do_Urden.hitpoints);

    const dnd_character_t Elminster = make_dnd_character();
    check_valid_score(Elminster.intelligence);
    TEST_ASSERT_EQUAL(10 + modifier(Elminster.constitution), Elminster.hitpoints);

    const dnd_character_t Cattie_Brie = make_dnd_character();
    check_valid_score(Cattie_Brie.wisdom);
    TEST_ASSERT_EQUAL(10 + modifier(Cattie_Brie.constitution), Cattie_Brie.hitpoints);

    const dnd_character_t Regis = make_dnd_character();
    check_valid_score(Regis.charisma);
    TEST_ASSERT_EQUAL(10 + modifier(Regis.constitution), Regis.hitpoints);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ability_modifier_for_score_3_is_4);
    RUN_TEST(test_ability_modifier_for_score_4_is_3);
    RUN_TEST(test_ability_modifier_for_score_5_is_3);
    RUN_TEST(test_ability_modifier_for_score_6_is_2);
    RUN_TEST(test_ability_modifier_for_score_7_is_2);
    RUN_TEST(test_ability_modifier_for_score_8_is_1);
    RUN_TEST(test_ability_modifier_for_score_9_is_1);
    RUN_TEST(test_ability_modifier_for_score_10_is_0);
    RUN_TEST(test_ability_modifier_for_score_11_is_0);
    RUN_TEST(test_ability_modifier_for_score_12_is_1);
    RUN_TEST(test_ability_modifier_for_score_13_is_1);
    RUN_TEST(test_ability_modifier_for_score_14_is_2);
    RUN_TEST(test_ability_modifier_for_score_15_is_2);
    RUN_TEST(test_ability_modifier_for_score_16_is_3);
    RUN_TEST(test_ability_modifier_for_score_17_is_3);
    RUN_TEST(test_ability_modifier_for_score_18_is_4);
    RUN_TEST(test_random_ability_is_within_range);
    RUN_TEST(test_random_character_is_valid);
    return UNITY_END();
}
