#include "vendor/unity.h"

#include <pthread.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdlib.h>

typedef void (*task_t)(void);
typedef void *(*worker_t)(void *);

extern void clobber(void);

extern void admit_group(int64_t *admissions, int64_t group_size);
extern int64_t change_reel(int64_t *mounted, int64_t next_reel);
extern int64_t sell_ticket(int64_t *tickets_sold);
extern int64_t claim_seat(int64_t *seats_taken, int64_t capacity);
extern void visit_booth(volatile int64_t *booth, task_t task);

#define THREAD_COUNT 8
#define CALLS_PER_THREAD 100000
#define SEAT_CAPACITY 10000

// A starting gate releases every thread at once, so the calls really overlap.
static pthread_mutex_t gate_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t gate_cond = PTHREAD_COND_INITIALIZER;
static int gate_open = 0;

static void gate_wait(void) {
    pthread_mutex_lock(&gate_mutex);
    while (!gate_open) pthread_cond_wait(&gate_cond, &gate_mutex);
    pthread_mutex_unlock(&gate_mutex);
}

static void run_threads(worker_t worker, void *args, size_t arg_stride) {
    pthread_t threads[THREAD_COUNT];
    pthread_mutex_lock(&gate_mutex);
    gate_open = 0;
    pthread_mutex_unlock(&gate_mutex);
    const size_t stride = args ? arg_stride : 0;
    char *raw_args_bytes = args;
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&threads[i], NULL, worker, raw_args_bytes);
        raw_args_bytes += stride;
    }
    pthread_mutex_lock(&gate_mutex);
    gate_open = 1;
    pthread_cond_broadcast(&gate_cond);
    pthread_mutex_unlock(&gate_mutex);
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
}

// Task 1
static int64_t lobby_admissions;

static void *door_worker(void *arg) {
    (void)arg;
    gate_wait();
    for (int i = 0; i < CALLS_PER_THREAD; i++) {
        admit_group(&lobby_admissions, (i & 3) + 1);
    }
    return NULL;
}

// Task 2
static int64_t relay_mounted;
static int64_t relay_held[THREAD_COUNT];

static void *reel_worker(void *arg) {
    int64_t *held = arg;
    gate_wait();
    int64_t reel = *held;
    for (int i = 0; i < CALLS_PER_THREAD; i++) {
        reel = change_reel(&relay_mounted, reel);
    }
    *held = reel;
    return NULL;
}

// Task 3
static int64_t rush_counter;
static int64_t rush_range;
static _Atomic unsigned char *rush_seen;
static _Atomic int64_t rush_errors;

static void *ticket_worker(void *arg) {
    (void)arg;
    gate_wait();
    for (int i = 0; i < CALLS_PER_THREAD; i++) {
        int64_t number = sell_ticket(&rush_counter);
        if (number < 1 || number > rush_range || atomic_fetch_add(&rush_seen[number - 1], 1) != 0) {
            atomic_fetch_add(&rush_errors, 1);
        }
    }
    return NULL;
}

// Task 4
static int64_t seats_taken_shared;
static _Atomic unsigned char seat_seen[SEAT_CAPACITY];
static _Atomic int64_t seat_successes;
static _Atomic int64_t seat_errors;

static void *seat_worker(void *arg) {
    (void)arg;
    gate_wait();
    for (int i = 0; i < CALLS_PER_THREAD; i++) {
        int64_t seat = claim_seat(&seats_taken_shared, SEAT_CAPACITY);
        if (seat == 0) {
            continue;
        }
        atomic_fetch_add(&seat_successes, 1);
        if (seat < 1 || seat > SEAT_CAPACITY || atomic_fetch_add(&seat_seen[seat - 1], 1) != 0) {
            atomic_fetch_add(&seat_errors, 1);
        }
    }
    return NULL;
}

// Task 5
// using volatile protects the variables from compiler optimizations that may interfere with the result
static volatile int64_t booth_word;
static volatile int64_t logbook_entries;
static volatile int64_t booth_seen_during_task;

static void observing_task(void) {
    clobber();
    booth_seen_during_task = booth_word;
}

static void logbook_task(void) {
    clobber();
    int64_t entries = logbook_entries;
    logbook_entries = entries + 1;
}

static void *booth_worker(void *arg) {
    (void)arg;
    gate_wait();
    for (int i = 0; i < CALLS_PER_THREAD; i++) {
        visit_booth(&booth_word, logbook_task);
    }
    return NULL;
}

void setUp(void) {
}

void tearDown(void) {
}

// TASK: 1
void test_admit_group_a_pair(void) {
    int64_t admissions = 0;
    admit_group(&admissions, 2);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(2, admissions, "The admissions tally is different from expected.");
}

void test_admit_group_example(void) {
    TEST_IGNORE();
    int64_t admissions = 120;
    admit_group(&admissions, 4);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(124, admissions, "The admissions tally is different from expected.");
}

