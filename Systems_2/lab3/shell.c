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
#include <signal.h>

#define MAX_LINE 80
#define HISTORY_SIZE 10 /* total amount of commands in the buffer at one time is 10 */
/* Globals for tracking command history */
char *command_history[HISTORY_SIZE];
int front_command_index = 0, next_command_index = 0;
int command_count = 0, sig_flag = 0;

/* Prints the last 10 commands entered by the user if <CTRL><D> is pressed */
void print_commands() {
    printf("\nPrinting command history..\n");
    int i = 0, front_index_copy = front_command_index;
    /*  Get the difference between the start and end of the command history 
        as they both will move */
    int diff = abs(front_command_index - next_command_index);
    if (diff == 0 && command_count > 1) {
        diff = 10;
    }
    int count_start = (command_count - diff);
    /* print the commands with the specific command count */
    while (i < diff) {
        printf("[%i]: %s\n", (count_start + i), command_history[front_index_copy]);
        front_index_copy = (front_index_copy + 1) % HISTORY_SIZE;
        i++;
    }
}

/* Handles the <CTRL><C> input */
void handle_SIGINT() {
        sig_flag = 1;
        /* Signal was caught, print commands and reset signal flag*/
        print_commands();
       
}

/* Gets the index of a previously entered command from the command history. Returns -1 if command cannot be found .*/
int get_command_index(char *input, int len) {
    int index = -1;
    /* Return the most recent command index if r is entered, else search through the command history for the desired command */
    if (len == 2) {
        /* The next command index increments to the next spot it has to write to. Need the index of the command behind that one */
        index = (next_command_index - 1 + HISTORY_SIZE) % HISTORY_SIZE; 
    } else {
        char user_command_letter = input[2];
        char *command_string; 
        int i = 0;
        while (command_history[i] != NULL) {
            command_string = command_history[i];
            if (command_string[0] == user_command_letter) {
                return i; // return the index of the specific command 
            }
            i++;
        }
    }
    return index;
}

/* Copies the user command into the command history array*/
void copy_input_to_history(char inputBuffer[]) {
    /* free the memory allocated to hold the previous command, and update the front */
    if (command_count > 0 && next_command_index == front_command_index) {
        free(command_history[front_command_index]);
        front_command_index = (front_command_index + 1) % HISTORY_SIZE;
    }
    /* Duplicate the following command and place into command history */
    command_history[next_command_index] = strdup(inputBuffer);
    next_command_index = (next_command_index + 1) % HISTORY_SIZE;
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
        if (command_count > 0) {
            int i = 0;
            /*free memory allocated by strdup before closing*/
            while (command_history[i] != NULL) {
                free(command_history[i]);
                i++;
            }
        }
        exit(0); /* ctrl+d entered */
    } else if (len < 0) {
        fprintf(stderr, "Error reading command\n");
        exit(-1);
    }
    
    /* remove the trailing newline */
    inputBuffer[len - 1] = '\0';
    /* Note: as I wrote my own parser, I have to look for '\0' here*/
    if (inputBuffer[0] == 'r' && (inputBuffer[1] == ' ' || inputBuffer[1] == '\0') && command_count >= 1) {
        int index = get_command_index(inputBuffer, len);
        if (index == -1) {
            printf("Error: %s not found in command history\n", inputBuffer);
            args[0] = null_ptr; // updates args to null so that the previous command cannot be run
            return;
        }
        /* replace the user input with a command from the history to be re-parsed*/
        inputBuffer = strdup(command_history[index]);
        free_inputBuffer = 1; /* need to free the input buffer after being parsed */
    }
    copy_input_to_history(inputBuffer);
    command_count++; 
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
    /* */
    if (free_inputBuffer == 1) {
        free(inputBuffer);
    }
}

int main(void) {
    char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
    int background;             /* equals 1 if a command is followed by '&' */
    char *args[MAX_LINE+1];     /* command line arguments */
    pid_t pid;
    struct sigaction handler;
    handler.sa_handler = handle_SIGINT;
    sigaction(SIGINT, &handler, NULL);
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
