#include "libcp7-matrix.h"

typedef struct result {
    int_vector rows_n;
    int_vector e_sum;
    int m_amount;
} result;

int sum_vec_range(int_vector v, int a, int b) {
    int res = 0;
    for(int i = a; i < b; ++i)
        res += vector_get(&v, i);
    return res;
}

// Task 7
result do_task(sparse_matrix* m) {
    result res = {.rows_n = create_vector(), .e_sum = create_vector(), .m_amount = 0};
    for(int i = 0; i < m->rows; i++) {
        int r_a = vector_get(&m->cip, i);
        int r_b = vector_get(&m->cip, i + 1);
        int amount = r_b - r_a;
        if(amount == res.m_amount && amount > 0) {
            vector_pushback(&res.rows_n, i);
            vector_pushback(&res.e_sum, sum_vec_range(m->ye, r_a, r_b));
        } else if(amount > res.m_amount) {
            vector_clean(&res.rows_n);
            vector_clean(&res.e_sum);
            res.m_amount = amount;
            vector_pushback(&res.rows_n, i);
            vector_pushback(&res.e_sum, sum_vec_range(m->ye, r_a, r_b));
        } else { continue; }
    }
    int l_amount = m->ye.size - vector_get(&m->cip, m->cip.size - 1);
    if(l_amount == res.m_amount && l_amount > 0) {
        vector_pushback(&res.rows_n, m->cip.size - 1);
        vector_pushback(&res.e_sum, sum_vec_range(m->ye, vector_get(&m->cip, m->cip.size - 1), m->ye.size));
    } else if(l_amount > res.m_amount) {
        vector_clean(&res.rows_n);
        vector_clean(&res.e_sum);
        res.m_amount = l_amount;
        vector_pushback(&res.rows_n, m->cip.size - 1);
        vector_pushback(&res.e_sum, sum_vec_range(m->ye, vector_get(&m->cip, m->cip.size - 1), m->ye.size));
    }
    return res;
}

int main(void) {
    sparse_matrix matrix = sm_create();
    printf("Enter matrix size (rows cols): ");
    scanf("%d %d", &matrix.rows, &matrix.cols);
    vector_resize(&matrix.cip, matrix.rows);
    for(int i = 0; i < matrix.rows; i++) {
        vector_set(&matrix.cip, i, matrix.pi.size);
        for(int j = 0; j < matrix.cols; j++) {
            int val = 0;
            scanf("%d", &val);
            if(val != 0) {
                vector_pushback(&matrix.pi, j);
                vector_pushback(&matrix.ye, val);
            }
        }
    }

    putchar('\n');
    sm_print(matrix);
    putchar('\n');

    printf("CIP: ");
    print_vector(&matrix.cip);

    printf("PI:  ");
    print_vector(&matrix.pi);

    printf("YE:  ");
    print_vector(&matrix.ye);

    putchar('\n');

    result r = do_task(&matrix);
    if(vector_empty(&r.rows_n)) {
        printf("Source matrix has no non-null elements\n");
    } else {
        for(int k = 0; k < r.rows_n.size; k++) 
            printf("Row %d has %d non-null elements (sum = %d)\n", vector_get(&r.rows_n, k), r.m_amount, vector_get(&r.e_sum, k));
    }
    return EXIT_SUCCESS;
}