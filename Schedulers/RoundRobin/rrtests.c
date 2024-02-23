#include <stdlib.h>
#include "ctest.h"
#include "rr.h"

CTEST_DATA(roundrobin) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(roundrobin) {
    int execution[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);
    int quantum = 2;

    init(data->task, execution, data->size);
    round_robin(data->task, quantum, data->size);
}

CTEST2(roundrobin, test_process) {
    for (int i = 0; i < data->size; i++) {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}

CTEST2(roundrobin, test_process1) {
    // Check initalization successful
    ASSERT_EQUAL(data->task[0].execution_time, 1);
    ASSERT_EQUAL(data->task[1].execution_time, 2);
    ASSERT_EQUAL(data->task[2].execution_time, 3);
}

CTEST2(roundrobin, test_process2) {
    // Check initalization successful
    ASSERT_EQUAL(data->task[0].turnaround_time, 1);
    ASSERT_EQUAL(data->task[1].turnaround_time, 3);
    ASSERT_EQUAL(data->task[2].turnaround_time, 6);
}

CTEST_DATA(roundrobin1) {
    struct task_t task[4];
    int size;
};

CTEST_SETUP(roundrobin1) {
    int execution[] = {4, 2, 3, 5};
    data->size = sizeof(execution) / sizeof(execution[0]);
    int quantum = 2;

    init(data->task, execution, data->size);
    round_robin(data->task, quantum, data->size);
}

CTEST2(roundrobin1, test_process) {
    // Check waiting times
    ASSERT_EQUAL(data->task[0].waiting_time, 6);
    ASSERT_EQUAL(data->task[1].waiting_time, 2);
    ASSERT_EQUAL(data->task[2].waiting_time, 8);
    ASSERT_EQUAL(data->task[3].waiting_time, 9);
}

CTEST2(roundrobin1, test_process1) {
    // Check turnaround times
    ASSERT_EQUAL(data->task[0].turnaround_time, 10);
    ASSERT_EQUAL(data->task[1].turnaround_time, 4);
    ASSERT_EQUAL(data->task[2].turnaround_time, 11);
    ASSERT_EQUAL(data->task[3].turnaround_time, 14);
}


CTEST_DATA(roundrobin2) {
    struct task_t task[4];
    int size;
};

CTEST_SETUP(roundrobin2) {
    int execution[] = {0, 5, 10, 1};
    data->size = sizeof(execution) / sizeof(execution[0]);
    int quantum = 2;

    init(data->task, execution, data->size);
    round_robin(data->task, quantum, data->size);
}

CTEST2(roundrobin2, test_process) {
    // Check waiting times
    ASSERT_EQUAL(data->task[0].waiting_time, 0);
    ASSERT_EQUAL(data->task[1].waiting_time, 5);
    ASSERT_EQUAL(data->task[2].waiting_time, 6);
    ASSERT_EQUAL(data->task[3].waiting_time, 4);

    // Check turnaround times
    ASSERT_EQUAL(data->task[0].turnaround_time, 0);
    ASSERT_EQUAL(data->task[1].turnaround_time, 10);
    ASSERT_EQUAL(data->task[2].turnaround_time, 16);
    ASSERT_EQUAL(data->task[3].turnaround_time, 5);

    // Check averages
    ASSERT_DBL_NEAR(calculate_average_wait_time(data->task, data->size), 15.0/4.0);
    ASSERT_DBL_NEAR(calculate_average_turn_around_time(data->task, data->size), 31.0/4.0);
}