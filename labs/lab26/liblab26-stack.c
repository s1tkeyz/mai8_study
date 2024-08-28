#include "liblab26-stack.h"

static bool expand_buffer(TStack* s) {
    int new_capacity = s->capacity * TS_EXPAND_FACTOR;
    T* new_buffer = (T*)realloc(s->buffer, new_capacity * sizeof(T));
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

    s->buffer = (T*)realloc(s->buffer, new_capacity * sizeof(T));
    s->capacity = new_capacity;
    return true;
}

TStack* ts_create() {
    TStack* s = (TStack*)malloc(sizeof(TStack));
    if(!s)
        return NULL;
    s->capacity = TS_MIN_CAPACITY;
    T* tmp = (T*)malloc(sizeof(T) * s->capacity);
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

bool ts_push(TStack* s, T v) {
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

T ts_pop(TStack* s) {
    T val = s->buffer[s->top];
    T t = {.key = T_DEFAULT_KEY, .value = T_DEFAULT_VALUE};
    s->buffer[s->top] = t;
    s->top--;
    s->size--;
    if(TS_EXPAND_FACTOR * TS_EXPAND_FACTOR * s->size <= s->capacity)
        shrink_buffer(s);
    if(!s->size)
        s->top = -1;
    return val;
}

TStack* ts_reversed(TStack s) {
    TStack* r = ts_create();
    if(!r)
        return NULL;
    while(!ts_empty(&s))
        ts_push(r, ts_pop(&s));
    return r;
}

void print_stack(TStack s) {
    while(!ts_empty(&s))
        T_print(ts_pop(&s));
}