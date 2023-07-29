/* help.c file */

#include "filesystem.h"

void print_help() {
    printf("cd      - changes working to directory to desired directory\n");
    printf("ls      - lists contents of the current working directory\n");
    printf("pwd     - print the current working directory path\n");
    printf("cat     - reads the contents of the specified file\n");
    printf("cp      - copies and/or renames a file to the given directory\n");
    printf("mv      - moves and/or renames a directory to");
    printf(" the specified directory\n");
    printf("rm      - removes the specified file from the");
    printf(" current working directory\n");
    printf("mkdir   - creates a directory in the current working directory,");
    printf(" parent directory, or specified directory\n");
    printf("rmdir   - removes a specified directory from the current");
    printf(" working directory\n");
    printf("file    - opens the text editor to create a new file,"); 
    printf(" or overwrite a current file\n");
    printf("help    - lists the user commands\n");
    printf("dirp    - lists all files and folder names from the");
    printf(" current working directory path to the root \n");
    printf("dwp     - Prints current working directory path in reverse order\n");
    printf("cr      - use this to change the name of your root directory\n");
    printf("ob      - CAUTION - this command deletes every subdirectory of\n");
    printf(" the current working directory.\n");
}
