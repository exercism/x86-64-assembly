// Version: 0

#include "stdint.h"
#include "vendor/unity.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define ALPHABET_SIZE 26

typedef struct {
    int32_t key;
    uint8_t values_size;
    char values[ALPHABET_SIZE];
} LegacyMap;

typedef struct {
    char key;
    int32_t value;
} NewMapEntry;

extern size_t transform(NewMapEntry *output, const LegacyMap *input, size_t input_size);

void setUp(void) {
}

void tearDown(void) {
}

void test_single_letter(void) {
    const LegacyMap input[] = {
        {1, 1, {'A'}},
    };
    NewMapEntry buffer[ALPHABET_SIZE];
    const NewMapEntry expected[] = {
        {'a', 1},
    };

    const size_t length = transform(buffer, input, 1);

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_UINT8(expected[i].key, buffer[i].key);
        TEST_ASSERT_EQUAL_INT32(expected[i].value, buffer[i].value);
    }
}

void test_single_score_with_multiple_letters(void) {
    TEST_IGNORE();
    const LegacyMap input[] = {
        {1, 5, {'A', 'E', 'I', 'O', 'U'}},
    };
    NewMapEntry buffer[ALPHABET_SIZE];
    const NewMapEntry expected[] = {
        {'a', 1},
        {'e', 1},
        {'i', 1},
        {'o', 1},
        {'u', 1},
    };

    const size_t length = transform(buffer, input, 1);

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_UINT8(expected[i].key, buffer[i].key);
        TEST_ASSERT_EQUAL_INT32(expected[i].value, buffer[i].value);
    }
}

void test_multiple_scores_with_multiple_letters(void) {
    TEST_IGNORE();
    const LegacyMap input[] = {
        {1, 2, {'A', 'E'}},
        {2, 2, {'D', 'G'}},
    };
    NewMapEntry buffer[ALPHABET_SIZE];
    const NewMapEntry expected[] = {
        {'a', 1},
        {'d', 2},
        {'e', 1},
        {'g', 2},
    };

    const size_t length = transform(buffer, input, 2);

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_UINT8(expected[i].key, buffer[i].key);
        TEST_ASSERT_EQUAL_INT32(expected[i].value, buffer[i].value);
    }
}

void test_multiple_scores_with_differing_numbers_of_letters(void) {
    TEST_IGNORE();
    const LegacyMap input[] = {
        {1, 10, {'A', 'E', 'I', 'O', 'U', 'L', 'N', 'R', 'S', 'T'}},
        {2, 2, {'D', 'G'}},
        {3, 4, {'B', 'C', 'M', 'P'}},
        {4, 5, {'F', 'H', 'V', 'W', 'Y'}},
        {5, 1, {'K'}},
        {8, 2, {'J', 'X'}},
        {10, 2, {'Q', 'Z'}},
    };
    NewMapEntry buffer[ALPHABET_SIZE];
    const NewMapEntry expected[] = {
        {'a', 1},
        {'b', 3},
        {'c', 3},
        {'d', 2},
        {'e', 1},
        {'f', 4},
        {'g', 2},
        {'h', 4},
        {'i', 1},
        {'j', 8},
        {'k', 5},
        {'l', 1},
        {'m', 3},
        {'n', 1},
        {'o', 1},
        {'p', 3},
        {'q', 10},
        {'r', 1},
        {'s', 1},
        {'t', 1},
        {'u', 1},
        {'v', 4},
        {'w', 4},
        {'x', 8},
        {'y', 4},
        {'z', 10},
    };

    const size_t length = transform(buffer, input, 7);

    TEST_ASSERT_EQUAL_UINT64(ARRAY_SIZE(expected), length);
    for (size_t i = 0; i < length; ++i) {
        TEST_ASSERT_EQUAL_UINT8(expected[i].key, buffer[i].key);
        TEST_ASSERT_EQUAL_INT32(expected[i].value, buffer[i].value);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_single_letter);
    RUN_TEST(test_single_score_with_multiple_letters);
    RUN_TEST(test_multiple_scores_with_multiple_letters);
    RUN_TEST(test_multiple_scores_with_differing_numbers_of_letters);
    return UNITY_END();
}
