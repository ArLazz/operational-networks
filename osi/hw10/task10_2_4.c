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
/*Протестировать работу сигналов в используемой Вами системе. Написать тестовые программы, которые позволяют ответить на
  эти вопросы, и дать комментарий по поводу результатов — что у вас получилось.
  Возобновляет ли работу функция wait(), если во время ожидания пришел сигнал, или она завершается с ошибкой?
*/
void test(int s){
    printf("Получение сигнала - %d\n", getpid());
}
int main(){
    int pid1, s, x = 1, t;
    signal(SIGUSR1, test);
    t = getpid();
    if((pid1 = fork()) == 0){
        while (x != 0){
            scanf("%d", &x);
            printf("%d\n", getpid());
            if (x == 10){
                kill(t, SIGUSR1);
            }
        }
        exit(0);
    } else {
        printf("1 ");
        wait(&s);
    }
    if (s == 0){
        printf("Функция wait() восстановила работу\n");
    } else {
        printf("Функция wait() не восстановила работу\n");
    }
}
/* Вывод данной программы:
    artur@artur-HP-Pavilion-Notebook-15-dp0xxx:~/cmc/osi/hw10$ ./a.out
    1
    15421
    2
    15421
    10
    15421
    1 Получение сигнала - 15420
    0
    15421
    Функция wait() восстановила работу
    artur@artur-HP-Pavilion-Notebook-15-dp0xxx:~/cmc/osi/hw10$
Из вывода мы можем понять,что возобновляет работу функция wait(), если во время ожидания пришел сигнал.*/
