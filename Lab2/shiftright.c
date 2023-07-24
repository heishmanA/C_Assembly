/* shiftright.c file */

#include "encrypt.h"

void shift_right(int bits[], int pos) {
    int i;
    /* replace the bit at pos with the bit to the left until i = 0 */ 
    for (i = pos; i > 0; i--) {
        bits[i] = bits [i-1];
    }
    /* all bits should have 0 at the front for this conversion */
    bits[0] = 0; 
}
