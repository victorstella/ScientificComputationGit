#include "sl_t.h"

// ASSUMINDO QUE É TRIDIAGONAL

// Calcula todas as funcoes em sl->func utilizando os x_aprox 
void calcula_funcs(sl_t *sl) {
    char *x_i = calloc(6, sizeof(char)), *x_j = calloc(6, sizeof(char)), *x_k = calloc(6, sizeof(char));
    char *x_names[] = { x_i, x_j, x_k };

    double *x_values = calloc(3, sizeof(double));
    
    sprintf(x_names[0], "x1");
    sprintf(x_names[1], "x2");
    x_values[0] = sl->x_aprox[0];
    x_values[1] = sl->x_aprox[1];
    sl->evaluated_curr_x[0] = evaluator_evaluate(sl->func[0].v_func, 2, x_names, x_values);
    

    for (int i = 1; i < sl->n - 1; i++) {
            sprintf(x_names[0], "x%d", i);
            sprintf(x_names[1], "x%d", i + 1);
            sprintf(x_names[2], "x%d", i + 2);
            x_values[0] = sl->x_aprox[i - 1];
            x_values[1] = sl->x_aprox[i];
            x_values[2] = sl->x_aprox[i + 1];
            sl->evaluated_curr_x[i] = evaluator_evaluate(sl->func[i].v_func, 3, x_names, x_values);
    }
    
    sprintf(x_names[0], "x%d", sl->n - 1);
    sprintf(x_names[1], "x%d", sl->n);
    x_values[0] = sl->x_aprox[sl->n - 1];
    x_values[1] = sl->x_aprox[sl->n];
    sl->evaluated_curr_x[sl->n] = evaluator_evaluate(sl->func[sl->n - 1].v_func, 2, x_names, x_values);
    
    for (size_t i = 0; i < sl->n; i++){
        printf("> %f\n", sl->evaluated_curr_x[i]);
    }
    

    printf("Deu boa :)\n");
    //free(x_names);
    free(x_values);
}

/**
 * Faz a alocação inicial do sl_t sl
 * @param n, tamanho do sistema linear
 * @param funcs, vetor de string de funcao
 * @return sistema linear sl_t
 */ 
sl_t *inicia_sl_t(int n, void **funcs, double *x_aprox, float epsilon, int maxit) {
    sl_t *sl = calloc(1, sizeof(sl_t));
    

    sl->n = n;
    sl->MAXIT = maxit;
    sl->epsilon = epsilon;
    sl->func = calloc(n, sizeof(function_t));
    sl->m_jacobi = calloc(sl->n, sizeof(void **));
    sl->jacobi_solution = calloc(sl->n, sizeof(double *));
    sl->evaluated_curr_x = calloc(sl->n, sizeof(double));
    sl->x_aprox_old = calloc(sl->n, sizeof(double));
    sl->x_aprox = calloc(sl->n, sizeof(double));

    for (int i = 0; i < n; i++) {
        sl->m_jacobi[i] = calloc(sl->n, sizeof(void *));
        sl->jacobi_solution[i] = calloc(sl->n, sizeof(double));
        sl->func[i].v_func = funcs[i];
        sl->func[i].s_func = strdup(evaluator_get_string(sl->func[i].v_func));
        sl->x_aprox[i] = x_aprox[i];
    }

    monta_jacobi(sl);

    return sl;
}

/**
 * Monta matriz jacobiana (aloca e insere as func(void*) derivadas) a partir de sistema linear
 * @param sl: sistema linear
 * @return 
 */ 
