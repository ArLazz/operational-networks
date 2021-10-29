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
Обмен данными через один канал. Синхронизация обращений к каналу должна быть организована с помощью сигналов.
*/
int fd[2], tar_pid,tar_pid1, c, status, min, max, q, pid;
void sh(int s){
    if (c < max){
        read(fd[0], &c, sizeof(c));
        printf("%d - %d\n",getpid(), c);
        c += 1;
        write(fd[1], &c, sizeof(c));
        kill(tar_pid, SIGUSR1);
    } else if (tar_pid == pid) {
        read(fd[0], &c, sizeof(c));
        write(fd[1], &c, sizeof(c));
        close(fd[1]);
        close(fd[0]);
        exit(0);
    } else {
        read(fd[0], &c, sizeof(c));
        write(fd[1], &c, sizeof(c));
        kill(tar_pid, SIGUSR1);
    }
}

int main(int argc, char *argv[]) {
    pipe(fd);
    signal(SIGUSR1, sh);
    min = atoi(argv[1]);
    max = atoi(argv[2]);
    max -= 1;
    c = min;
    pid = getpid();
    if ((tar_pid = fork())) {
        write(fd[1], &c, sizeof(c));
        waitpid(tar_pid, NULL, q);
        read(fd[0], &c, sizeof(c));
        close(fd[1]);
        close(fd[0]);
        return 0;
    } else {
        if ((tar_pid = fork())) {
            waitpid(tar_pid, NULL, q);
            close(fd[1]);
            close(fd[0]);
            exit(0);
        } else {
            read(fd[0], &c, sizeof(c));
            tar_pid = pid;
            write(fd[1], &c, sizeof(c));
            kill(tar_pid, SIGUSR1);
            for (;;);
        }
    }
}