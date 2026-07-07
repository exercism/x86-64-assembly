FUNC_PROTO = """\
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
    while (!gate_open)
        pthread_cond_wait(&gate_cond, &gate_mutex);
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
"""


def _sell(start, calls):
    return [start + k + 1 for k in range(calls)], start + calls


def _claim(taken, capacity, calls):
    returns = []
    for _ in range(calls):
        if taken < capacity:
            taken += 1
            returns.append(taken)
        else:
            returns.append(0)
    return returns, taken


def _chain(mounted, nexts):
    returns = []
    for reel in nexts:
        returns.append(mounted)
        mounted = reel
    return returns, mounted


def extra_cases():
    return [
        {
            "task_id": 1,
            "description": "admit_group_a_pair",
            "property": "admit_group",
            "input": [0, [2]],
            "expected": 2,
        },
        {
            "task_id": 1,
            "description": "admit_group_example",
            "property": "admit_group",
            "input": [120, [4]],
            "expected": 124,
        },
        {
            "task_id": 1,
            "description": "admit_group_a_stream_of_groups",
            "property": "admit_group",
            "input": [0, [3, 1, 5, 2]],
            "expected": 11,
        },
        {
            "task_id": 1,
            "description": "admit_group_doors_open",
            "property": "admit_group_rush",
            "input": [],
            "expected": None,
        },
        {
            "task_id": 2,
            "description": "change_reel_example",
            "property": "change_reel",
            "input": [7, [9]],
            "expected": _chain(7, [9]),
        },
        {
            "task_id": 2,
            "description": "change_reel_through_the_evening",
            "property": "change_reel",
            "input": [1, [2, 5, 8]],
            "expected": _chain(1, [2, 5, 8]),
        },
        {
            "task_id": 2,
            "description": "change_reel_busy_projection_room",
            "property": "change_reel_relay",
            "input": [],
            "expected": None,
        },
        {
            "task_id": 3,
            "description": "sell_ticket_the_first_of_the_night",
            "property": "sell_ticket",
            "input": [0, 1],
            "expected": _sell(0, 1),
        },
        {
            "task_id": 3,
            "description": "sell_ticket_example",
            "property": "sell_ticket",
            "input": [41, 1],
            "expected": _sell(41, 1),
        },
        {
            "task_id": 3,
            "description": "sell_ticket_three_sales_in_a_row",
            "property": "sell_ticket",
            "input": [0, 3],
            "expected": _sell(0, 3),
        },
        {
            "task_id": 3,
            "description": "sell_ticket_opening_rush",
            "property": "sell_ticket_rush",
            "input": [],
            "expected": None,
        },
        {
            "task_id": 4,
            "description": "claim_seat_plenty_of_seats",
            "property": "claim_seat",
            "input": [0, 150, 1],
            "expected": _claim(0, 150, 1),
        },
        {
            "task_id": 4,
            "description": "claim_seat_the_last_seat",
            "property": "claim_seat",
            "input": [149, 150, 1],
            "expected": _claim(149, 150, 1),
        },
        {
            "task_id": 4,
            "description": "claim_seat_sold_out",
            "property": "claim_seat",
            "input": [150, 150, 1],
            "expected": _claim(150, 150, 1),
        },
        {
            "task_id": 4,
            "description": "claim_seat_until_sold_out",
            "property": "claim_seat",
            "input": [0, 3, 5],
            "expected": _claim(0, 3, 5),
        },
        {
            "task_id": 4,
            "description": "claim_seat_premiere_rush",
            "property": "claim_seat_rush",
            "input": [],
            "expected": None,
        },
        {
            "task_id": 5,
            "description": "visit_booth_runs_the_task",
            "property": "visit_booth_runs",
            "input": [],
            "expected": None,
        },
        {
            "task_id": 5,
            "description": "visit_booth_holds_the_booth_during_the_task",
            "property": "visit_booth_holds",
            "input": [],
            "expected": None,
        },
        {
            "task_id": 5,
            "description": "visit_booth_a_full_shift_of_visits",
            "property": "visit_booth_shift",
            "input": [],
            "expected": None,
        },
        {
            "task_id": 5,
            "description": "visit_booth_everyone_at_once",
            "property": "visit_booth_rush",
            "input": [],
            "expected": None,
        },
    ]


