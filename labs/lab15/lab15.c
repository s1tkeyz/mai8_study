#include <stdio.h>
#include <stdlib.h>

int* turned(int n, int* matt) {
    int* copy = (int*)malloc(n * n * sizeof(int));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j)
            *(copy + n*j + i) = *(matt + n*i + (n - 1 - j));
    }
    return copy;
}

void print_mattrix(int n, int* matt) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j)
            printf("%d ", *(matt + n*j + i));
        putchar('\n');
    }
}

int main(void) {
    int n = 0;
    printf("Enter size: ");
    scanf("%d", &n);

    int* matt = (int*)malloc(n * n * sizeof(int));

    printf("Enter source mattrix: ");
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j)
            scanf("%d", (matt + n*j + i));
    }

    printf("Source mattrix:\n");
    print_mattrix(n, matt);

    printf("Turned mattrix:\n");
    int* new = turned(n, matt);
    print_mattrix(n, new);

    free(new);
    free(matt);
    
    return 0;
}