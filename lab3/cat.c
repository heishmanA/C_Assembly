/* cat.c file
 * Aaron Heishman
 * Systems 1 - Lab 3
 * */

#include "filesystem.h"

int cat(Tree *wd, char *file_name) {
    int i = 0;
    struct File *f_ptr = &(wd->files[i]);
    while (f_ptr->name != '\0' && strcmp(f_ptr->name, file_name) != 0) {
        i++;
        f_ptr = &(wd->files[i]);
    }
    if (f_ptr->name == '\0') {
        return -1; /* file not found */
    }
    printf("%s\n", f_ptr->content);
    return 0;
}
