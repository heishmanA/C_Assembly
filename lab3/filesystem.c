/* filesystem.c 
 * Aaron Heishman
 * Systems I - Lab 3
 * */

#include "filesystem.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* iterate over the commands to check what the user wants */
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


/* parses the user input into individual commands */
int parse_input(char *unparsed_args, Tree **wd, char * prog_name) {
    char arg1[30] = {0}, arg2[30] = {0},  arg3[30] = {0}, arg4[30] = {0};
    char *args[4];    
    int user_choice = 0;
    sscanf(unparsed_args, "%s %s %s %s",  arg1, arg2, arg3, arg4);
    if (arg1[0] == '\0' || arg1[0] == '\n') {
        printf("No input detected. Type 'help' to see available commands\n");
        } else {
            args[0] = arg1;
            args[1] = arg2;
            args[2] = arg3;
            args[3] = arg4;
            user_choice = call_function(get_command(args[0]), args, wd, prog_name);
    }
    return user_choice;
}


/* gets user input */
void get_input(Tree **wd, char *prog_name) {
    int user_choice = 0;
    char user_name[10] = {0};
    char user_input[105];
    printf("Enter your username: ");
    fgets(user_input, 10, stdin);
    sscanf(user_input, "%s", user_name);
    printf("Welcome, %s.\n", user_name);
    /* repeatedly post to the terminal similar to that of an actual system */    
    while (user_choice != -1) { 
        /* print the current path */
        printf("[%s | %s ~]$ ", user_name, (*wd)->name);   
        fgets(user_input, 120, stdin);
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
        int e_code = dirrent_f(&wd, argv[1]);
        if (e_code == -1) {
            printf("Dirent could not open the directory on path: %s\n", argv[1]);
        }
    }
    /* get user input */
    get_input(&wd, argv[0]); 
    /* free the memory */ 
    free_memory(&root);  
    return 0;
}

