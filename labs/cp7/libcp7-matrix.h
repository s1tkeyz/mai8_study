#pragma once

#include <stdio.h>
#include "libcp7-vector.h"

typedef struct sparse_matrix {
    int_vector cip;
    int_vector pi;
    int_vector ye;
    int cols;
    int rows;
} sparse_matrix;

// Creates new empty sparse matrix
sparse_matrix sm_create();

// Naturally prints martix to the stdout
void sm_print(sparse_matrix m);