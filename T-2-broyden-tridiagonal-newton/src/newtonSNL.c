#include "newtonSNL.h"

double maior_func_evaluated(sl_t *sl) {
    double max = 0;
    for (int i = 0; i < sl->n ; i++)
        if (fabs(sl->evaluated_curr_x[i]) > max) max = fabs(sl->evaluated_curr_x[i]);

    return max;
}

int calcula_novo_x(sl_t *sl) {
    int diff = 0;
    for(int i = 0; i < sl->n; i++) {
        sl->x_aprox_old[i] = sl->x_aprox[i];
        sl->x_aprox[i] = sl->x_aprox_old[i] + sl->delta_x[i];
        if(fabs(sl->delta_x[i]) >= fabs(sl->epsilon)) diff = 1;
    }
    return diff;
}

// Função principal para cada SL, executando cada função
int newton(sl_t *sl) {

    if(sl == NULL)
        return 0;

    double *oldX = calloc(sl->n, sizeof(double));

    if (!oldX) {
        perror("Erro de alocação de memória.");
        exit(1);
    }

    int iter, criterio1, criterio2, criterio3;

    iter = 0;

    
    criterio1 = 1;
    criterio2 = 1;
    criterio3 = 1;

    // Laço principal de cada SL da entrada, que executa todas as funções para o SL até os critérios
    // de parada serem satisfeitos
    do {
        printf("#\n");
        for (int i = 0; i < sl->n; i++)
            printf("x%d = %lf\n", i + 1, sl->x_aprox[i]);
        
        calcula_funcs(sl); // Calcula todas as sl->funcs com os x_aprox

        if (maior_func_evaluated(sl) < sl->epsilon){
            criterio2 = 0;
            exit(0);
        }
        
        calcula_jacobi(sl); // Calcula a matriz jacobiana do sistema sl


        // Calcula novo x
        criterio3 = calcula_novo_x(sl);

        iter++;
        if(iter > sl->MAXIT)
            criterio1 = 0;
        
    } while(criterio1 && criterio2 && criterio3);

    free(oldX);

    return 1;
}