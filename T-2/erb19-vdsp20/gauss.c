
#include "gauss.h"


/**
 * Resolve o sl e descobre o delta
 * @param sl, Sistema Linear que tem as funcoes, as aproximacoes de x e o delta
 * @return 
 */
//void gauss_seidel(sl_t *sl, double tol) {
void gauss_seidel(sl_t *sl) {
    double d = sl->jacobi_solution[0][0], 
        a = sl->jacobi_solution[1][0], 
        c = sl->jacobi_solution[0][1];

    sl->delta_x[0] = (sl->evaluated_curr_x[0] - (c * sl->delta_x[1])) / d;
    
    for (int i = 1; i < sl->n - 1; i++)
        sl->delta_x[i] = (sl->evaluated_curr_x[i] - (a * sl->delta_x[i - 1]) - (c * sl->delta_x[i + 1])) / d;

    sl->delta_x[sl->n - 1] = (sl->evaluated_curr_x[sl->n - 1] - (a * sl->delta_x[sl->n - 2])) / d;


    for (int j = 0; j < sl->n; j++)
        for (int l = 0; l < sl->n; l++) printf(">[%d][%d] jacobi_solution: %f\n", j, l, sl->jacobi_solution[j][l]);

    for (int k = 0; k < sl->n; k++) printf("> delta_x%d: %1.16f  --  a: %f | d: %f | c: %f | b: %f\n", k + 1, sl->delta_x[k], a, d, c, sl->evaluated_curr_x[k]);

    for (int m = 0; m < sl->n; m++)
        printf("* %d * evaluated_curr_x: %f | x_aprox: %f | x_aprox_old: %f\n", m + 1, sl->evaluated_curr_x[m], sl->x_aprox[m], sl->x_aprox_old[m]);
}