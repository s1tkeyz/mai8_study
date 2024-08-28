// lab9 tools implementation
#include "liblab9.h"

int abs(int n) { 
    return (n > 0) ? n : -n;
}

int max(int a, int b) { 
    return (a > b) ? a : b; 
}

int min(int a, int b) { 
    return (a < b) ? a : b; 
}

int sqr(int n) { 
    return n * n; 
}

// trunc for integer division
int trunc(float x) {
    return (int)x;
}

// floor for integer division
int floor(float x) {
    int xt = trunc(x);
    if (x >= 0)
        return xt;
    else {
        if(x < (float)xt)
            return xt - 1;
        return xt;
    }
}

// Python's % short implementation
int mod(int a, int b) { 
    return (a % b + b) % b; 
}

// Python's % implementation using floor()
int mod_v2(int a, int b) {
    float x = (float)a / (float)b;
    return a - b * floor(x);
} 

// reminder using trunc() 
int rem(int a, int b) {
    float x = floor(a) / floor(b);
    return a - b * trunc(x);
}

// Python's // implementation
int div(int a, int b) {
    return floor((float)a / (float)b);
}

int sqr_dist(point a, point b) { 
    return sqr(a.i - b.i) + sqr(a.j - b.j);
}

// Power of a point
int point_power(point p, circle w) { 
    return sqr_dist(p, w.o) - sqr(w.r);
}