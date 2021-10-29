#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
/*1. Реализовать игру в «ping-pong» для 3 процессов (кому мало, можно для произвольного N>=2 , N задавать в командной строке).
Главный процесс порождает двух (N-1) потомков по любой схеме (2 сына или сын-внук) и начинает передачу данных. Начальное
и конечное целые числа переданы в командной строке. Принимающий увеличивает число на 1 и передает дальше, и так по кругу
до тех пор, пока число не превысит заданный максимум.
Каждый процесс выводит на экран текущее число и свой pid.
Обмен данными через каналы (каждая пара процессов связана отдельным каналом).
*/
int main(int argc, char *argv[]) {
    int fd1[2], fd2[2], fd3[2], t, test, x, i;
    char c, s[80], q;
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    int min = atoi(argv[1]);
    int max = atoi(argv[2]);
    int pid1;
    int pid2;
    max += 1;
    write(fd3[1], &min, sizeof(min));
    if (pid1 = fork()) {
        close(fd1[1]);
        close(fd2[0]);
        while (1) {
            read(fd1[0], &x, sizeof(x));
            if (x == max) {
                write(fd2[1], &x, sizeof(x));
                break;
            }
            printf("%d - %d\n", getpid(), x);
            x += 1;
            write(fd2[1], &x, sizeof(x));
        }
        close(fd1[0]);
        close(fd2[1]);
    } else {
        if (pid2 = fork()) {
            close(fd2[1]);
            close(fd3[0]);
            while (1) {
                read(fd2[0], &x, sizeof(x));
                if (x == max) {
                    write(fd3[1], &x, sizeof(x));
                    break;
                }
                printf("%d - %d\n", getpid(), x);
                x += 1;
                write(fd3[1], &x, sizeof(x));
            }
            close(fd2[0]);
            close(fd3[1]);
        } else {
            close(fd3[1]);
            close(fd1[0]);
            while (1) {
                read(fd3[0], &x, sizeof(x));
                if (x == max) {
                    write(fd1[1], &x, sizeof(x));
                    break;
                }
                printf("%d - %d\n", getpid(), x);
                x += 1;
                write(fd1[1], &x, sizeof(x));
            }
            close(fd3[0]);
            close(fd1[1]);
        }
    }
}