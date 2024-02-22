/* lab4.c file
    Aaron Heishman
    Systems I
    Lab4
    Original File Supplied by Braeden Jeske
    Modifications by Aaron Heishman 
    - Removed the ENTRIES macro to allow for the user to input command line args
    - Added some printing prompts to show what's going on 
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


int main(int argc, char *argv[]){

    /*  Using command line args for easier testing */
    if (argc > 1) {
         /* setting up clock */
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        /* argv[1] = entry amt chosen by user */
        StackTest(1, atoi(argv[1]));
        StackTest(2, atoi(argv[1])); 
        
        /* Calculate CPU time in seconds, then output and close */
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Clock Time reads: %f seconds\n", cpu_time_used);
    } else {
        /* Error message */
        printf("%s: Missing entries command line argument\n", argv[0]);
    } 

    return 0;
}