/* cat_write.c file */
#include "filesystem.h"


int get_file_pos(Tree *wd, char *name) {
    int i, stop = wd->f_length;
    for (i = 0; i < stop; i++) {
        if (strcmp(wd->files[i].name, name) == 0) {
            return i;
        };
    }
    /* file not found - crate a new file */
       
    return i;
}

/* check for file_name to not be null before coming into cat_write */
int file(Tree **wd, char *file_name) {
    int pos = 0;
    if ((*wd)->f_length > 0) {
        pos = get_file_pos(*wd, file_name);
    }

    if (pos == (*wd)->f_length) {
         strncpy((*wd)->files[pos].name, file_name, 30);
        (*wd)->size++;
        (*wd)->f_length++;
    }

    /* indication of "writing" to a file */
    printf("[%s]>>", file_name);
    /* store the user input into the file "contents" */
    fgets((*wd)->files[pos].content, 255, stdin);
    /* fgets((*f_ptr)->content, 256, stdin); */
    return 0;
}

