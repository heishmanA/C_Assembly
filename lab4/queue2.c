/*  queue2.c file
    Aaron Heishman
    Systems I - Lab 4
    6/30/2023
*/

#include "lab4.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* "private" function declaration */

/* Checks if the given pointer is null */
static void check_null(void *queue_ptr);

/*  Checks if the array needs to be doubled, and then doubles the array if so 
    @param - **q2_ptr - Stack pointer that points at the stack being modified
*/
static void double_size(Queue2 *q2_ptr);

/*  Checks if the array needs halved, halves if so
    @param - **q2_ptr - Stack pointer that points at the stack being modified
*/
static void halve_size(Queue2 *q2_ptr);
/* "private" function definition */
static void check_null(void *ptr) {
        if (ptr == NULL) {
            printf("Could not allocate memory for queue. Quitting program..");
            exit(1);
        }
}

static void double_size(Queue2 *q2_ptr) {
    /* set up variables */
    int arr_length = q2_ptr->length;
    int arr_size = q2_ptr->arrSize;
    int *new_arr; /*if needed*/
    /* may just do this in the other func*/
    if (arr_length == arr_size) {
        int i, j = 0;
        int new_size = arr_size *= 2; /* double size */
        new_arr = (int*)malloc(new_size * sizeof(int));
        check_null(new_arr);
        for (i = q2_ptr->curFront; i < arr_length; i++, j++) {
            /*  starting at the current front, transfer all 
                the entries[currFront, arr_length] to new_arr[0, arr_length] */
            new_arr[j] = q2_ptr->entries[i];
        }
        /* arr_length shouldn't need modified, updating new position of front to pos 0*/
        q2_ptr->curFront = 0;
        q2_ptr->arrSize = new_size;
        /* Free old entries and update to the new entries made */
        free(q2_ptr->entries);
        q2_ptr->entries = NULL;
        q2_ptr->entries = new_arr;
    }
    
}

static void halve_size(Queue2 *q2_ptr) {
    /* set up variables */
    int arr_length = q2_ptr->length;
    int arr_size_by_four = (q2_ptr->arrSize) >> 2; /* arrsize/4 */
    int *new_arr; /*if needed*/
    /* check if the array's length is 1/4th that of the array's size */
    if (MIN_SIZE <= arr_length && arr_length == arr_size_by_four) {
        int i, j = q2_ptr->curFront;
        int new_size = (q2_ptr->arrSize) >> 1; /* arrsize / 2 */
        new_arr = (int*)malloc(new_size * sizeof(int));
        check_null(new_arr);
         /*  starting at the current front, transfer all 
            the entries[currFront, arr_length] to new_arr[0, arr_length] */
        for (i = 0; i < q2_ptr->length; i++, j++) {
            new_arr[i] = q2_ptr->entries[j];
        }
        /* arr_length shouldn't need modified, updating new position of front to pos 0*/
        q2_ptr->arrSize = new_size;
        q2_ptr->curFront = 0;
        /* Free old entries and update to the new entries made */
        free(q2_ptr->entries);
        q2_ptr->entries = NULL;
        q2_ptr->entries = new_arr;
    }
    
}

/* "public" function definitions */

Queue* newQueue2(){
    /* set up the queue "object" */
    Queue *queue_obj = (Queue*)malloc(sizeof(Queue));
    check_null((void*)queue_obj);
    /* set up the function pointers */
    queue_obj->enqueue = &enqueueQueue2;
    queue_obj->dequeue = &dequeueQueue2;
    queue_obj->length = &lengthQueue2;
    queue_obj->del = &delQueue2;
    /* array for entries */
    int *entries = (int*)malloc(MIN_SIZE * sizeof(int));
    check_null(entries);
    /* set up the queueu1 "object" */
    Queue2 *queue2_obj = (Queue2*)malloc(sizeof(Queue2));
    check_null((void*)queue2_obj);
    queue2_obj->length = 0;
    queue2_obj->curFront = 0;
    queue2_obj->arrSize = MIN_SIZE; /* 4 */
    queue2_obj->entries = entries;
    /* Point queue's vars at the new queue1 */
    queue_obj->vars = (void*)queue2_obj;
    return queue_obj;
}


void enqueueQueue2(Queue* q, int x) {
    Queue2 *q2_ptr = (Queue2*)q->vars;
    if (q2_ptr->length == 0) {
        /* place entry at the front */
        q2_ptr->entries[0] = x; /* currFront already zero, no need to change */
    } else {
        /* place entry at the end */
        q2_ptr->entries[q2_ptr->length] = x;
    }
    q2_ptr->length++;
    double_size(q2_ptr);
}


int dequeueQueue2(Queue* q) {
    Queue2 *q2_ptr = (Queue2*)q->vars;
    assert(q2_ptr->length > 0);
    /* get data from current front entry */
    int r = q2_ptr->entries[q2_ptr->curFront];
    /* curFront starts at 0 and increments as length goes down */
    q2_ptr->curFront++; /* next entry becomes the current front */  
    q2_ptr->length--;
    /* check if the array needs halved */
    halve_size(q2_ptr);
    return r;
}

int lengthQueue2(Queue* q) {
    Queue2 *q2_ptr = (Queue2*)q->vars;
    return q2_ptr->length;
}

void delQueue2(Queue* q) {
    Queue2 *q2_ptr = (Queue2*)q->vars;
    /* Free and null out each pointer */
    free(q2_ptr->entries);
    q2_ptr->entries = NULL;
    free(q->vars);
    q->vars = NULL;
    free(q);
    q = NULL;
}