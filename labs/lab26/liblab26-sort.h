#pragma once

#include "liblab26-stack.h"

// Two stacks concatenation function. Affects s1
void stack_concat(TStack* s1, TStack* s2);

// Hoare's quick sort for TStack
void hoare_sort(TStack* s);
