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
1) Сбрасывается ли обработка сигнала на значение по умолчанию после вызова
обработчика, если нет явной переустановки?
 */
void test1(int s){
    printf("123\n");
    return;
}
int main(){
    signal(SIGTSTP, test1);
    for(;;)
        pause();
}
/* Вывод данной программы:
    artur@artur-HP-Pavilion-Notebook-15-dp0xxx:~/cmc/osi/hw10$ ./a.out
    ^Z123
    ^Z123
    ^Z123
    ^Z123
    ^Z123
    ^C
    artur@artur-HP-Pavilion-Notebook-15-dp0xxx:~/cmc/osi/hw10$

Из вывода мы можем понять, что обработка сигнала на значение по умолчанию не сбрасывается,т.к. если бы сбрасывалось,то
 после второго ^Z программа бы выполнила стандартную реакцию на сигнал и завершила бы программу.
