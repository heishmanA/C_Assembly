/* lab4Queue.c file
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
    /* Setting up the clock */
    clock_t start, end;
    double cpu_time_used;
    
    /* Setting up the type of queue to test */
    Queue* new_q = type == 1 ? newQueue1() : newQueue2();
    
    int i, removed, errors;
    start = clock();
    errors = 0;
    /* added this to make things easier for testing */
    printf("Testing Queue%i with %i entries\n", type, entries); 
    for(i = 0; i < entries; i++){
        new_q->enqueue(new_q, i);
    }

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

int main(int argc, char *argv[]){
    int i, x;
    Stack *s;
    /*  Using command line args for easier testing */
    if (argc > 1) {

        /*call queue tests with command line arg 1 */
        QueueTest(1, atoi(argv[1]));
        QueueTest(2, atoi(argv[1]));
    } else {
        /* Error message  */
        printf("%s: Missing entries command line argument\n", argv[0]);
    } 

    return 0;
}