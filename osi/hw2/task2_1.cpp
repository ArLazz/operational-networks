#include <stdio.h>


double e, x, x0 = 1, x1, d;


int main() {

    printf("%s", "Введите е: ");
    scanf("%lf", &e);
    
    printf("%s", "Введите x: ");
    scanf("%lf", &x);
    
    while (getchar() != EOF) {
        do {
            x1 = (x0 + x / x0) / 2;
            d = x0 - x1;
            if (d < 0) 
            d = - d;
            x0 = x1;
        } 
        while (d >= e);
        printf("%f, %g, %e, %.10g\n", x1, x1, x1, x1);
        x0 = 1;
        printf("%s", "Введите x: ");
        scanf("%lf", &x);
    }
    return 0;
}