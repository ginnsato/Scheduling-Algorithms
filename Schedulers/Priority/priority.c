#include "priority.h"
#include "queue.h"
#include <stdio.h>

void init(struct task_t *task, int *execution, int *priority, int size) {
    // init the task array with execution times
    for(int i=0; i < size; i++){
        task[i].execution_time = execution[i];
        task[i].priority = priority[i];
        task[i].left_to_execute = execution[i];
        task[i].process_id = i;
    }
}

void priority_schedule(struct task_t *task, int size) {
    // Updated by create queue so that it pushes things into queue based on priority.
    int time = 0;

    struct node_t * head = create_queue(task, size);
    struct task_t * curr_task;

    while(!is_empty(&head)){

        // get task at top of queue
        curr_task = peek(&head);

        // check if we are going to finish this task in less than quantum time
        if(curr_task->left_to_execute == 1){
            curr_task->waiting_time = time - (curr_task->execution_time - curr_task->left_to_execute);
            curr_task->turnaround_time = curr_task->execution_time + curr_task->waiting_time;
            time += 1;
            curr_task->left_to_execute = 0;
        }
        else{
            // update time left to execute this
            curr_task->left_to_execute -= 1;
            time += 1;
            
        }
        // Update priorities
        update_priority(&head, time);

        // Empty old queue, and create a new queue with updated priorities
        empty_queue(&head);
        head = create_queue(task, size);
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