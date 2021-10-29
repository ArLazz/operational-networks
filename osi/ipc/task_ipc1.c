#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>
#define NMAX 256
int main(int argc, char **argv){
    key_t key;
    int semid, shmid;
    struct sembuf sops;
    char *shmaddr;
    char str[9];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            str[i * 3 + j] = '0';
        }
    }
    key = ftok("/cmc/osi/ipc", 'S');
    semid = semget(key, 1, 0666 | IPC_CREAT);
    shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
    shmaddr = shmat(shmid, NULL, 0);
    semctl(semid,0,SETVAL, (int) 0);
    sops.sem_num = 0;
    sops.sem_flg = 0;
    int u = 1, q, f = 0;
    do {
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (str[i * 3 + j] == '0') {
                    printf("_");
                } else if (str[i * 3 + j] == '1') {
                    printf("O");
                } else if (str[i * 3 + j] == '2') {
                    printf("X");
                }
            }
            printf("\n");
        }
        printf("Введите %d крестик в формате XX(где 1 число - № строки,2 число - № столбца):", u);
        scanf("%d", &q);
        q -= 11;
        str[(q / 10) * 3 + q % 10] = '2';
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (str[i * 3 + j] == '0') {
                    printf("_");
                } else if (str[i * 3 + j] == '1') {
                    printf("O");
                } else if (str[i * 3 + j] == '2') {
                    printf("X");
                }
            }
            printf("\n");
        }
        for (int i = 0; i < 3; i++){
            if (str[i * 3 + 1] == '2' && str[i * 3 + 2] == '2' && str[i * 3 + 0] == '2' ||
                str[3 + i] == '2' && str[i + 6] == '2' && str[i + 0] == '2' ||
                str[0] == '2' && str[4] == '2' && str[8] == '2' ||
                str[2] == '2' && str[4] == '2' && str[6] == '2') {
                printf("Крестики победили.\n");
                str[0] = '8';
            }
        }
        if (u == 5){
            str[0] = '9';
            printf("Игра закончилась.\n");
        }
        strcpy(shmaddr, str);
        if (str[0] == '9' || str[0] == '8'){
            break;
        }
        sops.sem_op = 3;
        semop(semid, &sops, 1);
        sops.sem_op = 0;
        semop(semid, &sops, 1);
        u += 1;
        printf("Waiting… \n");
        sops.sem_op = -2;
        semop(semid, &sops, 1);
        strcpy(str, shmaddr);
        if (str[0] == '9'){
            break;
        }
        if (str[0] == '8'){
            printf("Вы проиграли.\n");
            break;
        }
        sops.sem_op=-1;
        semop(semid, &sops, 1);
    } while (u != 6);
    shmdt(shmaddr) ;
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, (int) 0);
    return 0;
}