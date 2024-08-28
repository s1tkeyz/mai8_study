#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct int_vector{
    int* data;
    int cap;
    int size;
    int head;
    int tail;
} int_vector;

int_vector create_vector();

bool vector_resize(int_vector* v, int new_size);

bool vector_empty(int_vector* v);

int vector_get(int_vector* v, int idx); 

void vector_set(int_vector* v, int idx, int val); 

bool vector_pushback(int_vector* v, int val);

int vector_popback(int_vector* v);

bool vector_pushfront(int_vector* v, int val);

int vector_popfront(int_vector* v);

void vector_clean(int_vector* v);

void vector_destroy(int_vector* v);

void print_vector(int_vector* v);