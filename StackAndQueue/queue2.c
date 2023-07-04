/*  queue2.c file
    Aaron Heishman
    6/30/2023
*/

#include "stack_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* "private" function declaration */

/* Checks if the given pointer is null */
static void check_null(void *queue_ptr);

/*  Checks if the array needs to be doubled, and then doubles the array if so.
    @param - **q2_ptr - Stack pointer that points at the stack being modified
*/
static void double_size(Queue2 *q2_ptr);

/*  Checks if the array needs halved, halves if so
    @param - **q2_ptr - Stack pointer that points at the stack being modified
*/
static void halve_size(Queue2 *q2_ptr);

/*  copies the entries from the old entries into the new entries 
    @param new_entries - the new array that will hold all the old entries without the junk
    @param old_entries - the old array with the junk values
    @param start - the current front of the array
    @param stop - either the length of array + 1 for doubling, or new_size for halving
    @param old_size, the old size of the array
*/
static void copy(int *new_entries, int *old_entries, int start, int stop, int old_size);

/* "private" function definition */


static void check_null(void *ptr) {
        if (ptr == NULL) {
            printf("Could not allocate memory for queue. Quitting program..");
            exit(1);
        }
}

static void copy(int *new_entries, int *old_entries, int start, int stop, int old_size) {
    int i, y = start;
    for (i = 0; i < stop; i++) {
        /* Same concept as enqueue/dequeue. 
            y % old_size will give all the values on the left and right of where the starting
            position is based on if y is greater than or less than the old_size
        */
        int j = (y % old_size); 
        new_entries[i] = old_entries[j];
        y++;
    }
}

static void double_size(Queue2 *q2_ptr) {
    /* create the new array */
    int new_size = (q2_ptr->arrSize * 2);
    int *new_entries = (int*)malloc(new_size * sizeof(int));
    /* copy the old entries to the new entries */
    copy(new_entries, q2_ptr->entries, q2_ptr->curFront, q2_ptr->length + 1, q2_ptr->arrSize);
    /* update the size, entries and curFront (because it's at the beginning now)*/
    q2_ptr->arrSize = new_size;
    /* free the old entries pointer */
    free(q2_ptr->entries);
    q2_ptr->entries = NULL;
    /* update old entries to point at new entries*/
    q2_ptr->entries = new_entries;
    q2_ptr->curFront = 0;
}

static void halve_size(Queue2 *q2_ptr) {
    /* create the new array */
    int new_size = (q2_ptr->arrSize) >> 2;
    int *new_entries = (int*)malloc(new_size * sizeof(int));
    /* copy the old entries to the new entries */
    copy(new_entries, q2_ptr->entries, q2_ptr->curFront, new_size, q2_ptr->arrSize);
    /* update the size, entries and curFront (because it's at the beginning now)*/
    q2_ptr->arrSize = new_size;
    /* free the old entries pointer */
    free(q2_ptr->entries);
    q2_ptr->entries = NULL;
    /* update old entries to point at new entries*/
    q2_ptr->entries = new_entries;
    q2_ptr->curFront = 0;
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
    /* initialize variables */
    Queue2 *q2_ptr = (Queue2*)q->vars;
    int curr_front = q2_ptr->curFront, curr_length = q2_ptr->length;
    int curr_size = q2_ptr->arrSize, index;
     /*  Explanation:
        If the the sum of current front + current length is <  size
        then sum % mod > curr_front [new entry goes to the right]
        but if the sum of current front + current length is >= size
        and length != size (or length % size != 1)
        [new entry goes on the left]
    */
    index = (curr_front + curr_length) % curr_size;
    q2_ptr->entries[index] = x;
    /* check if the array should be double before continueing */
    if (curr_length + 1 == curr_size) {
        double_size(q2_ptr);
    }
    q2_ptr->length++;
}


int dequeueQueue2(Queue* q) {
    Queue2 *q2_ptr = (Queue2*)q->vars;
    assert(q2_ptr->length > 0); /* in case length is 0*/
    
    /* remove the entry from the front, decrement the length and increment the current front position */
    int r = q2_ptr->entries[q2_ptr->curFront];
    q2_ptr->length--;
    q2_ptr->curFront++;
    
    /* check to make sure that the length is not 0, or if the current front and arr siz are zero*/
    if (q2_ptr->length == 0 || q2_ptr->curFront == q2_ptr->arrSize) {
        q2_ptr->curFront = 0;
    }

    /* check if the array needs halved */
    if (MIN_SIZE <= q2_ptr->length && q2_ptr->length == (q2_ptr->arrSize) >> 2) {
        halve_size(q2_ptr);
    }

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