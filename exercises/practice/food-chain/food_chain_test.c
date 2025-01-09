#include "vendor/unity.h"

#define BUFFER_SIZE 4000

extern void recite(char *buffer, int start_verse, int end_verse);

void setUp(void) {
}

void tearDown(void) {
}

void test_fly(void) {
    char buffer[BUFFER_SIZE];

    recite(buffer, 1, 1);
    const char expected[] =
        "I know an old lady who swallowed a fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_spider(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 2, 2);
    const char expected[] =
        "I know an old lady who swallowed a spider.\n"
        "It wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_bird(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 3, 3);
    const char expected[] =
        "I know an old lady who swallowed a bird.\n"
        "How absurd to swallow a bird!\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_cat(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 4, 4);
    const char expected[] =
        "I know an old lady who swallowed a cat.\n"
        "Imagine that, to swallow a cat!\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_dog(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 5, 5);
    const char expected[] =
        "I know an old lady who swallowed a dog.\n"
        "What a hog, to swallow a dog!\n"
        "She swallowed the dog to catch the cat.\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_goat(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 6, 6);
    const char expected[] =
        "I know an old lady who swallowed a goat.\n"
        "Just opened her throat and swallowed a goat!\n"
        "She swallowed the goat to catch the dog.\n"
        "She swallowed the dog to catch the cat.\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_cow(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 7, 7);
    const char expected[] =
        "I know an old lady who swallowed a cow.\n"
        "I don't know how she swallowed a cow!\n"
        "She swallowed the cow to catch the goat.\n"
        "She swallowed the goat to catch the dog.\n"
        "She swallowed the dog to catch the cat.\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_horse(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 8, 8);
    const char expected[] =
        "I know an old lady who swallowed a horse.\n"
        "She's dead, of course!\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_multiple_verses(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 1, 3);
    const char expected[] =
        "I know an old lady who swallowed a fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n"
        "I know an old lady who swallowed a spider.\n"
        "It wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n"
        "I know an old lady who swallowed a bird.\n"
        "How absurd to swallow a bird!\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

void test_full_song(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    recite(buffer, 1, 8);
    const char expected[] =
        "I know an old lady who swallowed a fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n"
        "I know an old lady who swallowed a spider.\n"
        "It wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n"
        "I know an old lady who swallowed a bird.\n"
        "How absurd to swallow a bird!\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n"
        "I know an old lady who swallowed a cat.\n"
        "Imagine that, to swallow a cat!\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n"
        "I know an old lady who swallowed a dog.\n"
        "What a hog, to swallow a dog!\n"
        "She swallowed the dog to catch the cat.\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n"
        "I know an old lady who swallowed a goat.\n"
        "Just opened her throat and swallowed a goat!\n"
        "She swallowed the goat to catch the dog.\n"
        "She swallowed the dog to catch the cat.\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n"
        "I know an old lady who swallowed a cow.\n"
        "I don't know how she swallowed a cow!\n"
        "She swallowed the cow to catch the goat.\n"
        "She swallowed the goat to catch the dog.\n"
        "She swallowed the dog to catch the cat.\n"
        "She swallowed the cat to catch the bird.\n"
        "She swallowed the bird to catch the spider that wriggled and jiggled and tickled inside her.\n"
        "She swallowed the spider to catch the fly.\n"
        "I don't know why she swallowed the fly. Perhaps she'll die.\n"
        "\n"
        "I know an old lady who swallowed a horse.\n"
        "She's dead, of course!\n";
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fly);
    RUN_TEST(test_spider);
    RUN_TEST(test_bird);
    RUN_TEST(test_cat);
    RUN_TEST(test_dog);
    RUN_TEST(test_goat);
    RUN_TEST(test_cow);
    RUN_TEST(test_horse);
    RUN_TEST(test_multiple_verses);
    RUN_TEST(test_full_song);
    return UNITY_END();
}
