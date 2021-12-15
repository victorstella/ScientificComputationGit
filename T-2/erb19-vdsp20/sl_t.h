#ifndef __LINEAR_SYSTEM__
#define __LINEAR_SYSTEM__

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <matheval.h>

    typedef struct {
        char * s_func;              // Função como string
        void * v_func;              // Função como void*
        char ** var_names;          // Nome das variáveis
        int var_count;              // Quantidade de variaveis na func
    } function_t;

    typedef struct {
    int n;                          // Tamanho do sl
        function_t * func;          // Vetor de funcoes
        double * x_aprox;           // Aproximação atual de x
        double * x_aprox_old;       // Aproximação antiga de x
        double * evaluated_curr_x;  // Resultados das função aplicadas nos x atuais
        void *** m_jacobi;          // Matriz de funcoes jacobi
        double ** jacobi_solution;  // Matriz de resultado das funcoes jacobi
        float epsilon;
        int MAXIT;
    } sl_t;


    void inicia_function_t(function_t* f, void * s_func);

    sl_t * inicia_sl_t(int n, void ** funcs, double * x_aprox, float epsilon, int maxit);
    
    void monta_jacobi(sl_t *sl);

    void calcula_jacobi(sl_t* sl);

    void destroi_sl(sl_t* sl);

#endif