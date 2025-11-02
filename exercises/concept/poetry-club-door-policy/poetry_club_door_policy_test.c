#include "vendor/unity.h"

#include <stdint.h>

#define BUFFER_SIZE 50

extern char front_door_response(const char *line);
extern void front_door_password(char *letters);
extern char back_door_response(const char *line);
extern void back_door_password(char *buffer, char *letters);

void setUp(void) {
}

void tearDown(void) {
}

void test_front_door_response_s1(void) {
    const char actual = front_door_response("Sunshine warming my toes,");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("S", &actual, 1, "Passed line: Sunshine warming my toes,");
}

void test_front_door_response_u1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Underwater fun with my friends.");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("U", &actual, 1, "Passed line: Underwater fun with my friends.");
}

void test_front_door_response_m1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Making homemade ice cream on the porch,");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("M", &actual, 1, "Passed line: Making homemade ice cream on the porch,");
}

void test_front_door_response_m2(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Many long nights catching fireflies.");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("M", &actual, 1, "Passed line: Many long nights catching fireflies.");
}

void test_front_door_response_e1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Early morning walks to the creek,");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("E", &actual, 1, "Passed line: Early morning walks to the creek,");
}

void test_front_door_response_r1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Reveling in the freedom of lazy days.");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("R", &actual, 1, "Passed line: Reveling in the freedom of lazy days.");
}

void test_front_door_response_s2(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Serene, calming quality");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("S", &actual, 1, "Passed line: Serene, calming quality");
}

void test_front_door_response_o1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Organized, you always have it together");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("O", &actual, 1, "Passed line: Organized, you always have it together");
}

void test_front_door_response_p1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Picturesque, strikingly beautiful");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("P", &actual, 1, "Passed line: Picturesque, strikingly beautiful");
}

void test_front_door_response_h1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Honest, so genuine");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("H", &actual, 1, "Passed line: Honest, so genuine");
}

void test_front_door_response_i1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Imaginative, a creative mind");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("I", &actual, 1, "Passed line: Imaginative, a creative mind");
}

void test_front_door_response_a1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Alluring, so attractive");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("A", &actual, 1, "Passed line: Alluring, so attractive");
}

void test_front_door_response_c1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Compilers intensily bestow");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("C", &actual, 1, "Passed line: Compilers intensily bestow");
}

void test_front_door_response_o2(void) {
    TEST_IGNORE();
    const char actual = front_door_response("On commencing without ego");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("O", &actual, 1, "Passed line: On commencing without ego");
}

void test_front_door_response_d1(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Different processes ajar");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("D", &actual, 1, "Passed line: Different processes ajar");
}

void test_front_door_response_e2(void) {
    TEST_IGNORE();
    const char actual = front_door_response("Exit with zero quick");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("E", &actual, 1, "Passed line: Exit with zero quick");
}

void test_front_door_password_summer(void) {
    TEST_IGNORE();
    char letters[] = "SUMMER";
    front_door_password(letters);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Summer", letters, "Combined letters are: SUMMER");
}

void test_front_door_password_sophia(void) {
    TEST_IGNORE();
    char letters[] = "sophia";
    front_door_password(letters);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Sophia", letters, "Combined letters are: sophia");
}

void test_front_door_password_code(void) {
    TEST_IGNORE();
    char letters[] = "Code";
    front_door_password(letters);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Code", letters, "Combined letters are: Code");
}

void test_back_door_response_w1(void) {
    TEST_IGNORE();
    const char actual = back_door_response("Compilers intensily bestow");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("w", &actual, 1, "Passed line: Compilers intensily bestow");
}

void test_back_door_response_o1(void) {
    TEST_IGNORE();
    const char actual = back_door_response("On commencing without ego");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("o", &actual, 1, "Passed line: On commencing without ego");
}

void test_back_door_response_r1(void) {
    TEST_IGNORE();
    const char actual = back_door_response("Different processes ajar");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("r", &actual, 1, "Passed line: Different processes ajar");
}

void test_back_door_response_k1(void) {
    TEST_IGNORE();
    const char actual = back_door_response("Exit with zero quick");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("k", &actual, 1, "Passed line: Exit with zero quick");
}

void test_back_door_response_h1(void) {
    TEST_IGNORE();
    const char actual = back_door_response("Stands so HIGH   ");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("H", &actual, 1, "Passed line: Stands so HIGH   ");
}

void test_back_door_response_o2(void) {
    TEST_IGNORE();
    const char actual = back_door_response("	Huge ... hooves ... too!");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("o", &actual, 1, "Passed line: 	Huge ... hooves ... too!");
}

void test_back_door_response_r2(void) {
    TEST_IGNORE();
    const char actual = back_door_response("Impatiently waits for... 	 	");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("r", &actual, 1, "Passed line: Impatiently waits for... 	 	");
}

void test_back_door_response_s1(void) {
    TEST_IGNORE();
    const char actual = back_door_response("    Reins and harness    ");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("s", &actual, 1, "Passed line:     Reins and harness    ");
}

void test_back_door_response_e1(void) {
    TEST_IGNORE();
    const char actual = back_door_response("Eager to LEAVE!!!");
    TEST_ASSERT_EQUAL_STRING_LEN_MESSAGE("E", &actual, 1, "Passed line: Eager to LEAVE!!!");
}

void test_back_door_password_work(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    char letters[] = "work";
    back_door_password(buffer, letters);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Work, please.", buffer, "Combined letters are: work");
}

void test_back_door_password_horse(void) {
    TEST_IGNORE();
    char buffer[BUFFER_SIZE];
    char letters[] = "horse";
    back_door_password(buffer, letters);
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Horse, please.", buffer, "Combined letters are: horse");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_front_door_response_s1);
    RUN_TEST(test_front_door_response_u1);
    RUN_TEST(test_front_door_response_m1);
    RUN_TEST(test_front_door_response_m2);
    RUN_TEST(test_front_door_response_e1);
    RUN_TEST(test_front_door_response_r1);
    RUN_TEST(test_front_door_response_s2);
    RUN_TEST(test_front_door_response_o1);
    RUN_TEST(test_front_door_response_p1);
    RUN_TEST(test_front_door_response_h1);
    RUN_TEST(test_front_door_response_i1);
    RUN_TEST(test_front_door_response_a1);
    RUN_TEST(test_front_door_response_c1);
    RUN_TEST(test_front_door_response_o2);
    RUN_TEST(test_front_door_response_d1);
    RUN_TEST(test_front_door_response_e2);
    RUN_TEST(test_front_door_password_summer);
    RUN_TEST(test_front_door_password_sophia);
    RUN_TEST(test_front_door_password_code);
    RUN_TEST(test_back_door_response_w1);
    RUN_TEST(test_back_door_response_o1);
    RUN_TEST(test_back_door_response_r1);
    RUN_TEST(test_back_door_response_k1);
    RUN_TEST(test_back_door_response_h1);
    RUN_TEST(test_back_door_response_o2);
    RUN_TEST(test_back_door_response_r2);
    RUN_TEST(test_back_door_response_s1);
    RUN_TEST(test_back_door_response_e1);
    RUN_TEST(test_back_door_password_work);
    RUN_TEST(test_back_door_password_horse);
    return UNITY_END();
}
