#include "newtonSNL.h"

// Função principal para cada SL, alocando variáveis necessárias e executando cada função
int newton(sl_t* sl) {

    /*
    double *resultsFuncs = (double *) calloc(sl->n, sizeof(double));
    double *delta = (double *) calloc(sl->n, sizeof(double));
    double *oldX = (double *) calloc(sl->n, sizeof(double));

    //double **sl = criaSL();

    if(!delta || !oldX) {
        perror("Erro de alocação de memória.");
        exit(1);
    }

    int iter, criterio1, criterio2, criterio3;

    iter = 0;

    printf("%d\n", sl->n);
    for(int i = 0; i < sl->n; i++)
        printf("%s = 0\n", sl->func[i].s_func);
    
    criterio1 = 1;
    criterio2 = 1;
    criterio3 = 1;

    // Laço principal de cada SL da entrada, que executa todas as funções para o SL até os critérios
    // de parada serem satisfeitos
    do {
        printf("#\n");
        for(int i = 0; i < sl->n; i++)
            printf("x%d = %lf\n", i + 1, sl->x_aprox[i]);

        double maior = 0;

        maior = maior_func();

        if(maior < sl->epsilon)
            criterio2 = 0;
        
        criaJacobs();

        calculaSL(sl);

        calculaGauss(sl, resultsFuncs, delta);
        criterio3 = calculaNovoX(oldX, sl->x_aprox, delta);
        

        iter++;
        if(iter > sl->MAXIT)
            criterio1 = 0;
        
    } while(criterio1 && criterio2 && criterio3);
*/
    return 1;
}