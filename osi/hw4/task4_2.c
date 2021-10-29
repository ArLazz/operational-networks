#include <stdio.h>
#include <stdlib.h>
#define length 4


char * func1(){
    int i = 0,n = 4;
    char q, *str1, *str = (char*)malloc(n);
    q = getchar();
    *str = q;
    i += 1;
    while ((q != '\n') && (q != EOF)){
        if (n <= (i + 1)){
            n += length;
            str1 = (char*)realloc(str, n);
            if (str1 == NULL){
                printf("Ошибка");
            }else{
                str = str1;
            }
        }
        q = getchar();
        *(str + i) = q;
        i += 1;
    }
    *(str + i) = '\0';
    return str;
}


void *func2(char *s1, char *s2){

    int i = 0, q = 0, n, f=0;
    char *e = NULL, *p1 = s1, *p2 = s2;

    while (s2[i] != '\n'){
        i += 1;
    }

    n = i - 1;
    i = 0;
    if (n == 0){
        while (*(p1 + i) != '\n'){
            if (*(p1 + i) == *p2){
                e = p1 + i;
                f = 1;
            }
            i += 1;
        }
    } else {
        while (*(p1 + i) != '\n'){
            if (*(p1 + i) == *(p2 + q)){
                q += 1;
                if (q == n){
                    e = p1 + (i - n + 1);
                    f = 1;
                }
            } else {q = 0;}
            i += 1;
        }
    }

    if(f == 1) {return e;}
    else {return NULL;}

}


int main(void){

    char *s1, *s2, *s3;

    s1 = func1();
    s2 = func1();
    s3 = func2(s1, s2);

    printf("%s", s3);

    return 0;
}