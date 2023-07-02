/*  stack1.c file
    Aaron Heishman
*/

#include "stack_queue.h"
#include <stdlib.h>
#include <stdio.h>
/* Private function declaration*/

/*  Checks if the given pointer is null for malloc purposes, if NULL displays 
    error message and quits program
    @param *ptr - the specific pointer being checked if NULL*/
static void check_null(void *ptr);


/* Private functions definition */

static void check_null(void *ptr) {
    if (ptr == NULL) {
        printf("Error declaring a pointer for Stack2, not enough memory.");
        exit(0);
    }
}

/* Public function definitions */

Stack* newStack1() {
    /* Create the stack "objects" */
    Stack *stack_obj = malloc(sizeof(Stack));
    check_null((void*)stack_obj);
    Stack1 *stack1_obj = malloc(sizeof(Stack));
    check_null((void*)stack1_obj);
    /* set function pointers */
    stack_obj->push = &pushStack1;
    stack_obj->pop = &popStack1;
    stack_obj->length = &lengthStack1;
    stack_obj->del = &delStack1;
    /* set members of stack1obj*/
    stack1_obj->length = 0;
    stack1_obj->firstNode = NULL;
    stack1_obj->lastNode = NULL;
    /* update stackobj's vars to point at stack1obj*/
    stack_obj->vars = (void*)stack1_obj;
    return stack_obj;
}

void pushStack1(Stack* s, int x){
    Stack1 *stack1_ptr = (Stack1*)s->vars;
    LLNode *p = malloc(sizeof(LLNode));
    p->data = x;
    if (stack1_ptr->length == 0) {
        /*new node coming in is both first and last node*/
        stack1_ptr->firstNode = p;
        stack1_ptr->lastNode = p;
    } else {
        /*  new node coming in will point at the current first node
            saving the address if its previous node (so next works like previous)*/
        p->next = stack1_ptr->firstNode;
        /* update the first node to be the new node that came in*/
        stack1_ptr->firstNode = p;
        /*  lastNode's next points at the new node so that the new node
            can be popped */
        stack1_ptr->lastNode->next = p;
    }
    /* increment length by one*/
    stack1_ptr->length++;
}

int popStack1(Stack* s){
    Stack1 *stack1_ptr = (Stack1*)s->vars;
    int r = stack1_ptr->firstNode->data;
    if (stack1_ptr->length == 1) {
        /*  only one node in the stack, just free one because
            both should point at the same node
        */
        stack1_ptr->firstNode = NULL;
        free(stack1_ptr->lastNode);
        stack1_ptr->lastNode = NULL;
    } else {
        /*  firstNode's next will be the previous node added to the stack
            so update the firstNode to be that new node */
        stack1_ptr->firstNode = stack1_ptr->firstNode->next;
        /*  the last node->next in the list will point at whatever the first node
            is in list, so use lastNode to access that and free the pointer */
        free(stack1_ptr->lastNode->next);
        /*  zero out just in case */
        stack1_ptr->lastNode->next = NULL;
        /*  Update lastNode's next to point at the new "top" of the stack */
        stack1_ptr->lastNode->next = stack1_ptr->firstNode;
    }
    stack1_ptr->length--;
    return r;
}

int lengthStack1(Stack* s) {
    Stack1 *stack1_ptr = (Stack1*)s->vars;
    return stack1_ptr->length;
}

void delStack1(Stack* s) {
    Stack1 *stack1_ptr = (Stack1*)s->vars;
    if (stack1_ptr->length > 0) {
         /* firstNode's next will be the previous node added to the stack
            so update the firstNode to be that new node */
        stack1_ptr->firstNode = stack1_ptr->firstNode->next;
        /*  the last node->next in the list will point at whatever the first node
            is in list, so use lastNode to access that and free the pointer */
        free(stack1_ptr->lastNode->next);
        /*  zero out just in case */
        stack1_ptr->lastNode->next = NULL;
        /*  Update lastNode's next to point at the new "top" of the stack */
        stack1_ptr->lastNode->next = stack1_ptr->firstNode;
        /*  decrement the length of the stack so the recursion will stop */
        stack1_ptr->length--;
        delStack1(s);
    } else {
        /* Free vars and the stack*/
        free(s->vars);
        s->vars = NULL;
        free(s);
        s = NULL;
    }

}