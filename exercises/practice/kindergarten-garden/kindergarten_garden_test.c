// Version: 0

#include "vendor/unity.h"

#define BUFFER_SIZE 80

extern void plants(char *buffer, const char *diagram, const char *student);

void setUp(void) {
}

void tearDown(void) {
}

void test_garden_with_single_student(void) {
    char buffer[BUFFER_SIZE];

    plants(buffer, "RC\nGG", "Alice");
    TEST_ASSERT_EQUAL_STRING("radishes, clover, grass, grass", buffer);
}

void test_different_garden_with_single_student(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VC\nRC", "Alice");
    TEST_ASSERT_EQUAL_STRING("violets, clover, radishes, clover", buffer);
}

void test_garden_with_two_students(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VVCG\nVVRC", "Bob");
    TEST_ASSERT_EQUAL_STRING("clover, grass, radishes, clover", buffer);
}

void test_second_students_garden(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VVCCGG\nVVCCGG", "Bob");
    TEST_ASSERT_EQUAL_STRING("clover, clover, clover, clover", buffer);
}

void test_third_students_garden(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VVCCGG\nVVCCGG", "Charlie");
    TEST_ASSERT_EQUAL_STRING("grass, grass, grass, grass", buffer);
}

void test_for_alice_first_students_garden(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Alice");
    TEST_ASSERT_EQUAL_STRING("violets, radishes, violets, radishes", buffer);
}

void test_for_bob_second_students_garden(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Bob");
    TEST_ASSERT_EQUAL_STRING("clover, grass, clover, clover", buffer);
}

void test_for_charlie(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Charlie");
    TEST_ASSERT_EQUAL_STRING("violets, violets, clover, grass", buffer);
}

void test_for_david(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "David");
    TEST_ASSERT_EQUAL_STRING("radishes, violets, clover, radishes", buffer);
}

void test_for_eve(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Eve");
    TEST_ASSERT_EQUAL_STRING("clover, grass, radishes, grass", buffer);
}

void test_for_fred(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Fred");
    TEST_ASSERT_EQUAL_STRING("grass, clover, violets, clover", buffer);
}

void test_for_ginny(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Ginny");
    TEST_ASSERT_EQUAL_STRING("clover, grass, grass, clover", buffer);
}

void test_for_harriet(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Harriet");
    TEST_ASSERT_EQUAL_STRING("violets, radishes, radishes, violets", buffer);
}

void test_for_ileana(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Ileana");
    TEST_ASSERT_EQUAL_STRING("grass, clover, violets, clover", buffer);
}

void test_for_joseph(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Joseph");
    TEST_ASSERT_EQUAL_STRING("violets, clover, violets, grass", buffer);
}

void test_for_kincaid_second_to_last_students_garden(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Kincaid");
    TEST_ASSERT_EQUAL_STRING("grass, clover, clover, grass", buffer);
}

void test_for_larry_last_students_garden(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];

    plants(buffer, "VRCGVVRVCGGCCGVRGCVCGCGV\nVRCCCGCRRGVCGCRVVCVGCGCV", "Larry");
    TEST_ASSERT_EQUAL_STRING("grass, violets, clover, violets", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_garden_with_single_student);
    RUN_TEST(test_different_garden_with_single_student);
    RUN_TEST(test_garden_with_two_students);
    RUN_TEST(test_second_students_garden);
    RUN_TEST(test_third_students_garden);
    RUN_TEST(test_for_alice_first_students_garden);
    RUN_TEST(test_for_bob_second_students_garden);
    RUN_TEST(test_for_charlie);
    RUN_TEST(test_for_david);
    RUN_TEST(test_for_eve);
    RUN_TEST(test_for_fred);
    RUN_TEST(test_for_ginny);
    RUN_TEST(test_for_harriet);
    RUN_TEST(test_for_ileana);
    RUN_TEST(test_for_joseph);
    RUN_TEST(test_for_kincaid_second_to_last_students_garden);
    RUN_TEST(test_for_larry_last_students_garden);
    return UNITY_END();
}
