# Aaron Heishman
# Makefile for lab 3

#change the last dependency for each new lab
all:  tags headers lab4Stack lab4Queue clean 
# this entry has to change for lab 2 - 4
# NEVER compile .c files with this rule - it lacks needed compile time flags
# There is an entry below that turns .c files into .o files


# HF = header functions
Stack = stack1.c stack2.c
Queue = queue1.c queue2.c
Header = lab4.h
Mains = lab4Stack lab4Queue
#Target
lab4Stack: $(Stack) lab4Stack.o
	gcc -g -o $@ $^

lab4Queue: $(Queue) lab4Queue.o
	gcc -g -o $@ $^

lab4Stack2: $(Stack) lab4Stack.o
	gcc -O -pg -o $@ $^
	  
#this entry stays for C code labs
tags: *.c
	ctags -R .

# this entry stays for C code labs
headers: *.c tags
	headers.sh


# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c lab4.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@

# clean up
clean:
	rm *.o 
