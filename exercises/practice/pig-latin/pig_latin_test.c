#include "vendor/unity.h"

#define BUFFER_SIZE 80

extern void translate(char *buffer, const char *phrase);

void setUp(void) {
}

void tearDown(void) {
}

void test_word_beginning_with_a(void) {
    char buffer[BUFFER_SIZE];

    translate(buffer, "apple");
    TEST_ASSERT_EQUAL_STRING("appleay", buffer);
}

void test_word_beginning_with_e(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "ear");
    TEST_ASSERT_EQUAL_STRING("earay", buffer);
}

void test_word_beginning_with_i(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "igloo");
    TEST_ASSERT_EQUAL_STRING("iglooay", buffer);
}

void test_word_beginning_with_o(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "object");
    TEST_ASSERT_EQUAL_STRING("objectay", buffer);
}

void test_word_beginning_with_u(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "under");
    TEST_ASSERT_EQUAL_STRING("underay", buffer);
}

void test_word_beginning_with_a_vowel_and_followed_by_a_qu(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "equal");
    TEST_ASSERT_EQUAL_STRING("equalay", buffer);
}

void test_word_beginning_with_p(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "pig");
    TEST_ASSERT_EQUAL_STRING("igpay", buffer);
}

void test_word_beginning_with_k(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "koala");
    TEST_ASSERT_EQUAL_STRING("oalakay", buffer);
}

void test_word_beginning_with_x(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "xenon");
    TEST_ASSERT_EQUAL_STRING("enonxay", buffer);
}

void test_word_beginning_with_q_without_a_following_u(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "qat");
    TEST_ASSERT_EQUAL_STRING("atqay", buffer);
}

void test_word_beginning_with_consonant_and_vowel_containing_qu(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "liquid");
    TEST_ASSERT_EQUAL_STRING("iquidlay", buffer);
}

void test_word_beginning_with_ch(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "chair");
    TEST_ASSERT_EQUAL_STRING("airchay", buffer);
}

void test_word_beginning_with_qu(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "queen");
    TEST_ASSERT_EQUAL_STRING("eenquay", buffer);
}

void test_word_beginning_with_qu_and_a_preceding_consonant(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "square");
    TEST_ASSERT_EQUAL_STRING("aresquay", buffer);
}

void test_word_beginning_with_th(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "therapy");
    TEST_ASSERT_EQUAL_STRING("erapythay", buffer);
}

void test_word_beginning_with_thr(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "thrush");
    TEST_ASSERT_EQUAL_STRING("ushthray", buffer);
}

void test_word_beginning_with_sch(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "school");
    TEST_ASSERT_EQUAL_STRING("oolschay", buffer);
}

void test_word_beginning_with_yt(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "yttria");
    TEST_ASSERT_EQUAL_STRING("yttriaay", buffer);
}

void test_word_beginning_with_xr(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "xray");
    TEST_ASSERT_EQUAL_STRING("xrayay", buffer);
}

void test_y_is_treated_like_a_consonant_at_the_beginning_of_a_word(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "yellow");
    TEST_ASSERT_EQUAL_STRING("ellowyay", buffer);
}

void test_y_is_treated_like_a_vowel_at_the_end_of_a_consonant_cluster(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "rhythm");
    TEST_ASSERT_EQUAL_STRING("ythmrhay", buffer);
}

void test_y_as_second_letter_in_two_letter_word(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "my");
    TEST_ASSERT_EQUAL_STRING("ymay", buffer);
}

void test_a_whole_phrase(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    translate(buffer, "quick fast run");
    TEST_ASSERT_EQUAL_STRING("ickquay astfay unray", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_word_beginning_with_a);
    RUN_TEST(test_word_beginning_with_e);
    RUN_TEST(test_word_beginning_with_i);
    RUN_TEST(test_word_beginning_with_o);
    RUN_TEST(test_word_beginning_with_u);
    RUN_TEST(test_word_beginning_with_a_vowel_and_followed_by_a_qu);
    RUN_TEST(test_word_beginning_with_p);
    RUN_TEST(test_word_beginning_with_k);
    RUN_TEST(test_word_beginning_with_x);
    RUN_TEST(test_word_beginning_with_q_without_a_following_u);
    RUN_TEST(test_word_beginning_with_consonant_and_vowel_containing_qu);
    RUN_TEST(test_word_beginning_with_ch);
    RUN_TEST(test_word_beginning_with_qu);
    RUN_TEST(test_word_beginning_with_qu_and_a_preceding_consonant);
    RUN_TEST(test_word_beginning_with_th);
    RUN_TEST(test_word_beginning_with_thr);
    RUN_TEST(test_word_beginning_with_sch);
    RUN_TEST(test_word_beginning_with_yt);
    RUN_TEST(test_word_beginning_with_xr);
    RUN_TEST(test_y_is_treated_like_a_consonant_at_the_beginning_of_a_word);
    RUN_TEST(test_y_is_treated_like_a_vowel_at_the_end_of_a_consonant_cluster);
    RUN_TEST(test_y_as_second_letter_in_two_letter_word);
    RUN_TEST(test_a_whole_phrase);
    return UNITY_END();
}
