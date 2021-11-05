#ifndef __FUNCTIONS__
#define __FUNCTIONS__

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <float.h>
    #include <math.h>

    #include <matheval.h>
    #include "utils.h"


    void verificaErro(void* funcao);

    void inputs();

    void criaSL();
    
    void init();

    double gauss();

    int nwt_crit(double nwt_old);

#endif