#ifndef __GAUSS__
#define __GAUSS__

    #include "functions.h"

    //void gauss_seidel(sl_t *sl, double tol);
    void gauss_seidel(sl_t *sl);
    
    //void calcula_gauss(double **sl, double *resultsFuncs, double* delta, int n);
    void calcula_gauss(sl_t *sl);

#endif