void test_admit_group_a_stream_of_groups(void) {
    TEST_IGNORE();
    int64_t admissions = 0;
    admit_group(&admissions, 3);
    admit_group(&admissions, 1);
    admit_group(&admissions, 5);
    admit_group(&admissions, 2);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(11, admissions, "The admissions tally is different from expected.");
}

void test_admit_group_doors_open(void) {
    TEST_IGNORE();
    lobby_admissions = 0;
    int64_t per_thread = 0;
    for (int i = 0; i < CALLS_PER_THREAD; i++) per_thread += (i % 4) + 1;
    run_threads(door_worker, NULL, 0);
    TEST_ASSERT_EQUAL_INT64_MESSAGE((int64_t)THREAD_COUNT * per_thread, lobby_admissions,
                                    "Some updates were lost. The tally must equal the sum of every group let through.");
}

// TASK: 2
void test_change_reel_example(void) {
    TEST_IGNORE();
    int64_t mounted = 7;
    TEST_ASSERT_EQUAL_INT64_MESSAGE(7, change_reel(&mounted, 9), "The reel handed back is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(9, mounted, "The mounted reel is different from expected.");
}

void test_change_reel_through_the_evening(void) {
    TEST_IGNORE();
    int64_t mounted = 1;
    TEST_ASSERT_EQUAL_INT64_MESSAGE(1, change_reel(&mounted, 2), "The reel handed back is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(2, change_reel(&mounted, 5), "The reel handed back is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(5, change_reel(&mounted, 8), "The reel handed back is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(8, mounted, "The mounted reel is different from expected.");
}

void test_change_reel_busy_projection_room(void) {
    TEST_IGNORE();
    relay_mounted = 0;
    for (int i = 0; i < THREAD_COUNT; i++) relay_held[i] = i + 1;
    run_threads(reel_worker, relay_held, sizeof relay_held[0]);
    int seen[THREAD_COUNT + 1] = {0};
    TEST_ASSERT_TRUE_MESSAGE(relay_mounted >= 0 && relay_mounted <= THREAD_COUNT, "The mounted reel must be one of the reels in play.");
    seen[relay_mounted]++;
    for (int i = 0; i < THREAD_COUNT; i++) {
        TEST_ASSERT_TRUE_MESSAGE(relay_held[i] >= 0 && relay_held[i] <= THREAD_COUNT, "Every reel held must be one of the reels in play.");
        seen[relay_held[i]]++;
    }
    for (int i = 0; i <= THREAD_COUNT; i++) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(1, seen[i], "One reel was lost or duplicated. Every reel must come back exactly once.");
    }
}

// TASK: 3
void test_sell_ticket_the_first_of_the_night(void) {
    TEST_IGNORE();
    int64_t tickets_sold = 0;
    TEST_ASSERT_EQUAL_INT64_MESSAGE(1, sell_ticket(&tickets_sold), "The ticket number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(1, tickets_sold, "The count of tickets sold is different from expected.");
}

void test_sell_ticket_example(void) {
    TEST_IGNORE();
    int64_t tickets_sold = 41;
    TEST_ASSERT_EQUAL_INT64_MESSAGE(42, sell_ticket(&tickets_sold), "The ticket number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(42, tickets_sold, "The count of tickets sold is different from expected.");
}

void test_sell_ticket_three_sales_in_a_row(void) {
    TEST_IGNORE();
    int64_t tickets_sold = 0;
    TEST_ASSERT_EQUAL_INT64_MESSAGE(1, sell_ticket(&tickets_sold), "The ticket number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(2, sell_ticket(&tickets_sold), "The ticket number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(3, sell_ticket(&tickets_sold), "The ticket number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(3, tickets_sold, "The count of tickets sold is different from expected.");
}

void test_sell_ticket_opening_rush(void) {
    TEST_IGNORE();
    const int64_t total = (int64_t)THREAD_COUNT * CALLS_PER_THREAD;
    rush_counter = 0;
    rush_range = total;
    rush_errors = 0;
    rush_seen = calloc((size_t)total, sizeof *rush_seen);
    TEST_ASSERT_NOT_NULL_MESSAGE(rush_seen, "Failed to allocate the ticket tracking table.");
    run_threads(ticket_worker, NULL, 0);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(total, rush_counter, "Some updates were lost. The final count must equal the number of sales.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, rush_errors, "Every ticket number must be distinct and in range.");
    int64_t missing = 0;
    for (int64_t i = 0; i < total; i++) {
        if (rush_seen[i] != 1) missing++;
    }
    free(rush_seen);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, missing, "Every ticket number up to the total must be handed out exactly once.");
}

// TASK: 4
void test_claim_seat_plenty_of_seats(void) {
    TEST_IGNORE();
    int64_t seats_taken = 0;
    TEST_ASSERT_EQUAL_INT64_MESSAGE(1, claim_seat(&seats_taken, 150), "The seat number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(1, seats_taken, "The count of taken seats is different from expected.");
}

void test_claim_seat_the_last_seat(void) {
    TEST_IGNORE();
    int64_t seats_taken = 149;
    TEST_ASSERT_EQUAL_INT64_MESSAGE(150, claim_seat(&seats_taken, 150), "The seat number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(150, seats_taken, "The count of taken seats is different from expected.");
}

void test_claim_seat_sold_out(void) {
    TEST_IGNORE();
    int64_t seats_taken = 150;
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, claim_seat(&seats_taken, 150), "The seat number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(150, seats_taken, "The count of taken seats is different from expected.");
}

void test_claim_seat_until_sold_out(void) {
    TEST_IGNORE();
    int64_t seats_taken = 0;
    TEST_ASSERT_EQUAL_INT64_MESSAGE(1, claim_seat(&seats_taken, 3), "The seat number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(2, claim_seat(&seats_taken, 3), "The seat number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(3, claim_seat(&seats_taken, 3), "The seat number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, claim_seat(&seats_taken, 3), "The seat number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, claim_seat(&seats_taken, 3), "The seat number is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(3, seats_taken, "The count of taken seats is different from expected.");
}

void test_claim_seat_premiere_rush(void) {
    TEST_IGNORE();
    seats_taken_shared = 0;
    seat_successes = 0;
    seat_errors = 0;
    for (int i = 0; i < SEAT_CAPACITY; i++) seat_seen[i] = 0;
    run_threads(seat_worker, NULL, 0);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(SEAT_CAPACITY, seats_taken_shared, "The screening must fill exactly to capacity, never beyond.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(SEAT_CAPACITY, seat_successes, "Exactly one claim per seat must succeed.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, seat_errors, "Every seat number must be distinct and in range.");
    int64_t empty = 0;
    for (int i = 0; i < SEAT_CAPACITY; i++) {
        if (seat_seen[i] != 1) empty++;
    }
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, empty, "Every seat up to capacity must be claimed exactly once.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, claim_seat(&seats_taken_shared, SEAT_CAPACITY), "A sold-out screening must refuse further claims.");
}

// TASK: 5
void test_visit_booth_runs_the_task(void) {
    TEST_IGNORE();
    booth_word = 0;
    logbook_entries = 41;
    visit_booth(&booth_word, logbook_task);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(42, logbook_entries, "The task must be run exactly once per visit.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");
}

void test_visit_booth_holds_the_booth_during_the_task(void) {
    TEST_IGNORE();
    booth_word = 0;
    booth_seen_during_task = -1;
    visit_booth(&booth_word, observing_task);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(1, booth_seen_during_task, "The booth must be occupied while the task runs.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");
}

void test_visit_booth_a_full_shift_of_visits(void) {
    TEST_IGNORE();
    booth_word = 0;
    logbook_entries = 0;
    visit_booth(&booth_word, logbook_task);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(1, logbook_entries, "The count of logbook entries is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");
    visit_booth(&booth_word, logbook_task);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(2, logbook_entries, "The count of logbook entries is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");
    visit_booth(&booth_word, logbook_task);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(3, logbook_entries, "The count of logbook entries is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");
    visit_booth(&booth_word, logbook_task);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(4, logbook_entries, "The count of logbook entries is different from expected.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");
}

void test_visit_booth_everyone_at_once(void) {
    TEST_IGNORE();
    booth_word = 0;
    logbook_entries = 0;
    visit_booth(&booth_word, logbook_task);
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");
    logbook_entries = 0;
    run_threads(booth_worker, NULL, 0);
    TEST_ASSERT_EQUAL_INT64_MESSAGE((int64_t)THREAD_COUNT * CALLS_PER_THREAD, logbook_entries,
                                    "The booth admitted two visitors at once. The count of entries must be exact.");
    TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be free once everyone has left.");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_admit_group_a_pair);
    RUN_TEST(test_admit_group_example);
    RUN_TEST(test_admit_group_a_stream_of_groups);
    RUN_TEST(test_admit_group_doors_open);
    RUN_TEST(test_change_reel_example);
    RUN_TEST(test_change_reel_through_the_evening);
    RUN_TEST(test_change_reel_busy_projection_room);
    RUN_TEST(test_sell_ticket_the_first_of_the_night);
    RUN_TEST(test_sell_ticket_example);
    RUN_TEST(test_sell_ticket_three_sales_in_a_row);
    RUN_TEST(test_sell_ticket_opening_rush);
    RUN_TEST(test_claim_seat_plenty_of_seats);
    RUN_TEST(test_claim_seat_the_last_seat);
    RUN_TEST(test_claim_seat_sold_out);
    RUN_TEST(test_claim_seat_until_sold_out);
    RUN_TEST(test_claim_seat_premiere_rush);
    RUN_TEST(test_visit_booth_runs_the_task);
    RUN_TEST(test_visit_booth_holds_the_booth_during_the_task);
    RUN_TEST(test_visit_booth_a_full_shift_of_visits);
    RUN_TEST(test_visit_booth_everyone_at_once);
    return UNITY_END();
}
