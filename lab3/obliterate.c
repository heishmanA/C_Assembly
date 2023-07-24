/* obliterate.c file
 * Aaron Heisman
 * Systems I - Lab 3
 */

#include "filesystem.h"
void obliterate(Tree **wd, char *wd_name) {
   if (*wd != NULL) {
        int cmp;
        /* go down until the last child */
        if ((*wd)->children != NULL) {
            obliterate(&(*wd)->children, wd_name);
        }

        /* obliterate everything but the files and directory the user is currently in */
        if (strcmp((*wd)->name, wd_name) != 0) {
            /* obliterate siblings on the right */
            if ((*wd)->next_dir != NULL) {
                obliterate(&(*wd)->next_dir, wd_name);
            }
            /* NOTE: No need to obliterate the left as the children start at the left */
            /* obliterate the directory if it is not the working directory */
            printf("Obliterating %s\n", (*wd)->name);
            free(*wd);
            *wd = NULL;
        }

   }
}
