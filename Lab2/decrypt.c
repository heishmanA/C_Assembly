/* decrypt.c file - reads in the given input and decrypts every 7th character until all 
 *                  characters have been decrypted 
 * Aaron Heishman
 * Systems I Lab 2
 * */

#include <stdio.h>
#include "encrypt.h"

/* Converts {@code bits} from binary to decimal
 * @bits - the bits to be converted
 * @returns the decimal representation of the bits
 */
int convert(int bits[]) {
    int i, result = 0;
    int base = 2; /* binary is base 2 */
    /* least significant bit on the right, if a 1 is reached take 2^(7-i) */
    for (i = 7; i >= 0; i--) {
        if (bits[i] == 1) {
            result += power(base, 7 - i);
        }     
    }
    return result;
}


/* Decrypts the characters in {@code chars}
 * @chars - the characters to be decrypted
 */
void decrypt(int chars[]) {
    int d_bits[8] = {0}; /* Array for the binary values of the spliced characters */
    int e_pos = 7; /* spliced bit index*/
    int i;
    for (i = 0; i < 7; i++) {
        int ch_bits[8] = {0}; /* char bits */
        conv_to_bits(chars[i], ch_bits); /* convert current char to binary representation */
        d_bits[e_pos - i] = ch_bits[i]; /* extract spliced bit */
        shift_right(ch_bits, i); /* shift bits right one, place 0 at front */
        putchar(convert(ch_bits)); /* print decrypted character */
    }
    /* print to output the decrypted 8th character that was inside the previous 7 character s*/
    putchar(convert(d_bits));
     
}

int main() {
    int chars[8] = {0}; /* Seven encrypted characters */
    int i, ch = 0; 
    ch = getchar();
    i = 1;
    /* start with 1 because 1 character has been read in */
    /* read input char by char - decrypting each character when the 7th character is found */
    while (ch != EOF) {
        chars[i - 1] = ch; 
        if (i == 7) { 
            decrypt(chars); 
            i = 0; /* resetting count if more than 7 characters exist */
        }
        ch = getchar(); /* get character here to prevent EOF from manipulating character count */
        i++;
    }
    
    /* print any leftover characters if the amount of characters is not a multiple of 7 */
    if (i > 0) {
        int j;
        for (j = 0; j < i - 1; j++) {
            putchar(chars[j]);
        }
    }    
    return 0;
}

