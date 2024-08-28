#include <stdio.h>

long int bar(long int n) {
    if (n == 0)
        return 1;
    else if (n < 0)
        return n - 1;
    else if(n > 0 && n < 10)
        return n + bar(n - 1);
    else
        return 2 * (n - 5) * bar(n - 5);
}

long int foo(long int n) {
    if(n == 0)
        return 0;
    else if (n < 0)
        return 1 - n;
    else
        return n + foo(n - 3) - (bar(n - 2) % 17);
}

long int f() {
    int k = 7 - 2;
    return k;
}

int main(void) {
    long int n = f();
    printf("%ld\n", bar(n));
    return 0;
}