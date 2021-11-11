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

    void verificaErro(void* funcao);

    void inputs();

    void criaJacobs();

    int newton();

    void printa_resultados();

    void criaArrayResultado();

    void destroi_funcoes();

#endif