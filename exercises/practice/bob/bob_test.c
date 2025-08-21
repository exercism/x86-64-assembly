#include "vendor/unity.h"

extern const char *response(const char *hey_bob);

void setUp(void) {
}

void tearDown(void) {
}

void test_stating_something(void) {
    char str[] = "Tom-ay-to, tom-aaaah-to.";
    TEST_ASSERT_EQUAL_STRING("Whatever.", response(str));
}

void test_shouting(void) {
    TEST_IGNORE();
    char str[] = "WATCH OUT!";
    TEST_ASSERT_EQUAL_STRING("Whoa, chill out!", response(str));
}

void test_shouting_gibberish(void) {
    TEST_IGNORE();
    char str[] = "FCECDFCAAB";
    TEST_ASSERT_EQUAL_STRING("Whoa, chill out!", response(str));
}

void test_asking_a_question(void) {
    TEST_IGNORE();
    char str[] = "Does this cryogenic chamber make me look fat?";
    TEST_ASSERT_EQUAL_STRING("Sure.", response(str));
}

void test_asking_a_numeric_question(void) {
    TEST_IGNORE();
    char str[] = "You are, what, like 15?";
    TEST_ASSERT_EQUAL_STRING("Sure.", response(str));
}

void test_asking_gibberish(void) {
    TEST_IGNORE();
    char str[] = "fffbbcbeab?";
    TEST_ASSERT_EQUAL_STRING("Sure.", response(str));
}

void test_talking_forcefully(void) {
    TEST_IGNORE();
    char str[] = "Hi there!";
    TEST_ASSERT_EQUAL_STRING("Whatever.", response(str));
}

void test_using_acronyms_in_regular_speech(void) {
    TEST_IGNORE();
    char str[] = "It's OK if you don't want to go work for NASA.";
    TEST_ASSERT_EQUAL_STRING("Whatever.", response(str));
}

void test_forceful_question(void) {
    TEST_IGNORE();
    char str[] = "WHAT'S GOING ON?";
    TEST_ASSERT_EQUAL_STRING("Calm down, I know what I'm doing!", response(str));
}

void test_shouting_numbers(void) {
    TEST_IGNORE();
    char str[] = "1, 2, 3 GO!";
    TEST_ASSERT_EQUAL_STRING("Whoa, chill out!", response(str));
}

void test_no_letters(void) {
    TEST_IGNORE();
    char str[] = "1, 2, 3";
    TEST_ASSERT_EQUAL_STRING("Whatever.", response(str));
}

void test_question_with_no_letters(void) {
    TEST_IGNORE();
    char str[] = "4?";
    TEST_ASSERT_EQUAL_STRING("Sure.", response(str));
}

void test_shouting_with_special_characters(void) {
    TEST_IGNORE();
    char str[] = "ZOMG THE %^*@#$(*^ ZOMBIES ARE COMING!!11!!1!";
    TEST_ASSERT_EQUAL_STRING("Whoa, chill out!", response(str));
}

void test_shouting_with_no_exclamation_mark(void) {
    TEST_IGNORE();
    char str[] = "I HATE THE DENTIST";
    TEST_ASSERT_EQUAL_STRING("Whoa, chill out!", response(str));
}

void test_statement_containing_question_mark(void) {
    TEST_IGNORE();
    char str[] = "Ending with ? means a question.";
    TEST_ASSERT_EQUAL_STRING("Whatever.", response(str));
}

void test_nonletters_with_question(void) {
    TEST_IGNORE();
    char str[] = ":) ?";
    TEST_ASSERT_EQUAL_STRING("Sure.", response(str));
}

void test_prattling_on(void) {
    TEST_IGNORE();
    char str[] = "Wait! Hang on. Are you going to be OK?";
    TEST_ASSERT_EQUAL_STRING("Sure.", response(str));
}

void test_silence(void) {
    TEST_IGNORE();
    char str[] = "";
    TEST_ASSERT_EQUAL_STRING("Fine. Be that way!", response(str));
}

void test_prolonged_silence(void) {
    TEST_IGNORE();
    char str[] = "          ";
    TEST_ASSERT_EQUAL_STRING("Fine. Be that way!", response(str));
}

void test_alternate_silence(void) {
    TEST_IGNORE();
    char str[] = "\t\t\t\t\t\t\t\t\t\t";
    TEST_ASSERT_EQUAL_STRING("Fine. Be that way!", response(str));
}

void test_multiple_line_question(void) {
    TEST_IGNORE();
    char str[] = "\nDoes this cryogenic chamber make\n me look fat?";
    TEST_ASSERT_EQUAL_STRING("Sure.", response(str));
}

void test_starting_with_whitespace(void) {
    TEST_IGNORE();
    char str[] = "         hmmmmmmm...";
    TEST_ASSERT_EQUAL_STRING("Whatever.", response(str));
}

void test_ending_with_whitespace(void) {
    TEST_IGNORE();
    char str[] = "Okay if like my  spacebar  quite a bit?   ";
    TEST_ASSERT_EQUAL_STRING("Sure.", response(str));
}

void test_other_whitespace(void) {
    TEST_IGNORE();
    char str[] = "\n\r \t";
    TEST_ASSERT_EQUAL_STRING("Fine. Be that way!", response(str));
}

void test_nonquestion_ending_with_whitespace(void) {
    TEST_IGNORE();
    char str[] = "This is a statement ending with whitespace      ";
    TEST_ASSERT_EQUAL_STRING("Whatever.", response(str));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_stating_something);
    RUN_TEST(test_shouting);
    RUN_TEST(test_shouting_gibberish);
    RUN_TEST(test_asking_a_question);
    RUN_TEST(test_asking_a_numeric_question);
    RUN_TEST(test_asking_gibberish);
    RUN_TEST(test_talking_forcefully);
    RUN_TEST(test_using_acronyms_in_regular_speech);
    RUN_TEST(test_forceful_question);
    RUN_TEST(test_shouting_numbers);
    RUN_TEST(test_no_letters);
    RUN_TEST(test_question_with_no_letters);
    RUN_TEST(test_shouting_with_special_characters);
    RUN_TEST(test_shouting_with_no_exclamation_mark);
    RUN_TEST(test_statement_containing_question_mark);
    RUN_TEST(test_nonletters_with_question);
    RUN_TEST(test_prattling_on);
    RUN_TEST(test_silence);
    RUN_TEST(test_prolonged_silence);
    RUN_TEST(test_alternate_silence);
    RUN_TEST(test_multiple_line_question);
    RUN_TEST(test_starting_with_whitespace);
    RUN_TEST(test_ending_with_whitespace);
    RUN_TEST(test_other_whitespace);
    RUN_TEST(test_nonquestion_ending_with_whitespace);
    return UNITY_END();
}
