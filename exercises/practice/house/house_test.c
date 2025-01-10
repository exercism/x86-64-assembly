#include "vendor/unity.h"

#define BUFFER_SIZE 4000

extern void recite(char *buffer, int start_verse, int end_verse);

void setUp(void) {
}

void tearDown(void) {
}

void test_verse_one__the_house_that_jack_built(void) {
    const char *expected =
        "This is the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 1, 1);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_two__the_malt_that_lay(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 2, 2);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_three__the_rat_that_ate(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 3, 3);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_four__the_cat_that_killed(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 4, 4);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_five__the_dog_that_worried(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 5, 5);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_six__the_cow_with_the_crumpled_horn(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 6, 6);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_seven__the_maiden_all_forlorn(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 7, 7);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_eight__the_man_all_tattered_and_torn(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 8, 8);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_nine__the_priest_all_shaven_and_shorn(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the priest all shaven and shorn that married the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 9, 9);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_10__the_rooster_that_crowed_in_the_morn(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the rooster that crowed in the morn that woke the priest all shaven and shorn that married the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 10, 10);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_11__the_farmer_sowing_his_corn(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the farmer sowing his corn that kept the rooster that crowed in the morn that woke the priest all shaven and shorn that married the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 11, 11);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_verse_12__the_horse_and_the_hound_and_the_horn(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the horse and the hound and the horn that belonged to the farmer sowing his corn that kept the rooster that crowed in the morn that woke the priest all shaven and shorn that married the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 12, 12);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_multiple_verses(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 4, 8);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_full_rhyme(void) {
    TEST_IGNORE();
    const char *expected =
        "This is the house that Jack built.\n"
        "This is the malt that lay in the house that Jack built.\n"
        "This is the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the priest all shaven and shorn that married the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the rooster that crowed in the morn that woke the priest all shaven and shorn that married the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the farmer sowing his corn that kept the rooster that crowed in the morn that woke the priest all shaven and shorn that married the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n"
        "This is the horse and the hound and the horn that belonged to the farmer sowing his corn that kept the rooster that crowed in the morn that woke the priest all shaven and shorn that married the man all tattered and torn that kissed the maiden all forlorn that milked the cow with the crumpled horn that tossed the dog that worried the cat that killed the rat that ate the malt that lay in the house that Jack built.\n";
    char buffer[BUFFER_SIZE];

    recite(buffer, 1, 12);
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_verse_one__the_house_that_jack_built);
    RUN_TEST(test_verse_two__the_malt_that_lay);
    RUN_TEST(test_verse_three__the_rat_that_ate);
    RUN_TEST(test_verse_four__the_cat_that_killed);
    RUN_TEST(test_verse_five__the_dog_that_worried);
    RUN_TEST(test_verse_six__the_cow_with_the_crumpled_horn);
    RUN_TEST(test_verse_seven__the_maiden_all_forlorn);
    RUN_TEST(test_verse_eight__the_man_all_tattered_and_torn);
    RUN_TEST(test_verse_nine__the_priest_all_shaven_and_shorn);
    RUN_TEST(test_verse_10__the_rooster_that_crowed_in_the_morn);
    RUN_TEST(test_verse_11__the_farmer_sowing_his_corn);
    RUN_TEST(test_verse_12__the_horse_and_the_hound_and_the_horn);
    RUN_TEST(test_multiple_verses);
    RUN_TEST(test_full_rhyme);
    return UNITY_END();
}
