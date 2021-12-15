#include "sl_t.h"

// ASSUMINDO QUE É TRIDIAGONAL

// Calcula todas as funcoes em sl->func utilizando os x_aprox 
void calcula_funcs(sl_t* sl){
    
    // Pensa assim, i=0 e i=n tem só duas variáveis, o resto tem três.
    
    double xs[2] = {sl->x_aprox[1], sl->x_aprox[2]}
    evaluator_evaluate(sl->func[0].v_func, sl->func[0].var_count, sl->func[0].var_names, xs);

    for (int i = 0; i < sl->n; i++){
        evaluator_evaluate(sl->func[i].v_func, sl->func[0].var_count, sl->func[0].var_names, );
    }
    
    
}

void inicia_function_t(function_t* func , void * v_func) {
    char aux[124];
    func->v_func = v_func;
    
    sprintf(aux, "%s", evaluator_get_string(v_func));
    func->s_func = (char *) calloc(strlen(aux) , sizeof(char));
    strcpy(func->s_func, aux);

    func->var_count = 0;
    evaluator_get_variables(func->v_func, &func->var_names, &func->var_count);


    //printf("** func string: %s\n", func->s_func);
    //printf("** n vars: %d\n\n", func->var_count);
}

/**
 * Faz a alocação inicial do sl_t sl
 * @param n, tamanho do sistema linear
 * @param funcs, vetor de string de funcao
 * @return sistema linear sl_t
 */ 
sl_t * inicia_sl_t(int n, void ** funcs, double * x_aprox, float epsilon, int maxit) {
    sl_t * sl = calloc(1, sizeof(sl_t));
    
    sl->n = n;
    sl->MAXIT = maxit;
    sl->epsilon = epsilon;
    sl->func = calloc(n, sizeof(function_t));
    sl->m_jacobi = calloc(sl->n, sizeof(void ***));
    sl->evaluated_curr_x = calloc(sl->n, sizeof(double));
    sl->x_aprox_old = calloc(sl->n, sizeof(double));

    for (int i = 0; i < n; i++) {
        
        sl->m_jacobi[i] = calloc(sl->n, sizeof(void **));
        inicia_function_t(&sl->func[i] , funcs[i]);
    }

    if (x_aprox == NULL)
        sl->x_aprox = calloc(sl->n, sizeof(double*));
    else {
        sl->x_aprox = x_aprox;
    }

    monta_jacobi(sl);

    printf("incia %p\n", sl);
    return sl;
}

/**
 * Monta matriz jacobiana a partir de sistema linear
 * @param sl: sistema linear
 * @return 
 */ 
void monta_jacobi(sl_t *sl) {
    char * currX = calloc(6, sizeof(char));

    for(int i = 0; i < sl->n; i++) {
        for(int j = 0; j < sl->n; j++) {
            sprintf(currX, "x%d", j + 1);
            sl->m_jacobi[i][j] = evaluator_derivative(sl->func[i].v_func, currX);
            printf("\njacobi[%d][%d]: %s\n", i, j, evaluator_get_string(sl->m_jacobi[i][j]));
        }
    }

    free(currX);
}

/**
 * Calcula sistema jacobi
 * @param sl: sistema linear
 * @return 
 */ 
void calcula_jacobi(sl_t* sl) {
    char * currX = calloc(6, sizeof(char));
    for(int i = 0; i < sl->n; i++) {
        for(int j = 0; j < sl->n; j++) {
            sprintf(currX, "x%d", j);
            sl->jacobi_solution[i][j] = evaluator_evaluate(sl->m_jacobi[i][j], 1, &currX, sl->x_aprox + j);
        }
    }
} // !!! Revisar !!! Talvez possa usar evaluator_evaluate_x, testar

void destroi_function(function_t* func) {
        printf("AEa\n");
    free(func->var_names);
        printf("AIa\n");
    free(func->s_func);
        printf("AGa\n");
    free(func->v_func);
        printf("AFa\n");
    free(func);
}

void destroi_sl(sl_t* sl) {
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