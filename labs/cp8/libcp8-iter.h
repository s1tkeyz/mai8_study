#pragma once

#include "libcp8-list.h"

// List iterator structure
typedef struct Iterator {
    List* list; // Iteration list
    int current_bi; // Current buffer index 
    int current_li; // Current list index
} Iterator;

// Creates new iterator of the list
Iterator iter_create(List* list);

// Returns value under current pointer
uint64_t iter_value(Iterator* it);

// Returns buffer pointer to the current node
ListNode* iter_node(Iterator* it);

// Step next
void iter_next(Iterator* it);

// Step back
void iter_prev(Iterator* it);

// Iterator comparator
bool iter_equal(Iterator* lhs , Iterator* rhs);