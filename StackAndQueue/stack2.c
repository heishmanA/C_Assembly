/*  stack2.c file
    Aaron Heishman
*/

#include "stack_queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/* private function declarations */

/*  Checks if the array needs to be doubled, and then doubles the array if so 
    @param - *stack2_ptr - Stack pointer that points at the stack being modified
*/
static void double_size(Stack2 *stack2_ptr);

/*  Checks if the array needs halved, halves if so
    @param - *stack2_ptr - Stack pointer that points at the stack being modified
*/
static void halve_size(Stack2 * stack2_ptr);

/*  Checks if the given pointer is null for malloc purposes, if NULL displays 
    error message and quits program
    @param *ptr - the specific pointer being checked if NULL*/
static void check_null(void *ptr);



/* private function definitions */

static void double_size(Stack2 *stack2_ptr) {
    /* set up variables */
    int arr_length = stack2_ptr->length;
    int arr_size = stack2_ptr->arrSize;
    int *new_arr;
    /* check if the array needs to be doubled */
    if (arr_length == arr_size) {
        /* create a new array that is twice the size of the old array*/
        int new_size = arr_size *= 2;
        new_arr = (int*)malloc(new_size * sizeof(int));
        check_null((void*)new_arr);

        /* copy elements from old array to new */
        int i;
        for (i = 0; i < arr_length; i++) {
            new_arr[i] = stack2_ptr->entries[i];
        }

        /* Free the array pointer */
        free(stack2_ptr->entries);
        stack2_ptr->entries = NULL;

        /* Update the array pointer to point at the new array */
        stack2_ptr->entries = new_arr;
        stack2_ptr->arrSize = new_size;
    }
}

static void halve_size(Stack2 *stack2_ptr) {
    /* set up variables */
    int arr_length = stack2_ptr->length;
    int arr_size_by_four = (stack2_ptr->arrSize) >> 2; /* arrSize/4 */
    int *new_arr;
    /* check if the array needs halved */
    if (MIN_SIZE <= arr_length && arr_length == arr_size_by_four) {
        /* create a new array that is twice the size of the old array*/
        int new_size = (stack2_ptr->arrSize) >> 1; /* arrsize/2 */
        new_arr = (int*)malloc(new_size * sizeof(int));
        check_null((void*)new_arr);
        /* copy elements from old array to new */
        int i;
        for (i = 0; i < arr_length; i++) {
            new_arr[i] = stack2_ptr->entries[i];
        }
        /* Free the array pointer */
        free(stack2_ptr->entries);
        stack2_ptr->entries = NULL;
        /* Update the array pointer to point at the new array */
        stack2_ptr->entries = new_arr;
        stack2_ptr->arrSize = new_size;
    }
}

static void check_null(void *ptr) {
    if (ptr == NULL) {
        printf("Error declaring a pointer for Stack2, not enough memory.");
        exit(0);
    }
}


/* public function definitions */
Stack* newStack2() {
    /*Set up stack */
    Stack *stack_obj = (Stack*)malloc(sizeof(Stack));
    check_null((void*)stack_obj);
    stack_obj->push = &pushStack2;
    stack_obj->pop = &popStack2;
    stack_obj->length = &lengthStack2;
    stack_obj->del = &delStack2;
    /* Set up stack2 */
    Stack2 *stack2_obj = (void*)malloc(sizeof(Stack2));
    check_null((void*)stack2_obj);
    stack2_obj->length = 0;
    stack2_obj->arrSize = MIN_SIZE;
    /*minsize is 4, char size is 1 */
    stack2_obj->entries = (int*)malloc(MIN_SIZE * sizeof(int));
    check_null((void*)stack2_obj->entries);
    stack_obj->vars = stack2_obj;
    return stack_obj;
}

void pushStack2(Stack* s, int x){
    /* Initial setup of variables */
    Stack2 *stack2_ptr = (Stack2*)s->vars;
    /* update the current value at length (because length is the end) to x*/
    stack2_ptr->entries[stack2_ptr->length] = x;
    /* increment length by one */
    stack2_ptr->length++;
    /* check if the stack needs to be doubled */
    double_size(stack2_ptr);
}

int popStack2(Stack* s) {
    /* Set up stack2 ptr */
    Stack2 *stack2_ptr = (Stack2*)s->vars;
    /* Assertion just in case pop gets called at size 0*/
    assert(stack2_ptr->length != 0);
    /* get the value being "popped" off */
    int r = stack2_ptr->entries[(stack2_ptr->length) - 1];
    /* decrement size by 1 */
    stack2_ptr->length--;
    /* check if the stack needs halved */
    halve_size(stack2_ptr);
    return r;
}

int lengthStack2(Stack* s) {
    /* set up stack2 ptr */
    Stack2 *stack2_ptr = (Stack2*)s->vars;
    /* return length*/
    return stack2_ptr->length;
}

void delStack2(Stack* s) {
    /* set up stack2_ptr */
    Stack2 *stack2_ptr = (Stack2*)s->vars;
    /* free all in use pointers */
    free(stack2_ptr->entries);
    stack2_ptr->entries = NULL;
    free(s->vars);
    s->vars = NULL;
    free(s);
    s = NULL;
}