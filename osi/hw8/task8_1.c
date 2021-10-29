#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int r = 1, b = 0, f = 0, o = 0, i, j, s = 0, max = 0;
    char pl, q, *q1;
    for (i = 1; i <= 4; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'r') {
            r = -1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'b') {
            b = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'f') {
            f = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'o') {
            o = 1;
            j = i;
        } else
            break;
    }
    FILE *FOUT1, *F2;
    if (o == 1){
        FOUT1 = fopen(argv[j + 1], "w");
    }
    i += o;
    FILE *F1 = fopen("___help___.txt", "w");
    for (i; i < argc; i++){
        F2 = fopen(argv[i], "r");
        q = fgetc(F2);
        while (q != EOF){
            if (b == 1) {
                while (q == ' ') {
                    q = fgetc(F2);
                }
            }
            while (q != '\n' && q != EOF){
                if (f == 1){
                    if (q >= 'a' && q <= 'z'){
                        q = q - 'a' + 'A';
                    }
                }
                fputc(q, F1);
                q = fgetc(F2);
            }
            fputc('\n', F1);
            q = fgetc(F2);
        }
        fclose(F2);
    }
    fclose(F1);

    F1 = fopen("___help___.txt", "r");
    q = fgetc(F1);
    s = 0;
    while (q != EOF){
        if (q == '\n'){
            s += 1;
        }
        q = fgetc(F1);
    }
    fseek(F1, 0, SEEK_SET);
    char *a[s];
    q = ' ';
    i = 0;
    j = 0;
    while (q != EOF){
        q = fgetc(F1);
        j += 1;
        if (q == '\n' || q == EOF){
            fseek(F1, -(j), SEEK_CUR);
            q1 = (char *) malloc(j + 2);
            a[i] = fgets(q1, j + 1 , F1);
            i += 1;
            j = 0;
        }

    }
    for (i = s - 1; i >= 0; i--) {
        for (j = 0; j < i; j++) {
            if (r * strcmp(a[j], a[j + 1]) > 0) {
                q1 = a[j];
                a[j] = a[j + 1];
                a[j + 1] = q1;
            }
        }
    }
    if (o == 1){
        for (i = 0; i < s; i++){
            fputs(a[i], FOUT1);
        }
        fclose(FOUT1);
    } else {
        for (i = 0; i < s; i++) {
            printf("%s", a[i]);
        }
    }
    remove("___help___.txt");
    fclose(F1);
}
