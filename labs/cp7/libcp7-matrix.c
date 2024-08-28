#include "libcp7-matrix.h"

sparse_matrix sm_create() {
    sparse_matrix m;
    m.cip = create_vector();
    m.pi = create_vector();
    m.ye = create_vector();
    m.rows = 0;
    m.cols = 0;
    return m;
}

void sm_print(sparse_matrix m) {
    for(int i = 0; i < m.rows; i++) {
        int pi_r_s = vector_get(&m.cip, i);
        int pi_r_e = (i == m.cols - 1) ? m.ye.size : vector_get(&m.cip, i + 1);
        int amount = pi_r_e - pi_r_s;
        if(amount == 0)
            for(int j = 0; j < m.cols; j++) { printf("%d ", 0); }
        else {
            int next_nnc = vector_get(&m.pi, pi_r_s);
            int x = pi_r_s;
            for(int j = 0; j < m.cols; j++) {
                if(j == next_nnc) {
                    printf("%d ", vector_get(&m.ye, x));
                    x++;
                    next_nnc = vector_get(&m.pi, x);
                } 
                else
                    printf("%d ", 0);
            }   
        }
        putchar('\n');
    }
}