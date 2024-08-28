#include "liblab26-type.h"

T T_build(KEY_TYPE key, VALUE_TYPE value) {
    T t;
    t.key = key;
    t.value = value;
    return t;
}

bool T_cmp(const T* lhs, const T* rhs) { return lhs->value >= rhs->value; }

bool T_equal(const T* lhs, const T* rhs) { return lhs->value == rhs->value; }

void T_print(T v) { printf("%d ", v.value); }

bool T_fromstdin(T* t) {
    if(!scanf("%d", &(t->value)))
        return false;
    t->key = T_DEFAULT_KEY;
    return true;
}