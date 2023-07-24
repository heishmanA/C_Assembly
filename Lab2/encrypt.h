/* encrypt.h file - contains the declarations for each function used to encrypt and decrypt a file
 * Aaron Heishman
 * Systems I - Lab 2
 */

#ifndef ENCRYPT_FILE_H
#define ENCRYPT_FILE_H


/* Converts {@code ch} from its decimal representation to its binary representation
 * @ch - the decimal representation of a character
 * @bits - the array to hold the binary representation
 */
void conv_to_bits(int ch, int bits[]);

/* Raises the given integer {@code n} to the power {@code r}
 * @n - the integer to be raised to the power
 * @r - the expenonent
 * @Return - power = n^r
 */
int power(int n, int r);

/* shifts the bits left one time starting at {@code pos} and ending at 0
 * @bits - the binary values to be shifted
 * @pos - the position of to start shifting
 */
void shift_left(int bits[], int pos);

/* shifts decrypted bits back to the right to maintain their original binary value before encryption 
 * @bits - the binary values to be shifted
 * @pos - the position to shift to
 */
void shift_right(int bits[], int pos);

#endif

