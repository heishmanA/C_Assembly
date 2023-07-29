# Prints the fibonnaci sequence based on the user input 
# Aaron Heishman
# 7/8/2023

.file "fibonacci.s" # file name
.section .rodata    # read only

out_format:     # closing string for printing results
    .string "%i: %lu\n"

u_long_f:          # unsigned long format
    .string "%lu"

.global main
    .type main, @function

.text
main:
    # set up stack
    pushq   %rbp
    movq    %rsp, %rbp
    # save argument count and arguments before checking invalid input
    pushq   %rsi
    pushq   %rdi
    # check for invalid input, %rdi and %rsi hold CLI/Argcount
    call    check_input
    # restore argument count and arguments
    popq    %rdi
    popq    %rsi

    cmpq    $0, %rax        # compare the return value of check_input to 0
    je      .quit           # jump if equal to - %rax contains 0 (error for check_input)
    
    # if rax returns 0, convert the second argument from string to long
    # format = strloul (string, ptr to place in, base)
    movq    $10, %rdx
    movq    %r13, %rdi
    movq    8(%rsi), %rdi

    xor     %rax, %rax      # zero rax
    call    strtoul         # convert the argument from a string to an unsigned long
                            # rax will hold the unsigned long
    movq    $1, %r12        # move zero to %r12 to represent the count
                            # since fibonacci sequence starts at 1
    movq    %rax, %r13      # move value to %r13

    # loop from 0 to n printing the fibonnaci sequence in order
    .fib_sequence_loop:
        cmpq    %r13, %r12  # compare user input to current count
        jg     .quit        # jump if greater than (count > n)
        
        pushq   %r13        # save user value
        pushq   %r12        # save the count

        movq    %r12, %rdi  # move count to %rdi to get f(count)
        call    fib         # get fib(n)

        popq    %r12        # restore count
        popq    %r13        # restore count
        
        pushq   %r13        # save count
        pushq   %r12        # save user val
        movq    %rax, %rdx  # move the return value to the third param
        movq    %r12, %rsi  # move the current count to the second param
        movq    $out_format, %rdi # move the output message
        xor     %rax, %rax  # zero return
        call    printf  
        popq    %r12        # restore user val
        popq    %r13       # restore count

        incq    %r12        # increment count by one
        jmp     .fib_sequence_loop   # jump to beginning

    .quit:
        xorq    %rax, %rax
        leave
        ret
.size main, .-main



# Check for invalid input [No input, Empty Input, Negative, Non-Number]
# return a 0 for fail, 1 for success
invalid_msg:
    .string "Usage: Please input the count of fibonacci numbers to output\n"
.global check_input
    .type check_input, @function
.text
check_input:
    #set up stack frame for check_input
    pushq   %rbp
    movq    %rsp, %rbp
    # the first parameter, %rdi, holds the arg count
    # the second parameter, %rsi, holds the argument(s)
    # Start by checking if input is empty
    jmp .check_no_input

    # Case No input: <myprog> [no args]
    .check_no_input:
        cmpq    $0x01, %rdi         # Compare arg count to 1
        je      .print_error        # jump if equal (args count == 1)
        jmp     .check_empty_input
    
    # Case Empty input: <myprog> ""
    .check_empty_input: 
        movq    8(%rsi), %rsi   # Move the first argument to %rsi
        movb    (%rsi), %al     # move the first character to register %al
        cmpb    $0x00, %al      # compare first character to null terminator byte
        je      .print_error    # jump if equal (empty input)
        # if equal flag not set, then check the rest of the characters for valid input
        movq    $0, %r12        # move 0 to %r12 to use %r12 as a count for the loop
        jmp     .check_for_characters
        
    # Case Invalid input, not a number:
    .check_for_characters:
        movb    (%r12, %rsi), %al   # move the character to %al
        # Check if the character is null byte first
        cmpb    $0x00, %al          # compare character to null byte character
        je      .success            # jump if equal to

        # Compare the character to see if it falls in the range of [0, 9]
        cmp     $0x30, %al          # compare the character to 0
        jl      .print_error        # jump if less than (character is not a digit)

        cmp     $0x39, %al          # compare the character to 9
        jg      .print_error        # jump if greater than (character is not a digit)

        incq    %r12                # increment %r12 by one

        jmp     .check_for_characters

    .print_error:
        movq    $invalid_msg, %rdi  # move the error message to register
        xor     %rax, %rax          # zero return
        call    printf              # print error message
        movq    $0, %rax            # put error code in movq
        jmp     .leave
    
    .success:
        movq $1, %rax   # return 1 if a success

    .leave:
        leave
        ret
.size check_input, .-check_input

# Start of the fibonnaci sequence function
# fib(u_long n)
.global fib
    .type fib, @function
.text
fib:
    # set up the stack
    pushq   %rbp
    movq    %rsp, %rbp

    cmpq    $2, %rdi        # rdi holds n, compare n : 2
    jb      .fib_base       # base case n < 2 - jump to .fib_base and return n
                            # else n >= 2, so recursive step

    pushq   %rdi            # save the original value of %rdi (n)

    subq    $1, %rdi        # decrement n by 1 (n-1)
    call    fib             # call fib with (n-1)
    movq    %rax, %r9       # store the return value of fib(n-1) in %r9
    popq    %rdi            # restore the original value of rdi (n)

    subq    $2, %rdi        # decrement rdi by 2 to do n-2 since %r9's original value was saved
    pushq   %r9             # save %r9 as it holds return of fib(n-1)
                            # no need to save %rdi as it's value is no longer needed
    call    fib             # call fib with (n-2)
    popq    %r9             # restore %r9
    addq    %r9, %rax       # add result of fib(n-1) to fib(n-2) and return that value

    # done with recursion, return rax
    leave
    ret
    
    .fib_base: # label for base case n < 2
        movq   %rdi, %rax # copy %rdi to %rax (putting n in return value)
        leave
        ret

.size fib, .-fib

