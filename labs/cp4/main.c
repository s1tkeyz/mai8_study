#include <stdio.h>
#include <math.h>

#include "libcp4.h"

// First equation (20)
double f1(double x) { return 0.1 * x*x - x * log(x); }

// Second equation (21)
double f2(double x) { return tan(x) - pow(tan(x), 3) / 3.0 + pow(tan(x), 5) / 5.0 - 1.0 / 3.0; }

void solve(double (*f)(double), double a, double b, double theta, double m) {
    printf("Accuracy factor: %e\nSource range: [%.4f, %.4f]\n============\n", theta, a, b);

    answer answer_dichotomy = dichotomy(f, a, b, theta);
    printf("DICHOTOMY  | x0 = %.20f | count = %-3d |\n", answer_dichotomy.value, answer_dichotomy.icount);
    answer answer_iter = iterations(f, a, b, theta, m);
    printf("ITERATIONS | x0 = %.20f | count = %-3d |\n", answer_iter.value, answer_iter.icount);
    answer answer_newton = newton(f, a, b, theta);
    printf("NEWTON     | x0 = %.20f | count = %-3d |\n============\n", answer_newton.value, answer_newton.icount);

    // Calculate differences between results
    double DIdiff = answer_dichotomy.value - answer_iter.value;
    double INdiff = answer_iter.value - answer_newton.value;
    double DNdiff = answer_dichotomy.value - answer_newton.value;

    printf("D-I Diff. = %e\nI-N Diff. = %e\nD-N Diff. = %e\n============\n\n", DIdiff, INdiff, DNdiff);
}

int main(void) {
    const double delta = 75.0 * calculate_eps();
    solve(f1, 1.0, 2.0, delta, -1.0);
    solve(f2, 0.0, 0.8, delta, 1.0);
    return 0;
}