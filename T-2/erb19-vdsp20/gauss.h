#ifndef __GAUSS__
#define __GAUSS__

    #include "functions.h"

    //void gauss_seidel(sl_t *sl, double tol);
    void gauss_seidel(sl_t *sl);
void calculaGauss(double **sl, double *resultsFuncs, double* delta, int n);


#endif