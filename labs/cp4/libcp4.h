#pragma once

#define DELTA 0.000002

typedef struct {
    double value;
    int icount;
} answer;

// Returns the absolute value of n
double absolute(double n);

// Returns the machine epsilon (by zzz)
double calculate_eps();

// Returns x - f(x)/m value
double fi(double (*f)(double), double x, double m);

// Calculates the 1st derivative of f(x) in x
double derivative(double (*f)(double), double x);

// Calculates the 2nd derivative of f(x) in x
double derivative2(double (*f)(double), double x);

// Equation solver, uses dichotomy method
answer dichotomy(double (*f)(double), double a, double b, double eps);

// Equation solver, uses iterations method
answer iterations(double (*f)(double), double a, double b, double eps, double m);

// Equation solver, uses Newton's method
answer newton(double (*f)(double), double a, double b, double eps);