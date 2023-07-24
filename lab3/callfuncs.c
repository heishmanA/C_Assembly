/* callfuncs.c file 
 * Aaron Heishman
 * Systems I - Lab 3
 * */

#include "filesystem.h"

int call_function(int x, char *args[], Tree **wd, char *prog_name) {
    int r = 0;
    int e;
    Tree *dst;
    switch (x) {
        case 0: /* ls command */
            ls(*wd);
            break;
        case 1: 
            pwd(*wd, (*wd)->name);
            break;
        case 2: /* cd command */
            if (*args[1] == '\0'|| *args[1] == '\n') {
                printf("Error: Directory input needed\n");
                break;
            } 
            e = cd(wd, args[1]);
            if (e == -1) {
                printf("Error: %s not found\n", args[1]);
            }
            break;
        case 3: /* rmdir command */
            e = rmdir(&((**wd).children), args[1]);
            if (e == -1) {
                printf("Specified directory %i is not empty\n", args[1]);
            }
            break;
        case 4: /* mv command */
            if (*args[1] == '\0' || *args[1] == '\n') {
                printf("Error: Missing target direcotry name\n");
                break;
             } else if (*args[2] == '\0' || *args[2] == '\n') {
                printf("Error missing directoryi name\n");
                break;
             }
            e = mv(wd, args[1], args[2], args[3]);
            if (e < 0) {
                printf("Received error code %i\n", e);
                printf("-1: Target dir not found\n");
                printf("-2: Destination dir not found\n");
                printf("-3: Target and Destination are the same\n");
            } else if (e > 1) {
                printf("Received error code %i\n", e);
                printf("Duplicate file name in the destination folder\n");
            }
            break;
        case 5: /* cat command */
            if (*args[1] == '\0' || *args[1] == '\n') {
                printf("Error: file name input needed");
                break;
            }
            e = cat(*wd, args[1]);
            if (e == -1) {
                printf("Error: %s cannot be found\n", args[1]);
            }
            break;
        case 6: /* mkdir command */
            if (*args[1] == '\0' || *args[1] == '\n') {
                printf("Error: missing directory name\n"); 
            } else if (find_duplicates((*wd)->children, args[1]) == 0) {
                printf("Error: duplicate directory name found.\n");
            } else if ((*wd)->size < 64) {
                insert(&((*wd)->children), mkdir(*wd, args[1], prog_name));
            } else {
                printf("Error:  %s is full.\n", (*wd)->name);
            }
            break;
        case 7: /* file command */
            if (*args[1] == '\0'|| *args[1] == '\0') {
                printf("Error, missing directory name\n");
            } else if ((*wd)->size < 64) {
                file(wd, args[1]); 
            } else {
                printf("Error: Cannot create file. %s is full.\n", (*wd)->name);
            }
            break;
        case 8: /* cp command */
            if (*args[1] == '\0' || *args[1] == '\n') {
                printf("Error: missing source name\n");
            }  else if (*args[2] == '\0' || *args[2] == '\n') {
                printf("Error: missing directory name\n");
                break;
            }
            dst = *wd;
            e = cd(&dst, args[2]);
            if (e == -1) {
                printf("Error: destination directory not found.\n");
                break;
            }
            e = cp(*wd, args[1], dst, args[3]);
            if (e == -1) {
                printf("Error: %s not found\n", args[1]);
            } else if (e == -2) {
                printf("Error: Duplicate file name in destination directory\n");
            }
            break;
        case 9: /* rm command */
            if (*args[1] != '\0' || *args[1] != '\n') {
                e = rm(wd, args[1]);
                if (e == -1) {
                    printf("Error: %s not found\n", args[1]);
                }
            } else {
                printf("Error: missing file name\n");
            }
            break;
        case 10: /* file command */
            if (*args[1] == '\0' || *args[1] == '\n') {
                printf("Error: missing file name\n");
            } else {
                file(wd, args[1]);
            }
            break;
        case 11: /* Help command */
            print_help();
            break;
        case 12: /* quit command */
            printf("Closing file system...goodbye..\n");
            r = -1;
            break;
        case 13: /* dirprint command */
            dir_print(*wd, (*wd)->name);
            break;
        case 14: /* dwp command */
            dwp(*wd);
            break;
        case 15: /* change root name command */
            if (*args[1] == '\0' || *args[1] == '\n') {
                printf("Error: missing new name for directory");
            } else {
                ch_root(*wd, args[1]);
            }
            break;
        case 16: /* obliterate command */
            obliterate(wd, (*wd)->name);
            break;
        default: /* default if no input */
            printf("Command not recognized -- use 'help' to display the commands\n");
            break;
        }
    
    return r;
}

