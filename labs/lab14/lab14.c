#include <stdio.h>

void linearize(int n, int matt[n][n]) {
    printf("Linearized mattrix: ");

    int k = 1;

    printf("%d ", matt[n - 1][n - 1]);

    if(n > 1) {
        int i = n - 1;
        int j = n - 1;
        while(k < n) {
            if(k % 2) {
                if(i > 0) {
                    i--;
                    printf("%d ", matt[i][j]);
                    for(int q = 0; q < k; q++)
                        printf("%d ", matt[i][j - q - 1]);
                    j = j - k;
                    for(int r = 0; r < k; r++)
                        printf("%d ", matt[i + r + 1][j]);
                    i = i + k;
                    k++;
                }
            }
            else {
                if(j > 0) {
                    j--;
                    printf("%d ", matt[i][j]);
                    for(int q = 0; q < k; q++)
                        printf("%d ", matt[i - 1 - q][j]);
                    i = i - k;
                    for(int r = 0; r < k; r++)
                        printf("%d ", matt[i][j + 1 + r]);
                    j = j + k;
                    k++;
                }
            }
        } 
    }
}

int main(void) {
    int size = 0;
    printf("Enter mattrix size: ");
    scanf("%d", &size);

    int mattrix[size][size];

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j)
            scanf("%d", &mattrix[i][j]);
    }

    printf("Source mattrix:\n");
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j)
            printf("%d ", mattrix[i][j]);
        putchar('\n');
    }

    linearize(size, mattrix);
        putchar('\n');
    return 0;
}