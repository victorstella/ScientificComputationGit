#ifndef __FUNCTIONS__
#define __FUNCTIONS__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <float.h>
    #include <math.h>
    #include <ctype.h>

    #include <matheval.h>
    #include "utils.h"
    #include "gauss.h"

    int n; // Número de funções
    int MAXIT; // Número máximo de iterações respectivamente
    float epsilon; // Epsilon fornecido na entrada
    
    double *results, tempoTotal; // Array de aproximações (X's)
    double *resultsFuncs; // Array de resultados das Funcoes com os X's atuais
    char **sFuncs; // Array de funções em forma de strings
    void ***jacobs;

    int inputs();

    void criaJacobs();

    double maior(double a, double b);

    void destroi_funcoes();

#endif