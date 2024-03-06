Programmer: Aaron Heishman
Class: Systems I
Date: 10/11/2023
Readme for Lab 3 (Not lab1)

How to compile using make file or command line
----------------
Note: Change tags: *.c from ctags -R to etags -R in the makefile if you do not use vim.

# For some reason tags was not being created for me using make -r before submission
# To guarantee that the makefile will work correctly please use make in the following order
[1] make -r tags
[2] make -r headers
[3] make -r 

# After tags/headers are made then it should work. 

How to run
-----------
[1] $shell
or
[2] $./shell

How to use: Note: Program outputs "Command->" in shell then expects input
----------
[1]$Command->command # replace command with the desired command you wish to run
[2]$$Command-><CTRL><C> # pressing CTRL+C prints out the last 10 commands entered
[3]$Command->r  # simply typing 'r' will run the most recent command entered. includes any commands that did not work as well
[4]$Command->r 'x' # runs the first command in the command history that replaces 'x'
[5]<CTRL><D> # exit the program

Note 
-----------
Added extra functions to my makefile 
[1] $make -r clean 	- Cleans *.o and *.vs files [i use vscode ssh when writing code so .vs files get made when compiling]
[2] $make -r zip	- Zips the lab files
