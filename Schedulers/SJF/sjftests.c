#include <stdlib.h>
#include "ctest.h"
#include "sjf.h"
#include <time.h>

CTEST_DATA(shortestjobfirst) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(shortestjobfirst) {
    int execution[] = {1, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);

    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}

CTEST2(shortestjobfirst, test_process) {
    for (int i = 0; i < data->size; i++) {
        ASSERT_EQUAL(i, (int)data->task[i].process_id);
    }
}

CTEST2(shortestjobfirst, test_process1) {
    ASSERT_EQUAL(data->task[0].turnaround_time, 1);
    ASSERT_EQUAL(data->task[1].turnaround_time, 3);
    ASSERT_EQUAL(data->task[2].turnaround_time, 6);
}


CTEST_DATA(shortestjobfirst1) {
    struct task_t task[3];
    int size;
};

CTEST_SETUP(shortestjobfirst1) {
    int execution[] = {3, 2, 1};
    data->size = sizeof(execution) / sizeof(execution[0]);

    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}

CTEST2(shortestjobfirst1, test_process) {
    ASSERT_EQUAL(data->task[0].turnaround_time, 1);
    ASSERT_EQUAL(data->task[1].turnaround_time, 3);
    ASSERT_EQUAL(data->task[2].turnaround_time, 6);
}


CTEST_DATA(shortestjobfirst2) {
    struct task_t task[6];
    int size;
};

CTEST_SETUP(shortestjobfirst2) {
    int execution[] = {3, 2, 7, 1, 0, 10};
    data->size = sizeof(execution) / sizeof(execution[0]);

    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}

CTEST2(shortestjobfirst2, test_process) {
    ASSERT_EQUAL(data->task[0].turnaround_time, 0);
    ASSERT_EQUAL(data->task[1].turnaround_time, 1);
    ASSERT_EQUAL(data->task[2].turnaround_time, 3);
    ASSERT_EQUAL(data->task[3].turnaround_time, 6);
    ASSERT_EQUAL(data->task[4].turnaround_time, 13);
    ASSERT_EQUAL(data->task[5].turnaround_time, 23);
}

CTEST2(shortestjobfirst2, test_process1) {
    ASSERT_EQUAL(data->task[0].waiting_time, 0);
    ASSERT_EQUAL(data->task[1].waiting_time, 0);
    ASSERT_EQUAL(data->task[2].waiting_time, 1);
    ASSERT_EQUAL(data->task[3].waiting_time, 3);
    ASSERT_EQUAL(data->task[4].waiting_time, 6);
    ASSERT_EQUAL(data->task[5].waiting_time, 13);
}

CTEST_DATA(shortestjobfirst3) {
    struct task_t task[4];
    int size;
};

CTEST_SETUP(shortestjobfirst3) {
    int execution[] = {2, 3, 2, 3};
    data->size = sizeof(execution) / sizeof(execution[0]);

    init(data->task, execution, data->size);
    shortest_job_first(data->task, data->size);
}

CTEST2(shortestjobfirst3, test_process) {
    ASSERT_EQUAL(data->task[0].turnaround_time, 2);
    ASSERT_EQUAL(data->task[1].turnaround_time, 4);
    ASSERT_EQUAL(data->task[2].turnaround_time, 7);
    ASSERT_EQUAL(data->task[3].turnaround_time, 10);

}