/* conv2bits.c file */
#include "encrypt.h"
#include <stdio.h>
/* Converts the given character(decimal) into bits(binary) and places those bits into the array
 * @ch - the character to convert to bits
 * @ch_bin - array to hold the bits
 * */
void conv_to_bits(int ch, int bits[]) {
    int i = 7; /* first bit at the end, last bit at the front */
    int c = ch; 
    
    /* decimal to binary conversion */
    while (c > 0) {
        int r = c % 2; /* remainder */
        bits[i] = r;
        c /= 2;
        i--;
    } 
}


