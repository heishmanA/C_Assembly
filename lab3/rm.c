/* rm.c file 
 * Aaron Heishman
 * Systems I - lab 3
 * */

#include "filesystem.h"

int rm(Tree **wd, char *source) {
    int i = find_file(*wd, source);
    int stop = (*wd)->f_length;
    if (i == -1) {
        return -1; /* file not found */  
    }
    /* update files */
    if (i == 1) {
        /* single file just set the name to null */
        char *f = "\0";
        strncpy((*wd)->files[0].name, f, 33);
    } else { 
        while (i < stop - 1) {
            /* multiple files in system */
            struct File *file1 = &((**wd).files[i]);
            struct File *file2 = &((**wd).files[i + 1]);
            strncpy(file1->name, file2->name, 31);
            strncpy(file1->content, file2->content, 255);
            i++;
        }
        /* free the file name of the last file before decrementing size */
        strncpy((*wd)->files[0].name, "\0", 33);
    }   
    (*wd)->f_length--; 
    return 0;
}
