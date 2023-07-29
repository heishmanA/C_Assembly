/* rmdir.c file */
#include "filesystem.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int rmdir(Tree **wd_children, char *child_name) {
    /* Starting at the first directory - make a requires that wd_children can't be null */
    int cmpr = strcmp((*wd_children)->name, child_name);
    /* should skip the base case of first dir being */
    if (cmpr != 0) {
        while (wd_children != NULL && (*wd_children)->next_dir != NULL) {
            cmpr = strcmp((*wd_children)->next_dir->name, child_name);
            if (cmpr == 0) {
                break;
            }
            wd_children = &((**wd_children).next_dir); 
        } 
    }
    if (cmpr != 0) {
        return -1; /* dir not found */;
    } else if (cmpr == 0 && (*wd_children)->size > 0) {
        return 1; /*dir not empty */
    } else {
        Tree *next_address = (*wd_children)->next_dir;
        if (next_address == NULL) {
            printf("rmdir: %s\n", (*wd_children)->name);
            free(*wd_children);
            (*wd_children) = NULL;
            return 0;
        }
        printf("nxt = %s\n", next_address->name);
        (*wd_children)->next_dir = next_address->next_dir;
        printf("rmdir: %s\n", (*wd_children)->next_dir->name);
        free(next_address);
        next_address = NULL;
    }
    return 0;
  }
