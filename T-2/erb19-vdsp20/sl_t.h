#ifndef __LINEAR_SYSTEM__
#define __LINEAR_SYSTEM__

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <matheval.h>

    typedef struct {
        char * s_func;
        void * v_func;
        char ** var_names;
        int var_count;
    } function_t;

    typedef struct {
        int n;
        function_t * func;
        double * x_aprox;
        void *** m_jacobi;
        double ** jacobi_solution;
        float epsilon;
        int MAXIT;
    } sl_t;


    void inicia_function_t(function_t* f, void * s_func);

    sl_t * inicia_sl_t(int n, void ** funcs, double * x_aprox, float epsilon, int maxit);
    
    void monta_jacobi(sl_t *sl);

    void calcula_jacobi(sl_t* sl);

    void destroi_sl(sl_t* sl);

#endif