#pragma once

#define MAX_ITER_COUNT 250

typedef struct {
    double value;
    int icount;
} f_value;

double absolute(double n);

double calculate_eps();

double power(double a, int x);

f_value calculate_f(double x, double delta);