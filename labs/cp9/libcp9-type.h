#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define LINE_SIZE 48
#define KEY_SIZE 8

// Table row struct
typedef struct Row {
    char key[KEY_SIZE];
    char line[LINE_SIZE];
} Row;

// Key comparator
bool key_cmp(const Row* lhs, const Row* rhs);

// Returns true if keys are equal
bool key_eq(const Row* lhs, const Row* rhs);

// Data table
typedef struct Table {
    Row* rows;
    int size;
    int capacity;
} Table;

// Creates new empty table
Table* create_table();

// Adds row to the end of the table
bool table_add(Table* t, Row r);

// Prints table content to the stdout
void print_table(Table* t);

// Destroys table
void destroy_table(Table* t);

// Binary search (only for sorted table)
int table_search(Table* t, const char* k);

// Randomly shuffles rows of the table
void shuffle_rows(Table* t);

// Reverses table rows
void reverse_table(Table* t);

// Swaps two rows
void swap_rows(Row *a, Row *b);