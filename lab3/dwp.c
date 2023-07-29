/* dwp.c file */

#include "filesystem.h"

void dwp(Tree *wd) {
    if (wd->parent != NULL) {
        printf("%s\\", wd->name);
        dwp(wd->parent);
    } else {
         printf("%s\\\n", wd->name);
    }
}
