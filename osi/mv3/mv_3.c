#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct  symbol{
    char sym;
    struct symbol *next;
} list1;
typedef struct  line{
    char *c;
    struct line *next;
} list2;

void newsymbol(list1 *lst){
    list1 *t;
    t = (struct symbol *) malloc(sizeof(list1));
    lst -> next = t;
    t -> next = NULL;
}

void newline(list2 *list) {
    list2 *t;
    t = (struct line *) malloc(sizeof(list2));
    list->next = t;
    t->next = NULL;

}
void outputandfree(list2 *list){
    list2 *p;
    char *b;
    while (list != NULL){
        b = list -> c;
        printf("%s\n", b);
        p = list;
        list = list->next;
        free(p);
    }
    printf("\n");
}
void output(list2 *list){
    char *b;
    list = list -> next;
    while (list->next != NULL) {
        b = list->c;
        printf("%s\n", b);
        list = list->next;
    }
}

void func1(list2 *list, char c){
    list2 *w, *e, *q;
    int i;
    char *b, *a;
    while (list != NULL) {
        b = list -> c;
        i = strlen(b) - 1;
        if (b[i] == c){
            q = list -> next;
            newline(list);
            e = list ->next;
            a = (char *) malloc(3);
            a = "222";
            e -> c = a;
            e -> next = q;
        }
        list = list -> next;
    }
}
void func2(list2 *list, char a){
    int f = 0, i = 0;
    list2 *w, *e, *q;
    char *b;
    while (list ->next != NULL){
        b = list -> next -> c;
        while (b[i] != '\0'){
            if (b[i] == a){
                f = 1;
            }
            i += 1;
        }
        if (f) {
            w = list ->next;
            e = w -> next;
            newline(list);
            list -> next = e;
            free(w);
        }
        f = 0;
        i = 0;
        list = list -> next;
    }
}

int main() {
    char a, a1, a2, *b;
    int i = 0, j;
    list2 *list, *t, *start;
    list1 *c, *s, *starts;
    start = list;
    printf("Введите букву для первой части\n");
    a1 = getchar();
    printf("Введите букву для второй части\n");
    a2 = getchar();
    a2 = getchar();
    printf("Введите список строк\n");
    a = getchar();
    while (a != EOF){
        starts = (struct symbol *) malloc(sizeof(list1));
        s = starts;
        while (a != '\n' && a != EOF){
            newsymbol(s);
            s = s -> next;
            s -> sym = a;
            a = getchar();
            i += 1;
        }

        b = (char *) malloc(i);
        s = starts -> next;
        j = 0;
        while (s != NULL){
            *(b + j) = s->sym;
            j += 1;
            c = s;
            s = s -> next;
            free(c);
        }
        i = 0;
        *(b + j) = '\0';
        newline(list);
        list -> c = b;
        list = list -> next;
        a = getchar();
    }
    printf("\n");
    printf("Введеный вами список:\n");
    list = start;
    output(list);

    func1(list, a1);
    list = start;
    printf("Преобразованный по первому правилу список:\n");
    output(list);

    func2(list, a2);
    list = start;
    printf("Преобразованный по второму правилу список:\n");
    output(list);
}