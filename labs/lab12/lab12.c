#include <stdio.h>

int abs(int n) { return (n > 0) ? n : -n; }

void solve(int n) {
    printf("For %d: ", n);
    n = abs(n);
    int pos = 0;
    while(n > 99) {
            int d = n % 10;
            n /= 10;
            int p = n % 100;
            if(d == (p / 10) + (p % 10))
                printf("%d (pos=%d); ", d, pos);
            pos++;
    }
    printf("\n");
}

int main(void) {
    int n = 0;
    while(scanf("%d", &n) == 1)
        solve(n);
    return 0;
}