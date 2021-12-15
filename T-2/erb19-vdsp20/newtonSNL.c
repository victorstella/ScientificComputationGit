#include "newtonSNL.h"
/*
// Função principal para cada SL, alocando variáveis necessárias e executando cada função
int newton() {
    resultsFuncs = (double *) calloc(n, sizeof(double));
    delta = (double *) calloc(n, sizeof(double));
    double *oldX = (double *) calloc(n, sizeof(double));

    double **sl = criaSL();

    if(!resultsFuncs || !delta || !oldX) {
        perror("Erro de alocação de memória.");
        exit(1);
    }

    int iter, criterio1, criterio2, criterio3;

    iter = 0;

    printf("%d\n", n);
    for(int i = 0; i < n; i++)
        printf("%s = 0\n", sFuncs[i]);
    
    criterio1 = 1;
    criterio2 = 1;
    criterio3 = 1;

    // Laço principal de cada SL da entrada, que executa todas as funções para o SL até os critérios
    // de parada serem satisfeitos
    do {
        printf("#\n");
        for(int i = 0; i < n; i++)
            printf("x%d = %lf\n", i + 1, results[i]);

        double maior = 0;


        maior = maiorFunc();

        if(maior < epsilon)
            criterio2 = 0;
        
        criaJacobs();

        calculaSL(sl);

        calculaGauss(sl, resultsFuncs, delta);
        criterio3 = calculaNovoX(oldX, results, delta);
        

        iter++;
        if(iter > MAXIT)
            criterio1 = 0;
        
        tempoTotal = timestamp() - tempoTotal;
    } while(criterio1 && criterio2 && criterio3);

    return 1;
}*/