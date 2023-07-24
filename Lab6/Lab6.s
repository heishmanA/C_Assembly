# Lab6.s file
# Aaron Heishman
# Sysmtes I - Lab 6
# 7/17/2023
.file "Lab6.s"
.section .rodata # read only

#################################################################
#   Eeach string corresponds to a different test case           #
#   You can simply replace any of the strings in here           #
#   without worrying about changing any other values in the code#
#   If you'd like to add more string then make sure you         #
#   create a label (.S6 maybe?) and then add that to the        #
#   .str array [line 50] so that the program will use it        #
#   and make sure to update the immediate value on line 73      #
#################################################################
.S1:
    .string "I'm a big fan of small word. No like big word or good grammaer. Grammary too hard."

.S2:
    .string "I really hate how nice the weather is getting."

.S3:
    .string "What"

.S4:
    .string "Amazing, isn't it? With just the slighest touch the material wraps around the skin effortlessly"

.S5:
    .string "Mmm, ice cream so good!"

.fs_short_string:
    .string "The shortest string is: '%s'\n"
.fs_short_word:
    .string "The string with the shortest word count is: '%s' | The word count is: %d\n"

.global main
    .type main, @function

.section .data
.align 8

#########################################################
#   THIS ARRAY IS MEANT TO HOLD THE ADDRESSES OF EACH   #
#     STRING IN .RODATA. IF YOU ADD/REMOVE A STRING     #
#     THEN BE SURE TO ADD THE LABEL INTO THIS ARRAY     #
#     AND UPDATE LINE 73 IN MAIN TO MATCH THE NEW       #
#       FINAL INDEX VALUE TO WORK PROPERLY              #
#########################################################
.str_array:
    .quad .S1   # Pointer to first string
    .quad .S2   # Pointer to second string
    .quad .S3   # pointer to third string
    .quad .S4   # pointer to fourth string
    .quad .S5   # pointer to fifth string

.text
main:
    # stack setup
    pushq   %rbp
    movq    %rsp, %rbp
    # Check Args
    cmpq    $1, %rdi                # check if there are command line arguments other than the program name
    jg      .main_print_alignment_info   # jump if greater than (argument count > 0)
# if argc == then no arguments - Get the string with the shortest length first
.main_count_length:
    movq    $.str_array, %rdi       # move the address of the array into the first param register
    #####################################
    #   CHANGE THE NUMBER ON LINE 73    #
    #    IF YOU REMOVED OR ADDED        #
    #           TO THE ARRAY            #
    #####################################
    movq    $4, %rsi                # Accounts for the final index 
    pushq   %rsi                    # save the index value to be used for later
    pushq   %rdi                    # save the address of the array
    call    get_shortest_string     # call function to get the shortest string
    movq    %rax, %rsi              # move string returned by get_shortest_string into second param
    movq    $.fs_short_string, %rdi # move format string specifier into first param
    xorq    %rax, %rax              # zero rax
    call    printf                  # print to console the shortest string
    popq    %rdi                    # restore array to have original array in rdi
    popq    %rsi                    # restore index to have original index in rsi

# Get the string with the least word count next
.main_count_words:
    call    get_word_count          # call function to get the string with the shortest word count
    movq    $.fs_short_word, %rdi   # move the format specifier to parameter 1
    movq    (%rax), %rsi            # move the string with the shortest word count to the second parameter
    movq    8(%rax), %rdx           # move the string's word count into the third parameter
    xorq    %rax, %rax              # zero return
    call    printf                  # print
    jmp     .main_exit              # exit
    
# jump here if command line arguments have been entered
.main_print_alignment_info:
    #####################################################
    #           # Register info                         #
    #      RDI contains the argument count              #
    #      RSI contains the array for arguments         #
    #      call get_struct_alignment to print the       #
    #          "alignment info"                         #
    #####################################################
    call get_struct_alignment
