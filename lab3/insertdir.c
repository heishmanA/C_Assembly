/* insertdir.c file 
 * Aaron Heishman
 * Systems I - Lab 3
 * */

#include "filesystem.h"


void insert(Tree **children_ptr, Tree *new_dir) {
    /* if child coming in is null, make that child the new dir */
    if (*children_ptr == NULL) { /* children empty, insert new dir */
        new_dir->next_dir = NULL;
        new_dir->prev_dir = NULL;
        *children_ptr = new_dir;  
        new_dir->parent = (*children_ptr)->parent;
    } else {
        /* cycle through child address until the last child is found
         * making the new dir the last directory */
        while ((*children_ptr)->next_dir != NULL ) {
            children_ptr = &((**children_ptr).next_dir);
        }
        new_dir->prev_dir = *children_ptr;
        (*children_ptr)->next_dir = new_dir;  
        new_dir->parent = (*children_ptr)->parent;
        new_dir->next_dir = NULL;
    }
        (*children_ptr)->parent->size++; /* update directory size */
}



