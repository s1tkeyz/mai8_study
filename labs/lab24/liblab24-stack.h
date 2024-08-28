#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "liblab24-token.h"

#define TS_MIN_CAPACITY 4
#define TS_EXPAND_FACTOR 2

// Ring buffer stack of Tokens 
typedef struct TStack {
    Token* buffer;
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
bool ts_push(TStack* s, Token v);

// Pops value from top of TStack
Token ts_pop(TStack* s);

Token ts_top(TStack* s);