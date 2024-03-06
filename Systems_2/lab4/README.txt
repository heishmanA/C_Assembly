# Readme file for Lab 4 - Thread Parallelism
# Author: Aaron Heishman
# Date: 10/19/2023

How to compile using make at command line
-------------------------------

# Compile all
    make -r # Makes all tags, headers and compiles main
# compile individually
    make -r tags # make tags first
    make -r headers # make headers next
    make -r main # compile main last
# Clean *.o and *.vs files
    make -r clean

-------------------------------

How to run (at command line)
-------------------------------
    # Run the program like so replaced pthread count with any number ranging from 1 to 5
        main <pthread_count>
        # or
        ./main <pthread_count> 
    # Running the program with a pthread_count outside the range will produce an error
        Example : main 10345 
    # Running the program without an argument will also produce an error
        Example : main