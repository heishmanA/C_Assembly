#include "encrypt.h"


void shift_left(int bits[], int pos) {
    int i = 0;
            
    for (i = 0; i < pos; i++) {
        bits[i] = bits[i +1];
    }
    
}
