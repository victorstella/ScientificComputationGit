#include "sl_t.h"

// ASSUMINDO QUE É TRIDIAGONAL

// Calcula todas as funcoes em sl->func utilizando os x_aprox 
void calcula_funcs(sl_t *sl) {
    char *x_ime = calloc(6, sizeof(char));
    char *x_i = calloc(6, sizeof(char));
    char *x_ima = calloc(6, sizeof(char));
    
    for (int i = 0; i < sl->n; i++) {
        if (i == 0) {
            sprintf(x_i, "x1");
            sprintf(x_ima, "x2");
            evaluator_evaluate(sl->func[0].v_func, 2, &x_i, &sl->x_aprox[0]);
            printf("primeiro foi");
            evaluator_evaluate(sl->func[0].v_func, 2, &x_ima, &sl->x_aprox[1]);
            printf("segundo foi");
        } else if (i == sl->n - 1) {
            sprintf(x_ime, "x%d", sl->n - 1);
            sprintf(x_i, "x%d", sl->n);
            evaluator_evaluate(sl->func[i].v_func, 2, &x_ime, &sl->x_aprox[i - 1]);
            printf("penultimo foi");
            evaluator_evaluate(sl->func[i].v_func, 2, &x_i, &sl->x_aprox[i]);
            printf("ultimo foi");
        } else {
            sprintf(x_ime, "x%d", i);
            sprintf(x_i, "x%d", i + 1);
            sprintf(x_ima, "x%d", i + 2);
            evaluator_evaluate(sl->func[i].v_func, 3, &x_ime, &sl->x_aprox[i - 1]);
            evaluator_evaluate(sl->func[i].v_func, 3, &x_i, &sl->x_aprox[i]);
            evaluator_evaluate(sl->func[i].v_func, 3, &x_ima, &sl->x_aprox[i + 1]);
        }
    }
    
    free(x_ime);
    free(x_i);
    free(x_ima);
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
    sl->evaluated_curr_x = calloc(sl->n, sizeof(double));
    sl->x_aprox_old = calloc(sl->n, sizeof(double));

    for (int i = 0; i < n; i++) {
        sl->m_jacobi[i] = calloc(sl->n, sizeof(void *));
        sl->func[i].v_func = funcs[i];
        sl->func[i].s_func = strdup(evaluator_get_string(sl->func[i].v_func));
    }

    if (x_aprox == NULL)
        sl->x_aprox = calloc(sl->n, sizeof(double));
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
    char *x_ime = calloc(6, sizeof(char));
    char *x_i = calloc(6, sizeof(char));
    char *x_ima = calloc(6, sizeof(char));

    for (int i = 0; i < sl->n; i++) {
        if (i == 0) {
            sl->m_jacobi[i][i] = evaluator_derivative(sl->func[i].v_func, "x1");
            sl->m_jacobi[i][i + 1] = evaluator_derivative(sl->func[i].v_func, "x2");
            printf("\njacobi[%d][%d]: %s\n", i, i, evaluator_get_string(sl->m_jacobi[i][i]));
            printf("\njacobi[%d][%d]: %s\n", i, i + 1, evaluator_get_string(sl->m_jacobi[i][i + 1]));
        } else if (i == sl->n - 1) {
            sprintf(x_ime, "x%d", sl->n - 1);
            sprintf(x_i, "x%d", sl->n);
            sl->m_jacobi[i][i - 1] = evaluator_derivative(sl->func[i].v_func, x_ime);
            sl->m_jacobi[i][i] = evaluator_derivative(sl->func[i].v_func, x_i);
            printf("\njacobi[%d][%d]: %s\n", i, i - 1, evaluator_get_string(sl->m_jacobi[i][i - 1]));
            printf("\njacobi[%d][%d]: %s\n", i, i, evaluator_get_string(sl->m_jacobi[i][i]));
        } else {
            sprintf(x_ime, "x%d", i);
            sprintf(x_i, "x%d", i + 1);
            sprintf(x_ima, "x%d", i + 2);
            sl->m_jacobi[i][i - 1] = evaluator_derivative(sl->func[i].v_func, x_ime);
            sl->m_jacobi[i][i] = evaluator_derivative(sl->func[i].v_func, x_i);
            sl->m_jacobi[i][i + 1] = evaluator_derivative(sl->func[i].v_func, x_ima);
            printf("\njacobi[%d][%d]: %s\n", i, i - 1, evaluator_get_string(sl->m_jacobi[i][i - 1]));
            printf("\njacobi[%d][%d]: %s\n", i, i, evaluator_get_string(sl->m_jacobi[i][i]));
            printf("\njacobi[%d][%d]: %s\n", i, i + 1, evaluator_get_string(sl->m_jacobi[i][i + 1]));
        }
    }

    free(x_ime);
    free(x_i);
    free(x_ima);
}

/**
 * Calcula sistema jacobi
 * @param sl: sistema linear
 * @return 
 */ 
void calcula_jacobi(sl_t *sl) {
    char *x_ime = calloc(6, sizeof(char));
    char *x_i = calloc(6, sizeof(char));
    char *x_ima = calloc(6, sizeof(char));
    
    for (int i = 0; i < sl->n; i++) {
        if (i == 0) {
            sprintf(x_i, "x1");
            sprintf(x_ima, "x2");
            sl->jacobi_solution[i][i] = evaluator_evaluate(sl->m_jacobi[i][i], 1, &x_i, &sl->x_aprox[i]);
            sl->jacobi_solution[i][i + 1] = evaluator_evaluate(sl->m_jacobi[i][i + 1], 1, &x_ima, &sl->x_aprox[i + 1]);
        } else if (i == sl->n - 1) {
            sprintf(x_ime, "x%d", sl->n - 1);
            sprintf(x_i, "x%d", sl->n);
            sl->jacobi_solution[i][i - 1] = evaluator_evaluate(sl->m_jacobi[i][i - 1], 1, &x_ime, &sl->x_aprox[i - 1]);
            sl->jacobi_solution[i][i] = evaluator_evaluate(sl->m_jacobi[i][i], 1, &x_i, &sl->x_aprox[i]);
        } else {
            sprintf(x_ime, "x%d", i);
            sprintf(x_i, "x%d", i + 1);
            sprintf(x_ima, "x%d", i + 2);
            sl->jacobi_solution[i][i - 1] = evaluator_evaluate(sl->m_jacobi[i][i - 1], 1, &x_ime, &sl->x_aprox[i - 1]);
            sl->jacobi_solution[i][i] = evaluator_evaluate(sl->m_jacobi[i][i], 1, &x_i, &sl->x_aprox[i]);
            sl->jacobi_solution[i][i + 1] = evaluator_evaluate(sl->m_jacobi[i][i + 1], 1, &x_ima, &sl->x_aprox[i + 1]);
        }
        /* for (int j = 0; j < sl->n; j++) {
            sprintf(currX, "x%d", j);
            sl->jacobi_solution[i][j] = evaluator_evaluate(sl->m_jacobi[i][j], 1, &currX, sl->x_aprox + j);
        } */
    }

    free(x_ime);
    free(x_i);
    free(x_ima);
} // !!! Revisar !!! Talvez possa usar evaluator_evaluate_x, testar

void destroi_function(function_t *func) {
        printf("AEa\n");
    free(func->s_func);
        printf("AGa\n");
    free(func->v_func);
        printf("AFa\n");
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