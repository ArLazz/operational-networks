#include <stdio.h>


void bin(int k) {
    int c;


    for (int i = 0; i < 32; i++) {
        c = k / q;
        printf("%d", c);
        k = k % q;
        q = q >> 1;
    }
   printf("\n");
}


unsigned shift(unsigned x, int n, int dir) {
    unsigned y = x;
    if (dir == 1) {
        x = x >> n;
        n = 32 - n;
        y = y << n;
        x = x | y;
    }
    else {
        x = x << n;
        n = 32 - n;
        y = y >> n;
        x = x | y; 
    }
    return x;
}


int x, n, dir;


int main(void) {
    printf("%s", "Введите число: ");
    scanf("%d", &x);
    printf("%s", "Число в двоичном виде: ");
    bin(x);
    printf("%s", "Введите кол-во позиция сдвига: ");
    scanf("%d", &n);
    printf("%s", "Введите направление сдвига([R = 1] or [L = -1]): ");
    scanf("%d", &dir);
    printf("%s", "Полученное число в двоичном виде: ");
    x = shift(x, n, dir);
    bin(x);
    printf("%s", "Полученное число в десятичном виде: ");
    printf("%d\n", x);
    return 0;
}