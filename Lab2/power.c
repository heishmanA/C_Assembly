#include "encrypt.h"


/* Convers the given binary value back to a decimal representation 
 * @n - the binary value to be converted
 * @r - the exponent
 * @returns the converted decimal value of {@code n}
 */
int power(int n, int r) {
    int result = 1;

    if (r > 0) {
        result = power(n, r/2);
        result *= result;
        if (r % 2 != 0) {
            result *= n;
        }
    } 

    return result;
}

