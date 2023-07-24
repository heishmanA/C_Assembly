/* cat_write.c file */
#include "filesystem.h"

int find_file(Tree *wd, char *file_name, struct File **f_ptr) {
    int i, stop = wd->f_last;
    for (i = 0; i < stop; i++) {
        (*f_ptr) = &(wd->files[i]);
        if (strcmp((*f_ptr)->name, file_name) == 0) {
            return 1;
        }
    }
    /* if file does not break early, then we know it's the last file */
    return i;
}

/* check for file_name to not be null before coming into cat_write */
int file(Tree **wd, char *file_name) {
    struct File *f_ptr;
    int pos = find_file(wd, file_name, &f_ptr);
    /* pos > f_last means adding a new file */
    if (pos > wd->f_last) {
        f_ptr = &(wd->files[pos+1]);
        wd->size++;
        wd->f_last++;
        f_ptr->name = file_name;
    }
    /* indication of "writing" to a file */
    printf("[%s]>>", file_name);
    /* store the user input into the file "contents" */
    fgets(f_ptr->content, 256, stdin);
    return 0;
}
