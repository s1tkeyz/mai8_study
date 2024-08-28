#include "liblab24-stack.h"

static bool expand_buffer(TStack* s) {
    int new_capacity = s->capacity * TS_EXPAND_FACTOR;
    Token* new_buffer = (Token*)realloc(s->buffer, new_capacity * sizeof(Token));
    if(!new_buffer)
        return false;
    s->capacity = new_capacity;
    s->buffer = new_buffer;
    return true;
}

static bool shrink_buffer(TStack* s) {
    if(s->capacity == TS_MIN_CAPACITY)
        return false;
    int new_capacity = s->capacity / TS_EXPAND_FACTOR;
    s->buffer = (Token*)realloc(s->buffer, new_capacity * sizeof(Token));
    s->capacity = new_capacity;
    return true;
}

TStack* ts_create() {
    TStack* s = (TStack*)malloc(sizeof(TStack));
    if(!s)
        return NULL;
    s->capacity = TS_MIN_CAPACITY;
    Token* tmp = (Token*)malloc(sizeof(Token) * s->capacity);
    if(!tmp) {
        free(s);
        return NULL;
    }
    s->buffer = tmp;
    s->top = -1;
    s->size = 0;
    return s;
}

void ts_destroy(TStack* s) {
    free(s->buffer);
    free(s);
}

bool ts_empty(TStack* s) { return s->size == 0; }

bool ts_push(TStack* s, Token v) {
    if(s->top == -1) {
        s->top = 0;
        s->buffer[s->top] = v;
        s->size++;
        return true;
    }
    if(s->size == s->capacity) {
        if(!expand_buffer(s))
            return false;
    }
    s->top++;
    s->buffer[s->top] = v;
    s->size++;
    return true;
}

Token ts_pop(TStack* s) {
    Token val = s->buffer[s->top];
    s->top--;
    s->size--;
    if(TS_EXPAND_FACTOR * TS_EXPAND_FACTOR * s->size <= s->capacity)
        shrink_buffer(s);
    if(!s->size)
        s->top = -1;
    return val;
}

Token ts_top(TStack* s) { return s->buffer[s->top]; }