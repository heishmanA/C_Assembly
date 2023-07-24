/* mv.c file */

#include "filesystem.h"

int mv(Tree **wd, char *target, char*destination, char *rename) {
    Tree *target_dir = *wd, *target_dest = *wd;
    int x = cd(&(target_dir), target), y = cd(&(target_dest), destination);
    int cmp = strcmp((*wd)->name, target);
    /* error, soemthing  wasn't found */
    if (x != 0 || y != 0 || cmp == 0) { 
        return -1;
    }
    if (*rename != '\0' && *rename != '\n') {
        strncpy(target_dir->name, rename, 33);
    }
    if (find_duplicates(target_dest->children, target_dir->name) == 0) {
        return -2;
    }
    Tree *left = target_dir->prev_dir, *right = target_dir->next_dir;
    /* update previous and next of target node to not lose connection */
    if (left != NULL && right != NULL) {
        left->next_dir = right;
        right->prev_dir = left;
    } else if (left == NULL && right != NULL) {
        (*wd)->parent->children = right;
    } else if (left != NULL && right == NULL) {
        left->next_dir = NULL;
    }

    if ((*wd)->size == 1) { /* current directory will have no children */
        (*wd)->children = NULL;
    }
    (*wd)->size--;
    if (target_dest->children == NULL) { /* target directory has no children */
        target_dest->children = target_dir;
        target_dir->next_dir = NULL;
        target_dir->prev_dir = NULL;
    } else {
        /* target directory has children, insert at the last position */
        Tree *d_children = target_dest->children;
        while (d_children->next_dir != NULL) {
            d_children = d_children->next_dir;
        }
        d_children->next_dir = target_dir;
        target_dir->prev_dir = d_children;
        target_dir->next_dir = NULL;
    }
    target_dir->parent = target_dest;
    target_dir->parent->size++;
    return 0; 
}
