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
/*2. Протестировать работу сигналов в используемой Вами системе. Написать тестовые программы, которые позволяют ответить
на эти вопросы, и дать комментарий по поводу результатов — что у вас получилось.
2) Блокируется ли на время работы обработчика
а) тот же сигнал, что в данный момент обрабатывается,
б) другие сигналы?
 */
void test1(int s){
    printf("Перехват ^Z и запуск бесконечного цикла\n");
    for(;;);
}
void test2(int s){
    printf("\nПерехват ^С и вывод 1\n");
    for(int i = 0; i < 10; i++){
        printf("%d", 1);
    }
    printf("\n");
    exit(1);
}
int main(){
    signal(SIGTSTP, test1);
    signal(SIGINT, test2);
    for(;;)
        pause();
}
/* Вывод данной программы:
    artur@artur-HP-Pavilion-Notebook-15-dp0xxx:~/cmc/osi/hw10$ ./a.out
    ^ZПерехват ^Z и запуск бесконечного цикла
    ^Z^Z^Z^Z^Z^Z^C
    Перехват ^С и вывод 1
    1111111111
    artur@artur-HP-Pavilion-Notebook-15-dp0xxx:~/cmc/osi/hw10$
Из вывода мы можем понять,что на время работы обработчика тот же сигнал,что в данный момент находится в обработке -
 блокируется, т.к. после второго ^Z у нас не вывелся текст "Перехват ^Z и запуск бесконечного цикла", а другие сигналы не
 блокируются, т.к. при вызове ^C, у нас запустился обработчик test2,вывел 1111111111 и завершил работу.
 */
