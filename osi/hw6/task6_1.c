#include <stdio.h>
#include <limits.h>
#define BINPRINT(k) ({ \
    long long j = k;   \
    long long int q = 1;\
    int n = 8 * sizeof(k) - 1;\
    for (int i = 0; i < n; i++){ \
        q <<= 1;                  \
    }\
    for (int i = 0; i <= n; i++) {\
        printf("%c", (j & q) ? '1' : '0'); \
        j <<= 1; \
        }              \
    printf("\n");    \
})

int main(){
    char c=-3;
    if(c) BINPRINT(c); else printf("Zero!\n");
    BINPRINT((short)7);
    long x=15;
    if(x) BINPRINT(x); else printf("Zero!\n");
    BINPRINT((long long)x);
}