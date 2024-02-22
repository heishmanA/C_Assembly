/* lab4.c file
    Supplied by Braeden Jeskse
    Modifications by Aaron Heishman (aka me, the student)
    Systems I
    Lab4
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lab4.h"

void StackTest(int type, int entries){
    Stack* newStack = type == 1 ? newStack1() : newStack2();

    int i, removed, errors;
    errors = 0;
    /* added this to make things easier for testing */
    printf("Testing Stack %i with %i entries\n", type, entries); 
    for(i = 0; i < entries; i++){
        newStack->push(newStack, i);
    }

    for(i = 0; i < entries; i++){
        removed = newStack->pop(newStack);
        if(removed != entries - i - 1){
            printf("Expected %i, removed %i\n", entries - i - 1, removed);
            errors++;
        }
    }

    newStack->del(newStack);

    printf("Ended with %i errors\n", errors);
}

void QueueTest(int type, int entries){
    Queue* new_q = type == 1 ? newQueue1() : newQueue2();
    
    int i, removed, errors;
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
}

int main(int argc, char *argv[]){
    int i, x;
    Stack *s;
    /* setting up clock */
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    /*  Using command line args for easier testing */
    if (argc > 1) {
        /*call stack tests with command line arg 1 */
        StackTest(1, atoi(argv[1]));
        StackTest(2, atoi(argv[1]));
    } else {
        /* Error message  */
        printf("%s: Missing entries command line argument\n", argv[0]);
    } 
    
    /* if (argc > 1) {
       QueueTest(1, atoi(argv[1]));
       QueueTest(2, atoi(argv[1])); 
       
    } else {
        printf("%s: Missing entries command line argument\n", argv[0]);
    }
    */
    /* Calculate CPU time in seconds, then output and close */
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Clock Time reads: %f seconds\n", cpu_time_used);

    return 0;
}