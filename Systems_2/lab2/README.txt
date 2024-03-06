# Aaron Heishman
# Readme File
# CSE 2431 Lab 2


    

How to build with makefile:
    # compile all (main, clean, tags)
        - [user]$make -r
    # compile just main and headers
        - [user]$make -r main

Note:
    Two changes were made to my header.sh to allow for proper compilation
        - The first change was an update to concatenate directives into buffer.h as they were being overwritten
        - The second change was that I had to change < cat $f >> filename > to < sed 's/ {//g' $f >> $filename > to prevent the parsing from including the the ' {'
            - Note: If there is an issue here just simply remove the space that separates the '/' and '{' in sed
            - I added the space as the new concatentation of my function in the header would place a space between the function name and semi colon

How to build without makefile:
    [user]$ gcc -g3 -std=gnu11 -Wall -pedantic -Wextra -c main.c -o main.o
    [user]$ gcc -g -o main main.o buffer.c -lpthread -lrt

How to use:
    # Main requires three arguments. 
    # The first argument s the time the main file should sleep [an integer between 1 and 10]
    # The second is how many producer threads there should be [an integer between 1 and 5]
    # The third is how many consumer threads there should be [an integer between 1 and 5]
    # In the example given below 10 is entered for the sleep time, 5 is entered for the number of producers
    # and 5 is entered for the number of consumers
    [user] ./main 10 5 5 