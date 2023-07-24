/* rmdir.c file
 * Aaron Heishman
 * Systems I - Lab 3
 * */
#include "filesystem.h"

int rmdir(Tree **wd_children, char *target_name) {
    /* point wd_children at the target directory to be removed */
    while (*wd_children != NULL && strcmp((*wd_children)->name, target_name) != 0) {
        wd_children = &((**wd_children).next_dir);
    }

    /* check if dir can be deleted or not */
    if (*wd_children == NULL) {
        return -1; /* dir not found */
    } else if ((*wd_children)->size > 0) {
        return 1; /* dir is not empty */
    }

    /* checking if first or last dir */
    Tree **temp = wd_children;
    Tree **prev = &(**wd_children).prev_dir;
    Tree **next = &(**wd_children).next_dir;
    Tree **prnt = &(**wd_children).parent;
    if (*prev  == NULL && *next != NULL) { /* first dir */
        /* update the children node of parent to point to the next dir */
        (*prnt)->children = *next;
        (*next)->prev_dir = NULL;
    } else if (*prev != NULL && *next == NULL) { /* last_dir */
        (*prev)->next_dir = NULL;
    } else if (*prev != NULL && *next != NULL) { 
        /* remove dir between two non-null dirs */
        wd_children = &((**temp).prev_dir); 
        (*wd_children)->next_dir = (*temp)->next_dir;
        (*temp)->next_dir->prev_dir = (*wd_children);
    }
    /* free temp because it should be the address of the tree made by malloc */
    
    (*prnt)->size--; 
    /* not the most ideal way, but frees the child of the directory if it was removed
     * else frees the specific directory that was moved */
    if ((*prnt)->size == 0) {
       free((*prnt)->children);
       (*prnt)->children = NULL;
    } else {
        free(*temp);
        temp = NULL;
    }
    
    return 0;
  }
