/* cp.c file 
 * Aaron Heishman
 * Systems 1 - Lab 3
 * */

#include "filesystem.h"


/* get destination and check if *wd and *dest are the same */

int find_duplicate_files(Tree *dest, char *name) {
    int i;
    struct File *f_ptr = &(dest->files[0]);
    for (i = 0; i < dest->f_length; i++) {
        if (strcmp(f_ptr->name, name) == 0) {
            return i;
        }
        i++;
    }  
    return 0;
}


int cp(Tree *wd, char *source, Tree *dest, char *new_name) {
    int dst_pos;
    char *name = source;
    /* check file exists */
    int pos = find_file(wd, source);
    if (pos == -1) {
        return -1; /* file not found */
    }
    /* check if renaming file */
    if (new_name != NULL && *new_name && '\0' && *new_name != '\n') {
        name = new_name;
    }
    /* check for duplicates */
    if (find_duplicate_files(dest, wd->files[pos].name) != 0) {
        return -2; /* duplicate file name */
    }
    /* copy file into destination */
    dst_pos = dest->f_length; 
    strncpy(dest->files[dst_pos].name, name, 31); 
    strncpy(dest->files[dst_pos].content, wd->files[pos].content, 255);
    dest->f_length++; 
    rm(&wd, source); /* remove file from the source */
    return 0;
}
