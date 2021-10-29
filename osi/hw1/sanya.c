#include <stdio.h>
#include <stdlib.h>

#define BinPrint(x) {\
    int i;\
    long long int s=1; \
    long long x2=x;\
    for(i=0;i<8 * sizeof(x)-1;i++){ \
        s=s<<1; \
    } \
    for (i = 0; i < 8 * sizeof(x); i++) { \
        printf("%c", (x2 & s) ? '1' : '0'); \
        x2 <<= 1; \
    } \
    printf("\n"); \
}


int main(void) {
    char c = -3;  // Или любое другое
    if(c){BinPrint(c)}else printf("Zero!\n");

    BinPrint((short)7);

    long x=15;
    if(x){BinPrint(x)}else printf("Zero!\n");

    BinPrint((long long) x);
    return 0;
}