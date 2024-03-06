/*  cmd log file
    Aaron Heishman
    Systems I
    Lab 5*/
#include "cmdlog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

/* Globals for recoding command history */
char *command_history[HISTORY_SIZE];
int front_command_index = 0;
int next_command_index = 0;
int command_count = 0;

/* Get the current command count*/
int get_command_count() {
    return command_count;
}

/* Check the input buffer in case the user wants to rerun a command
   Note: as I wrote my own parser, I have to look for '\0' here
   returns 0 if user wants to execute a command from the command history
   -1 otherwise*/
int check_input_buffer(char inputBuffer[]) {
    if (inputBuffer[0] == 'r' && (inputBuffer[1] == ' ' ||  inputBuffer[1] == '\0')) {
        return 0;
    }
    return -1;
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
        /* search through command history and return the index at which the command can be found if it exists in the history*/
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
        printf("[%i]: %s\n", (count_start+=1), command_history[front_index_copy]);
        front_index_copy = (front_index_copy + 1) % HISTORY_SIZE;
        i++;
    }
    fflush(stdout);
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
    command_count++;
}

/* Swaps input buffer with the new command  */
char *get_previous_command(int index) {
    char *previous_command = strdup(command_history[index]);
    return previous_command;
}


/* Frees the memory allocated for the command history */
void free_memory() {
    int i = 0;
    /*free memory allocated by strdup before closing*/
    while (command_history[i] != NULL && i < command_count) {
          free(command_history[i]);
          i++;
    }
}

/*  build the file path of the history file as we 
    won't know what the user name is upon runtime */
char *get_file_path() {
    char *prefix = "./";
    char *user_name = getlogin();
    char *suffix = ".history";
    int length = strlen(user_name) + strlen(prefix) + strlen(suffix);
    char *path = (char*)malloc(length + 1);
    strcpy(path, prefix);
    strcat(path, user_name);
    strcat(path, suffix);
    return path;
}

/*  Try to read the command file, return if file does not
    exist */
void try_read_file(char *path) {
    /* check if the file exists, return if it doesn't */
    if (access(path, F_OK) < 0) {
        return;
    }
    
    /* try to open the file if it exists*/
    int fd = open(path, O_RDONLY);
    assert(fd >= 0);
    
    /* setup for parsing file */
    char delims[3] = ",\n\0";
    char buffer[MAX_LINE+1];
    char *token;
    
    /* read file */
    int len = read(fd, buffer, MAX_LINE);
    assert(len >= 0);

    // return if the file exists, but is empty
    if (buffer[0] == '\n' || buffer[0] == '\0') { return; }
    
    /* parse input buffer into separate commands and add to the command history */
    
    token = strtok(buffer, delims);
    while (token != NULL && next_command_index < HISTORY_SIZE) {
        command_history[next_command_index] = strdup(token); // duplicate token
        next_command_index = (next_command_index + 1) % HISTORY_SIZE; // update next index
        command_count++; // track commands read in
        token = strtok(NULL, delims);
    }
  
    assert(close(fd) == 0);
}

/*  try to write to the history file
    if file does not exist then create file and try
    to write command history */
void try_write_file(char *path) { 
    /*  try to open the file for writing with the following
        O_CREATE - create file if it it doesnt exist
        O_WRONLY - write only
        O_TRUCT - truncate contents of previous file 
        S_IRWXU - give user the rights to read, open, edit
        */
    int fd = open(path, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    assert (fd >= 0);
    int i = 0;
    char *new_line = "\n";
    if (command_count >= 10) {
        command_count = 10;
    }
    /*  write each command in the command history
        to the file separating each command by a comma
        and ending with a newline separator*/
    while (i < command_count) {
        char *buffer = command_history[front_command_index];
        char *delim = ",";
        /* place commas between each command */
        if (i < command_count - 1) {
            strcat(buffer, delim);
        }
        int len = strlen(buffer);
        write(fd, buffer, len);
        i++;
        front_command_index = (front_command_index + 1) % HISTORY_SIZE;
    }
    /* Add newline to the end of the file*/
    write(fd, new_line, strlen(new_line));
    assert(close(fd) == 0);
}
