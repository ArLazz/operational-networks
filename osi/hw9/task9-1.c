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
/*В командной строке передаются имена двух исполняемых файлов, для каждого передается по одному параметру. Также должен быть передан параметр, определяющий режим запуска — параллельно (1) или последовательно (2).
Командная строка выглядит примерно так:
>./a.out prog1 arg11 prog2 arg21 1
В зависимости от значения последнего параметра запустить эти программы
с использованием векторной передачи данных для параллельного исполнения ( т. е. работают одновременно) .
или запустить эти программы с использованием передачи данных в виде списка для последовательного исполнения ( работают строго одна после другой) .
Определить, завершились ли они успешно (с точки зрения программы — узнать, что вернул exit, и с точки зрения системы).
По окончании работы не должно остаться процессов «зомби».
Для тестирования напишите программу (достаточно одной), которая должна работать не слишком быстро и осуществлять вывод на экран (пусть многократно выводит pid процесса), и запускайте ее.
*/
int main(int argc, char *argv[]) {
    int i,j,k,l,x,y,s1 = 0,s2 = 0;
    char c, *q1[3];
    j = atoi(argv[5]);
    if (j == 1){
        if (fork() == 0){
            q1[0] = argv[1];
            q1[1] = argv[2];
            q1[2] = NULL;
            execv(argv[1], q1);
            exit(1);
        } else {
            if (fork() == 0) {
                q1[0] = argv[3];
                q1[1] = argv[4];
                q1[2] = NULL;
                execv(argv[3], q1);
                exit(1);
            }
        }
        wait(&s1);
        wait(&s2);
    } else {
        if (fork() == 0) {
            execl(argv[1], argv[1], argv[2], NULL);
            exit(1);
        } else {
            wait(&s1);
            if (fork() == 0) {
                execl(argv[3], argv[3], argv[4], NULL);
                exit(1);
            }
        }
        wait(&s2);
    }
    if (s1 == 0){
        printf("Первая программа завершилась.\n");
    }  else {
        printf("Первая программа  завершилась авайрийно.\n");
    }
    if (s2 == 0){
        printf("Вторая программа завершилась.\n");
    }  else {
        printf("Вторая программа завершилась аварийно.\n");
    }
}