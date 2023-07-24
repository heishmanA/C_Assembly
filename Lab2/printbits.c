/* test c file */


#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
void printbits(int val) {
    int x = val;
    char *c = malloc(8 *sizeof(int)); /* 8 x 4*/
    int t = 31;
    while (x > 0) {
        c[t] = x % 2; /* first remainder is lsb, last is msb */
        x /= 2; /* divide by two to get next bit */
        t--;
    }
    t++; 
    x = 1; /* should be 0 at this point */
    printf("%i in binary: ", val);
    while (t < 32) {
        printf("%i ", c[t]);
        t++;
        x++;
    }
    printf("\n");
    free(c);
    c = NULL;
}



int main() {

    int x = 123456;
    int *p = &x;
    printf("%p\n", p);
    printf("%p\n", (p + 1));
    return 0;
}
