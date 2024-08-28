#include <stdio.h>
#include "liblab24-dss.h"

int main(void) {
    printf("F(x) = ");
    TQueue q = TQueue_create();
    if(!read_expression(&q)) {
        fprintf(stderr, "An error occured while expr. read. Terminating.\n");
        return EXIT_FAILURE;
    }
    printf("Expression queue: ");
    TQueue_print(&q);

    double x = 0.0;
    printf("x = ");
    scanf("%lf", &x);

    TQueue dss = TQueue_create();
    if(!dijkstra_sort(&q, &dss, x)) {
        fprintf(stderr, "Error while DSS.\n");
        return EXIT_FAILURE;
    }
    printf("\nPolish notation: ");
    TQueue_print(&dss);

    double f;
    calculate(&dss, &f);
    printf("F(%lf) = %lf\n", x, f);

    return EXIT_SUCCESS;
}