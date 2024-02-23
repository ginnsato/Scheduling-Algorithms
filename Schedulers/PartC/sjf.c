#include "sjf.h"
#include "queue.h"
#include <stdio.h>

void init(struct task_t *task, int *execution, int size) {
    // init the task array with execution times
    for(int i=0; i < size; i++){
        task[i].execution_time = execution[i];
        task[i].process_id = i;
    }
}

void shortest_job_first(struct task_t *task, int size) {
    // Note that I use in-place sorting here,
    // thus the indexes change for tasks in my test cases

    // Run sorting algorithm based on execution time
    // Using Insertion sort here (from Geeksforgeeks.org)
    int key, j;
    for (int i = 1; i < size; i++) {
        key = task[i].execution_time;
        j = i - 1;

        while (j >= 0 && task[j].execution_time > key) {
            task[j + 1].execution_time = task[j].execution_time;
            j = j - 1;
        }
        task[j + 1].execution_time = key;
    }

    // Peform FCFS after ordering the tasks
    int time = 0;

    // Create queue with ordered tasks 
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
    float total = 0;
    for(int i=0; i < size; i++){
        total += task[i].waiting_time;
    }
    return (float) total / size;
}

float calculate_average_turn_around_time(struct task_t *task, int size) {
    float total = 0;
    for(int i=0; i < size; i++){
        total += task[i].turnaround_time;
    }
    return (float) total / size;
}