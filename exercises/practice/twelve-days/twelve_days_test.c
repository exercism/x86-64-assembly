#include "vendor/unity.h"

#define BUFFER_SIZE 4000

extern void recite(char *buffer, int start_verse, int end_verse);

void setUp(void) {
}

void tearDown(void) {
}

void test_first_day_a_partridge_in_a_pear_tree(void) {
    char buffer[BUFFER_SIZE];

    recite(buffer, 1, 1);
    const char expected[] = "On the first day of Christmas my true love gave to me: a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_second_day_two_turtle_doves(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 2, 2);
    const char expected[] = "On the second day of Christmas my true love gave to me: two Turtle Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_third_day_three_french_hens(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 3, 3);
    const char expected[] =
        "On the third day of Christmas my true love gave to me: three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_fourth_day_four_calling_birds(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 4, 4);
    const char expected[] =
        "On the fourth day of Christmas my true love gave to me: four Calling Birds, three French Hens, two Turtle Doves, and a Partridge "
        "in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_fifth_day_five_gold_rings(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 5, 5);
    const char expected[] =
        "On the fifth day of Christmas my true love gave to me: five Gold Rings, four Calling Birds, three French Hens, two Turtle Doves, "
        "and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_sixth_day_six_geesealaying(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 6, 6);
    const char expected[] =
        "On the sixth day of Christmas my true love gave to me: six Geese-a-Laying, five Gold Rings, four Calling Birds, three French "
        "Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_seventh_day_seven_swansaswimming(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 7, 7);
    const char expected[] =
        "On the seventh day of Christmas my true love gave to me: seven Swans-a-Swimming, six Geese-a-Laying, five Gold Rings, four "
        "Calling Birds, three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_eighth_day_eight_maidsamilking(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 8, 8);
    const char expected[] =
        "On the eighth day of Christmas my true love gave to me: eight Maids-a-Milking, seven Swans-a-Swimming, six Geese-a-Laying, five "
        "Gold Rings, four Calling Birds, three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_ninth_day_nine_ladies_dancing(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 9, 9);
    const char expected[] =
        "On the ninth day of Christmas my true love gave to me: nine Ladies Dancing, eight Maids-a-Milking, seven Swans-a-Swimming, six "
        "Geese-a-Laying, five Gold Rings, four Calling Birds, three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_tenth_day_ten_lordsaleaping(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 10, 10);
    const char expected[] =
        "On the tenth day of Christmas my true love gave to me: ten Lords-a-Leaping, nine Ladies Dancing, eight Maids-a-Milking, seven "
        "Swans-a-Swimming, six Geese-a-Laying, five Gold Rings, four Calling Birds, three French Hens, two Turtle Doves, and a Partridge "
        "in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_eleventh_day_eleven_pipers_piping(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 11, 11);
    const char expected[] =
        "On the eleventh day of Christmas my true love gave to me: eleven Pipers Piping, ten Lords-a-Leaping, nine Ladies Dancing, eight "
        "Maids-a-Milking, seven Swans-a-Swimming, six Geese-a-Laying, five Gold Rings, four Calling Birds, three French Hens, two Turtle "
        "Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_twelfth_day_twelve_drummers_drumming(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 12, 12);
    const char expected[] =
        "On the twelfth day of Christmas my true love gave to me: twelve Drummers Drumming, eleven Pipers Piping, ten Lords-a-Leaping, "
        "nine Ladies Dancing, eight Maids-a-Milking, seven Swans-a-Swimming, six Geese-a-Laying, five Gold Rings, four Calling Birds, "
        "three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_recites_first_three_verses_of_the_song(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 1, 3);
    const char expected[] =
        "On the first day of Christmas my true love gave to me: a Partridge in a Pear Tree.\n"
        "On the second day of Christmas my true love gave to me: two Turtle Doves, and a Partridge in a Pear Tree.\n"
        "On the third day of Christmas my true love gave to me: three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_recites_three_verses_from_the_middle_of_the_song(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 4, 6);
    const char expected[] =
        "On the fourth day of Christmas my true love gave to me: four Calling Birds, three French Hens, two Turtle Doves, and a Partridge "
        "in a Pear Tree.\n"
        "On the fifth day of Christmas my true love gave to me: five Gold Rings, four Calling Birds, three French Hens, two Turtle Doves, "
        "and a Partridge in a Pear Tree.\n"
        "On the sixth day of Christmas my true love gave to me: six Geese-a-Laying, five Gold Rings, four Calling Birds, three French "
        "Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_recites_the_whole_song(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 1, 12);
    const char expected[] =
        "On the first day of Christmas my true love gave to me: a Partridge in a Pear Tree.\n"
        "On the second day of Christmas my true love gave to me: two Turtle Doves, and a Partridge in a Pear Tree.\n"
        "On the third day of Christmas my true love gave to me: three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n"
        "On the fourth day of Christmas my true love gave to me: four Calling Birds, three French Hens, two Turtle Doves, and a Partridge "
        "in a Pear Tree.\n"
        "On the fifth day of Christmas my true love gave to me: five Gold Rings, four Calling Birds, three French Hens, two Turtle Doves, "
        "and a Partridge in a Pear Tree.\n"
        "On the sixth day of Christmas my true love gave to me: six Geese-a-Laying, five Gold Rings, four Calling Birds, three French "
        "Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n"
        "On the seventh day of Christmas my true love gave to me: seven Swans-a-Swimming, six Geese-a-Laying, five Gold Rings, four "
        "Calling Birds, three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n"
        "On the eighth day of Christmas my true love gave to me: eight Maids-a-Milking, seven Swans-a-Swimming, six Geese-a-Laying, five "
        "Gold Rings, four Calling Birds, three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n"
        "On the ninth day of Christmas my true love gave to me: nine Ladies Dancing, eight Maids-a-Milking, seven Swans-a-Swimming, six "
        "Geese-a-Laying, five Gold Rings, four Calling Birds, three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n"
        "On the tenth day of Christmas my true love gave to me: ten Lords-a-Leaping, nine Ladies Dancing, eight Maids-a-Milking, seven "
        "Swans-a-Swimming, six Geese-a-Laying, five Gold Rings, four Calling Birds, three French Hens, two Turtle Doves, and a Partridge "
        "in a Pear Tree.\n"
        "On the eleventh day of Christmas my true love gave to me: eleven Pipers Piping, ten Lords-a-Leaping, nine Ladies Dancing, eight "
        "Maids-a-Milking, seven Swans-a-Swimming, six Geese-a-Laying, five Gold Rings, four Calling Birds, three French Hens, two Turtle "
        "Doves, and a Partridge in a Pear Tree.\n"
        "On the twelfth day of Christmas my true love gave to me: twelve Drummers Drumming, eleven Pipers Piping, ten Lords-a-Leaping, "
        "nine Ladies Dancing, eight Maids-a-Milking, seven Swans-a-Swimming, six Geese-a-Laying, five Gold Rings, four Calling Birds, "
        "three French Hens, two Turtle Doves, and a Partridge in a Pear Tree.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_first_day_a_partridge_in_a_pear_tree);
    RUN_TEST(test_second_day_two_turtle_doves);
    RUN_TEST(test_third_day_three_french_hens);
    RUN_TEST(test_fourth_day_four_calling_birds);
    RUN_TEST(test_fifth_day_five_gold_rings);
    RUN_TEST(test_sixth_day_six_geesealaying);
    RUN_TEST(test_seventh_day_seven_swansaswimming);
    RUN_TEST(test_eighth_day_eight_maidsamilking);
    RUN_TEST(test_ninth_day_nine_ladies_dancing);
    RUN_TEST(test_tenth_day_ten_lordsaleaping);
    RUN_TEST(test_eleventh_day_eleven_pipers_piping);
    RUN_TEST(test_twelfth_day_twelve_drummers_drumming);
    RUN_TEST(test_recites_first_three_verses_of_the_song);
    RUN_TEST(test_recites_three_verses_from_the_middle_of_the_song);
    RUN_TEST(test_recites_the_whole_song);
    return UNITY_END();
}
