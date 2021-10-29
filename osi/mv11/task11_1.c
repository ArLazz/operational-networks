#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/signal.h>
#include <signal.h>
#include <sys/wait.h>
/* Программа. Процесс в командной строке получает имя файла. Длина строк в файле ограничена. Создает 2 сыновей.
Сыновья читают по строке из файла и выводят их на печать строго поочередно. 1-ый выводит нечетные строки, а 2-ой – четные.
Перед строкой напечатать pid выводящего ее процесса.
Синхронизировать работу сыновей через отца с помощью
 а) сигналов.
 */
int fd[2], tar_pid,tar_pid1, status, min, max, q, pid1, pid2, ss;
FILE *F1;

void so(int s) {
    char sq[80];
    if (fgets(sq, 80, F1)) {
        printf("Pid = %d --- string = %s", getpid(), sq);
        fflush(F1);
        kill(getppid(), SIGUSR1);
    } else {
        fflush(F1);
        kill(getppid(), SIGUSR1);
        exit(0);
    }
}

void fo(int s){
    static int c = 0;
    if (c % 2 == 0){
        kill(pid2, SIGUSR1);
        c = 1;
    } else {
        kill(pid1, SIGUSR1);
        c = 0;
    }
}

int main(int argc, char *argv[]){
    F1 = fopen(argv[1], "r");
    signal(SIGUSR1, so);
    if ((pid1 = fork())) {
        if ((pid2 = fork())) {
            signal(SIGUSR1, fo);
            kill(pid1, SIGUSR1);
            wait(&ss);
            wait(&ss);
        } else
            for(;;);
    } else
        for(;;);
}