/* encrypt.c file - reads input in - encrypting 7 characters with the spliced bits of the 8th character
 * Aaron Heishman
 * Systems I - Lab 2
 */
#include <stdio.h>
#include "encrypt.h"
#include <time.h>
/* Convert the given bits to their decimal representation
 * @bits - the bits to be converted
 * @returns - the decimal representation of the bits
 */
int convert(int bits[]) {
   int i, exp, result = 0;
   int base = 2; /* binary is base 2 */
   /* least significant bit on the right, if a 1 is reached take 2^(7-i) */
   for (i = 7; i >= 0; i--) {
   if (bits[i] == 1) {
            result += power(base, 7 - i);
        } 
   }
   return result; 
}

/* Encrypts the first seven characters of {@code chars) with the 8th character in {@code chars}
 * int chars[] - the characters to be encrypted
 */
void encrypt(int chars[]) {
    int e_bits[9] = {0}; /* encryptor bits */
    int i, dec; 
    conv_to_bits(chars[7], e_bits); /* convert 8th character to binary values */
    /*  convert each character to bits, while splicing 8th character bits into them */
    for (i = 0; i < 7; i++) {
        int ch_bits[9] = {0};
        conv_to_bits(chars[i], ch_bits);
        shift_left(ch_bits, i); /* shifts left by one */
        ch_bits[i] = e_bits[7 - i]; /* place the spliced bit into the character bits */ 
        putchar(convert(ch_bits)); /* print the new encrypted character */
    }
}

int main() {
    int chars[9] = {0}; /* Eight characters */
    int ch, i = 0;
    ch = getchar(); 
    i = 1;
    /* read input in, decrypting only when the 8th character is found */
    while (ch != EOF) {  
        chars[i-1] = ch;
        if (i == 8) { 
            encrypt(chars);
            i = 0; /* reset count if more than 8 characters exist */
        }
        ch = getchar(); /* get character here to prevent EOF from manipulating count */
        if (ch != EOF) {
            i++;
        }
    }
    /* print any leftover characters if the amount of characters is not a multiple of 8 */
    if (i > 0) {
        int j;
        for (j = 0; j < i; j++) {
            putchar(chars[j]);
        }
    }
    return 0;
}

