#include "sl_t.h"

// ASSUMINDO QUE É TRIDIAGONAL

function_t* inicia_function_t(char* s_func, double solution, int * var_count) {
    function_t* func = calloc(1, sizeof(function_t));
    
    func->s_func = strdup(s_func);
    func->v_func = evaluator_create(s_func);

    evaluator_get_variables(func, func->var_names, var_count); 
    
    for(int i = 0; i < var_count; i++)
        func->x_aprox[i] = 0;


    return func;
}

/**
 * Faz a alocação inicial do sl_t sl
 * @param n, tamanho do sistema linear
 * @param funcs, vetor de string de funcao
 * @return sistema linear sl_t
 */ 
sl_t * inicia_sl_t(int n, char ** funcs, double* x_aprox) {
    sl_t * sl = calloc(1, sizeof(sl_t));
    int * var_count = calloc(n, sizeof(int));

    sl->n = n;
    sl->func = calloc(n, sizeof(function_t));
    
    for (int i = 0; i < n; i++) {
        inicia_function_t(sl->func[i].s_func, x_aprox[i], var_count);
        /* sl->func[i].s_func = strdup(funcs[i]);
        sl->func[i].v_func = evaluator_create(funcs[i]);
        sl->func[i].x_aprox = x_aprox; */
    }    

    return sl;
}

int calcula_jacobi(sl_t sl){

}