#include "vendor/unity.h"

#include "stddef.h"
#include "stdint.h"

#define NAME_SIZE 6
#define MAX_NUM_OF_NAMES 676000

extern void create_name(char *robot_name);
extern void reset_name(char *robot_name);
extern void release_names(void);

void setUp(void) {
}

void tearDown(void) {
}

void check_name_validity(const char *name) {
    for (size_t i = 0; i < 2; ++i) {
        TEST_ASSERT_GREATER_OR_EQUAL('A', name[i]);
        TEST_ASSERT_LESS_OR_EQUAL('Z', name[i]);
    }
    for (size_t i = 2; i < 5; ++i) {
        TEST_ASSERT_GREATER_OR_EQUAL('0', name[i]);
        TEST_ASSERT_LESS_OR_EQUAL('9', name[i]);
    }
    TEST_ASSERT_EQUAL(0, name[5]);
}

size_t hash_name(const char *name) {
    size_t hash = 0;
    size_t multiplier = 1;
    for (size_t i = 0; i < 2; ++i) {
        hash += multiplier * (name[i] - 'A');
        multiplier *= 26;
    }
    for (size_t i = 2; i < 5; ++i) {
        hash += multiplier * (name[i] - '0');
        multiplier *= 10;
    }
    return hash;
}

int64_t get_number_for_name(const char *name) {
    size_t number = 0;
    number += 100 * (name[2] - '0');
    number += 10 * (name[3] - '0');
    number += name[4] - '0';
    return number;
}

int are_sequential(const char *name1, const char *name2) {
    const int64_t number1 = get_number_for_name(name1);
    const int64_t number2 = get_number_for_name(name2);
    const int64_t num_diff = number2 - number1;
    const int64_t alpha_diff = (name1[0] - name2[0]) * 26 + (name1[1] - name2[1]);
    const int64_t total_diff = 1000 * alpha_diff + num_diff;
    return (total_diff < 0 ? -total_diff : total_diff) <= 1;
}

void test_name_is_valid(void) {
    char buffer[NAME_SIZE];

    create_name(buffer);
    check_name_validity(buffer);
}

void test_different_robots_have_different_names(void) {
    TEST_IGNORE();

    char buffer1[NAME_SIZE];

    create_name(buffer1);
    check_name_validity(buffer1);

    char buffer2[NAME_SIZE];

    create_name(buffer2);
    check_name_validity(buffer2);

    int is_different = 0;
    for (size_t j = 0; j < 5; ++j) {
        is_different = is_different || buffer1[j] != buffer2[j];
    }
    TEST_ASSERT_EQUAL(1, is_different);

    release_names();
}

void test_new_names_are_not_sequential(void) {
    TEST_IGNORE();

    char buffer1[NAME_SIZE];

    create_name(buffer1);
    check_name_validity(buffer1);

    char buffer2[NAME_SIZE];

    create_name(buffer2);
    check_name_validity(buffer2);

    char buffer3[NAME_SIZE];

    create_name(buffer3);
    check_name_validity(buffer3);

    TEST_ASSERT_EQUAL(1, are_sequential(buffer1, buffer1));
    TEST_ASSERT_EQUAL(0, are_sequential(buffer1, buffer2));
    TEST_ASSERT_EQUAL(0, are_sequential(buffer2, buffer3));

    release_names();
}

void test_names_are_unique(void) {
    TEST_IGNORE();

    uint8_t hash_table[MAX_NUM_OF_NAMES] = {0};
    uint32_t non_unique_elements = 0;

    for (size_t i = 0; i < 10000; ++i) {
        char buffer[NAME_SIZE];

        create_name(buffer);
        check_name_validity(buffer);

        const size_t hash = hash_name(buffer);
        non_unique_elements += hash_table[hash];
        TEST_ASSERT_LESS_OR_EQUAL(1, non_unique_elements);
        hash_table[hash] = 1;
    }

    release_names();
}

void test_names_can_be_reset(void) {
    TEST_IGNORE();

    char buffer[NAME_SIZE];

    create_name(buffer);
    check_name_validity(buffer);

    char memo[NAME_SIZE];
    for (size_t i = 0; i < NAME_SIZE; ++i) {
        memo[i] = buffer[i];
    }

    reset_name(buffer);
    check_name_validity(buffer);

    int is_different = 0;
    for (size_t i = 0; i < 5; ++i) {
        is_different = is_different || buffer[i] != memo[i];
    }
    TEST_ASSERT_EQUAL(1, is_different);

    release_names();
}

void test_names_are_not_sequential_after_reset(void) {
    TEST_IGNORE();

    char buffer[NAME_SIZE];

    create_name(buffer);
    check_name_validity(buffer);

    TEST_ASSERT_EQUAL(1, are_sequential(buffer, buffer));

    char memo[NAME_SIZE];
    for (size_t i = 0; i < NAME_SIZE; ++i) {
        memo[i] = buffer[i];
    }

    reset_name(buffer);
    check_name_validity(buffer);

    TEST_ASSERT_EQUAL(0, are_sequential(memo, buffer));

    for (size_t i = 0; i < NAME_SIZE; ++i) {
        memo[i] = buffer[i];
    }

    reset_name(buffer);
    check_name_validity(buffer);

    TEST_ASSERT_EQUAL(0, are_sequential(memo, buffer));

    release_names();
}

void test_names_are_unique_after_reset(void) {
    TEST_IGNORE();

    uint8_t hash_table[MAX_NUM_OF_NAMES] = {0};
    char buffer[NAME_SIZE];

    create_name(buffer);
    check_name_validity(buffer);

    const size_t hash = hash_name(buffer);
    hash_table[hash] = 1;

    uint32_t non_unique_elements = 0;

    for (size_t i = 0; i < 10000; ++i) {
        reset_name(buffer);
        check_name_validity(buffer);

        const size_t hash = hash_name(buffer);
        non_unique_elements += hash_table[hash];
        TEST_ASSERT_LESS_OR_EQUAL(1, non_unique_elements);
        hash_table[hash] = 1;
    }

    release_names();
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_name_is_valid);
    RUN_TEST(test_different_robots_have_different_names);
    RUN_TEST(test_new_names_are_not_sequential);
    RUN_TEST(test_names_are_unique);
    RUN_TEST(test_names_can_be_reset);
    RUN_TEST(test_names_are_not_sequential_after_reset);
    RUN_TEST(test_names_are_unique_after_reset);
    return UnityEnd();
}
