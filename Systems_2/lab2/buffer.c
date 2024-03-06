/* buffer.c file
   Aaron Heishman
   Lab2: Systems 2
   9/5/2023
*/
#include <stdlib.h> /* for rand */
#include "buffer.h"
#include <stdio.h>
buffer_item buffer[BUFFER_SIZE] = {0};
int end_index = 0;
int front_index = 0;


int insert_item(buffer_item item) {
    /* insert item into buffer */
    printf("producer produced %d\n", item);
    buffer[end_index] = item;
    /* check if the value inserted hasn't been removed or over written*/
    if (buffer[end_index] != item) { 
        return -1; 
    }
    end_index = (end_index + 1) % BUFFER_SIZE; // update the 
    return 0;
}

int remove_item(buffer_item *item) {
    /* remove an object from buffer and placing it in item*/
    *item = buffer[front_index];
    buffer[front_index] = -1; // change the value to a number rand_r can't produce
    /* return 0 for success, -1 for not*/
    if (buffer[front_index] != -1 || *item == -1) { // check to make sure that this number is still there
        return -1;
    }
    front_index = (front_index + 1) % BUFFER_SIZE;
    return 0;
}
