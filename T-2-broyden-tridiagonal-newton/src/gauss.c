
#include "gauss.h"

// Retro-substitui o SL triangularizado
 void retroSubst(sl_t *sl) {
    
    double old_delta;
    double maior_dif = 0;
    int k = 0;
    
    do {
        old_delta = sl->delta_x[0];
        sl->delta_x[0] = (sl->evaluated_curr_x[0] - (sl->jacobi_solution_superior * sl->delta_x[1])) / sl->jacobi_solution_principal[0];

        for (int i = 1; i < sl->n - 1; i++) {
            old_delta = sl->delta_x[i];

            sl->delta_x[i] = (sl->evaluated_curr_x[i] - ( (sl->jacobi_solution_inferior * sl->delta_x[i - 1]) + (sl->jacobi_solution_superior * sl->delta_x[i + 1]) ))/ sl->jacobi_solution_principal[i];
                
        }
        
        old_delta = sl->delta_x[sl->n - 1];

        sl->delta_x[sl->n - 1] = (sl->evaluated_curr_x[sl->n - 1] - (sl->jacobi_solution_inferior * sl->delta_x[sl->n - 2])) / sl->jacobi_solution_principal[sl->n - 1];

        k++;
    } while (k<4);


} 

// Inverte o sinal dos valores do vetor de resultados para efetuar a retrosubstituição
// Depois inverte novamente para o vetor ficar como era inicialmente.
void calcula_gauss(sl_t *sl) {
    for(int i = 0; i < sl->n; i++)
        sl->evaluated_curr_x[i] = - sl->evaluated_curr_x[i];

    retroSubst(sl);

    for(int i = 0; i < sl->n; i++)
        sl->evaluated_curr_x[i] = - sl->evaluated_curr_x[i];
}
