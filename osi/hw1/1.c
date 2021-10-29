#include <stdio.h>


int N1, N2, S;


int pal(int N1, int N2){
    int x = 0;
    int s = 0;
    for (int n = N1; n <= N2; n ++){
        x = 0;
        int k = n;
        while (k != 0){
            x = x * 10 + k % 10;
            k = k / 10;
        }
        if (x == n){
            s += 1;
             printf("%d\n", n);
        }
    }
    return s;
}


int main(){
    scanf("%d",&N1);
    scanf("%d",&N2);
    if (N1 == 0 || N2 == 0){
        return 0;
    }
    else if (N1 > N2){
        printf("Некорректно введены числа\n");
        return 0;
    }
    else{
        S = pal(N1, N2);
        printf("Количество палиндромов - %d\n", S);
        return 0;
    }
}    
