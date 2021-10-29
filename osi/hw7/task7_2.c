#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int s = 0, n = 0, p = 0, l, w, j = 0, t = 0;
    char *pl, q, q1;
    for (int i = 1; i < argc - 1; i++){
        if (argv[i][1] == 's')
            s = 1;
        if (argv[i][1] <= '9' && argv[i][1] >= '0' && argv[i][0] == '-') {
            n = 1;
            w = i;
        }
        if (argv[i][0] == '+') {
            p = 1;
            l = i;
        }
    }

    if (n == 0){
        w = 10;
    } else {
        w = atoi(argv[w] + 1);
    }

    if (p != 0){
        l = atoi(argv[l]);
    }
    FILE *F1 = fopen(argv[argc - 1], "r");
    q1 = fgetc(F1);
    if (p == 1){
        for (int i = 0; i < l; i++){
            while (q1 != '\n'){
                q1 = fgetc(F1);
            }
            q1 = fgetc(F1);
        }
    }
    q = getchar();
    while (q != 'q' && q1 != EOF){
        while (j < w) {
            if (q1 != EOF)
                putchar(q1);
            if (s == 1 && q1 == '\n') {
                while (q1 == '\n') {
                    q1 = fgetc(F1);
                    t += 1;
                } g
                if (t > 1) {
                    putchar('\n');
                    j += 1;
                }
                t = 0;
                fseek(F1, -1, SEEK_CUR);
                j += 1;
            }
            if (s == 0 && q1 == '\n'){
                j += 1;
            }
            if (q1 == EOF){
                break;
            }
            q1 = fgetc(F1);
        }
        q = getchar();
        j = 0;
    }
}