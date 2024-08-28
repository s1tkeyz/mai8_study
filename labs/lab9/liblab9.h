// lab9 tools header
#ifndef LIBLAB9_H
#define LIBLAB9_H

typedef struct { int i; int j; } point;

typedef struct { int r; point o; } circle;

int abs(int n);

int max(int a, int b);

int min(int a, int b);

int sqr(int n);

int trunc(float x);

int floor(float x);

int mod(int a, int b);

int mod_v2(int a, int b);

int rem(int a, int b);

int div(int a, int b);

int sqr_dist(point a, point b);

int point_power(point p, circle w);

#endif