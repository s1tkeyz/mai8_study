#pragma once

#define T_DEFAULT_KEY 0
#define T_DEFAULT_VALUE 0

#define VALUE_TYPE int
#define KEY_TYPE int

#include <stdbool.h>
#include <stdio.h>

// User data type declaration
typedef struct T {
    KEY_TYPE key;
    VALUE_TYPE value;
} T;

// Data type build function
T T_build(KEY_TYPE key, VALUE_TYPE value);

// Custom T comparator.
bool T_cmp(const T* lhs, const T* rhs);

// Returns true, if lhs and rhs are equal
bool T_equal(const T* lhs, const T* rhs);

// Prints T object to stdout
void T_print(T v);

// Reads T object from stdin
bool T_fromstdin(T* t);