
#include "gauss.h"

void gauss_seidel(sl_t *sl) {

    sl->diagonal_central[0] = sl->jacobi_solution[0][0];
    sl->diagonal_direita[0] = sl->jacobi_solution[0][1];

    for(int i = 1; i < sl->n - 1; i++){
        sl->diagonal_central[i] = sl->jacobi_solution[i][i];
        sl->diagonal_direita[i] = sl->jacobi_solution[i][i + 1];
        sl->diagonal_esquerda[i] = sl->jacobi_solution[i][i - 1];
    }

    sl->diagonal_esquerda[sl->n - 1] = sl->jacobi_solution[sl->n - 1][sl->n - 2];
    sl->diagonal_central[sl->n - 1] = sl->jacobi_solution[sl->n-1][sl->n - 1];

    double *a = sl->diagonal_esquerda;
    double *d = sl->diagonal_central;
    double *c = sl->diagonal_direita;
    

    double maior = 0;

    do {
        sl->delta_x[0] = (sl->evaluated_curr_x[0] - (c[0] * sl->delta_x[1])) / d[0];
        if (maior < fabs(sl->delta_x[0])) maior = sl->delta_x[0];
        printf("ççç %1.16lf\n", sl->delta_x[0]);
    
        for (int i = 1; i < sl->n - 1; i++) {
            sl->delta_x[i] = (sl->evaluated_curr_x[i] - (a[i - 1] * sl->delta_x[i - 1]) - (c[i] * sl->delta_x[i + 1])) / d[i];
            if (maior < fabs(sl->delta_x[i])) maior = sl->delta_x[i];
            printf("ççç %1.16lf\n", sl->delta_x[i]);
        }

        sl->delta_x[sl->n - 1] = (sl->evaluated_curr_x[sl->n - 1] - (a[sl->n-2] * sl->delta_x[sl->n - 2])) / d[sl->n - 1];
        if (maior < fabs(sl->delta_x[sl->n-1])) maior = sl->delta_x[sl->n-1];
        printf("ççç %1.16lf\n", sl->delta_x[sl->n -1]);

        printf("Maior = %1.16f\n", maior);
    } while (fabs(maior) < sl->epsilon);
    printf("Saiu com maior = %1.16lf > %1.16lf\n", maior, sl->epsilon );
}

/**
 * Resolve o sl e descobre o delta
 * @param sl, Sistema Linear que tem as funcoes, as aproximacoes de x e o delta
 * @return 
 */
//void gauss_seidel(sl_t *sl, double tol) {
    /*
void gauss_seidel(sl_t *sl) {
    double d = sl->jacobi_solution[0][0], 
        a = sl->jacobi_solution[1][0], 
        c = sl->jacobi_solution[0][1];

    sl->delta_x[0] = (sl->evaluated_curr_x[0] - (c * sl->delta_x[1])) / d;
    
    for (int i = 1; i < sl->n - 1; i++)
        sl->delta_x[i] = (sl->evaluated_curr_x[i] - (a * sl->delta_x[i - 1]) - (c * sl->delta_x[i + 1])) / sl->jacobi_solution[i][i];

    sl->delta_x[sl->n - 1] = (sl->evaluated_curr_x[sl->n - 1] - (a * sl->delta_x[sl->n - 2])) / sl->jacobi_solution[sl->n - 1][sl->n - 1];


    for (int j = 0; j < sl->n; j++)
        for (int l = 0; l < sl->n; l++) printf(">[%d][%d] jacobi_solution: %f\n", j, l, sl->jacobi_solution[j][l]);

    for (int k = 0; k < sl->n; k++) printf("> delta_x%d: %1.16f  --  a: %f | d: %f | c: %f | b: %f\n", k + 1, sl->delta_x[k], a, sl->jacobi_solution[k][k], c, sl->evaluated_curr_x[k]);

    for (int m = 0; m < sl->n; m++)
        printf("* %d * evaluated_curr_x: %f | x_aprox: %f | x_aprox_old: %f\n", m + 1, sl->evaluated_curr_x[m], sl->x_aprox[m], sl->x_aprox_old[m]);
}*/
