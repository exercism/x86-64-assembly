#include "vendor/unity.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct car_t {
    char name[10];
    int16_t speed;
    float battery;
};

enum surface_t {
    ASPHALT,
    SAND,
    ICE,
    CLAY
};

struct track_t {
    enum surface_t surface;
    size_t distance;
};

struct race_t {
    struct track_t track;
    uint8_t num_of_laps;
    struct car_t cars[6];
    uint8_t num_of_running_cars;
};

struct tournament_t {
    struct race_t races[20];
    size_t num_of_races;
};

extern struct car_t new_car(short speed, const char name[]);
extern struct track_t new_track(enum surface_t surface, size_t distance);
extern struct race_t new_race(struct track_t track, uint8_t num_of_laps);
extern bool add_participant(struct race_t *race, struct car_t car);
extern void add_race(struct tournament_t *tournament, struct race_t race);

void setUp(void) {
}

void tearDown(void) {
}

void test_new_cars(void) {
    char name1[10] = "Thunder";
    struct car_t car1 = new_car(517, name1);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(517, car1.speed, "Mismatch on car speed.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Thunder", car1.name, "Mismatch on car name.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, car1.battery, "Mismatch on car battery.");
    char name2[10] = "Opal";
    struct car_t car2 = new_car(626, name2);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(626, car2.speed, "Mismatch on car speed.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Opal", car2.name, "Mismatch on car name.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, car2.battery, "Mismatch on car battery.");
    char name3[10] = "Monster";
    struct car_t car3 = new_car(483, name3);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(483, car3.speed, "Mismatch on car speed.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Monster", car3.name, "Mismatch on car name.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, car3.battery, "Mismatch on car battery.");
    char name4[10] = "Firebolt";
    struct car_t car4 = new_car(789, name4);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(789, car4.speed, "Mismatch on car speed.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Firebolt", car4.name, "Mismatch on car name.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, car4.battery, "Mismatch on car battery.");
    char name5[10] = "Jumbo";
    struct car_t car5 = new_car(548, name5);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(548, car5.speed, "Mismatch on car speed.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Jumbo", car5.name, "Mismatch on car name.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, car5.battery, "Mismatch on car battery.");
    char name6[10] = "Rampage";
    struct car_t car6 = new_car(773, name6);
    TEST_ASSERT_EQUAL_INT16_MESSAGE(773, car6.speed, "Mismatch on car speed.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Rampage", car6.name, "Mismatch on car name.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, car6.battery, "Mismatch on car battery.");
}

void test_new_tracks(void) {
    TEST_IGNORE();
    struct track_t track1 = new_track(SAND, 4780);
    TEST_ASSERT_EQUAL_MESSAGE(SAND, track1.surface, "Mismatch on track surface.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(4780, track1.distance, "Mismatch on track distance.");
    struct track_t track2 = new_track(ASPHALT, 10450);
    TEST_ASSERT_EQUAL_MESSAGE(ASPHALT, track2.surface, "Mismatch on track surface.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(10450, track2.distance, "Mismatch on track distance.");
    struct track_t track3 = new_track(CLAY, 5587);
    TEST_ASSERT_EQUAL_MESSAGE(CLAY, track3.surface, "Mismatch on track surface.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(5587, track3.distance, "Mismatch on track distance.");
    struct track_t track4 = new_track(ICE, 1384);
    TEST_ASSERT_EQUAL_MESSAGE(ICE, track4.surface, "Mismatch on track surface.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1384, track4.distance, "Mismatch on track distance.");
}

void test_new_races(void) {
    TEST_IGNORE();
    struct race_t race1 = new_race(new_track(CLAY, 7628), 18);
    TEST_ASSERT_EQUAL_MESSAGE(CLAY, race1.track.surface, "Mismatch on track surface.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7628, race1.track.distance, "Mismatch on track distance.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(18, race1.num_of_laps, "Mismatch on number of laps.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, race1.num_of_running_cars, "Mismatch on number of running cars.");
    struct race_t race2 = new_race(new_track(SAND, 3456), 25);
    TEST_ASSERT_EQUAL_MESSAGE(SAND, race2.track.surface, "Mismatch on track surface.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(3456, race2.track.distance, "Mismatch on track distance.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(25, race2.num_of_laps, "Mismatch on number of laps.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, race2.num_of_running_cars, "Mismatch on number of running cars.");
    struct race_t race3 = new_race(new_track(ASPHALT, 5287), 36);
    TEST_ASSERT_EQUAL_MESSAGE(ASPHALT, race3.track.surface, "Mismatch on track surface.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(5287, race3.track.distance, "Mismatch on track distance.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(36, race3.num_of_laps, "Mismatch on number of laps.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, race3.num_of_running_cars, "Mismatch on number of running cars.");
    struct race_t race4 = new_race(new_track(ICE, 4981), 17);
    TEST_ASSERT_EQUAL_MESSAGE(ICE, race4.track.surface, "Mismatch on track surface.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(4981, race4.track.distance, "Mismatch on track distance.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(17, race4.num_of_laps, "Mismatch on number of laps.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, race4.num_of_running_cars, "Mismatch on number of running cars.");
}

void test_add_participants(void) {
    TEST_IGNORE();
    struct race_t race = new_race(new_track(ASPHALT, 5287), 36);
    char name1[10] = "Thunder";
    TEST_ASSERT_EQUAL_MESSAGE(true, add_participant(&race, new_car(517, name1)),
                              "Number of cars in array before the function is called - 1.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Thunder", race.cars[0].name, "Mismatch on name for car at index 0.");
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(517, race.cars[0].speed, "Mismatch on speed for car at index 0.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, race.cars[0].battery, "Mismatch on battery for car at index 0.");
    char name2[10] = "Opal";
    TEST_ASSERT_EQUAL_MESSAGE(true, add_participant(&race, new_car(626, name2)),
                              "Number of cars in array before the function is called - 2.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Opal", race.cars[1].name, "Mismatch on name for car at index 1.");
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(626, race.cars[1].speed, "Mismatch on speed for car at index 1.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, race.cars[1].battery, "Mismatch on battery for car at index 1.");
    char name3[10] = "Monster";
    TEST_ASSERT_EQUAL_MESSAGE(true, add_participant(&race, new_car(483, name3)),
                              "Number of cars in array before the function is called - 3.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Monster", race.cars[2].name, "Mismatch on name for car at index 2.");
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(483, race.cars[2].speed, "Mismatch on speed for car at index 2.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, race.cars[2].battery, "Mismatch on battery for car at index 2.");
    char name4[10] = "Firebolt";
    TEST_ASSERT_EQUAL_MESSAGE(true, add_participant(&race, new_car(789, name4)),
                              "Number of cars in array before the function is called - 4.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Firebolt", race.cars[3].name, "Mismatch on name for car at index 3.");
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(789, race.cars[3].speed, "Mismatch on speed for car at index 3.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, race.cars[3].battery, "Mismatch on battery for car at index 3.");
    char name5[10] = "Jumbo";
    TEST_ASSERT_EQUAL_MESSAGE(true, add_participant(&race, new_car(548, name5)),
                              "Number of cars in array before the function is called - 5.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Jumbo", race.cars[4].name, "Mismatch on name for car at index 4.");
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(548, race.cars[4].speed, "Mismatch on speed for car at index 4.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, race.cars[4].battery, "Mismatch on battery for car at index 4.");
    char name6[10] = "Rampage";
    TEST_ASSERT_EQUAL_MESSAGE(true, add_participant(&race, new_car(773, name6)),
                              "Number of cars in array before the function is called - 6.");
    TEST_ASSERT_EQUAL_STRING_MESSAGE("Rampage", race.cars[5].name, "Mismatch on name for car at index 5.");
    TEST_ASSERT_EQUAL_UINT16_MESSAGE(773, race.cars[5].speed, "Mismatch on speed for car at index 5.");
    TEST_ASSERT_FLOAT_WITHIN_MESSAGE(0.001, 100.0, race.cars[5].battery, "Mismatch on battery for car at index 5.");
    char name7[10] = "Razor";
    TEST_ASSERT_EQUAL_MESSAGE(false, add_participant(&race, new_car(633, name7)),
                              "Number of cars in array before the function is called - 7.");
    char name8[10] = "Astro";
    TEST_ASSERT_EQUAL_MESSAGE(false, add_participant(&race, new_car(892, name8)),
                              "Number of cars in array before the function is called - 8.");
}

void test_add_races(void) {
    TEST_IGNORE();
    struct tournament_t tournament = {0};
    add_race(&tournament, new_race(new_track(ICE, 23435), 27));
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1, tournament.num_of_races, "Mismatch on number of races.");
    TEST_ASSERT_EQUAL_MESSAGE(ICE, tournament.races[0].track.surface, "Mismatch on track surface for race at index 0.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(23435, tournament.races[0].track.distance, "Mismatch on track distance for race at index 0.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(27, tournament.races[0].num_of_laps, "Mismatch on number of laps for race at index 0.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, tournament.races[0].num_of_running_cars, "Mismatch on number of running cars for race at index 0.");
    add_race(&tournament, new_race(new_track(CLAY, 3456), 12));
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, tournament.num_of_races, "Mismatch on number of races.");
    TEST_ASSERT_EQUAL_MESSAGE(CLAY, tournament.races[1].track.surface, "Mismatch on track surface for race at index 1.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(3456, tournament.races[1].track.distance, "Mismatch on track distance for race at index 1.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(12, tournament.races[1].num_of_laps, "Mismatch on number of laps for race at index 1.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, tournament.races[1].num_of_running_cars, "Mismatch on number of running cars for race at index 1.");
    add_race(&tournament, new_race(new_track(ASPHALT, 5287), 21));
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, tournament.num_of_races, "Mismatch on number of races.");
    TEST_ASSERT_EQUAL_MESSAGE(ASPHALT, tournament.races[2].track.surface, "Mismatch on track surface for race at index 2.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(5287, tournament.races[2].track.distance, "Mismatch on track distance for race at index 2.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(21, tournament.races[2].num_of_laps, "Mismatch on number of laps for race at index 2.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, tournament.races[2].num_of_running_cars, "Mismatch on number of running cars for race at index 2.");
    add_race(&tournament, new_race(new_track(ICE, 4981), 33));
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(4, tournament.num_of_races, "Mismatch on number of races.");
    TEST_ASSERT_EQUAL_MESSAGE(ICE, tournament.races[3].track.surface, "Mismatch on track surface for race at index 3.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(4981, tournament.races[3].track.distance, "Mismatch on track distance for race at index 3.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(33, tournament.races[3].num_of_laps, "Mismatch on number of laps for race at index 3.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, tournament.races[3].num_of_running_cars, "Mismatch on number of running cars for race at index 3.");
    add_race(&tournament, new_race(new_track(SAND, 1245), 13));
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, tournament.num_of_races, "Mismatch on number of races.");
    TEST_ASSERT_EQUAL_MESSAGE(SAND, tournament.races[4].track.surface, "Mismatch on track surface for race at index 4.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1245, tournament.races[4].track.distance, "Mismatch on track distance for race at index 4.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(13, tournament.races[4].num_of_laps, "Mismatch on number of laps for race at index 4.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, tournament.races[4].num_of_running_cars, "Mismatch on number of running cars for race at index 4.");
    add_race(&tournament, new_race(new_track(ASPHALT, 7736), 24));
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(6, tournament.num_of_races, "Mismatch on number of races.");
    TEST_ASSERT_EQUAL_MESSAGE(ASPHALT, tournament.races[5].track.surface, "Mismatch on track surface for race at index 5.");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7736, tournament.races[5].track.distance, "Mismatch on track distance for race at index 5.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(24, tournament.races[5].num_of_laps, "Mismatch on number of laps for race at index 5.");
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, tournament.races[5].num_of_running_cars, "Mismatch on number of running cars for race at index 5.");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_cars);
    RUN_TEST(test_new_tracks);
    RUN_TEST(test_new_races);
    RUN_TEST(test_add_participants);
    RUN_TEST(test_add_races);
    return UNITY_END();
}