.main_exit:
    xorq     %rax, %rax             # zero out rax for a successful run
    leave
    ret
.size main, .-main


.global get_shortest_string
    .type get_shortest_string, @function

.text

# Iterate through the array in %rdi to find which string is the shortest
get_shortest_string:
    # stack setup
    pushq   %rbp
    movq    %rsp, %rbp
    pushq   %r15    # save the only callee saved register used
    #################################################################
    #                   REGISTER VALUES                             #
    #       %rdi -  Holds the address to the array of               #
    #               addresses to the string arrays                  #
    #       %rsi - Holds the final index of the array in rdi        #
    #################################################################

    # get the length of the last string and declare it as the "shortest"
    pushq   %rdi        # save the array address in %rdi
    movq    (%rdi, %rsi, 8), %rdi   # move the string located at %rsi (index) to %rdi
    call    strlen      # get the length of the string
    movq    %rax, %r15  # move the length of the string into %r15
    popq    %rdi        # restore the array
    movq    (%rdi, %rsi, 8), %rax # store assumed shortest string in return

    # compare the rest of the string lengths to the current "shortest" string
.get_shortest_loop:
    decq    %rsi        # decrement the count by 1
    jl      .ss_exit    # jump to exit if count < 0
    pushq   %rdi        # save array
    pushq   %rax        # save current shortest string
    movq    (%rdi, %rsi, 8), %rdi   # move next string to %rdi
    call    strlen      # get the next string length
    movq    %rax, %rdx  # move strlen to rdx
    popq    %rax        # restore shortest string
    popq    %rdi        # restore array of strings
    cmpq    %r15, %rdx  # compare the length of the current shortest string with the new string
    cmovl   %rdx, %r15  # if the current shortest string is larger than the new one, update current shortest string
    cmovl   (%rdi, %rsi, 8), %rax # move the smallest string to return if rdx < r15
    jmp     .get_shortest_loop  # loop

.ss_exit:   # shortest string is in %rax, restore rbp/rsp and and return
    popq    %r15        # restore the original value of %r15
    leave
    ret
.size get_shortest_string, .-get_shortest_string

# Counts the strings given in %rsi to find the string that has the smallest word count
# returns the original array with index 0 and 1 having been modified to hold
# the string with the shortest wordcount at pos 0, and that string's word count in pos 1
.global get_word_count
    .type get_word_count, @function
.text
get_word_count:
    # stack setup
    pushq   %rbp
    movq    %rsp, %rbp
    #################################################################
    #       REGISTER VALUES                                         #
    #       %rdi - holds the array with the strings to count        #
    #       %rsi - Holds the final index value                      #
    #################################################################
    movq    $0xFFFFFFFFFFF, %r8  # %r8 will hold the word count of the string
    movq    (%rdi, %rsi, 8), %r9 # %r9 will hold the string with the least word count [assuming last string is shortest]

# save the original value of %rbx and %r12 
    pushq   %rbx
    pushq   %r12
