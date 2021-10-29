#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    int j = atoi(argv[argc - 1]);
    printf("Вывод PID процесса %d раз(а):\n", j);
    for(int i = 0; i < j; i++)
        printf("%d\n", getpid());
    return 0;
}