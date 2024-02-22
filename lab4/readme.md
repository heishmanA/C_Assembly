Aaron Heishman
Lab 4 readme (For Stack)
Systems I


-------------------------------------------------------------------------- Instructions ----------------------------------------------------------------------------------------
                -   For this lab I modified things a bit


                -   main.c has been split into two separate mains to better test
                        -   lab4Stack.c - this contains the testing stuff required for the stack implementation
                        -   lab4Queue.c - like lab4Stack.c this just contains testing stuff required to test the queue implementation
                        -   I also added some changes to both files to print things out to help give an idea of what's going on during testing

                -   HOW TO USE AFTER COMPILING
                    -   I added command lind args so here is how you should run my program

                    -   $make -r                - this will create boith the lab4Stack and lab4Queue executable file, heads, tags and clean the *.o files
                    -   $make -r lab4Stack2     - for this you'll have to modify the flags at the bottom of the makefile, but this was used for profiling\
                    -   $make -r lab4Stack      - this will just make the lab4Stack executable file
                    -   $make -r lab4Queue      - this will just make the lab4Queue executable file
                    -   $lab4Stack [entry]      - this will run lab4Stack with the desired amount of entries as command line arguments have been implemented
                    -   $lab4Queue [entry]      - this will run lab4Queue with the desired amount of entries as command line arguments have been implemented

                    -   Note: I didn't really put checks in to make sure that non-positive integers are in, so break it if you want
                    -   Note: All the profiling output should have some rendition of 'lab4' + 'out' or 'lab4Stack2' + out