
#include "gauss.h"

double xAprox(sl_t *sl, int i) {
    return sl->x_aprox_old[i];
}

//void gauss_seidel(sl_t *sl, double tol) {
void gauss_seidel(sl_t *sl) {

    sl->x_aprox[0] = (xAprox(sl, 0) - (-2) * xAprox(sl, 0) + 1 * sl->x_aprox[1]) / (3 - 2 * xAprox(sl, 0)) * xAprox(sl, 0);
    for (int i = 1; i < sl->n - 1; ++i)
        sl->x_aprox[i] = (xAprox(sl, i) - xAprox(sl, i - 1) * (-1) * sl->x_aprox[i - 1] - ((-2) * xAprox(sl, i) + 1) * sl->x_aprox[i + 1]) / (3 - 2 * xAprox(sl, i)) * xAprox(sl, i);

    sl->x_aprox[sl->n - 1] = (xAprox(sl, sl->n - 1) - xAprox(sl, sl->n - 2) * (-1) * sl->x_aprox[sl->n - 2]) / (3 - 2 * xAprox(sl, sl->n - 2)) * xAprox(sl, sl->n - 2);
    
    for (int j = 0; j < sl->n; j++)
        printf("> sl->x_aprox[%d]: %f\n", j, sl->x_aprox[j]);

}