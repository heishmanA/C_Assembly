/*  queue1.c file
    Aaron Heishman
    Systems I - Lab 4
    6/30/2023
*/

#include "lab4.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* "private" function declaration */
static void check_null(void *queue_ptr);
/* "private" function definition */
static void check_null(void *queue_ptr) {
        if (queue_ptr == NULL) {
            printf("Could not allocate memory for queue. Quitting program..");
            exit(1);
        }
}

/* "public" function definitions */

Queue* newQueue1(){
    /* set up the queue "object" */
    Queue *queue_obj = (Queue*)malloc(sizeof(Queue));
    check_null((void*)queue_obj);
    /* set up the function pointers */
    queue_obj->enqueue = &enqueueQueue1;
    queue_obj->dequeue = &dequeueQueue1;
    queue_obj->length = &lengthQueue1;
    queue_obj->del = &delQueue1;
    /* set up the queueu1 "object" */
    Queue1 *queue1_obj = (Queue1*)malloc(sizeof(Queue1));
    check_null((void*)queue1_obj);
    queue1_obj->length = 0;
    queue1_obj->firstNode = NULL;
    queue1_obj->lastNode = NULL;
    /* Point queue's vars at the new queue1 */
    queue_obj->vars = (void*)queue1_obj;
    return queue_obj;
}

void enqueueQueue1(Queue* q, int x) {
    Queue1 *q1_ptr = (Queue1*)q->vars;
    LLNode *p = malloc(sizeof(LLNode));
    p->data = x;
    check_null(p);
    /*  Node set up like a circle.
        firstNode points to the next, the last node points
        to the first node. This is set up for easy access
        of the first node in the queue being removed.
        First in, First out
    */
    if (q1_ptr->length == 0) {
        q1_ptr->firstNode = p;
        q1_ptr->lastNode = q1_ptr->firstNode;
        p->next = q1_ptr->firstNode;
    } else {
        q1_ptr->lastNode->next = p;
        q1_ptr->lastNode = p;
        p->next = q1_ptr->firstNode;
    }
    q1_ptr->length++;
}


int dequeueQueue1(Queue* q) {
    Queue1 *q1_ptr = (Queue1*)q->vars;
    /*  Just in case dequeue is called when there's nothing in it
        or the the first node is null*/
    assert(q1_ptr->length > 0);
    assert(q1_ptr->firstNode != NULL);
    int r = q1_ptr->firstNode->data;
    /*  Original setup was like a circle
        When there's one node in the list, free that node
        but when there's more than one node in the list
        Update the first node to the next node, then use lastNode
        to free the original first node
    */
    if (q1_ptr->length == 1) {
        free(q1_ptr->firstNode);
        q1_ptr->firstNode = NULL;
        q1_ptr->lastNode = NULL;
    } else {
        q1_ptr->firstNode = q1_ptr->firstNode->next;
        free(q1_ptr->lastNode->next);
        q1_ptr->lastNode->next = q1_ptr->firstNode;
    }
    q1_ptr->length--;
    return r;
}

int lengthQueue1(Queue* q) {
    Queue1 *q_ptr = (Queue1*)q->vars;
    return q_ptr->length;
}

void delQueue1(Queue* q) {
    Queue1 *q1_ptr = (Queue1*)q->vars;
    if (q1_ptr->length > 0) {
        /* set up for recursion */
        q1_ptr->firstNode = q1_ptr->firstNode->next;
        free(q1_ptr->lastNode->next);
        q1_ptr->lastNode->next = q1_ptr->firstNode;
        q1_ptr->length--;
        delQueue1(q);
    } else {
        /* free the memory of vars and q*/
        free(q->vars);
        q->vars = NULL;
        free(q);
        q = NULL;
    }
}