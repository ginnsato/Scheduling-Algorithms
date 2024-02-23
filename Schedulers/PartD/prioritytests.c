#include <stdlib.h>
#include "ctest.h"
#include "priority.h"

CTEST_DATA(priority) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(priority) {
    int execution[] = {1, 2, 3};
    int priority[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, priority, data->size);
    priority_schedule(data->task, data->size);
}

CTEST2(priority, test_process) {
    for (int i = 0; i < data->size; i++) {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}

CTEST2(priority, test_process1) {
    ASSERT_EQUAL(data->task[0].turnaround_time, 2);
    ASSERT_EQUAL(data->task[1].turnaround_time, 6);
    ASSERT_EQUAL(data->task[2].turnaround_time, 5);
}

CTEST_DATA(priority1) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(priority1) {
    int execution[] = {1, 2, 3};
    int priority[] = {0, 0, 0};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, priority, data->size);
    priority_schedule(data->task, data->size);
}

CTEST2(priority1, test_process1) {
    ASSERT_EQUAL(data->task[0].turnaround_time, 1);
    ASSERT_EQUAL(data->task[1].turnaround_time, 3);
    ASSERT_EQUAL(data->task[2].turnaround_time, 6);
}

CTEST_DATA(priority2) {
    struct task_t task[5];
    int size;
};

CTEST_SETUP(priority2) {
    int execution[] = {0, 2, 4, 5, 3};
    int priority[] = {1, 2, 3, 4, 5};
    data->size = sizeof(execution) / sizeof(execution[0]);
    init(data->task, execution, priority, data->size);
    priority_schedule(data->task, data->size);
}

CTEST2(priority2, test_process1) {
    ASSERT_EQUAL(data->task[0].turnaround_time, 0);
    ASSERT_EQUAL(data->task[1].turnaround_time, 14);
    ASSERT_EQUAL(data->task[2].turnaround_time, 13);
    ASSERT_EQUAL(data->task[3].turnaround_time, 10);
    ASSERT_EQUAL(data->task[4].turnaround_time, 4);
}

CTEST2(priority2, test_process2) {
    ASSERT_EQUAL(data->task[0].waiting_time, 0);
    ASSERT_EQUAL(data->task[1].waiting_time, 12);
    ASSERT_EQUAL(data->task[2].waiting_time, 9);
    ASSERT_EQUAL(data->task[3].waiting_time, 5);
    ASSERT_EQUAL(data->task[4].waiting_time, 1);
}


CTEST2(priority2, test_process3) {
    // Check averages
    ASSERT_DBL_NEAR(calculate_average_wait_time(data->task, data->size), 27.0/5.0);
    ASSERT_DBL_NEAR(calculate_average_turn_around_time(data->task, data->size), 41.0/5.0);
}
    
