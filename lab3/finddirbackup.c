/* finddir.c file */
#include "filesystem.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
Tree **finddir(Tree **wd_children, char *child_name) {
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
    return &(*wd_children);
  }
