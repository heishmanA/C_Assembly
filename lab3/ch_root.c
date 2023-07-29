/* ch_root.c file 
 * Aaron Heishman
 * Systems I - Lab 3
 * */

#include "filesystem.h"

void ch_root(Tree *wd, char *new_name) {
    /* find root and rename it */     
    if (wd->parent == NULL) {
        strncpy(wd->name, new_name, 32); 
    } else { 
        ch_root(wd->parent, new_name);
    }
}
