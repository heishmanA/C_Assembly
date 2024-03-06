Programmer: Aaron Heishman
Class: Systems I
Date: 9/1/2023

How to compile 
----------------
Note: Change tags: *.c from ctags -R to etags -R in the makefile if you do not use vim.

[1] $make -r - compile all
[2] %make -r shell.c
[3] gcc -g shell.c -p [program_name] - does not include flags and warns


How to run
-----------
[1] $mysh
[2] $./mysh


Note 
-----------
Added extra functions to my makefile 
[1] $make -r clean 	- Cleans *.o and *.vs files [i use vscode ssh when writing code so .vs files get made when compiling]
[2] $make -r zip	- Zips the lab files
