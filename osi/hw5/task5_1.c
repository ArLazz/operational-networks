#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct N1 {
    char mychar;
    struct N1 *next;
} l1;
typedef struct N {
    char *c;
    struct N *next;
    struct N *prev;
} l2;


l1 *plus1(l1 *lst) {
    l1 *t;
    t = (struct N1 *) malloc(sizeof(l1));
    lst->next = t;
    t->next = NULL;
    return (t);
}
l2 *plus2(l2 *lst) {
    l2 *t;
    t = (struct N *) malloc(sizeof(l2));
    lst->next = t;
    t->prev = lst;
    t->next = NULL;
    return (t);
}


struct N1 *plus1(struct N1 *lst);
struct N *plus2(struct N *lst);


void outputrev(l2 *l){
    printf("Последовательность слов в обратном порядке:\n");
    while (l != NULL){
        printf("%s ", l->c);
        l = l->prev;
    }
    printf("\n");
}


void outputandfree(l2 *l){
    printf("Послеловательность слов в алфавитном порядке(букв больше-слово правее):\n");
    l2 *p;
    while (l->next != NULL){
        printf("%s ", l->c);
        p = l;
        free(l->c-1);
        l = l->next;
        free(p);
    }
    printf("\n");
}


void res(l2 *l){
    int i;
    char *b, *a;
    l2 *p;
    while (l->next->next != NULL){
        p = l->next;
        while (p->next != NULL){
            i = 0;
            b = p->c;
            a = l->c;
            while (*(a + i) == *(b + i) && *(a + i) != '\0' && *(b + i) != '\0'){
                i++;
            }
            if (*a != '\0' && *b != '\0'){
                if (*(a + i) > *(b + i)) {
                    l->c = b;
                    p->c = a;
                }
            } else {
                if (*(a + i - 1) > *(b + i - 1)){
                    l->c = b;
                    p->c = a;
                }
            }
            p = p->next;
        }
        l = l->next;
    }
}


int main(void) {
    l1 *t1, *st1, *pt1;
    l2 *p2, *l2, *st2, *end2;
    char q, *b;
    int i = 0, k = 1, z = 1, w = 0, j;
    st1 = (struct N1 *) malloc(sizeof(l1));
    t1 = st1;
    st2 = (struct N *) malloc(sizeof(l2));
    st2->prev = NULL;
    l2 = st2;
    printf("Последовательность слов:\n");
    q = getchar();
    while (q != EOF && q != '\n'){
        if (q != ' ') {
            if (z == 1) {
                i = 0;
                z = 0;
            }
            pt1 = plus1(t1);
            t1 = t1->next;
            t1->mychar = q;
            i += 1;
            w = 1;
        } else {
            if (i != 0) {
                t1 = st1;
                j = 0;
                b = (char *) malloc(sizeof(char) * (i));
                while (t1 != NULL){
                    *(b + j) = t1->mychar;
                    j += 1;
                    pt1 =t1;
                    t1 = t1->next;
                    free(pt1);
                }
                *(b + j) = '\0';
                p2 = plus2(l2);
                l2->c = b + 1;
                l2 = l2->next;
                st1 = (struct N1 *) malloc(sizeof(l1));
                t1 = st1;
            }
            z = 1;
            w = 0;
            i = 0;
        }
        q = getchar();
    }

    if (i != 0){
        t1 = st1;
        j = 0;
        b = (char *) malloc(sizeof(char) * i);
        while (t1 != NULL) {
            *(b + j) = t1->mychar;
            j++;
            t1 = t1->next;
        }
        *(b + j) = '\0';
        l2->c = b + 1;
    }
    if (l2->c == NULL){
        end2 = l2;
    } else {
        end2 = plus2(l2);
    }


    l2 = end2->prev;
    outputrev(l2);


    l2 = st2;
    res(l2);


    l2 = st2;
    outputandfree(l2);


    return 0;
}


