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

/*Разбор командной строки осуществляется Shelloм по следующим правилам:
<Команда Shellа > →
    < Команда с условным выполнением >{ [; | &] < Команда Shellа>}{ ; |&}

<Команда с условным выполнением > →
        <Команда> { [&& | || ] <Команда с условным выполнением>}
<Команда> → {<перенаправление ввода/вывода>}<Конвейер> |
        <Конвейер>{<перенаправление ввода/вывода>} | ( <Команда Shellа>)
<перенаправление ввода/вывода> →
    {<перенаправление ввода > } <перенаправление вывода> |
    {<перенаправление вывода>}<перенаправление ввода >
<перенаправление ввода > → ‘<’ файл
<перенаправление вывода> → ‘>’ файл | ‘>>’ файл
<Конвейер>→ <Простая команда> {‘|’ <Конвейер>}
<Простая команда>→ <имя команды><список аргументов>
*/
int counter = 0;
struct info {
    char **argv;//простая команда с аргументами
    char *input;//перенаправление ввода
    char *output;// перенаправление вывода c созданием файлаж
    char *output1;//перенаправление вывода с созданием файла или записью в конец
    int bg;//работа в фоне
    struct info *c1;//после &&
    struct info *c2;//после ||
    struct info *shell;// новый shell
    struct info *palka;// команда после |
    struct info *next;// команда после ;
    struct info **arr;// массив
};
void r(struct info *q){
    q -> argv = NULL;
    q -> input = NULL;
    q -> output = NULL;
    q -> output1 = NULL;
    q -> bg = 0;
    q -> c1 = NULL;
    q -> c2 = NULL;
    q -> shell = NULL;
    q -> palka = NULL;
    q -> next = NULL;
}

/*void parse(char *argv[], int s, int argc) {
    if (s == argc - 1)
        return 0;
    if (strcmp(string, "<") == 0){
        redirection_input(argv[s + 1]);
        parse(argv, s + 2, argc);
    }
    if (strcmp(string, ">") == 0 || strcmp(string, ">>") == 0){
        redirection_output(argv[s + 1]);
        parse(argv, s + 2, argc);
    }
    if (argv[s][0] >= 'a' && argv[s][0] <= 'z' || argv[s][0] >= 'A' && argv[s][0] <= 'Z' || argv[s][0] >= '0' && argv[s][0] <= '9'){
        for (int i = s; argv[i][0] >= 'a' && argv[i][0] <= 'z' || argv[i][0] >= 'A' && argv[i][0] <= 'Z' || argv[i][0] >= '0' && argv[i][0] <= '9'; i++);
        char* e[i - s];
        for (int j = s; j <= i; j++){

        }
    }
}*/
struct info ** cratearr(struct info *Infocmd,struct info ** a){
    struct info *p = Infocmd;
    int i = 0, b = 256;
    a = calloc(b, sizeof (Infocmd));
    a[0] = p;
    while(1){
        if (p -> shell != NULL)
            p -> arr = cratearr(p -> shell, p -> arr);
        if (p -> palka != NULL)
            p = p -> palka;
        else if (p -> c1 != NULL)
            p = p -> c1;
        else if (p -> c2 != NULL)
            p = p -> c2;
        else if (p -> next != NULL){
            if (i >= b){
                b += 256;
                a = realloc(a, b * sizeof (Infocmd));
            }
            i += 1;
            a[i] = p;
            p = p -> next;
            i += 1;
            a[i] = p;
        } else {
            i += 1;
            a[i] = p;
            a[i + 1] = NULL;
            return a;
        }
    }
}
struct info* parse(struct info *Infocmd, char **words) {
    struct info *q = calloc(1, sizeof(struct info)), *w;
    r(q);
    int j = 0, f = 1;
    Infocmd = q;
    w = Infocmd;
    //printf("123\n");
    while (words[j] != NULL){
        if (strcmp(words[j],"<") == 0){
            w -> input = words[j + 1];
            j += 2;
            f = 1;
        } else if (strcmp(words[j],">") == 0) {
            w -> output = words[j + 1];
            j += 2;
            f = 1;
        } else if (strcmp(words[j],">>") == 0) {
            w->output1 = words[j + 1];
            j += 2;
            f = 1;
        } else if (strcmp(words[j],"|") == 0) {
            q = calloc(1 , sizeof(struct info));
            r(q);
            w -> palka = q;
            w = w -> palka;
            j += 1;
            f = 1;
        } else if (strcmp(words[j],"(") == 0) {
            w -> shell = parse(w -> shell, words + j + 1);
            j += counter + 1;
            continue;
        } else if (strcmp(words[j],")") == 0) {
            j += 1;
            counter = j;
            return Infocmd;
        } else if (strcmp(words[j],";") == 0) {
            if (words[j + 1] != NULL) {
                q = calloc(1, sizeof(struct info));
                r(q);
                w -> next = q;
                w = w -> next;
            }
            f = 1;
            j += 1;
        } else if (strcmp(words[j],"&") == 0) {
            w -> bg = 1;
            if (words[j + 1] != NULL) {
                q = calloc(1, sizeof(struct info));
                r(q);
                w -> next = q;
                w = w -> next;
            }
            f = 1;
            j += 1;
        } else if (strcmp(words[j],"&&") == 0) {
            if (words[j + 1] != NULL) {
                q = calloc(1, sizeof(struct info));
                r(q);
                w -> c1 = q;
                w = w -> c1;
            }
            f = 1;
            j += 1;
        } else if (strcmp(words[j],"||") == 0) {
            if (words[j + 1] != NULL) {
                q = calloc(1, sizeof(struct info));
                r(q);
                w -> c2 = q;
                w = w -> c2;
            }
            f = 1;
            j += 1;
        } else if (words[j] != NULL) {
            //printf("123\n");
            w -> argv = realloc(w -> argv, f * sizeof(char*) + 1);
            //printf("123\n");
            w -> argv[f - 1] = words[j];
            w -> argv[f] = NULL;
            f += 1;
            j += 1;
        }
    }
    return Infocmd;
}

