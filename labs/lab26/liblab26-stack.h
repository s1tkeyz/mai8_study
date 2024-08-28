#pragma once

#include <stdlib.h>
#include "liblab26-type.h"

#define TS_MIN_CAPACITY 4
#define TS_EXPAND_FACTOR 2

// Ring buffer stack of T structure 
typedef struct TStack {
    T* buffer;
    int top;
    int size;
    int capacity;
} TStack;

// Crates new TStack. Returns pointer
TStack* ts_create();

// Destroys stack structure
void ts_destroy(TStack* s);

// Returns true if stack is empty
bool ts_empty(TStack* s);

// Pushes value to the top of TStack
bool ts_push(TStack* s, T v);

// Pops value from top of TStack
T ts_pop(TStack* s);

// Returns reversed stack of stack s
TStack* ts_reversed(TStack s);

void print_stack(TStack s);