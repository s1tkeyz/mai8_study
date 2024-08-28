#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#include "libcp3.h"

int main(void) {
    const double delta = 500.0 * calculate_eps(); // Defines the accuracy of calculation

    // Lower and higher bounds (a < b)
    const double a = -0.1;
    const double b = 0.6;

    printf("Accuracy factor: %e\n", delta);
    printf("Calculation range: [%.5f, %.5f]\n", a, b);

    int64_t n = 0;
    printf("Enter number of cuts: ");
    scanf("%ld", &n);
    printf("===========\n");

    for(int64_t i = 0; i <= n; i++) {
        double x = a + (double)i * ((b - a) / (double)n);

        f_value f = calculate_f(x, delta);
        double ref_f = exp(2 * x);

        printf("| N = %-3ld | x = %.5f | f(x) = %.16f | ref.f(x) = %.16f | i = %-3d | err = %e |\n", i + 1, x, f.value, ref_f, f.icount, ref_f - f.value);
    }

    printf("===========\n");

    return 0;
}