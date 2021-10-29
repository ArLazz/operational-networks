#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    char q;
    int n = atoi(argv[1]);
    FILE *F1, *F2;
    int i = 1;
    F1 = fopen(argv[2], "r");
    F2 = fopen("___help___.txt", "w");
    q = fgetc(F1);

    while (q != EOF) {
        while (q != '\n' && q != EOF){
            i += 1;
            q = fgetc(F1);
        }
        if (i > n) {
            fseek(F1, -i, SEEK_CUR);
            q = fgetc(F1);
            while (q != '\n' && q != EOF){
                fputc(q, F2);
                q = fgetc(F1);
            }
            fputc('\n', F2);
        }

        i = 1;
        q = fgetc(F1);
    }
    fclose(F1);
    fclose(F2);
    F1 = fopen(argv[2], "w");
    F2 = fopen("___help___.txt", "r");
    q = fgetc(F2);
    while (q != EOF){
        fputc(q, F1);
        q = fgetc(F2);
    }
    remove("___help___.txt");
    fclose(F1);
    fclose(F2);
}