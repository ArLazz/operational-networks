
int main(int argc, char *argv[]) {
    int fd[2], fd1[2], t, test, x, i;
    char c, s[80], q;
    pipe(fd);
    pipe(fd1);
    int File = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0660);
    int pid1 = fork();
    if (pid1) {
        close(fd[1]);
        close(fd1[0]);
        while (1) {
            read(fd[0], &q, sizeof(q));
            read(fd[0], s, 80);
            if (strcmp(s, "exit") == 0) {
                t = -1;
                write(fd1[1], &t, sizeof(t));
                break;
            } else {
                t = 1;
                write(fd1[1], &t, sizeof(t));
            }
            int u = 0;
            for (i = 0; i < strlen(s);i++){
                if (s[i] == q){
                    u += 1;
                }
            }
            if (u >= 10){
                c = '0';
                c += u / 10;
                write(File, &c, sizeof(c));
            }
            c = '0';
            c += u % 10;
            write(File, &c, sizeof(c));
            write(File, "\n", 1);
        }
        close(fd[0]);
        close(fd1[1]);
    } else {
        close(fd[0]);
        close(fd1[1]);
        char s[80];
        while (1) {
            printf("Введите строку(конец ввода exit):\n");
            scanf("%s", s);
            if (strcmp(s, "exit") == 0)
                break;
            fgetc(stdin);
            printf("Введите символ:\n");
            c = fgetc(stdin);
            write(File, s, strlen(s));
            write(File, "\n", 1);
            write(fd[1], &c, sizeof(c));
            write(fd[1], &s, strlen(s) + 1);
            read(fd1[0], &test, sizeof(test));
            if (test == -1) {
                break;
            }
        }
        close(fd1[0]);
        close(fd[1]);
    }
    close(File);
}