int outfunc(struct info *Infocmd){
    int f = 1;
    if (Infocmd -> output != NULL){
        int F = open (Infocmd -> output, O_CREAT|O_TRUNC|O_WRONLY, 0666);
        dup2 (F, 1);
        close (F);
    }
    else if (Infocmd -> output1 != NULL) {
        int F = open (Infocmd -> output1, O_CREAT|O_APPEND|O_WRONLY, 0666);
        dup2 (F, 1);
        close (F);
    } else {
        f = 0;
    }
    return f;
}

int infunc(struct info *Infocmd){
    if (Infocmd->input) {
        int F = open (Infocmd->input, O_RDONLY);
        dup2 (F, 0);
        close(F);
    }
}
void func();

void main1 (struct info *start, struct info *finish) {
    struct info *p = start;
    int status = 0, f1 = 1, f2 = 1, OutS = dup (1),  fd[2];
    pid_t pid;

    while  (p != finish) {
        if (f1 == 0) {
            if (p -> c1) {
                p = p -> c1;
                continue;
            } else if (p -> c2) {
                p = p->c2;
                f1 = 1;
                continue;
            } else if (p->palka) {
                p = p->palka;
                continue;
            } else
                break;
        }
        if (f2 == 0) {
            if (p -> c1) {
                p = p -> c1;
                f2 = 1;
                continue;
            } else if (p->c2) {
                p = p->c2;
                continue;
            } else if (p->palka) {
                p = p->palka;
                continue;
            } else
                break;
        }

        infunc(p);
        outfunc(p);
        
        if  (p -> palka != NULL) {
            pipe(fd);
            if (fork()==0) {
                close (fd[0]);
                if (outfunc(p) == 0)
                    dup2 (fd[1], 1);
                close (fd[1]);
                if (p -> shell != NULL)
                    func (p -> arr);
                else
                    execvp(p -> argv[0], p -> argv);
                exit(0);
            }
            else {
                dup2(fd[0], 0);
                close(fd[0]);
                close(fd[1]);
                p = p->palka;
            }
        }
        else if (p -> c1) {
            if (p -> output == NULL && p->output1 == NULL)
                dup2(OutS, 1);
            else
                outfunc(p);
            if ((pid = fork()) == 0) {
                if (p -> shell != NULL)
                    func (p -> arr);
                else
                    execvp(p -> argv[0], p -> argv);
                exit(0);
            }
            p = p->c1;
            waitpid (pid, &status, 0);
            f1 = (WIFEXITED(status) && !WEXITSTATUS(status));//WIFEXITED - не равно нулю(равно 1), если дочерний процесс успешно завершился.
        }
        else if (p -> c2) {
            if (p -> output == NULL && p->output1 == NULL)
                dup2(OutS, 1);
            else 
                outfunc(p);
            if ((pid = fork()) == 0) {
                if (p -> shell != NULL) {
                    func(p->arr);
                }
                else
                    execvp(p -> argv[0], p -> argv);
                exit(0);
            }
            p = p->c2;
            waitpid (pid, &status, 0);
            f2 = !(WIFEXITED(status) && !WEXITSTATUS(status));//WIFEXITED - не равно нулю(равно 1), если дочерний процесс успешно завершился.
        }
    }
    if (!f1 || !f2) {
        while (wait(0) > 0);
        return;
    } else
        infunc(p);
    outfunc(p);
    if ((pid = fork()) == 0) {
        if (p -> output == NULL && p->output1 == NULL)
            dup2(OutS, 1);
        else 
            outfunc(p);
        if (p -> shell != NULL) {
            func(p->arr);
        }
        else
            execvp(p -> argv[0], p -> argv);
        exit(0);
    } else {
        waitpid(pid, &status, 0);
    }
}

