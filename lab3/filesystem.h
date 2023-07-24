/* file system */

#ifndef __FILE_SYSTEM_H
#define __FILE_SYSTEM_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Supplementary file struct to contain file information of a directory 
 * @member *name - character pointer that pointers to the address of the file name
 * @member content - character array containing the content of the file*/
struct File {
    char name[30];
    char content[256];
};

/* "Tree" style directory struct
 * @member name - character pointer that points to the address of the directory name
 * @member size - the total size of the directory (includes subdirectory and files)
 * @member f_last - the total amount of files in the directory
 * @member *parent - tree pointer that points to the address of the directory's parent
 * @member files - a collection of the directory's files
 * @member *next_dir - tree pointer that points to the address of the next sibling
 * @member *prev_dir - tree pointer that points to the address of the the previous sibling
 * @member *children - tree pointer that points to the address of the first child
 */
typedef struct Tree {
    char name[33];
    int size;
    int f_length;
    struct Tree *parent;
    struct File files[64];
    struct Tree *next_dir;
    struct Tree *prev_dir;
    struct Tree *children;
}   Tree;

/* Creates and returns a new directory with the given name, and parent pointer 
 * @param parent - the parent of the directory being made
 * @param dir_name - the name of the directory
 * @prog_name - the specific program name in case malloc fails
 * @returns - a new directory pointer with the parent pointer pointing at the parent directory
 *            that the directory is created in or NULL if malloc cannot write to memory 
 * @requires - dir_name != '\0'
 */
Tree *mkdir(Tree *parent, char *dir_name, char *prog_name);

/* prints the current working directories file names and subfolder names 
 * @param *wd - a Tree pointer pointing to the current working directory
 * @requires *wd != NULL 
 * */
void ls(Tree *wd);
/* Frees the memory of all the directories created by malloc
 * @param **root - Tree pointer to Tree pointer that points at the root directory
 * requires **root != NULL
 */
void free_memory(Tree **root);

/* Prints the current working directory path
 * @param *wd_ptr - Tree pointer to the current working directory
 * @param *wd_name - Character pointer pointing at the address of the
 *                  name of the current working directory 
 */
void pwd(Tree *wd_ptr, char *wd_name);

/* Changes the working directory to a new directory
 * @param - **wd_ptr - Tree pointer to Tree pointer that points at the directory to change
 * @param - *dir_name - Character pointer that points at the name of the directory to change to
 * @returns - -1 if directory is not found, 0 otherwise
 */
int cd(Tree **wd_ptr, char *dir_name);

/* Removes the specified subdirectory from the current working directory 
 * @param **wd_children - Tree pointer to Tree pointer that is pointing at the first child
 *                        of the parent directory
 * @param *target_name - Character pointer that points at the address of the directory to remove
 * @returns - -1 if file not found, 0 otherwise 
 */
int rmdir(Tree **wd_children, char *target_name);

/* inserts the given directory at the end of the list of children
 * @param **children_ptr - The list of children of the parent directory
 * @param *new_dir - the new directory to add to the list of children
 */
void insert(Tree **children_ptr, Tree *new_dir);

/* Finds duplicate file names 
 * @param *children - the children to search for duplicates in
 * @param *name - the name of the directory
 * @reeturns -1 if duplicate is not found, 0 otherwise
 */
int find_duplicates(Tree *children, char *name);

/* Moves a directory to a new directory or renames and moves the directory if specified
 * @param **wd - the current working directory the file is removed from
 * @param *destination - the name of the directory to move to
 * @param char *rename (optional) - the new name of the file if specified
 * @returns -1 if file not found, -2 if destination not found, -3 if dir already exists
 *          0 otherwise
 * @requires wd != NULL && target != '\0' && destination != '\0'
 */
int mv(Tree **wd, char *target, char *destination, char *rename);

/* Reads the contents of the specified file
 * @param wd - the current working directory the file is in
 * @param file_name - the file to be read
 * @returns -1 if the file cannot be found
 * @requires wd != NULL && file_name != '\0'
 */
int cat(Tree *wd, char *file_name);

/* Creates a new file if the given file is not found, overwrites the file if it can be
 * @param **wd - the working directory
 * @param *file_name - the new file to be created, or file to be overwritten
 * @returns -1 if file_name is NULL (gonna remove)
 * @requires file_name != '0'
 */
int file(Tree **wd, char *file_name);

/* Copies the given file from the given working directory to the new directory, renames the file
 * if specified
 * @param *wd - the current working directory
 * @param *source - the specific file to be copied
 * @param *destination - the new directory to move the file to
 * @param *new_name (optional) - the new name of the file
 * @returns -1 if source can't be found, -2 if destination can't be found, 0 otherwise
 * @requires *wd != NULL && *source != '\0' && *destination != NULL
 */
int cp(Tree *wd, char *source, Tree *destination, char *new_name);

/* Removes the specified file from the list of files in the directory
 * @param **wd - the current working directory
 * @param *source - the target file to be removed
 * @returns -1 if the file can't be found, 0 otherwise
 * @requires **wd != NULL
 */
int rm(Tree **wd, char *source);

/* finds and returns the index of the specified file
 * @param *wd - the current working directory
 * @param *source - the name of the target file to be removed
 * @requires *wd != NULL
 * @returns -1 if source can't be found, 0 other wise
 */
int find_file(Tree *wd, char *source);

/* prints the current working directory path up to the root, including any siblings 
 * @param *wd - tree pointer to current working directory
 * @param *wd_name - char pointer to current working directory name
 * */

void dir_print(Tree *wd, char *wd_name);

/* Prints the working directory path backwards 
 * @member wd - the current working directory 
 */
void dwp(Tree *wd);

/* Changes the root name to the specified name by the user
 * @param *root - Tree pointer pointing at the current working directory
 * @param *new_name - the new name to change root to
 */
void ch_root(Tree *root, char *new_name);


/* USE WITH CAUTION. This deletes every single folder that is a child of the current 
 * working director and the contents within them. Does not remove the files of the current wd that called the command though.
 * Cannot be used on the root directory, so do not worry about that.
 * @param **wd - p2p at the working directory
 * @param *wd_name - char pointer pointing at name of the working directory so it doesn't get obliterated
 */
void obliterate(Tree **wd, char *wd_name);

/* creates "dummy files" of the specified path as the children of root 
 * @param **wd - p2p at the root folder 
 * @param *path - the path specified in the arguments 
 */
int dirrent_f(Tree **wd, char *path);

/* Calls the specific function based on the {@code x}
 * @param x - the value representing the specific function to call
 * @param *args - the user arguments
 * @param **wd - the current working directory
 * @param *prog_name - the name of the program incase malloc fails
 * returns -1 if the user wants to quit, >=0 otherwise 
 */
int call_function(int x, char *arg[], Tree **wd, char *prog_name);

/* Prints all available commands to the user input */
void print_help();

#endif

