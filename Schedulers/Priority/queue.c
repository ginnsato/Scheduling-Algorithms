#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct node_t* create_queue(struct task_t* task, int size) {
    // Define head node
    struct node_t * head = NULL;

    // Push all tasks in task array
    for(int i=0; i < size; i++){
        if(task[i].left_to_execute != 0){
            push(&head, &task[i]);
        }
    }
    return head;
}

struct node_t* create_new_node(struct task_t* task) {
    // Dynamically allocate memory for a new node
    struct node_t * node = (struct node_t *)malloc(sizeof(struct node_t));
    
    // ensure that malloc was successful
    if(node != NULL){
        // assign task
        node->task = task;
        node->next = NULL;
    }
    
    return node;
}

struct task_t* peek(struct node_t** head) {
    // peek the task at head of queue
    if(!is_empty(head))
        return (*head)->task;
    return NULL;
}

void pop(struct node_t** head) {
    // Ensure queue has something to pop
    if(!is_empty(head)){

        // set temp to the next node in queue
        struct node_t * temp = (*head)->next;

        // free the head node
        free(*(head));

        // set target of head to the next node 
        *head = temp;
    }
}

void push(struct node_t** head, struct task_t* task) {
    // Creating a sorted queue based on priority
    // Higher priority towards head

    // create new node
    struct node_t* node = create_new_node(task);

    // Handles edge case where queue is empty
    if(is_empty(head)){
        (*head) = node;
        return;
    }

    struct node_t * temp = (*head);

    if(node->task->priority > temp->task->priority){
        node->next = temp;
        *head = node;
        return;
    }

    while(temp->next != NULL){
        if(node->task->priority > temp->next->task->priority){
            node->next = temp->next;
            temp->next = node;
            return;
        }
        temp = temp->next;
    }

    temp->next = node;
}



int is_empty(struct node_t** head) {
    if(head != NULL){
        if((*head) != NULL){
            // means that the head points to a node, so its not empty
            return 0;
        }
    }
    return 1;
}

void empty_queue(struct node_t** head) {
    while(!is_empty(head)){
        pop(head);
    }
}

void update_priority(struct node_t** head, int time) {
    if(!is_empty(head)){
        struct node_t * temp = (*head);
        // Iterate through all tasks
        while(temp != NULL){
            // Change priority accordingly
            if(temp->task->execution_time == time){
                temp->task->priority *= 4;
            }
            if(temp->task->left_to_execute == time){
                temp->task->priority *= 2;
            }
            temp = temp->next;
        }
    }
}

/*
// HELPFUL PRINT FUNCTION USED IN DEBUGGING
void print_queue(struct node_t** head){
    if(!is_empty(head)){
        struct node_t * temp = (*head);
        // Iterate through all tasks
        while(temp != NULL){
            printf("Node: %d ->", temp->task->execution_time);
            temp = temp->next;
        }
        printf("\n");
    }
}
*/ 