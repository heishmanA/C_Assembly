/*  lab1.c file
    Aaron Heishman
    Systems II - Lab 1 Unix Shell
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "cmdlog.h"


int sig_flag = 0; /* signal flag for control c input*/
char *command_file_path; /* must be global as exitting the program is done in setup*/

/* Handles the <CTRL><C> input */
void handle_SIGINT() {
        sig_flag = 1;
        /* Signal was caught, print commands */
        print_commands();
}

/* setup() reads in the next command line string stored in inputBuffer,
separating it into distinct tokens using whitespace as delimiters.
setup() modifies the args parameter so that it holds pointers to the
null-terminated strings that are the tokens in the most recent user
command line as well as a NULL pointer, indicating the end of the
argument list, which comes after the string pointers that have been
assigned to args. */

void setup(char inputBuffer[], char *args[], int *background) {
    int free_inputBuffer = 0;
    char *token, *null_ptr = NULL;
    char delims[2] = " ";
    /* read input */
    int len = read(STDIN_FILENO, inputBuffer, MAX_LINE);
    /* Check for <CTRL><D>, <CTRL><C> or user input */
    if (sig_flag == 1) {
        return;
    } else if (len == 0) {
        if (command_file_path != NULL) {
            printf("Writing command file to: %s\n", command_file_path);
            try_write_file(command_file_path);
            free(command_file_path);
        }
        free_memory(); /* free memory before closing*/
        exit(0); /* ctrl+d entered */
    } else if (len < 0) {
        fprintf(stderr, "Error reading command\n");
        exit(-1);
    }
    
    /* remove the trailing newline */
    inputBuffer[len - 1] = '\0';
    if (get_command_count() >= 1 && check_input_buffer(inputBuffer) == 0) {
        int index = get_command_index(inputBuffer, len);
        if (index == -1) {
            printf("Error: %s not found in command history\n", inputBuffer);
            args[0] = null_ptr; // updates args to null so that the previous command cannot be run
            return;
        }
        /* replace the user input with a command from the history to be re-parsed*/
        inputBuffer = get_previous_command(index);
        free_inputBuffer = 1; /* need to free the input buffer after being parsed */
    }

    copy_input_to_history(inputBuffer);
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
    /* free the input buffer as strdup allocates memory */
    if (free_inputBuffer == 1) {
        free(inputBuffer);
    }
}

int main(void) {
    char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
    char *args[MAX_LINE+1];     /* command line arguments */
    int background;             /* equals 1 if a command is followed by '&' */
    pid_t pid;
    struct sigaction handler;
    memset(&handler, 0, sizeof(handler));
    handler.sa_handler = handle_SIGINT;
    sigaction(SIGINT, &handler, NULL);
    command_file_path = get_file_path();
    try_read_file(command_file_path);
    while (1) {
        background = 0;
        printf("Command->\n");
        setup(inputBuffer, args, &background);
        if (sig_flag == 0) {
            int retCode;
            int status;
            /* fork a new child based on user input */
            pid = fork(); /* create new process */
            if (pid < 0) {
                /* fork failed */
                fprintf(stderr, "Fork failed\n");
                exit(-1);
            } else if (pid == 0) {
                /* child process, execute commands */
                status = execvp(args[0], args);
                /* if error when executing then print error and exit*/
                if (status < 0) {
                    printf("Command %s: command not found\n", args[0]);
                    exit(status);
                }
            } else {
                /*  parent waits if background is zero, else returns
                    to setup()*/
                if (background == 0) {
                    waitpid(pid, &retCode, 0);
                }
                int i = 0;
                /* Free args*/
                while (args[i] != NULL) {
                    free(args[i]);
                    i++;
                }
            }
        } else {
            sigaction(SIGINT, &handler, NULL); // reinstall signal to prevent double press of ctrl+c from closing program
            sig_flag = 0;
        }
    }
    return 0;
}
