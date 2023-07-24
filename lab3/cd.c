/* changedir.c */

#include "filesystem.h"

int cd(Tree **wd_ptr, char *dir_name) {
    Tree *helper;
    /* check if target directory is parent */
    if ((*wd_ptr)->parent != NULL && strcmp((*wd_ptr)->parent->name, dir_name) == 0) {
       *wd_ptr = ((*wd_ptr)->parent);
       return 0;
    }

    /* check if target directory is part of working directory children */
    helper = (*wd_ptr)->children;
    while (helper != NULL) {
        if (strcmp(helper->name, dir_name) == 0) {
            (*wd_ptr) = &(*helper);
            return 0;
        }
        helper = helper->next_dir;
    }
    
    /* return -1 if directory is not found */
    return -1;    
}

