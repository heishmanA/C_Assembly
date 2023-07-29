/* cat.c file */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filesystem.h"

int cat_read(Tree *wd, char *file_name) {
    int i = 0;
    struct File *f_ptr = &(wd->files[i]);
    while (f_ptr->name != '\0' && strcmp(f_ptr->name, file_name) != 0) {
        i++;
        f_ptr = &(wd->files[i]);
    }
    if (f_ptr->name == '\0') {
        return -1; /* file not found */
    }
    
    printf("%s", f_ptr->content);
    return 0;
}
