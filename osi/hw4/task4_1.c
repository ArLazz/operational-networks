#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define length 4


char * func(){
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


int main(void){
    char  *c;
    c = func();
    printf("%s", c);
    return 0;
}
