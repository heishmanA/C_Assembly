/* mkdir.c file 
 * Aaron Heishman
 * Systems I - Lab 3
 */
#include "filesystem.h"

Tree *mkdir(Tree *parent, char *dir_name, char *prog_name) {
    Tree *new_dir = malloc(sizeof(Tree));
    /* verify new dir isn't NULL */
    if (new_dir == NULL) {
        printf("%s: Error creating new directory\n", prog_name);
        printf("Closing program..\n");
        exit(0);
    }
    /* initialize values */
    strcpy(new_dir->name, dir_name);
    new_dir->parent = parent;
    if (parent != NULL) {
        parent->size++;
    }
    new_dir->next_dir = NULL;
    new_dir->children = NULL;
    new_dir->prev_dir = NULL;
    new_dir->size = 0;
    new_dir->f_length = 0;
    return new_dir;
}
