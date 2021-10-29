#include <stdio.h>


void format(int *array, int m, int n){
    int i = 0, j = 0, k = 1, m_2 = m, n_2 = n, i_2, j_2;
    while (k <= m * n){
        j_2 = j;
        for (i_2 = i; i_2 < m_2; i_2++){
            if (k <= m * n){
                *(array + (i_2 * n) + j_2) = k;
                k += 1;
            }
        }
        i_2 -= 1;
        for (++j_2; j_2 < n_2; j_2++){
            if (k <= m * n){
                *(array + (i_2 * n) + j_2) = k;
                k += 1;
            }
        }
        j_2 -= 1;
        for (i_2 = m_2 - 2; i_2 >= m - m_2; i_2--){
            if (k <= m * n){
                *(array + (i_2 * n) + j_2) = k;
                k += 1;
            }
        }
        i_2 += 1;
        for (j_2 = n_2 - 2; j_2 > n - n_2; j_2--){
            if (k <= m * n){
                *(array + (i_2 * n) + j_2) = k;
                k += 1;
            }
        }
        m_2 -= 1; n_2 -= 1; j += 1; i += 1;
    }
}


int main(void){
    int m, n;
    printf("%s", "Введите размер массива: ");
    scanf("%d", &m);
    scanf("%d", &n);
    int array[m][n];
    format(&array[0][0], m, n);
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < n; j++) {
            if (array[i][j] < 10){
                printf("%d   ", array[i][j]);
            }
            else if (array[i][j] > 99) {
                printf("%d ", array[i][j]);
            }
            else{
                printf("%d  ", array[i][j]);
            }
        }
        printf("\n");
    }
}