void monta_jacobi(sl_t *sl) {
    char *x_min = calloc(6, sizeof(char));
    char *x_i = calloc(6, sizeof(char));
    char *x_max = calloc(6, sizeof(char));

    sl->m_jacobi[0][0] = evaluator_derivative(sl->func[0].v_func, (char*)"x1");
    sl->m_jacobi[0][1] = evaluator_derivative(sl->func[0].v_func, (char*)"x2");

    for (int i = 1; i < sl->n - 1; i++) {
        sprintf(x_min, "x%d", i);
        sprintf(x_i, "x%d", i + 1);
        sprintf(x_max, "x%d", i + 2);
        sl->m_jacobi[i][i - 1] = evaluator_derivative(sl->func[i].v_func, x_min);
        sl->m_jacobi[i][i] = evaluator_derivative(sl->func[i].v_func, x_i);
        sl->m_jacobi[i][i + 1] = evaluator_derivative(sl->func[i].v_func, x_max);    
    }

    sprintf(x_min, "x%d", sl->n - 1);
    sprintf(x_i, "x%d", sl->n);
    sl->m_jacobi[sl->n - 1][sl->n - 2] = evaluator_derivative(sl->func[sl->n - 1].v_func, x_min);
    sl->m_jacobi[sl->n - 1][sl->n - 1] = evaluator_derivative(sl->func[sl->n - 1].v_func, x_i);

    free(x_min);
    free(x_i);
    free(x_max);
}

/**
 * Calcula sistema jacobi
 * @param sl: sistema linear
 * @return 
 */ 
void calcula_jacobi(sl_t *sl) {
    char *x_name = calloc(3, sizeof(char));
    char *x_names[] = { x_name };

    sprintf(x_names[0], "x1");    
    sl->jacobi_solution[0][0] = evaluator_evaluate(sl->m_jacobi[0][0], 1, x_names, &sl->x_aprox[0]);

    sprintf(x_names[0], "x2");

    sl->jacobi_solution[0][1] = evaluator_evaluate(sl->m_jacobi[0][1], 1, x_names, &sl->x_aprox[1]);
    
    for (int i = 1; i < sl->n - 1; i++) {
        sprintf(x_names[0], "x%d", i);
        sl->jacobi_solution[i][i - 1] = evaluator_evaluate(sl->m_jacobi[i][i - 1], 1, x_names, &sl->x_aprox[i - 1]);
        sprintf(x_names[0], "x%d", i+1);
        sl->jacobi_solution[i][i] = evaluator_evaluate(sl->m_jacobi[i][i], 1, x_names, &sl->x_aprox[i]);
        sprintf(x_names[0], "x%d", i+2);
        sl->jacobi_solution[i][i + 1] = evaluator_evaluate(sl->m_jacobi[i][i + 1], 1, x_names, &sl->x_aprox[i + 1]);
    }

    sprintf(x_names[0], "x%d", sl->n - 1);
    sl->jacobi_solution[sl->n - 1][sl->n - 2] = evaluator_evaluate(sl->m_jacobi[sl->n - 1][sl->n - 2], 1,x_names, &sl->x_aprox[sl->n - 2]);
    sprintf(x_names[0], "x%d", sl->n);
    sl->jacobi_solution[sl->n - 1][sl->n - 1] = evaluator_evaluate(sl->m_jacobi[sl->n - 1][sl->n - 1], 1, x_names, &sl->x_aprox[sl->n - 1]);

}

void destroi_function(function_t *func) {
    free(func->s_func);
    free(func->v_func);
    free(func);
}

void destroi_sl(sl_t *sl) {
    if(sl == NULL)
        return;
    printf("Destruindo para n=%d, p===%s!!\n", sl->n, evaluator_get_string(sl->m_jacobi[0][0]));
    /*for(int i = 0; i < sl->n; i++){
        printf("A[%d]\n", i);
        free(sl->jacobi_solution[i]);
    }*/

    //free(sl->jacobi_solution);

    printf("B\n");


    for (int i = 0; i < sl->n; i++) {
        for (int j = 0; j < sl->n; j++) {
            evaluator_destroy(sl->m_jacobi[i][j]);
        }
        free(sl->m_jacobi[i]);
    }

    destroi_function(sl->func);
    printf("B\n");
    free(sl->evaluated_curr_x);
    free(sl->m_jacobi);
    printf("C\n");
    free(sl->x_aprox);
    free(sl->x_aprox_old);
    printf("D\n");
    free(sl->jacobi_solution);
    printf("E\n");

    free(sl);
    printf("F\n");
}