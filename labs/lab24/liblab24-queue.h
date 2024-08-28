#pragma once

#define MIN_CAPACITY 4
#define BUFF_EXPAND_MULT 2

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "liblab24-token.h"

typedef struct {
    Token* buffer;
    int size;
    int capacity;
    int head;
} TQueue;

TQueue TQueue_create();
void TQueue_destroy(TQueue* queue);
bool TQueue_empty(TQueue* queue);
bool TQueue_push(TQueue* queue, Token value);
Token TQueue_pop(TQueue* queue);
void TQueue_print(TQueue* queue);