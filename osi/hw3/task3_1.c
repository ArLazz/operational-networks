#include <stdio.h>


void bin(int k) {
    int c;
    unsigned q = 0x80000000;
    for (int i = 0; i < 32; i++) {
        c = k / q;
        printf("%d", c);
        k = k % q;
        q = q >> 1;
    }
    printf("\n");
}


int numbers_of_bits(int a) {
    int x = 0;
    while (a != 0) {
        x += a % 2;
        a /= 2;
    }
    return x;
}

void sortbin(int *array, int dimension){
    int x;
    for (int i = dimension - 1; i >= 0; i--){
        for (int j = 0; j < i; j++){
            if (numbers_of_bits(array[j]) > numbers_of_bits(array[j + 1])){
                x = array[j];
                array[j] = array[j + 1];
                array[j + 1] = x;
            }
            else if ((numbers_of_bits(array[j]) == numbers_of_bits(array[j + 1])) && (array[j] < array[j + 1])){
                x = array[j];
                array[j] = array[j + 1];
                array[j + 1] = x;
            }
        }
    }
}


int n,x;

int main(void){
    printf("%s", "Введите размер массива: ");
    scanf("%d", &n);
    int array[n];
    printf("%s", "Введите элементы массива: ");
    for (int  i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }
    printf("%s", "Введенные элементы массива в 10м виде: \n");
    for (int  i = 0; i < n; i++) printf("%d, ", array[i]);
    printf("%s", "\nВведенные элементы массива в 2м виде: \n");
    for (int  i = 0; i < n; i++) bin(array[i]);
    sortbin(array, n);
    printf("%s", "Ввенные элементы массива в 10м виде: \n");
    for (int  i = 0; i < n; i++) printf("%d, ", array[i]);
    return 0;
}