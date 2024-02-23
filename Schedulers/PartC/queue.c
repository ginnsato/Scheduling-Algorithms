#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct node_t* create_queue(struct task_t* task, int size) {
    // Define head node
    struct node_t * head = NULL;

    // Push all tasks in task array
    for(int i=0; i < size; i++)
        push(&head, &task[i]);

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
    // create new node
    struct node_t* node = create_new_node(task);

    // Handles edge case where queue is empty
    if(is_empty(head)){
        (*head) = node;
        return;
    }

    struct node_t * temp = (*head);
    
    // loop until temp points to the last node in queue
    while(temp->next != NULL){
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
