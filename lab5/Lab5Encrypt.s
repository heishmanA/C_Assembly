# Aaron Heishman
# Lab 5 - Systems I
# Lab5Encrypt file
.file "Lab5Encrypt.s"
.section .rodata

.string_f:
    .string "%s"
.data
.align 8
# Array to hold all characters, initalized as null ['0x0']
.encryptee_arr:   
    .byte 0x0
    .byte 0x0
    .byte 0x0
    .byte 0x0
    .byte 0x0
    .byte 0x0
    .byte 0x0
    .byte 0x0
    
.global main
    .type main, @function

.text
main:
    # stack setup
    pushq   %rbp
    movq    %rsp, %rbp
    # Set up "variables"
    movq    $0, %r12                    # load '0' in r12b as r12b will represent both
                                        # the count and current index of the array
    movq    $.encryptee_arr, %r13       # load the address of encryptee char into %r12
   
    # Read in 8 chars at a time
    .read:
        # save original values of %r12d, %r13d, %r14d
        pushq   %r12
        pushq   %r13
        # Read in the character 
        xor     %rax, %rax      # zero out the entire value of rax
        call    getchar         # get the character

        # Restore all values before checking if next char is EOF
        popq    %r13
        popq    %r12

        # check for EOF value
        cmpl    $-1, %eax     # Check if EOF is returned
        je      .check        # jump to check to make sure if the array has any values
        movb    %al, (%r13, %r12, 1)    # move the lowest byte from %al to r13[count]
        incq    %r12           # increment count/index by 1
        cmpq    $8, %r12      # compare count : 8
        jl      .read         # jump if less than (count < 8)
        je      .encrypt      # jump if equal to (count == 8)
    
    .encrypt:
        # Encrypt the the 7 characters using the 8th character then loop
        pushq   %r12               # save the count
        pushq   %r13               # save the address of the the array
        movzbq  7(%r13), %rsi      # move the 8th character to the second parameter
        movq    %r13, %rdi         # move the char array (or string) to second param
        call    encrypt            # encrypt 7 characters found in .encryptee_arr by the character now in %rsi
        popq    %r13               # restore the address of the array
        popq    %r12               # restore the count
        xor     %r12, %r12         # zero out the count
        movq    $0, (%r13)         # replace all bytes in .encryptee_arr with 0x0
        jmp     .read              # loop again to check for more chars

    .check:  # check to make sure if %rsi has any unencrypted chars to be placed into the document
        cmpq $0, %r12   # compare the count : 0
        je   .end       # jump if equal (count == 0 no chars in array)
        # print the last characters read in unencrypted
        movq    %r13, %rsi          # move the character array into the second parameter
        movq    $.string_f, %rdi    # move the format specifier into first param
        xor     %rax, %rax          # zero return
        call    printf              # print the array

    .end:
        xor %rax, %rax  # zero out return to signify a successful run
        leave
        ret
.size main, .-main

# Encrypts the array that will passed to %rdi
.global encrypt
    .type encrypt, @function

encrypt:
    # stack set up
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $8, %rsp        # allocate space on the stack
    # Set up "variables"
    movq    %rsi, %rax      # 8th character was in param two, move to rax
    movq    $0, %r13        # %r13 used as "index"
    movq    $7, %r14        # %r14 will count as "k" 

    # Encrypt each character in %rsi with a bit from the character in  %rax
    .encrypt_chars:     # start of loop
        # save all the values
        pushq   %rax    # save encryptor character (8th character)
        pushq   %r13    # save index/count
        pushq   %r14    # save "k"
        pushq   %rdi    # save the array

        # Get the "ith" bit from encryptor character as it is on the right
        movq    $0x01, %rbx     # move "0000 0001" into %rbx
        movq    %r13, %rcx      # move "i" into %rcx
        shlq    %cl, %rbx       # shift %rbx by "index"
        andq    %rbx, %rax      # and %rbx and %rax to get the "ith" bit

        # Get the [0, k] bits from the character to be encrypted
        movq    (%rdi, %r13, 1), %rdx   # move the encryptee char to %rdx [rdx = %rdi[i]]
        movq    $0xFF, %rbx     # move "1111 1111" into rbx
        movq    %r14, %rcx      # move "k" into %rcx
        shlq    %cl, %rbx       # shift %rbx "k" bits [rbx << k]
        andq    %rbx, %rdx      # and %rbx and %rdx to get the [0, k] bits
        cmpq    $0, %r13        # compare [i : 0]
        je      .encrypt_chars_cont # jump if equalk to (i == 0)
        jg      .encrypt_shl_char  # jump if greater than (i > 0)
        
    # Shift characters [2, 6] left by one to make space for encryptor bit
    .encrypt_shl_char:
        shlq     $1, %rdx    # shift %rdx "i" bits [rdx << 1]

    # Continue with encryption
    .encrypt_chars_cont:    
        # This combination of moves will move rax the "difference" between i and k (k - i) 
        movq    %r13, %rcx      # move "i" into %rcx
        shrq    %cl, %rax       # shift %rax "i" bits [%rax >> i] - bit is not at pos 7
        movq    %r14, %rcx      # move k to %rcx
        shlq    %cl, %rax       # shift %rax "k" bits [%rax << k] - bit is now at the k position
        orq     %rax, %rdx      # add the byte at the "k" position to %rdx 
        movq    %rdx, %r15      # store the left side into %r15

        # get the right sided bits of the character
        movq    $0xFF, %rbx             # move "1111 1111" to %rbx
        movq    (%rdi, %r13, 1), %rdx   # restore the character to get the right side
        movq    %r13, %rcx              # move "i" to rcx
        incq    %rcx                    # increment "i" by one to not get the bit that was shifted left one
        shrq    %cl, %rbx               # shift %rbx "i" times
        andq    %rbx, %rdx              # and %rbx and %rdx to zero the left side of the bits to replace
        orq     %r15, %rdx              # combine %r15 and %rdx to create the encrypted char

    # put the encrypted character into the file or console
    .encrypt_put_char:      # label for easier reading
        movq    %rdx, %rdi  # move the encrypted character to the first param
        xor     %rax, %rax  # zero return
        call    putchar     # print char
        popq    %rdi        # restore the array
        popq    %r14        # restore bit "k"
        popq    %r13        # restore the "i"
        popq    %rax        # restore the encryptor character
        incq    %r13        # increment "i" by 1
        decq    %r14        # decrement "k" by 1
        cmpq    $7, %r13    # check if (i < 7)
        jl     .encrypt_chars # jump ff less than (%r13 < 7)

    # leave function
    .encrypt_end:       # label for easier reading
        addq $8, %rsp   # deallocate the space made for the stack
        xor %rax, %rax  # zero out return to signify completion
        leave
        ret
.size encrypt, .-encrypt