def gen_func_body(prop, inp, expected):
    s = []
    if prop == "admit_group":
        start, sizes = inp
        s.append(f"int64_t admissions = {start};")
        for size in sizes:
            s.append(f"admit_group(&admissions, {size});")
        s.append(
            f'TEST_ASSERT_EQUAL_INT64_MESSAGE({expected}, admissions, "The admissions tally is different from expected.");'
        )
    elif prop == "admit_group_rush":
        s.append("lobby_admissions = 0;")
        s.append("int64_t per_thread = 0;")
        s.append("for (int i = 0; i < CALLS_PER_THREAD; i++)")
        s.append("    per_thread += (i % 4) + 1;")
        s.append("run_threads(door_worker, NULL, 0);")
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE((int64_t)THREAD_COUNT * per_thread, lobby_admissions, "Some updates were lost. The tally must equal the sum of every group let through.");'
        )
    elif prop == "sell_ticket":
        start, _calls = inp
        returns, final = expected
        s.append(f"int64_t tickets_sold = {start};")
        for number in returns:
            s.append(
                f'TEST_ASSERT_EQUAL_INT64_MESSAGE({number}, sell_ticket(&tickets_sold), "The ticket number is different from expected.");'
            )
        s.append(
            f'TEST_ASSERT_EQUAL_INT64_MESSAGE({final}, tickets_sold, "The count of tickets sold is different from expected.");'
        )
    elif prop == "sell_ticket_rush":
        s.append("const int64_t total = (int64_t)THREAD_COUNT * CALLS_PER_THREAD;")
        s.append("rush_counter = 0;")
        s.append("rush_range = total;")
        s.append("rush_errors = 0;")
        s.append("rush_seen = calloc((size_t)total, sizeof *rush_seen);")
        s.append(
            'TEST_ASSERT_NOT_NULL_MESSAGE(rush_seen, "Failed to allocate the ticket tracking table.");'
        )
        s.append("run_threads(ticket_worker, NULL, 0);")
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(total, rush_counter, "Some updates were lost. The final count must equal the number of sales.");'
        )
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(0, rush_errors, "Every ticket number must be distinct and in range.");'
        )
        s.append("int64_t missing = 0;")
        s.append("for (int64_t i = 0; i < total; i++) {")
        s.append("    if (rush_seen[i] != 1)")
        s.append("        missing++;")
        s.append("}")
        s.append("free(rush_seen);")
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(0, missing, "Every ticket number up to the total must be handed out exactly once.");'
        )
    elif prop == "claim_seat":
        taken, capacity, _calls = inp
        returns, final = expected
        s.append(f"int64_t seats_taken = {taken};")
        for seat in returns:
            s.append(
                f'TEST_ASSERT_EQUAL_INT64_MESSAGE({seat}, claim_seat(&seats_taken, {capacity}), "The seat number is different from expected.");'
            )
        s.append(
            f'TEST_ASSERT_EQUAL_INT64_MESSAGE({final}, seats_taken, "The count of taken seats is different from expected.");'
        )
    elif prop == "claim_seat_rush":
        s.append("seats_taken_shared = 0;")
        s.append("seat_successes = 0;")
        s.append("seat_errors = 0;")
        s.append("for (int i = 0; i < SEAT_CAPACITY; i++)")
        s.append("    seat_seen[i] = 0;")
        s.append("run_threads(seat_worker, NULL, 0);")
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(SEAT_CAPACITY, seats_taken_shared, "The screening must fill exactly to capacity, never beyond.");'
        )
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(SEAT_CAPACITY, seat_successes, "Exactly one claim per seat must succeed.");'
        )
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(0, seat_errors, "Every seat number must be distinct and in range.");'
        )
        s.append("int64_t empty = 0;")
        s.append("for (int i = 0; i < SEAT_CAPACITY; i++) {")
        s.append("    if (seat_seen[i] != 1)")
        s.append("        empty++;")
        s.append("}")
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(0, empty, "Every seat up to capacity must be claimed exactly once.");'
        )
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(0, claim_seat(&seats_taken_shared, SEAT_CAPACITY), "A sold-out screening must refuse further claims.");'
        )
    elif prop == "change_reel":
        mounted, nexts = inp
        returns, final = expected
        s.append(f"int64_t mounted = {mounted};")
        for reel, previous in zip(nexts, returns):
            s.append(
                f'TEST_ASSERT_EQUAL_INT64_MESSAGE({previous}, change_reel(&mounted, {reel}), "The reel handed back is different from expected.");'
            )
        s.append(
            f'TEST_ASSERT_EQUAL_INT64_MESSAGE({final}, mounted, "The mounted reel is different from expected.");'
        )
    elif prop == "change_reel_relay":
        s.append("relay_mounted = 0;")
        s.append("for (int i = 0; i < THREAD_COUNT; i++)")
        s.append("    relay_held[i] = i + 1;")
        s.append("run_threads(reel_worker, relay_held, sizeof relay_held[0]);")
        s.append("int seen[THREAD_COUNT + 1] = {0};")
        s.append(
            'TEST_ASSERT_TRUE_MESSAGE(relay_mounted >= 0 && relay_mounted <= THREAD_COUNT, "The mounted reel must be one of the reels in play.");'
        )
        s.append("seen[relay_mounted]++;")
        s.append("for (int i = 0; i < THREAD_COUNT; i++) {")
        s.append(
            '    TEST_ASSERT_TRUE_MESSAGE(relay_held[i] >= 0 && relay_held[i] <= THREAD_COUNT, "Every reel held must be one of the reels in play.");'
        )
        s.append("    seen[relay_held[i]]++;")
        s.append("}")
        s.append("for (int i = 0; i <= THREAD_COUNT; i++) {")
        s.append(
            '    TEST_ASSERT_EQUAL_INT_MESSAGE(1, seen[i], "One reel was lost or duplicated. Every reel must come back exactly once.");'
        )
        s.append("}")
    elif prop == "visit_booth_runs":
        s.append("booth_word = 0;")
        s.append("logbook_entries = 41;")
        s.append("visit_booth(&booth_word, logbook_task);")
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(42, logbook_entries, "The task must be run exactly once per visit.");'
        )
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");'
        )
    elif prop == "visit_booth_holds":
        s.append("booth_word = 0;")
        s.append("booth_seen_during_task = -1;")
        s.append("visit_booth(&booth_word, observing_task);")
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(1, booth_seen_during_task, "The booth must be occupied while the task runs.");'
        )
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");'
        )
    elif prop == "visit_booth_shift":
        s.append("booth_word = 0;")
        s.append("logbook_entries = 0;")
        for k in range(4):
            s.append("visit_booth(&booth_word, logbook_task);")
            s.append(
                f'TEST_ASSERT_EQUAL_INT64_MESSAGE({k + 1}, logbook_entries, "The count of logbook entries is different from expected.");'
            )
            s.append(
                'TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");'
            )
    elif prop == "visit_booth_rush":
        s.append("booth_word = 0;")
        s.append("logbook_entries = 0;")
        s.append("visit_booth(&booth_word, logbook_task);")
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be reopened before the function returns.");'
        )
        s.append("logbook_entries = 0;")
        s.append("run_threads(booth_worker, NULL, 0);")
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE((int64_t)THREAD_COUNT * CALLS_PER_THREAD, logbook_entries, "The booth admitted two visitors at once. The count of entries must be exact.");'
        )
        s.append(
            'TEST_ASSERT_EQUAL_INT64_MESSAGE(0, booth_word, "The booth must be free once everyone has left.");'
        )
    return "\n".join(s)
