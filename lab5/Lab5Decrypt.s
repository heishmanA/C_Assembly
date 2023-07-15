# Aaron Heishman
# Lab 5 - Systems I
# Lab5Decrypt file
.file "Lab5Decrypt.s"
.section .rodata

.string_f:  # format string for printing the chars 0-6 if there are any left in the array
    .string "%s"

.data
.align 8
# Array to hold all 7 characters, initalized as null ['0x0']
.encryptee_arr:   
    .byte 0x0
    .byte 0x0
    .byte 0x0
    .byte 0x0
    .byte 0x0
    .byte 0x0
    .byte 0x0   # this null byte will allow printf to be called for 6 or less characters
    
.global main
    .type main, @function

.text
main:
    # stack setup
    pushq   %rbp
    movq    %rsp, %rbp
    # Set up "variables"
    movq    $0, %r12                    # load '0' in r12 as r12 will represent both
                                        # the count and current index of the array
    movq    $.encryptee_arr, %r13       # load the address of encryptee char into %r12
   
    # Read in 8 chars at a time
    .read:
        # save original values of %r12, %r13, %r14
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
        je      .check        #  Jump if equal (check for any if any unecrypted characters are in the array)
        movb    %al, (%r13, %r12, 1)    # move the lowest byte from %al to r13[count]
        incq    %r12          # increment count/index by 1
        cmpq    $7, %r12      # compare count : 7
        jl      .read         # jump if less than (count < 7)
        je      .decrypt      # jump if equal to (count == 7)
    
    .decrypt:
        # Save values then call decrypt to decrypt the first 7 characters, then call assemble to assemble the 8th character
        pushq   %r12               # save the count
        pushq   %r13               # save the address of the the array
        movq    %r13, %rdi         # move the char array (or string) to first param
        call    decrypt            # decrypt the 7 charactrers in the array
        call    assemble           # as %rdi is maintained in decrypt, call assemble to assemble the 8th character
        popq    %r13               # restore the address of the array
        popq    %r12               # restore the count
        xor     %r12, %r12         # zero out the count
        movq    $0, (%r13)         # replace all bytes in .encryptee_arr with 0x0
        jmp     .read              # loop again to check for more chars

    .check:  # check to make sure if the array in %rdi has any unencrypted chars to be placed into the document
        cmpq $0, %r12   # compare the count : 0
        je   .end       # jump if equal (count == 0 no chars in array)
        # print the last characters read in 
        movq    %r13, %rsi          # move the character array into the second parameter
        movq    $.string_f, %rdi    # move the format specifier into first param
        xor     %rax, %rax          # zero return
        call    printf              # print the array

    .end:
        xor %rax, %rax  # zero out return to signify a successful run
        leave
        ret
.size main, .-main

# Decrypts all 7 characters back to their original format
.global decrypt
    .type decrypt, @function

decrypt:
    # stack set up
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $8, %rsp        # allocate space on the stack
    
    # initial setup
    movq    $0, %r12    # r12 will be used as index / position of bit to be removed
    movq    $7, %r13    # r13 with used for bit position "kth position"
    xor     %r15, %r15  # zero out r15 to hold the bits of the 8th character 
    .decrypt_bits:
        # get left first, it will contain the bit for the 8th character
        cmpq   $7, %r12        # compare %12 : 7
        je      .decrypt_end   # jump if equal to (%r12 == 7)
        movq    (%rdi, %r12, 1), %rdx   # move the character to rdx
        pushq   %rdx            # save the character
        movq    $0xFF, %rax     # move "1111 1111" to be shifted and used as a mask to get the left side of the bits
        movq    %r13, %rcx      # move the "kth position" count into rcx
        shl     %cl, %al        # shift "1111 1111" left by "kth position"
        and     %rax, %rdx      # and the mask %rax with %rdx to get the left side of the bits

        # restore the character to its original bit value
        shr     $1, %rdx        # shift %rdx one to the right to put left side of the bits back into their
                                # original positions
        and     %rax, %rdx      # use %rax as a mask again to remove the the extra bit
        movq    %rdx, %r9       # copy the left side bits from %rdx to %r9

        # get the right side
        popq    %rdx            # restore the original character
        movq    $0xFF, %rax     # move "1111 1111" back into %rax for mask purposes
        incq    %r12            # increment the index by one
        movq    %r12, %rcx      # move the index counter into %rcx
        shr     %cl, %rax       # shift the masking character in %rax to the right 
                                # (if cl = 1 then rax = "0111 1111" and so on)

        and     %rax, %rdx      # and the mask in %rax with the bits in %rdx 
                                # to get the right character's right side bits

        or      %r9, %rdx       # combine the left and ride side of the bits 
                                # in %r9 and %rdx to restore the original character
        # print the char
        pushq   %rdi            # save the array just in case
        movzbq  %dl, %rdi       # move the bits to %rdi, use sign extension to zero any possible values out
        call    putchar         # print the character
        popq    %rdi            # restore the array in rdi
        decq    %r13            # decrement the "kth position" counter
        jmp     .decrypt_bits   # unconditional jump back to decrypt_bits for loop

    # all characters decrypted, return to main
    .decrypt_end:
        xor %rax, %rax      # zero out rax to signify a successful function call
        leave               # leave and return
        ret
.size decrypt, .-decrypt

# This function specifically assembles the 8th char from the characters in the array in %rdi
.global assemble
    .type assemble, @function

assemble:
     # stack set up
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $8, %rsp    # allocate space on the stack
    
    movq    $1, %r8     # move "0000 ... 0001" to r8, this will be used to shift 8th bit to the right
    movq    $2, %r9     # move "0000 ... 0010" to %r9 to be used as a mask
    movq    $6, %r10    # move 6 to r10 - this will be used to simultaneously get the character 
                        # that contains the bit for 8th char, and for shifting the difference of abs(r8 - r9)
                        # which will be the specific placement of the bit
    
    xor     %rdx, %rdx  # zero out %rdx to guarantee it has no values
                        # as this register will be used to build the 8th character

    .assemble_eighth_char:
        cmpq    $0, %r10                # compare %r10 : 0
        jl      .assemble_end           # jump if less than (%r10 < 0)
        movq    (%rdi, %r10, 1), %rax   # move characters from %rdi[index] to %rax
        andq    %r9, %rax               # and %rax with %r9 to get the bits of the 8th character
        movq    %r8, %rcx               # move %r8 (reset count) to %rcx to set up getting difference
        shr     %cl, %rax               # shift the bit in %rax to the first position "0000 000[b]"
        movq    %r10, %rcx              # move %r10 (index) to rcx to make up for the difference : Example: [000[b] 0000]
        shl     %cl, %rax               # shift the bits left by the value in %rcx to place the bit in the correct position
        or      %rax, %rdx              # or %rax and %rdx to place the bit in the correct position
        incq    %r8                     # increment r8 by one to keep track of how far bits need to be pushed right
        shl     $1, %r9                 # bitshift the mask in %r9 to the left by one
                                        # to keep it in line with position of the location of the bit for the 8th char

        decq    %r10                    # decrement %r10 to to keep track of which character needs removed 
                                        # and to keep track of where the 8th character's extracted bit should go

        jmp    .assemble_eighth_char    # unconditional jump back to the top
        
    .assemble_end:
    # put the 8th character into output
    pushq   %rdi    # maintain %rdi 
    movq    %rdx, %rdi    # move the character from rdx to rdi
    call  putchar   # print the character
    popq    %rdi    # restore %rdi for return
    addq  $8, %rsp  # deallocate the space made for the stack
        leave
        ret
.size assemble, .-assemble
