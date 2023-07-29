/* filesystem.c */

#include "filesystem.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int get_command(char *command) {
    char c[13][10] = {"ls", "pwd", "cd", "rmdir", "mv", "cat", "mkdir", "file", "cp", "rm", "file", "help", "quit"};
    char c2[5][20] = {"dirp", "dwp", "cr", "ob"};
    int i;
    for (i = 0; i < 13; i++) {
        if (strcmp(c[i], command) == 0) {
            return i;
        }
        if (i < 4) {
            if (strcmp(c2[i], command) == 0) {
                return i + 13;
            }
        }
    }
    return 20;
}

int do_something(int x, char *args[], Tree **wd, char *prog_name) {
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


int parse_input(char *unparsed_args, Tree **wd, char * prog_name) {
    char arg1[10] = {0};
    char arg2[50] = {0};
    char arg3[50] = {0};
    char arg4[50] = {0};
    char *args[4];    
    int user_choice = 0;
    sscanf(unparsed_args, "%s %s %s %s",  arg1, arg2, arg3, arg4);
    if (arg1[0] == '\0' || arg1[0] == '\n') {
        printf("No input detected. Type 'help' to see available commands\n");
        } else {
            args[0] = arg1;
            args[1] = arg2;
            args[2] = arg3;
            if (arg3 != "\n") { /* prevent cp or mv from give the file the wrong name */
                args[3] = arg4;
            }
            user_choice= do_something(get_command(args[0]), args, wd, prog_name);
    }
    return user_choice;
}

void get_input(Tree **wd, char *prog_name) {
    int user_choice = 0;
    char user_name[10] = {0};
    char user_input[105];
    printf("Enter your username: ");
    fgets(user_input, 10, stdin);
    sscanf(user_input, "%s", user_name);
    printf("Welcome, %s.\n", user_name);
    /* var declaration */
    
    while (user_choice != -1) { 
        /* print the current path */
        printf("[%s | %s ~]$ ", user_name, (*wd)->name);   
        fgets(user_input, 100, stdin);
        user_choice = parse_input(user_input, wd, prog_name); 
    }
}

int main(int argc, char *argv[]) {   
    /* initalize program */
    Tree *root, *wd;
    /* create root */
    printf("Starting system..\n");
    root = mkdir(NULL, "root", argv[0]);
    /* update working directory */
    wd = root;
    if (argc > 1) {
        printf("Dirrent returned: %i\n", dirrent_f(&wd, argv[1]));
    }
    /* get user input */
    get_input(&wd, argv[0]); 
    /* free the memory */ 
    free_memory(&root);
    
    return 0;
}

