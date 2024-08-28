// lab9 main source
#include "liblab9.h"
#include <stdio.h>

// constants
#define I_0 -15
#define J_0 -15
#define L_0 -4

int main(void) {
    int step = 0;

    int l = L_0;

    point x;
    x.i = I_0; 
    x.j = J_0;

    circle w1;
    w1.o.i = -10; 
    w1.o.j = -10;
    w1.r = 10;

    circle w2;
    w2.o.i = -20; 
    w2.o.j = -20;
    w2.r = 10;
    
    for (int k = 0; k < 50; k++) {
        step += 1;

        // pre-calc check
        if (point_power(x, w1) < 0 && point_power(x, w2) < 0) {
            printf("Hit on step %d! i=%d, j=%d, l=%d\n", step, x.i, x.j, l);
            return 0;
        }

        // cached values
        int ci = x.i; 
        int cj = x.j;
        int cl = l;

        // calculate new values
        x.i = div(mod(ci + cj, 30), (mod(abs(cl), 5) + 1)) + div(mod(ci + cl, 30), (mod(abs(cj), 5) + 1));
        x.j = mod(max(k*ci, (k + 1)*cj), 25) - div(abs(cj - cl), 10);
        l = div(abs(cj - cl), 10) + min(mod(ci + cl, 20), mod(k*cj, 20)) - 10;
    }

    printf("Missed! Maximum step count exceeded.\n");

    return 0;
}