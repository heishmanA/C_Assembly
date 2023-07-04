/* queue_main.c file
    Aaron Heishman

    Original File Supplied by Braeden Jeske
    Modifications by Aaron Heishman 
    - This one is specifically for testing queue, it's the same as stack's except modified to work for queue
    - Removed the ENTRIES macro to allow for the user to input command line args
    - Added some printing prompts to show what's going on 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack_queue.h"

void QueueTest(int type, int entries){
    Queue* new_q = type == 1 ? newQueue1() : newQueue2();
    /* setting up clock */
    clock_t start, end;
    double cpu_time_used;
    int i, removed, errors;
    errors = 0;
    start = clock();
    /* added this to make things easier for testing */
    printf("Testing Queue%i with %i entries\n", type, entries); 
    printf("\n");
    /* expand queue */
    for(i = 0; i < entries; i++){
        new_q->enqueue(new_q, i);
    }
    /* shrink queue */
    for(i = 0; i < entries; i++){
        removed = new_q->dequeue(new_q);
        if(removed != i){
            printf("Expected %i, removed %i\n", i, removed);
            errors++;
        }
    }
    new_q->del(new_q);
    printf("Ended with %i errors\n", errors);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Clock Time reads: %f seconds\n", cpu_time_used);
}

void QueueTest2(int type) {
    Queue* new_q = type == 1 ? newQueue1() : newQueue2();
    /* setting up clock */
    clock_t start, end;
    double cpu_time_used;
    /* testing vals*/
    int i, removed, errors, length, half;
    errors = 0;
    /* start clock */
    start = clock();
    printf("Start QueueTest2 with Queue%i\n", type);
    /*  this setup is to make sure that even if
        dequeue happens while enqueing, then the array
        updates accordingly, by dequeuing the first,
        and enqueing the last
    */
    printf("------------Enqueue with dequeue-----------------\n");
    for (i = 0; i < 17; i++) {
        new_q->enqueue(new_q, i);
        if (i % 2 == 0) {
            /* dequeing at even intervals to make sure table doubling works*/
            printf("[%i] ", new_q->dequeue(new_q));
        }
    }
    /*  This setup is to verify that even if a value
        is enqueued after dequeueing then that value 
        would still be at the end*/
    length = new_q->length(new_q);
    half = length / 2;
    printf("\n-----------Dequeue with Enqueue------------------\n");
    for (i = 0; i < length; i++) {
        removed = new_q->dequeue(new_q);
        printf("[%i] ", removed);
        /* enqueuing values at every even interval until half the original array length is reached */
        if (i < half) {
            new_q->enqueue(new_q, removed);
            length++;
        }
    }
    printf("\n\n");
    new_q->del(new_q);
    /* display clock time*/
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Clock Time reads: %f seconds\n", cpu_time_used);
}

void QueueTest3(int type) {
    Queue* new_q = type == 1 ? newQueue1() : newQueue2();
    /* setting up clock */
    clock_t start, end;
    double cpu_time_used;
    /* testing vals*/
    int i, removed, errors, length, half;
    errors = 0;
    printf("Start QueueTest3 with Queue%i\n", type);
    /* start clock */
    start = clock();
    for (i = 0; i < 100; i++) {
        new_q->enqueue(new_q, i);
    }
    new_q->del(new_q);
    /* display clock time*/
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Clock Time reads: %f seconds\n", cpu_time_used);
}

int main(int argc, char *argv[]){
    int i, x;
    Stack *s;
    /* Testing queue based on whether arguments are given or not */
    printf("-------------------------------------------------\n");
    if (argc > 1) {
        /*call queue tests with command line arg 1 */
        QueueTest(1, atoi(argv[1]));
        printf("-------------------------------------------------\n");
        QueueTest(2, atoi(argv[1]));
    } else  {
        /* Both tests with type 1 and type 2 should match*/
        QueueTest2(1);
        printf("-------------------------------------------------\n");
        QueueTest2(2);
        /* Deleting queue with entries */
        printf("-------------------------------------------------\n");
        QueueTest3(1);
        printf("-------------------------------------------------\n");
        QueueTest3(2);
    } 
    printf("-------------------------------------------------\n");
    return 0;
}