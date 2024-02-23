#include "fcfs.h"
#include "queue.h"
#include <stdio.h>

void init(struct task_t *task, int *execution, int size) {
    // init the task array with execution times
    for(int i=0; i < size; i++){
        task[i].execution_time = execution[i];
        task[i].process_id = i;
    }
}

void first_come_first_served(struct task_t *task, int size) {
    int time = 0;

    struct node_t * head = create_queue(task, size);
    struct task_t * curr_task;
    while(!is_empty(&head)){
        curr_task = peek(&head);
        pop(&head);

        curr_task->waiting_time = time;
        curr_task->turnaround_time = curr_task->execution_time + time;
        time += curr_task->execution_time;
    }

}

float calculate_average_wait_time(struct task_t *task, int size) {
    float total_time = 0;

    for(int i=0; i < size; i++){
        total_time += task[i].waiting_time;
    }
    return (float) total_time / size;
}

float calculate_average_turn_around_time(struct task_t *task, int size) {
    float total_time = 0;

    for(int i=0; i < size; i++){
        total_time += task[i].turnaround_time;
    }
    return (float) total_time / size;
}