void func ( struct info **a) {
    int InS = dup (0);
    int OutS = dup (1);
    int i = 0;
    while (a[i]) {
        if (a[i+1] -> bg == 1) {
            if (fork() == 0) {
                if (fork() == 0) {
                    signal(SIGINT, SIG_IGN);
                    int f = open("/dev/null", O_RDWR | 0666);
                    dup2(f, 0);
                    close(f);
                    f = open("/dev/null", O_RDWR | 0666);
                    dup2(f, 1);
                    close(f);
                    main1(a[i], a[i + 1]);
                    exit(0);
                } else {
                    raise(SIGTERM);
                }
            }
        } else {
            main1(a[i], a[i + 1]);
        }
        dup2(InS, 0);
        dup2(OutS, 1);
        i += 2;
    }
}

char ** splitting(char ** words, char *string, int count){
    char **helpwords = calloc(count + 1, sizeof(char *));
    int s[count];
    int i, j, c;
    //printf("123\n");
    for(i = 0, j = 0, c = 0; string[i] != '\0'; i++){
        if (string[i] == ' '){
            s[j] = c;
            c = 0;
            j += 1;
        } else {
            c += 1;
        }
    }
    s[count - 1] = c;
    for (i = 0,c = 0, j = 0; i <= count - 1; i++) {
        char *word = calloc(s[i] + 1, 1);
        while (string[j] != ' ' && string[j] != '\0') {
            word[c] = string[j];
            j += 1;
            c += 1;
        }
        helpwords[i] = word;
        c = 0;
        j += 1;
     }
    helpwords[count] = NULL;
    words = helpwords;
    return words;
}
char *inputstr(){
    int i = 0, buf = 8, f_ = 0, fs = 0;
    char q, *s = NULL;
    s = calloc(buf, 1);
    while((q = getchar()) != '\n') {
        if (q != ' ') {
            if (i == buf) {
                buf += 8;
                s = realloc(s, buf);
            }
            s[i] = q;
            i += 1;
            if (f_ == 1)
                f_ = 0;
            if (fs == 0)
                fs = 1;
        } else if ((q == ' ') && (f_ == 0) && (fs == 1)) {
            if (i == buf) {
                buf += 8;
                //printf("123\n");
                s = realloc(s, buf);
            }
            s[i] = q;
            f_ = 1;
            i += 1;
            counter += 1;
        }
    }
    if (i == 0){
        free(s);
        return NULL;
    }
    if (s[i - 1] == ' ')
        s[i - 1] = 0;
    else
        counter += 1;
    s[i] = 0;
    return s;
}



void free1(struct info *L) {
    if (L -> argv)
        free(L -> argv);
    if (L -> c1)
        free1(L -> c1);
    if (L -> c2)
        free1(L -> c2);
    if (L -> shell)
        free1(L -> shell);
    if (L -> palka)
        free1(L -> palka);
    if (L -> next)
        free1(L -> next);
    free(L);
    return;
}


int main(int argc, char *argv[]) {
    struct info *Infocmd, **a;
    char *string, c;
    int s1 = dup(1), count = 0;
    int s0 = dup(0);
    while(1) {
        printf("Напишите команду ( выход - exit() ) >> ");
        string = inputstr();
        if (string == NULL){
            printf("Вы ничего не ввели - Напишите команду ( выход - exit() ) >> ");
            continue;
        }
        if (strcmp(string, "exit()") == 0){
            printf("Вы точно хотите выйти (Y/N)?\n");
            c = getchar();
            if (c == 'Y'){
                return 0;
            } else { if (c == 'N') {
                    string = inputstr();
                    continue;
                }
            }
        }
        char **words;
        count = counter;

        //printf("123\n");
        words = splitting(words, string, count);
        Infocmd = parse(Infocmd, words);
        counter = 0;
//        printf("\n");
//        for (int i = 0; i < count; i++){
//            printf("%s -- ", words[i]);
//        }
        printf("\n");
        a = cratearr(Infocmd, a);
        func(a);
        free1(Infocmd);
        int i = 0;
        while (words[i]) {
            free(words[i]);
            i++;
        }
        free(words);
        free(a);
        free(string);
        while (wait(0) > 0);
        printf("\n");
   }
}