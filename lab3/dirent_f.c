/* dirent_f.c file 
 * Aaron Heishman
 * Systems 1 - Lab 3
 */

#include "filesystem.h"
#include <dirent.h>
int dirrent_f(Tree **wd, char *path) {
    /* open the specified path */
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return -1; /* path does not exist */
    }
    /* read from the path, creating new files in the system for each file found */
    struct dirent *file;
    file = readdir(dir);
    int i = 0;
    while (file != NULL) {
        /* ignoring any . or .. */
        int cmp1 = strcmp(".", file->d_name);
        int cmp2 = strcmp("..", file->d_name);
        if (i <= 64 && cmp1 != 0 && cmp2 != 0) {
            /* copy file name to current list of files */
            strncpy((*wd)->files[i].name, file->d_name, 30);
            strncpy((*wd)->files[i].content, "garb", 4);
            (*wd)->size++;
            (*wd)->f_length++;
            i++;
        } if (i > 64 ) {
            break; /*if there a more than 64 files just stop reading from the dir */
        }
        file = readdir(dir);
    }
    /* close dir to prevent leaks*/
    closedir(dir);
    return 0;
}
