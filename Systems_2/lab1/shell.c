/*  lab1.c file
    Aaron Heishman
    Systems II - Lab 1 Unix Shell
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80

/* setup() reads in the next command line string stored in inputBuffer,
separating it into distinct tokens using whitespace as delimiters.
setup() modifies the args parameter so that it holds pointers to the
null-terminated strings that are the tokens in the most recent user
command line as well as a NULL pointer, indicating the end of the
argument list, which comes after the string pointers that have been
assigned to args. */

void setup(char inputBuffer[], char *args[], int *background) {
    char *token, *null_ptr = NULL;
    char delims[2] = " ";
    /* read input */
    int len = read(STDIN_FILENO, inputBuffer, MAX_LINE);
    
    /* check input */
    if (len == 0) {
        exit(0); /* ctrl+d entered */
    } else if (len < 0) {
        fprintf(stderr, "Error reading command\n");
    }
    
    /* remove the trailing newline */
    inputBuffer[len - 1] = '\0';

    /* tokenize the user input */
    token = strtok(inputBuffer, delims);
    int i = 0;
    /*  parse the input into commands, if & is found 
            set background to 1 and break out */
    while (token != NULL) {
        if (strcmp(token, "&") == 0) {
            *background = 1;
            break;
        } else {
            args[i] = strdup(token);
            i++;
        }
        token = strtok(0, delims);
    }
    /* place null pointer at the end of the argument list */
    args[i] = null_ptr;
}

int main(void) {
    char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
    int background;             /* equals 1 if a command is followed by '&' */
    char *args[MAX_LINE+1];     /* command line arguments */
    pid_t pid;
    
    while (1) {
        background = 0;
        printf(" Command->\n");
        setup(inputBuffer, args, &background);
        int retCode;
        
        /* fork a new child based on user input */
        pid = fork(); /* create new process */
        if (pid < 0) {
            /* fork failed */
            fprintf(stderr, "Fork failed\n");
            exit(-1);
        } else if (pid == 0) {
            /* child process, execute commands */
            int status = execvp(args[0], args);
            /* if error when executing then print error and exit*/
            if (status < 0) {
                printf("Command %s: command not found\n", args[0]);
                exit(-1);
            }
        } else {
            /*  parent waits if background is zero, else returns
                to setup()*/
            if (background == 0) {
                waitpid(pid, &retCode, 0);
            } 
        }   
    }
    
    return 0;
}
