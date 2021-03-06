#ifndef __LINEAR_SYSTEM__
#define __LINEAR_SYSTEM__

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <matheval.h>

    typedef struct {
        char *s_func;              // Função como string
        void *v_func;              // Função como void*
    } function_t;

    typedef struct {
        int n;                      // Tamanho do sl
        function_t *func;           // Vetor de funcoes
        double *x_aprox;            // Aproximação atual de x
        double *x_aprox_old;        // Aproximação antiga de x
        double *delta_x;            // Delta entre x_aprox e x_aprox_old
        double *evaluated_curr_x;   // Resultados das função aplicadas nos x atuais
        double *jacobi_solution_principal;   // Vetor de resultado das funcoes jacobi da diagonal principal
        double jacobi_solution_inferior;
        double jacobi_solution_superior;
        
        float epsilon;

        double *diagonal_central;
        double *diagonal_direita;
        double *diagonal_esquerda;

        void *jacobi_superior;
        void *jacobi_principal;
        void *jacobi_inferior;

        int MAXIT;
    } sl_t;


    sl_t *inicia_sl_t(int n, void **funcs, double *x_aprox, float epsilon, int maxit);

    void calcula_funcs(sl_t *sl);

    void monta_jacobi(sl_t *sl);

    void calcula_jacobi(sl_t *sl);

    void destroi_function(function_t *func);

    void destroi_sl(sl_t *sl);

#endif
