#include "libcp9-type.h"

#define MIN_CAPACITY 14
#define EXPAND_FACTOR 2

bool key_cmp(const Row* lhs, const Row* rhs) {
    return strcmp(lhs->key, rhs->key) > 0;
}

bool key_eq(const Row* lhs, const Row* rhs) {
    return strcmp(lhs->key, rhs->key) == 0;
}

// Expands table buffer if necessary
static bool expand_buffer(Table* t) {
    if(t->size < t->capacity)
        return true;
    int new_cap = EXPAND_FACTOR * t->capacity;
    Row* tmp = (Row*)realloc(t->rows, sizeof(Row) * new_cap);
    if(!tmp)
        return false; 
    t->capacity = new_cap;
    t->rows = tmp;
    return true;
}

Table* create_table() {
    Table* tb = (Table*)malloc(sizeof(Table));
    if(!tb)
        return NULL;
    Row* buff = (Row*)malloc(MIN_CAPACITY * sizeof(Row));
    if(!buff) {
        free(tb);
        return NULL;
    }
    tb->capacity = MIN_CAPACITY;
    tb->rows = buff;
    tb->size = 0;
    return tb;
}

bool table_add(Table* t, Row r) {
    if(!expand_buffer(t))
        return false; 
    t->rows[t->size] = r;
    t->size++;
    return true;
}

void print_table(Table* t) {
    for(int i = 0; i < t->size; ++i)
        printf("%2d | %6s | %s\n", i, t->rows[i].key, t->rows[i].line);
}

void destroy_table(Table* t) {
    free(t->rows);
    free(t);
}

int table_search(Table* t, const char* k) {
    int l = 0;
    int r = t->size - 1;
    int result = -1;
    while(l <= r) {
        int x = (l + r) >> 1;
        int cmp = strcmp(t->rows[x].key, k);
        if(cmp == 0) {
            result = x;
            r = x - 1;
        } else if(cmp > 0)
            r = x - 1;
        else 
            l = x + 1;
    }
    return result;
}

void shuffle_rows(Table* t) {
    srand (time(NULL));
    for(int i = t->size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap_rows(&t->rows[i], &t->rows[j]);
    }
}

void reverse_table(Table* t) {
    for(int i = 0; i < t->size / 2; ++i)
        swap_rows(&t->rows[i], &t->rows[t->size - i - 1]);
}

void swap_rows(Row *a, Row *b) {
    Row temp = *a;
    *a = *b;
    *b = temp;
}