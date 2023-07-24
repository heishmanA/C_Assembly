/* pwd.c file 
 * Aaron Heishman
 * Systems I - Lab 3
 */

#include "filesystem.h"
 
void pwd(Tree *wd_ptr, char *wd_name) {
    /* Recursive call to the root, printing /root..../wd(if wd is not root) */
    if (wd_ptr != NULL) {
        pwd(wd_ptr->parent, wd_name);
        printf("/%s", wd_ptr->name);
        /* print new line after recursion is back at wd */
        if (strcmp(wd_ptr->name, wd_name) == 0) {
            printf("\n");
        }
    }
}

