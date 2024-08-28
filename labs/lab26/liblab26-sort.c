#include "liblab26-sort.h"

void stack_concat(TStack* s1, TStack* s2) {
    if(!s1 || !s2)
        return;
    TStack* tmp = ts_reversed(*s2);
    while(!ts_empty(tmp))
        ts_push(s1, ts_pop(tmp));
    ts_destroy(tmp);
}

void hoare_sort(TStack* s) {
    if(s->size < 2)
        return;
    T pivot = ts_pop(s);

    TStack* less = ts_create();
    TStack* greater = ts_create();
    TStack* equal = ts_create();

    ts_push(equal, pivot);
    while(!ts_empty(s)) {
        T v = ts_pop(s);
        if(T_equal(&v, &pivot)) {
            ts_push(equal, pivot);
            continue;
        }
        if(T_cmp(&v, &pivot)) {
            ts_push(greater, v);
            continue;
        } else {
            ts_push(less, v);
            continue;
        }
    }
    hoare_sort(less);
    hoare_sort(greater);
    stack_concat(s, less);
    stack_concat(s, equal);
    stack_concat(s, greater);
}