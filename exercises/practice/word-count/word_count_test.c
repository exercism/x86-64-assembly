#include "vendor/unity.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 20
#define WORD_SIZE 48
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct {
    char word[WORD_SIZE];
    size_t count;
} wordMap;

extern size_t count_words(wordMap *buffer, const char *sentence);

void setUp(void) {
}

void tearDown(void) {
}

void test_count_one_word(void) {
    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"word", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "word"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_count_one_of_each_word(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"one", 1}, {"of", 1}, {"each", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "one of each"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_multiple_occurrences_of_a_word(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"one", 1}, {"fish", 4}, {"two", 1}, {"red", 1}, {"blue", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "one fish two fish red fish blue fish"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_handles_cramped_lists(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"one", 1}, {"two", 1}, {"three", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "one,two,three"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_handles_expanded_lists(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"one", 1}, {"two", 1}, {"three", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "one,\ntwo,\nthree"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_ignore_punctuation(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"car", 1}, {"carpet", 1}, {"as", 1}, {"java", 1}, {"javascript", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "car: carpet as java: javascript!!&@$%^&"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_include_numbers(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"testing", 2}, {"1", 1}, {"2", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "testing, 1, 2 testing"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_normalize_case(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"go", 3}, {"stop", 2}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "go Go GO Stop stop"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_with_apostrophes(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"first", 1}, {"don't", 2},  {"laugh", 1},   {"then", 1},
                                {"cry", 1},   {"you're", 1}, {"getting", 1}, {"it", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "'First: don't laugh. Then: don't cry. You're getting it.'"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_with_quotations(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"joe", 1}, {"can't", 1}, {"tell", 1}, {"between", 1}, {"large", 2}, {"and", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "Joe can't tell between 'large' and large."));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_substrings_from_the_beginning(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"joe", 1}, {"can't", 1}, {"tell", 1}, {"between", 1}, {"app", 1}, {"apple", 1}, {"and", 1}, {"a", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "Joe can't tell between app, apple and a."));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_multiple_spaces_not_detected_as_a_word(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"multiple", 1}, {"whitespaces", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, " multiple   whitespaces"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_alternating_word_separators_not_detected_as_a_word(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"one", 1}, {"two", 1}, {"three", 1}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, ",\n,one,\n ,two \n 'three'"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

void test_quotation_for_word_with_apostrophe(void) {
    TEST_IGNORE();

    wordMap buffer[BUFFER_SIZE];
    const wordMap expected[] = {{"can", 1}, {"can't", 2}};
    const size_t arr_length = ARRAY_SIZE(expected);

    TEST_ASSERT_EQUAL_UINT64(arr_length, count_words(buffer, "can, can't, 'can't'"));
    for (size_t i = 0; i < arr_length; ++i) {
        bool flag = false;
        for (size_t j = 0; j < arr_length && !flag; ++j) {
            flag = expected[i].count == buffer[j].count && !strcmp(expected[i].word, buffer[j].word);
        }
        TEST_ASSERT_EQUAL(true, flag);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_count_one_word);
    RUN_TEST(test_count_one_of_each_word);
    RUN_TEST(test_multiple_occurrences_of_a_word);
    RUN_TEST(test_handles_cramped_lists);
    RUN_TEST(test_handles_expanded_lists);
    RUN_TEST(test_ignore_punctuation);
    RUN_TEST(test_include_numbers);
    RUN_TEST(test_normalize_case);
    RUN_TEST(test_with_apostrophes);
    RUN_TEST(test_with_quotations);
    RUN_TEST(test_substrings_from_the_beginning);
    RUN_TEST(test_multiple_spaces_not_detected_as_a_word);
    RUN_TEST(test_alternating_word_separators_not_detected_as_a_word);
    RUN_TEST(test_quotation_for_word_with_apostrophe);
    return UNITY_END();
}
