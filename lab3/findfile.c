/* rm.c file */

#include "filesystem.h"

/* finds the source file - maybe make a function */
int find_file(Tree *wd, char *source) {
    int i, stop = wd->f_length;
    for (i = 0; i < stop; i++) {
        if (strcmp(wd->files[i].name, source) == 0) {
            return i;
        }
    }
    return -1;
}

