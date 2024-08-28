#include <math.h>

#include "libcp4.h"

double calculate_eps() {
    double eps = 1.0;
    for(; 1.0 + eps / 2.0 > 1.0; eps /= 2.0);
    return eps;
}

double fi(double (*f)(double), double x, double m) { return x - f(x) / m; }

double absolute(double n) { return (n >= 0.0) ? n : -n; }

double derivative(double (*f)(double), double x) {
    return (f(x + DELTA) - f(x - DELTA)) / (2.0 * DELTA);
}

double derivative2(double (*f)(double), double x) {
    return (derivative(f, x + DELTA) - derivative(f, x - DELTA)) / (2.0 * DELTA);
}

answer dichotomy(double (*f)(double), double a, double b, double eps) {
    answer result;
    if(f(a) * f(b) < 0) {
        do {
            if(f(a) * f((a + b) / 2.0) < 0)
                b = (a + b) / 2.0;
            else 
                a = (a + b) / 2.0;
            result.icount++;
        }
        while(b - a > eps);
        result.value = (a + b) / 2.0;
    }
    else {
        result.icount = -1;
        result.value = NAN;
    }

    return result;
}

answer iterations(double (*f)(double), double a, double b, double eps, double m) {
    answer result;

    double x0 = (a + b) / 2.0;
    double cx = x0;

    do {
        if(absolute(1 - derivative(f, x0) / m) > 1) {
            result.icount = -1;
            result.value = NAN;
            return result;
        }
        cx = x0;
        x0 = fi(f, x0, m);
        result.icount++;
    }
    while(absolute(cx - x0) > eps);

    result.value = x0;

    return result;
}

answer newton(double (*f)(double), double a, double b, double eps) {
    answer result;

    double x0 = (a + b) / 2.0;
    double cx = x0;

    do {
        double der1 = derivative(f, x0);
        double der2 = derivative2(f, x0);

        if(absolute(f(x0) * der2) > der1 * der1) {
            result.icount = -1;
            result.value = NAN;
            return result;
        }

        cx = x0;
        x0 = x0 - f(x0) / derivative(f, x0);
        result.icount++;
    }
    while(absolute(cx - x0) > eps);

    result.value = x0;

    return result;
}