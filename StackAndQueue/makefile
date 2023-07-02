# Aaron Heishman
# makefile specifically meant for queue_main/stack_main

# All command
all:  stack_main queue_main clean 

# all files
Stack = stack1.c stack2.c
Queue = queue1.c queue2.c
Mains = stack_main.c queue_main.c

#target to create the stack exe
stack_main: $(Stack) stack_main.o
	gcc -g -o $@ $^
# target to create the queue exe
queue_main: $(Queue) queue_main.o
	gcc -g -o $@ $^


# this will take care of the header files
%.o:%.c stack_queue.h
	gcc -ansi -Wpedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@

# clean up
clean:
	del *.o 
