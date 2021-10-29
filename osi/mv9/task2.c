#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    char str[200], q;
    struct stat buf;
    int n = atoi(argv[2]), m = atoi(argv[3]), i, k = atoi(argv[4]), s = 0, o = 1, p = 0, j = 0;
    FILE *F1 = fopen(argv[1], "r");
    long int u = 1;


    if (!F1){
        printf("Такого файла нет, введите первые %d строк файла\n", n);
        F1 = fopen(argv[1], "w");
        for (i = 0; i < n ;i++) {
            scanf("%s", str);
            fputs(str, F1);
            fputc('\n', F1);
        }
        fclose(F1);
        F1 = fopen(argv[1], "a+");
    } else {
            printf("Файл существует\n");
            fclose(F1);
            F1 = fopen(argv[1], "a+");
    }
    stat(argv[1], &buf);
    printf("Номер индексного дескриптора - %ld\nДлина файла - %ld\n"
           "Количество жестких ссылок на файл - %ld\n", buf.st_ino, buf.st_size, buf.st_nlink);


    fseek(F1, 0, SEEK_SET);
    q = fgetc(F1);
    u = buf.st_size;
    s = 0;
    while(q != EOF){
        if (q == '\n'){
            j += 1;
        }
        q = fgetc(F1);
    }
    fseek(F1, 0, SEEK_SET);
    q = fgetc(F1);
    if (m <= j) {
        while (u != 0) {
            if (q == '\n') {
                p += 1;
                if (p % m == 0) {
                    fseek(F1, -s, SEEK_CUR);
                    fgets(str, 200, F1);
                    fputs(str, F1);
                    fseek(F1, o, SEEK_SET);
                }
                s = 0;
            }
            q = fgetc(F1);
            o += 1;
            s += 1;
            u -= 1;
        }
    } else {
        printf("Строк в файле меньше,чем %d.\n", m);
    }
    j += j / m;
    fclose(F1);
    F1 = fopen(argv[1], "r");
    FILE *F2 = fopen("___help___.txt", "w");
    q = fgetc(F1);
    if (2 * k >= j){
        fclose(F1);
        F1 = fopen(argv[1], "w");
    } else {
        o = 0;
        while (o != k) {
            if (q == '\n')
                o += 1;
            q = fgetc(F1);
        }
        p = k;
        fseek(F1, -1, SEEK_CUR);
        while (p < j - k) {
            fgets(str, 200, F1);
            fputs(str, F2);
            p += 1;
        }
        fclose(F1);
        fclose(F2);
        F1 = fopen(argv[1], "w");
        F2 = fopen("___help___.txt", "r");
        q = fgetc(F2);
        while (q != EOF){
            fputc(q, F1);
            q = fgetc(F2);
        }
    }
    remove("___help___.txt");
    fclose(F2);
    fclose(F1);
}