#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "enum.h"

// Geteral tree node structure
typedef struct GTNode GTNode;
struct GTNode {
    City value;
    GTNode* major_child;
    GTNode* next_brother;
};

// GTNode* stack node wrapper
typedef struct GTNStackNode GTNStackNode;
struct GTNStackNode {
    GTNode* pointer;
    GTNStackNode* next;
};

// GTNode* stack structure
typedef struct GTNStack GTNStack;
struct GTNStack {
    int size;
    GTNStackNode* top;
};

typedef struct TaskAnswer {
    int level_number;
    int nodes_count;
} TaskAnswer;

GTNStack* GTNStack_create();
GTNode* GTNStack_pop(GTNStack* s);
void GTNStack_push(GTNStack* s, GTNode* n);
bool GTNStack_empty(GTNStack* s);
void GTNStack_destroy(GTNStack* s);

// Creates tree node with value v
GTNode* build_tree(City v);

// Returns major child pointer of non-NULL node
GTNode* get_major_child(GTNode* node);

// Returns next brother pointer of non-NULL node
GTNode* get_next_brother(GTNode* node);

// Sets value v to non-NULL node
void set_value(GTNode* node, City v);

// Adds child with value v to parent node
bool add_child(GTNode* parent, City v);

// Returns pointer to (idx+1)'th child of the node
GTNode* get_child(GTNode* node, int idx);

// Recursively deletes child tree
void delete_child(GTNode* node, int idx);

// Recursively deletes tree
void delete_tree(GTNode* node);

// Counts children of the node
int count_children(GTNode* node);

// Counts next brothers amount 
int count_brothers(GTNode* major_brother);

// Prints tree to stdout
void print_tree(GTNode* root, int level);

GTNStack* measure_tree_layer(GTNStack* layer, int ln, TaskAnswer* a);