# FIrst get the string, then find the string with the smallest word count
    .get_word:
        movq    (%rdi, %rsi, 8), %r12   # move strings to %rbx
        xorq    %r10, %r10              # %r10 will be used to iterate through the string 
        xorq    %r11, %r11              # using %r11 to track the previous character
        xorq    %rdx, %rdx              # used to keep track of the current word count of the string    
        .count_words:
            movzbq  (%r12, %r10, 1), %rcx   # move - zero extend - byte to quad the first character to %rcx
            cmpq    $0x21, %rcx             # compare current character : 0x21 (lower boundary)
            setge   %al                     # set lower byte of %rax to 1 if within range, 0 otherwise
            cmpq    $0xFF, %rcx             # compare current character : 0xFF (upper boundary)
            setle   %bl                     # set lower byte of rbx to 1 if within range, 0 otherwise
            andq    %rbx, %rax              # and %rax and %rbx, if both are within range then will be 1, store in rax
            cmpq    %r11, %rax              # compare rax with r11 
            setg    %bl                     # set lower byte of %rbx to 1 if %rax is 1 and r11 is 0
            addq    %rbx, %rdx              # add the value to %rdx which will track the word count of the string
            movq    %rax, %r11              # result of previous word moved to %r11
            incq    %r10                    # increment count
            cmpq    $0x0, %rcx              # compare the character that was just read to null byte character
            jne     .count_words            # jump if not equal (%rcx != '\0')

    # compare the word count of the previous string to the word count of the current string    
    cmpq    %r8, %rdx       # compare %r8 : %rdx
    cmovl   %rdx, %r8       # if %rdx < %r8 move smaller word count to %r8
    cmovl   %r12, %r9       # if %rdx < %r8 move the smaller string into %r9
    decq    %rsi
    jg      .get_word       # loop if rsi >= 0

    .get_word_count_exit:
        movq    $0, %rsi  # move 0 into rsi
        movq    %r9, (%rdi, %rsi, 8) # move the string with the shortest word count into the index 0 of the array in %rsi
        incq    %rsi                 # increment rsi by one
        movq    %r8, (%rdi, %rsi, 8) # move the word count into the second index of the array in %rdi
        movq    %rdi, %rax           # move the array back into %rax to return to main
        popq    %r12    # restore called saved register
        popq    %rbx    # restore caller saved register
        leave
        ret
.size get_word_count, .-get_word_count

# Parses the the arguments given by the user
# printing the specific alignment information
# as if it were a struct
.global get_struct_alignment
    .type get_struct_alignment, @function
# Read only data for array
.section .rodata 
.align 8 # start on an 8 byte address

# Contains each primitive data type from c
# where each string is aligned on an 8 byte address
.data_types: 
    .align 8
    .string "char"   # 0
    .align 8
    .string "short"  # 8
    .align 8
    .string "int"    # 16
    .align 8
    .string "float"   # 24
    .align 8
    .string "double" # 32
    .align 8
    .string "long"  # 40

# Contains the respective size of each data type
# located in .data_types
.data_sizes:
    .byte 0x01        # 1
    .byte 0x02        # 2
    .byte 0x04        # 4
    .byte 0x04        # 4
    .byte 0x08        # 8
    .byte 0x08        # 8
    
