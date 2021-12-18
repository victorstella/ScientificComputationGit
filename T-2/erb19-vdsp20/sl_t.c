#include "sl_t.h"

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
    x_values[0] = sl->x_aprox[sl->n - 2];
    x_values[1] = sl->x_aprox[sl->n - 1];
    sl->evaluated_curr_x[sl->n - 1] = evaluator_evaluate(sl->func[sl->n - 1].v_func, 2, x_names, x_values);
    
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
    sl->jacobi_solution_principal = calloc(sl->n, sizeof(double));
    sl->evaluated_curr_x = calloc(sl->n, sizeof(double));
    sl->x_aprox_old = calloc(sl->n, sizeof(double));
    sl->x_aprox = calloc(sl->n, sizeof(double));
    sl->delta_x = calloc(sl->n, sizeof(double));
    sl->func = calloc(n, sizeof(function_t));

    for (int i = 0; i < n; i++) {
        sl->func[i].v_func = funcs[i];
        sl->func[i].s_func = strdup(evaluator_get_string(sl->func[i].v_func));
        sl->x_aprox[i] = x_aprox[i];
        sl->delta_x[i] = 1;
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

    sl->jacobi_superior = evaluator_derivative(sl->func[0].v_func, "x2");
    sl->jacobi_principal = evaluator_derivative(sl->func[0].v_func, "x1");
    sl->jacobi_inferior = evaluator_derivative(sl->func[1].v_func, "x3");


    sl->jacobi_solution_superior = evaluator_evaluate_x(sl->jacobi_superior, 0);
    sl->jacobi_solution_inferior = evaluator_evaluate_x(sl->jacobi_inferior, 0);

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
    
    for (int i = 0; i < sl->n; i++) {
        sl->jacobi_solution_principal[i] = evaluator_evaluate(sl->jacobi_principal, 1, x_names, &sl->x_aprox[i]);
    }

}

void destroi_function(function_t *func) {
    free(func->s_func);
    free(func->v_func);
    free(func);
}

void destroi_sl(sl_t *sl) {
    if(sl == NULL)
        return;

    destroi_function(sl->func);
    free(sl->evaluated_curr_x);
    evaluator_destroy(sl->jacobi_principal);
    evaluator_destroy(sl->jacobi_inferior);
    evaluator_destroy(sl->jacobi_superior);
    free(sl->x_aprox);
    free(sl->x_aprox_old);
    free(sl->jacobi_solution_principal);
    free(sl->delta_x);
    free(sl);
    sl = NULL;
}
