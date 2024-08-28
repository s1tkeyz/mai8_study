#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#define MIN_BUFFER_CAPACITY 4
#define BUFFER_EXPAND_FACTOR 2
#define LISTNODE_DEFAULT_VALUE UINT64_MAX

// List node structure
typedef struct ListNode {
    int next; // Buffer index of the next node
    int prev; // Buffer index of the previous node
    uint64_t value; // Value of the node (uint64_t)
} ListNode;

// Returns empty list node
ListNode empty_node();

// Double-linked cycled list of uint64_t
typedef struct List {
    ListNode* buffer; // List buffer
    int head; // Buffer index of the "first" element
    int size; // List size
    int capacity; // Buffer capacity
} List;

// Creates new empty list
List* list_create();

// Destroys list object
void list_destroy(List* list);

// Pushes value to the "end" of the list
bool list_push(List* list, uint64_t value);

// Inserts value into the list by index
bool list_insert(List* list, int li, uint64_t value);

// Removes value from the list by index
void list_remove(List* list, int li);

// Gets value from the list by index
uint64_t list_get(List* list, int li);

// Sets value of the node by list index
void list_set(List* list, int li, uint64_t value);

// Returns true if list is empty
bool list_empty(List* list);

// Prints list to the stdout
void list_print(List* list);

// Cleans list
void list_clean(List* list);