.text
get_struct_alignment:
    # stack housekeeping
    pushq   %rbp
    movq    %rsp, %rbp
    #################################################################
    #       REGISTER VALUES                                         #
    #       %rdi - Holds argument count                             #
    #       %rsi - holds the argument array                         #
    #################################################################

    # Allocate memory for an array that will hold the data types
    pushq   %rdi    # save the argument count 
    pushq   %rsi    # save the array values
    call    malloc  # create array - %rsi = malloc(argc * sizeof(char))
                    # rax contains the address for the dynamically allocated array
    popq    %rsi    # restore the array
    popq    %rdi    # restore the argument count

    # callee saved register setup
    pushq   %r15    ##########################################################################
    pushq   %r14    #  Not exactly needed, but saving all values caller saved registers used #
    pushq   %r13    #  In both this function and the child function called by this function  #
    pushq   %r12    #  primarily for building better habits                                  #
    pushq   %rbx    ##########################################################################
    movq    $.data_types, %r15  # move the data_types array into %r15 
    movq    $.data_sizes, %r14  # move the data_sizes array into %r14
    movq    %rax, %r13          # store the array that will hold data sizes in it 
    movq    $1, %r12            # store one in %r12 to be used to get the argument values from argv

    #  caller saved register suetup 
    xorq    %r11, %r11          # zero out %r11 - this will keep track of where to place values into the array in %r13
    xorq    %r10, %r10          # zero out %r10 as it will be used to keep track of the largest data type size
    
    # iterate through the arguments to get each value starting from 1 and ending at argcount
    .get_arguments:
        cmpq    %r12, %rdi  # compare %rdi : %r12 (current count < argcount)
        je      .exit       # jump if equal to (%r12 == argcount) print the values
        # save caller saved registers 
        pushq   %r10    
        pushq   %r11
        pushq   %r15   # saving original value to reset %r15 back to base address when popped
        pushq   %rdi    
        pushq   %rsi    

        # set up the registers for comparing
        movq    (%rsi, %r12, 8), %rdi # move each element of argv into %rdi
        movq    $0, %rcx    # used for pulling values out of .data_type array
        movq    $0, %r9     # used for pulling values from .data_sizes array

        # compare data types to find out which data types the user entered
        .compare_types:
            # save the other caller saved registers before calling strcmp
            pushq   %rcx
            pushq   %r9
            # compare strings
            movq   %r15, %rsi    # move value from .data_types to %rsi
            call   strcmp  # compare the argument with a data type
            # restore caller saved registers
            popq    %r9
            popq    %rcx
            # check if strings were equal
            cmpq    $0, %rax    # compare 0 to rax, if rax == 0 then match found
            je      .next       # jump if equal to (rax == 0)

            # strings weren't equal, move to the next data type
            addq    $8, %rcx    # add 8 to %r10 to get the value from data type if rax != 0
            incq    %r9         # increment r9 if rax != 0 to make sure the correct value is grabbed
            addq    $8, %r15    # add 8 to %r18 to get the next data type
            jmp     .compare_types # jump back to compare types - as long as the values entered are correct an inf loop won't happen
    # .next processes the end result
    .next:
        # restore the rest of the caller saved registers and %r15
        popq    %rsi
        popq    %rdi
        popq    %r15    # restore %r15 back to base address
        popq    %r11
        popq    %r10
        # get largest size - store in r10
        # get the data type size - store in r13
        movzbq  (%r14, %r9, 1), %r8 # move each data type size to %r8
        cmpq    %r8, %r10   # compare %r10 : %r8
        cmovl   %r8, %r10   # if %r10 < %r8 , move the value of %r8 to %r10 to update max size
        movb    %r8b, (%r13, %r11, 1)   # move the size of the data type into position in %r13
        incq    %r11    # increment %r11 by one
        incq    %r12    # increment %r12 by one
        jmp     .get_arguments  # jump up to get arguments when done


.exit:
    movq    %r13, %rdx  # move the array containing individual sizes into 3rd parameter
    movq    %r10, %rcx  # move the max size of the array to the 4th parameter(this is how the struct is alligned)
    call    print_alignment_info    # print the alignment info
    # free %r13 before leaving
    movq    %r13, %rdi  # move the address of the allocated memory to %rdi
    call    free        # free the allocated memory
    xorq    %r13, %r13  # zero out %r13
    # restore callee saved registers
    popq    %rbx
    popq    %r12
    popq    %r13
    popq    %r14
    popq    %r15
    leave
    ret
.size get_struct_alignment, .-get_struct_alignment

.section .rodata

# Prints the alignment info of the specified data type sent in
.global print_alignment_info
    .type print_alignment_info, @function

.section .rodata
.opening_message:
    .string "The struct contains the following sizes and members\n"
.data_type_string:
    .string "%d bytes for %s\n"
.spacing_string:
    .string "%d bytes for spacing\n"
.closing_message:
    .string "The total size of the struct is %d bytes with an alignent of %d bytes\n"

