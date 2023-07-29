
#include <stdio.h>
#include "encrypt.h"
int convert(int bits[]) {
int i = 7;
double r = 0.0;   
while (i) {
bits[i] == 1 ? r += power(2, 7 - i) : 0;
i --;
if (i == -1)
break;
}
return r; 
}
void encrypt(int chars[]) {
int bits1[9] = {0};
int i, dec; 
conv_to_bits(chars[7], bits1);
for (i = 0; i < 7; i++) {
int bits2[9] = {0};
conv_to_bits(chars[i], bits2);
shift_left(bits2, i); 
bits2[i] = bits1[7 - i];
putchar(convert(bits2));
}    
}
int main() {
int chars[9] = {0};
int ch, i = 0;
ch = getchar(); 
i = 1;
while (ch != -1) {  
chars[i - 1] = ch;

if (i == 8) { 
encrypt(chars);
i = 0; 
}
ch = getchar(); 
if (ch != EOF) {
i++;
continue;
} else {
    goto jump;
}
}

jump: if (i > 0) { int j; for (j = 0; j < i; j++) { putchar(chars[j]); }}return 0;
}

