/* Copyright (C) 2023 Aaron Heishman */

#define MAX_LINE 80

#define HISTORY_SIZE 10

/* Auto-generated */

int check_input_buffer(char inputBuffer[]);
void copy_input_to_history(char inputBuffer[]);
void free_memory();
int get_command_count();
int get_command_index(char *input, int len);
char *get_file_path();
char *get_previous_command(int index);
void print_commands();
void try_read_file(char *path);
void try_write_file(char *path);
