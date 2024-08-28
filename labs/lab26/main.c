#include <stdio.h>
#include "liblab26-sort.h"

int main(void) {
    TStack* stack = ts_create();

    printf("Enter stack values: ");
    int c = getchar();
    while(c != EOF && c != '\n') {
        ungetc(c, stdin);
        T t;
        if(!T_fromstdin(&t))
            break;
        ts_push(stack, t);
        c = getchar();
    }

    hoare_sort(stack);

    printf("Sorted stack: ");
    while(!ts_empty(stack)) 
        printf("%d ", ts_pop(stack).value);
    putchar('\n');
    return EXIT_SUCCESS;
}