/* free.c file 
 * Aaron Heishman
 * Systems I - Lab 3
 */

#include "filesystem.h"


void free_memory(Tree **root) {
    /* Recursively free all nodes created by malloc */
    
    if (*root != NULL) { 
        printf("freeing %s\n",(*root)->name);
        /* check if there are children */
        if ((*root)->children != NULL) {
            free_memory(&((*root)->children));
        }
        /* check if there are siblings */
        if ((*root)->next_dir != NULL) {
            free_memory(&((*root)->next_dir));
        } 
        free(*root);
        *root = NULL;
    }

}
