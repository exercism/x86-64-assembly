#include "vendor/unity.h"

#include <stdalign.h>
#include <stdint.h>
#include <stddef.h>

#define MAX_WORD_SIZE 27
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef enum {
    Error = -1,
    Ongoing,
    Lose,
    Win
} state_t;

typedef struct {
    state_t state;
    char masked_word[MAX_WORD_SIZE];
    uint8_t remaining_failures;
} result_t;

extern result_t guess(const char word[], const char guesses[], size_t num_guesses);

void setUp(void) {
}

void tearDown(void) {
}

void test_initially_9_failures_are_allowed_and_no_letters_are_guessed(void) {
    alignas(16) const char word[MAX_WORD_SIZE] = "loot";
    const result_t result = guess(word, NULL, 0);
    TEST_ASSERT_EQUAL_INT(Ongoing, result.state);
    TEST_ASSERT_EQUAL_STRING("____", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(9, result.remaining_failures);
}

void test_after_10_failures_the_game_is_over(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "loot";
    alignas(16) const char guesses[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Lose, result.state);
    TEST_ASSERT_EQUAL_STRING("____", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(0, result.remaining_failures);
}

void test_losing_with_several_correct_guesses(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "loot";
    alignas(16) const char guesses[] = {'t', 'o', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Lose, result.state);
    TEST_ASSERT_EQUAL_STRING("_oot", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(0, result.remaining_failures);
}

void test_feeding_a_correct_letter_removes_underscores(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "loot";
    alignas(16) const char guesses[] = {'t'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Ongoing, result.state);
    TEST_ASSERT_EQUAL_STRING("___t", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(9, result.remaining_failures);
}

void test_feeding_a_correct_letter_twice_counts_as_a_failure(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "loot";
    alignas(16) const char guesses[] = {'t', 't'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Ongoing, result.state);
    TEST_ASSERT_EQUAL_STRING("___t", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(8, result.remaining_failures);
}

void test_guessing_a_repeated_letter_reveals_all_instances(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "loot";
    alignas(16) const char guesses[] = {'t', 't', 'o'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Ongoing, result.state);
    TEST_ASSERT_EQUAL_STRING("_oot", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(8, result.remaining_failures);
}

void test_getting_all_the_letters_right_makes_for_a_win(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "loot";
    alignas(16) const char guesses[] = {'t', 't', 'o', 'l'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Win, result.state);
    TEST_ASSERT_EQUAL_STRING("loot", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(8, result.remaining_failures);
}

void test_winning_on_the_last_guess_is_still_a_win(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "loot";
    alignas(16) const char guesses[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 't', 'o', 'l'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Win, result.state);
    TEST_ASSERT_EQUAL_STRING("loot", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(0, result.remaining_failures);
}

void test_guessing_after_a_lose_is_error(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "loot";
    alignas(16) const char guesses[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Error, result.state);
}

void test_guessing_after_a_win_is_error(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "loot";
    alignas(16) const char guesses[] = {'t', 'o', 'l', 'l'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Error, result.state);
}

void test_big_word_ongoing_after_many_guesses(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "authentic";
    alignas(16) const char guesses[] = {'a', 'e', 'p', 'm', 'i', 'l', 'c', 'n', 'o', 'r', 'q', 'u'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Ongoing, result.state);
    TEST_ASSERT_EQUAL_STRING("au__en_ic", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(3, result.remaining_failures);
}

void test_big_word_win_after_few_guesses(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "intelligence";
    alignas(16) const char guesses[] = {'a', 'e', 'i', 'l', 'n', 't', 'g', 'c'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Win, result.state);
    TEST_ASSERT_EQUAL_STRING("intelligence", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(8, result.remaining_failures);
}

void test_small_word_win_after_few_guesses(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "car";
    alignas(16) const char guesses[] = {'a', 'm', 'c', 'p', 'r'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Win, result.state);
    TEST_ASSERT_EQUAL_STRING("car", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(7, result.remaining_failures);
}

void test_small_word_still_lose_with_a_gotcha(void) {
    TEST_IGNORE();
    alignas(16) const char word[MAX_WORD_SIZE] = "dye";
    alignas(16) const char guesses[] = {'a', 'r', 'm', 'p', 'c', 'o', 'q', 'n', 'u', 'e', 'd', 'i'};
    const result_t result = guess(word, guesses, ARRAY_SIZE(guesses));
    TEST_ASSERT_EQUAL_INT(Lose, result.state);
    TEST_ASSERT_EQUAL_STRING("d_e", result.masked_word);
    TEST_ASSERT_EQUAL_UINT8(0, result.remaining_failures);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_initially_9_failures_are_allowed_and_no_letters_are_guessed);
    RUN_TEST(test_after_10_failures_the_game_is_over);
    RUN_TEST(test_losing_with_several_correct_guesses);
    RUN_TEST(test_feeding_a_correct_letter_removes_underscores);
    RUN_TEST(test_feeding_a_correct_letter_twice_counts_as_a_failure);
    RUN_TEST(test_guessing_a_repeated_letter_reveals_all_instances);
    RUN_TEST(test_getting_all_the_letters_right_makes_for_a_win);
    RUN_TEST(test_winning_on_the_last_guess_is_still_a_win);
    RUN_TEST(test_guessing_after_a_lose_is_error);
    RUN_TEST(test_guessing_after_a_win_is_error);
    RUN_TEST(test_big_word_ongoing_after_many_guesses);
    RUN_TEST(test_big_word_win_after_few_guesses);
    RUN_TEST(test_small_word_win_after_few_guesses);
    RUN_TEST(test_small_word_still_lose_with_a_gotcha);
    return UNITY_END();
}
