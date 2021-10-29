#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void pd(DIR *p, char *c, int l){
    struct dirent *p1, *p2, *pl;
    DIR *p3, *p4;
    int i, j, k;
    while(*(c + i) != '\0'){
        i += 1;
    }
    j = i;
    if (p != NULL){
        p1 = readdir(p);
        while (p1 != NULL){
            printf("%s ", p1 ->d_name);
            if (l == 1){
                struct stat buf;
                stat(p1 ->d_name, &buf);
                printf("Тип файла - %d \n", p1 -> d_type);
                printf("Права доступа - %d \n", buf.st_mode);
                printf("Число ссылок на файл %lu \n", buf.st_nlink);
                printf("Размер файла - %ld \n", buf.st_size);
                printf("ID пользователя-владельца - %d \n", buf.st_uid);
                printf("ID группы-владельца - %d \n\n", buf.st_gid);
            }
            p1 = readdir(p);
        }
        printf("\n");
        p3 = opendir(c);
        p1 = readdir(p3);
        while (p1 != NULL) {
            if (*(p1->d_name) != '.') {
                char *q1 = NULL;
                for (i = 0; (*(p1 -> d_name + i)!='\0'); i++);
                q1 = (char *) malloc(i + j + 1);
                for (i = 0; (*(c + i) != '\0'); i++) {
                    *(q1 + i) = *(c + i);
                }
                k = i;
                *(q1 + i) = '/';
                k += 1;
                for (i = 0; (*(p1->d_name + i) != '\0'); i++) {
                    *(q1 + i + k) = *(p1->d_name + i);
                }
                *(q1 + i + k) = '\0';
                p4 = opendir(q1);
                if ((p4 = opendir(q1)) != NULL) {
                    printf("Файлы из каталога --> %s\n", q1);
                    pd(p4, q1, l);
                }
            }
            p1 = readdir(p3);
        }
    }
}
int main(int argc, char *argv[]) {
    int b = 0, f = 0, o = 0, i, j, s = 0, max = 0, a = 0, l = 0, r = 0;
    char pl, q, *q1;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'a') {
            a = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'l') {
            l = 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'R') {
            r = 1;
        }
    }
    char c[20000];
    DIR * p;
    o = a + l + r + 1;
    if (argc - 1 >= o){
        q1 = argv[argc - 1];
    } else {
        getcwd(c, 20000);
        q1 = c;
    }
    for (i = 0; *(q1 + i) != '\0'; i++) {
        if (*(q1 + i) == '.') {
            f = 1;
        }
    }
    if (f == 1){
        printf("Имя файла - %s \n", q1);
        if (l == 1) {
            struct stat buf;
            stat(q1, &buf);
            printf("Тип файла - %d \n", 4);
            printf("Права доступа - %d \n", buf.st_mode);
            printf("Число ссылок на файл %lu \n", buf.st_nlink);
            printf("Размер файла - %ld \n", buf.st_size);
            printf("ID пользователя-владельца - %d \n", buf.st_uid);
            printf("ID группы-владельца - %d \n\n", buf.st_gid);
        }
    } else {
        p = opendir(q1);
        if (a == 1) {
            printf("Файлы из каталога --> %s\n", q1);
            if (r == 1) {
                pd(p, q1, l);
                printf("\n");
            } else {
                if (p != NULL) {
                    struct dirent *p1 = readdir(p);
                    while (p1 != NULL) {
                        printf("Имя файла - %s \n", p1->d_name);
                        if (l == 1) {
                            struct stat buf;
                            stat(p1->d_name, &buf);
                            printf("Тип файла - %d \n", p1->d_type);
                            printf("Права доступа - %d \n", buf.st_mode);
                            printf("Число ссылок на файл %lu \n", buf.st_nlink);
                            printf("Размер файла - %ld \n", buf.st_size);
                            printf("ID пользователя-владельца - %d \n", buf.st_uid);
                            printf("ID группы-владельца - %d \n\n", buf.st_gid);
                        }
                        p1 = readdir(p);
                    }
                }
            }
        }
    }
}