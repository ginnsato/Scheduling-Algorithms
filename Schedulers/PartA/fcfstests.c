#include <stdlib.h>
#include "ctest.h"
#include "fcfs.h"

// Note: the name in the first parameter slot must match all tests in that group
CTEST_DATA(firstcomefirstserved) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(firstcomefirstserved) {
    int execution[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    first_come_first_served(data->task, data->size);
}

CTEST2(firstcomefirstserved, test_process) {
    for (int i = 0; i < data->size; i++) {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}


CTEST2(firstcomefirstserved, test_process1) {
    // Check initalization successful
    ASSERT_EQUAL(data->task[0].execution_time, 1);
    ASSERT_EQUAL(data->task[1].execution_time, 2);
    ASSERT_EQUAL(data->task[2].execution_time, 3);
    // Check waiting times
    ASSERT_EQUAL(data->task[0].waiting_time, 0);
    ASSERT_EQUAL(data->task[1].waiting_time, 1);
    ASSERT_EQUAL(data->task[2].waiting_time, 3);
    // Check turnaround times
    ASSERT_EQUAL(data->task[0].turnaround_time, 1);
    ASSERT_EQUAL(data->task[1].turnaround_time, 3);
    ASSERT_EQUAL(data->task[2].turnaround_time, 6);
}


CTEST2(firstcomefirstserved, test_process2) {
    // check averages
    ASSERT_DBL_NEAR(calculate_average_wait_time(data->task, data->size), 4.0/3.0);
    ASSERT_DBL_NEAR(calculate_average_turn_around_time(data->task, data->size), 10.0/3.0);
}


CTEST_DATA(firstcomefirstserved1) {
    struct task_t task[6];
    int size;
};

CTEST_SETUP(firstcomefirstserved1) {
    int execution[] = {1, 9, 8, 4, 2, 4};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    first_come_first_served(data->task, data->size);
}

CTEST2(firstcomefirstserved1, test_process) {
    ASSERT_EQUAL(data->task[0].waiting_time, 0);
    ASSERT_EQUAL(data->task[0].turnaround_time, 1);
    ASSERT_EQUAL(data->task[1].turnaround_time, 10);
    ASSERT_EQUAL(data->task[2].turnaround_time, 18);
    ASSERT_EQUAL(data->task[3].turnaround_time, 22);
    ASSERT_EQUAL(data->task[4].turnaround_time, 24);
    ASSERT_EQUAL(data->task[5].turnaround_time, 28);
}

CTEST2(firstcomefirstserved1, test_process1) {
    ASSERT_EQUAL(data->task[0].waiting_time, 0);
    ASSERT_EQUAL(data->task[1].waiting_time, 1);
    ASSERT_EQUAL(data->task[2].waiting_time, 10);
    ASSERT_EQUAL(data->task[3].waiting_time, 18);
    ASSERT_EQUAL(data->task[4].waiting_time, 22);
    ASSERT_EQUAL(data->task[5].waiting_time, 24);
}

CTEST_DATA(firstcomefirstserved2) {
    struct task_t task[1];
    int size;
};

CTEST_SETUP(firstcomefirstserved2) {
    int execution[] = {5};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, data->size);
    first_come_first_served(data->task, data->size);
}

CTEST2(firstcomefirstserved2, test_process) {
    ASSERT_EQUAL(data->task[0].turnaround_time, 5);
    ASSERT_EQUAL(data->task[0].waiting_time, 0);
}


// TODO add additional tests to help debug
