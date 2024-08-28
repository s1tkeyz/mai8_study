#include "libcp7-vector.h"

#define MIN_CAPACITY 10

static bool expand_buffer(int_vector *v) {
    int new_cap = v->cap * 2;
    if (new_cap < MIN_CAPACITY) 
        new_cap = MIN_CAPACITY;
    int* tmp = (int *) realloc(v->data, sizeof(int) * new_cap);
    if (!tmp) 
        return false;
    for (int i = v->cap; i < new_cap; i++)
        tmp[i] = 0;
    v->data = tmp;
    if (v->head + v->size > v->cap) {
        for (int i = 0; i < (v->head + v->size) - v->cap; i++) {
            v->data[v->cap + i] = v->data[i];
            v->data[i] = 0;
        }
    }
    v->tail = v->head + v->size;
    v->cap = new_cap;
    return true;
}

static void shrink_buffer(int_vector *v) {
    if (v->size < v->cap / 4) {
        int new_cap = v->cap / 2;
        if ((v->head > new_cap) && (v->head + v->size) > v->cap) {
            for (int i = 0; i <= (v->cap - v->head); i++) 
                v->data[new_cap - i] = v->data[v->cap - i];
            v->head = new_cap - (v->cap - v->head);
        } else if ((v->head < new_cap - 1) && (v->head + v->size) > new_cap) {
            for (int i = new_cap; i < v->head + v->size; i++) 
                v->data[i - new_cap] = v->data[i];
            v->tail = v->head + v->size - new_cap - 1;
        } else if ((v->head >= new_cap - 1) && (v->head + v->size) <= v->cap) {
            for (int i = 0; i <= v->size; i++) 
                v->data[i] = v->data[v->head + i];
            v->head = 0;
            v->tail = v->head + v->size - 1;
        v->data = (int *) realloc(v->data, sizeof(int) * new_cap);
        v->cap = new_cap;
        }
    }
}

bool vector_resize(int_vector *v, int new_size) {
    if(new_size == v->size)
        return true;
    if(new_size > v->cap) {
        int new_cap = v->cap * 2;
        while (new_cap < new_size) 
            new_cap *= 2;
        int* tmp = (int *) realloc(v->data, sizeof(int) * new_cap);
        if (!tmp) 
            return false;
        for (int i = v->cap; i < new_cap; i++) 
            tmp[i] = 0;
        v->data = tmp;
        if (v->head + v->size > v->cap) {
            for (int i = 0; i < (v->head + v->size) - v->cap; i++) {
                v->data[v->cap + i] = v->data[i];
                v->data[i] = 0;
            }
        }
        v->size = new_size;
        v->tail = v->head + v->size;
        v->cap = new_cap;
        return true;
    } else if (new_size < v->size) {
        for (int i = new_size; i < v->size; i++) {
            v->data[(v->head + i) % v->cap] = 0;
            v->tail = (v->tail - 1 + v->cap) % v->cap;
        }
        v->size = new_size;
        return true;
    } else {
        v->size = new_size;
        v->tail = v->head + v->size;
        return true;
    }
}

int_vector create_vector() {
    int_vector v;
    v.cap = MIN_CAPACITY;
    v.head = 0;
    v.size = 0;
    v.tail = 0;
    v.data = (int*)malloc(v.cap * sizeof(int));
    return v;
}

bool vector_empty(int_vector *v) { return v->size == 0; }

int vector_get(int_vector *v, int idx) { return v->data[(v->head + idx) % v->cap]; }

void vector_set(int_vector *v, int idx, int val) { v->data[(v->head + idx) % v->cap] = val; }

bool vector_pushback(int_vector *v, int val) {
    if ((v->size == v->cap) && (!expand_buffer(v))) 
        return false;
    v->data[v->tail] = val;
    v->tail = (v->tail + 1) % v->cap;
    v->size++;
    return true;
}

bool vector_pushfront(int_vector *v, int val) {
    if ((v->size == v->cap) && (!expand_buffer(v))) 
        return false;
    v->head = (v->head - 1 + v->cap) % v->cap;
    v->data[v->head] = val;
    v->size++;
    return true;
}

int vector_popback(int_vector *v) {
    v->tail = (v->tail - 1 + v->cap) % v->cap;
    int res = v->data[v->tail];
    v->data[v->tail] = 0;
    shrink_buffer(v);
    v->size--;
    return res;
}

int vector_popfront(int_vector *v) {
    int res = v->data[v->head];
    v->data[v->head] = 0;
    shrink_buffer(v);
    v->head = (v->head + 1) % v->cap;
    v->size--;
    return res;
}

void vector_clean(int_vector* v) {
    v->size = 0;
    v->tail = 0;
    v->head = 0;
    v->cap = MIN_CAPACITY;
    v->data = (int*)realloc(v->data, v->cap * sizeof(int));
}

void vector_destroy(int_vector *v) {
    free(v->data);
    free(v);
}

void print_vector(int_vector *v) {
    for (int i = 0; i < v->size; i++)
        printf("%d ", v->data[(v->head + i) % v->cap]);
    putchar('\n');
}