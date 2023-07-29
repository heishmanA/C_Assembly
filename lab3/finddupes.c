/* checkdupes.c file 
 * Aaron Heishman
 * Systems I - Lab 3
 * */

#include "filesystem.h"

int find_duplicates(Tree *children, char *name) {
    while (children != NULL) {
        if (strcmp(children->name, name) == 0) {
            return 0;
        }
        children = children->next_dir;
    }
    return -1;
}
