#include "libcp9-sort.h"

void shell_sort(Table* t) {
    for (int step = t->size / 2; step > 0; step /= 2) {
        for (int i = step; i < t->size; ++i) {
            for (int j = i - step; j >= 0 && key_cmp(&t->rows[j], &t->rows[j + step]); j -= step)
                swap_rows(&t->rows[j], &t->rows[j + step]);  
        }
    }
}