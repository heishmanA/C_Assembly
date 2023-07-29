/* list.c file
 * Aaron Heishman
 * Systems I - Lab 3
 * */

#include "filesystem.h"


void ls(Tree *wd) {
    Tree *children_ptr = wd->children;
    int i = 0, j = 0;
    struct File *file_ptr = &(wd->files[0]);
    /* iterate and list the subfolders and file of the current working directory */
    while (children_ptr != NULL || j < wd->f_length) {
        if (children_ptr != NULL) {  
            printf(" |%s| ", children_ptr->name);
            children_ptr = children_ptr->next_dir;
        }
        if (i < wd->f_length) {
            printf(" |%s| ", wd->files[j].name);
        }
        /* print newline every 8th read in */ 
        if (i == 7) {
            printf("\n");
            i = 0;
        }
        i++;
        j++;
    }
    /* print a new line only if there wasn't a mutiple of 8 */
    if (i != 0) {
        printf("\n");
    }
}
