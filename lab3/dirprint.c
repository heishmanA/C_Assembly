/* dirprint.c */

#include "filesystem.h"

void print_left(Tree *helper) {
    while (helper != NULL) {  
            printf("<%s> ", helper->name);
            helper = helper->prev_dir;
    }
 
}

void print_right(Tree *helper) {
    ;
    while (helper != NULL) {
        printf("<%s> ", helper->name);
        helper = helper->next_dir;
    }
}

void dir_print(Tree *wd, char *wd_name) {
    if (wd != NULL) {
        dir_print(wd->parent, wd_name);
       /* check if directory current wd is a parent or the current wd */
       if (strcmp(wd->name, wd_name) != 0) {
            printf("Parent directory: <%s>\n", wd->name);
        } else if (strcmp(wd->name, wd_name) == 0) {
            printf("Current directory: <%s>\n", wd->name);
        }
        Tree *helper;
        /* print siblings if they exist */
        if (wd->prev_dir != NULL || wd->next_dir != NULL) {
            printf("------  siblings     -------\n");
            if (wd->prev_dir != NULL) {
                helper = wd->prev_dir;
                print_left(helper);
            }
            printf("<-- %s --> ", wd->name); /* put directory in the list to show where it is */
            if (wd->next_dir != NULL) {
                helper = wd->next_dir;
                print_right(helper);
            }
            printf("\n---------------------------\n");
        }
        
    }

}
