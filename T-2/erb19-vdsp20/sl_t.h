#ifndef __LINEAR_SYSTEM__
#define __LINEAR_SYSTEM__

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <matheval.h>

    typedef struct {
        char * s_func;
        void * v_func;
        double* x_aprox;
        double solution;
        char** var_names;
    } function_t;

    typedef struct {
        int n;
        function_t * func;
        void *** m_jacobi;
        double ** jacobi_solution; 
    } sl_t;


    function_t* inicia_function_t(char* s_func, double solution, int var_count);

    sl_t * inicia_sl_t(int n, char ** funcs, double* x_aprox);


#endif