#include "libcp3.h"

// Returns the absolute value of n
double absolute(double n) { return (n > 0) ? n : -n; }

// Calculates the machine epsilon (by zzz)
double calculate_eps() {
    double eps = 1.0;
    for(; 1.0 + eps / 2.0 > 1.0; eps /= 2.0);
    return eps;
}

// Returns a^x
double power(double a, int x) {
    if(x == 0)
        return 1;
    int y = (x >= 0) ? x : -x;
    double res = a;
    while(y > 1) {
        res *= a;
        y--;
    }
    res = (x >= 0) ? res : 1.0 / res;
    return res;    
}

// Calculates f(x) = e^2x via Taylor's formula
f_value calculate_f(double x, double delta) {
    f_value result;
    result.icount = 0;
    result.value = 0.0;

    double S = 0.0;
    double factorial = 1.0;
    
    do {
        factorial = (result.icount == 1 || result.icount == 0) ? 1 : result.icount * factorial;
        S = power(2.0 * x, result.icount) / factorial;
        result.value += S;
        result.icount++;
    }
    while((absolute(S) > delta) && (result.icount < MAX_ITER_COUNT));

    return result; 
}