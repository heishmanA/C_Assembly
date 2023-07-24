/* cp.c file */

#include "filesystem.h"


/* get destination and check if *wd and *dest are the same */
/* maybe check duplicates outside? */

int find_duplicates_files(Tree *dest, char *name) {
    int i;
    struct File *f_ptr = &(dest->files[0]);
    for (i = 0; i < dest->f_last; i++) {
        if (strcmp(f_ptr->name, name) == 0) {
            return i;
        }
        i++;
    }  
    return 0;
}

/* might be able to just call rm for this */
void update_files(Tree **wd, int start) {
    int i, stop = (*wd)->f_last;
    for (i = start; i < stop - 1; i++) {
        (*wd)->files[i].name = (*wd)->files[i+1].name;
        strcpy((*wd)->files[i].content, (*wd)->files[i+1].content);
    }
    (*wd)->f_last--;
}

int find_source(Tree *wd,char *source) {
    int i, stop = wd->f_last;
    for (i = 0; i < wd->f_last; i++) {
        if (strcmp(wd->files[i].name, source) == 0) {
            return i;
        }
    }
    return -1;
}

int cp(Tree *wd, char *source, Tree *dest, char *new_name) {
    int dst_pos;
    /* check file exists */
    int pos = find_source(wd, source);
    if (pos == -1) {
        return -1; /* file not found */
    }
    /* check if renaming file */
    if (new_name != NULL) {
        (*wd).files[pos].name = new_name;
    }
    /* check for duplicates */
    if (find_duplicates_files(dest, wd->files[pos].name) != 0) {
        return -2; /* duplicate file name */
    }
    dst_pos = dest->f_last;
    /* insert the file into dest */
    dest->files[dst_pos].name = wd->files[pos].name; 
    strcpy(dest->files[dst_pos].content, wd->files[pos].content);
    dest->f_last++;
    update_files(&wd, pos);
    
    return 0;
}