.text
print_alignment_info:
    # stack setup
    pushq   %rbp
    movq    %rsp, %rbp
    #################################################################
    #       REGISTER VALUES                                         #
    #       %rdi - Holds argument count                             #
    #       %rsi - holds the argument array                         #
    #       %rdx - holds the array that has the individual sizes    #
    #       %rcx - Holds the largest data type                      #
    #################################################################

    # moving each value to calee saved register for printf purposes
    movq    %rdi, %r15  # argument count
    movq    %rsi, %r14  # array containing data types (CLI Args)
    movq    %rdx, %r13  # array containing the individual sizes of data types
    movq    %rcx, %r12  # the largest data type / alignment
    movq    $0, %rbx    # used as an index to get values from the arrays
    
    # print opening message
    movq    $.opening_message, %rdi
    xorq    %rax, %rax
    call    printf
    # caller saved registers
    movq    $0, %r9            # r9 will be the temporary "address" for alignment purposes, start at 0

    # Loop through the arguments and string containing data types
    # to print the proper alignment information in order
    .print_data_sizes:
        movzbq  (%r13, %rbx, 1), %rsi # move data type size to second parameter
        cmpq    $0, %rsi            # array in %r13 is null terminated, compare %rsi : 0
        je      .check_end_padding  # if rsi == 0 then check if anymore padding is required and exit
        incq    %rbx                # increment rbx by one
        addq    %rsi, %r9           # add the data type size to %r9
        movq    (%r14, %rbx, 8), %rdx       # move the data type name into the third parameter
        movq    $.data_type_string, %rdi    # move the formatted string to the first parameter
        xorq    %rax, %rax          # zero out return
        pushq   %r9                 # save total size before print
        call    printf              # print 
        popq    %r9                 # restore total size

    .check_alignment:
        # check if padding is required before printing next character
        movzbq  (%r13, %rbx, 1), %rsi # move the next size into rbx (dividend)
        cmpq    $0, %rsi              # array in %r13 is null terminated, compare %rsi : 0
        je      .check_end_padding    # if rsi == 0, then exit
        pushq   %rbx                  # save the count
        movq    %rsi, %rbx            # move current data type size into rbx (dividend)
        movq    %r9, %rax             # move total struct size into rax (divisor)
        xorq    %rdx, %rdx            # zero out rdx for remainder
        divq    %rbx                  # divide rax by rbx
        cmpq    $0, %rdx              # Check if the current size is a multiple of the current data type size 
        popq    %rbx                  # restore count
        je      .print_data_sizes     # jump back to print if the current size is a multiple of the size of the data type
    
    # Prints the required padding if the size of the struct isn't a multiple of the largest data type size
    .print_padding:
        movzbq  (%r13, %rbx, 1), %rsi   # move next size to second parameter
        subq    %rdx, %rsi              # get the difference between the next size and current total size
        addq    %rsi, %r9               # add the difference to %r9
        movq    $.spacing_string, %rdi  # move the spacing formatted string to the first parameter
        pushq   %r9                     # save the total size
        xorq    %rax, %rax              # zero out rax
        call    printf                  # print the spacing
        popq    %r9                     # restore the total size of the struct
        jmp     .print_data_sizes                  # print the next data type

    # Check if any padding is required before exitting
    .check_end_padding:   #    function exit - print how bytes are aligned
        movq    %r9, %rax   # move total size to rbx (divisor)
        movq    %r12, %rbx  # move max size (alignment) to rax (dividend) 
        xorq    %rdx, %rdx  # zero out rdx for remainder
        divq    %rbx        # divide rax by rbx to find remainder
        cmpq    $0, %rdx    # compare remainder to zero
        je      .pai_exit   # jump if equal to (remainder = 0)

    # calculate and print the final padding
    .print_final_spaing:
        movq    %r12, %rsi
        subq    %rdx, %rsi
        addq    %rsi, %r9
        movq    $.spacing_string, %rdi
        xorq    %rax, %rax
        pushq   %r9
        call    printf
        popq    %r9

    .pai_exit:
        movq    %r12, %rdx               # move largest data type to second parameter
        movq    %r9, %rsi
        movq    $.closing_message, %rdi  # move the data alignment string to first parameter
        xorq    %rax, %rax               # zero return
        call    printf                   # print
        leave
        ret
.size print_alignment_info, .-print_alignment_info
