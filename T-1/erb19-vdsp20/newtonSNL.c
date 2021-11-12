#include "newtonSNL.h"

double *delta;


// Calcula SL dos Jacobianos aplicados nos X's
double** criaSL() {
    double **sl = (double **) calloc(n, sizeof(double *));
    for (int a = 0; a < n; a++) {
        sl[a] = (double *) calloc(n, sizeof(double));
    }

    return sl;
}

// Calcula uma nova aproximação
double calculaFunc(char *func) {

    int xyz[3] = {-1, -1, -1}, xyzPos = -1;

    char *currFunc = strdup(func);
    char aux[6];
    
    for(int i = 1; i <= n && xyzPos <= 2; i++) {
        aux[0] = 'x';
        aux[1] = '\0';
        // Percorre a função atual, procurando uma ocorrência do caractere 'x' 
        for(int k = 0; k < strlen(currFunc); k++) {
            if(currFunc[k] == aux[0]) {
                int numSize = 0;
                if(strcmp(aux, "x") == 0){
                    // Encontrado um X, verifica se o valor a seguir é um número e descobre quantas casas decimais possui
                    while(isdigit(currFunc[k + numSize + 1])) {
                        aux[numSize] = currFunc[k + numSize + 1];
                        numSize++;
                        aux[numSize] = '\0';
                    }

                    if (numSize > 0){
                        xyzPos++;
                        xyz[xyzPos] = atoi(aux) - 1;
                    }
                }
                if (strncmp(&currFunc[k], aux, strlen(aux))) {
                    switch(xyzPos){
                        case 0:
                            currFunc[k] = 'x';
                            break;
                        case 1:
                            currFunc[k] = 'y';
                            break;
                        case 2:
                            currFunc[k] = 'z';
                            break;
                        default:
                            printf("Help!%i\n", xyzPos);
                            exit(1);
                            break;
                    }

                    for (int l = 0; l < numSize; l++) {
                        currFunc[k + l + 1] = ' ';
                    }
                }

            }
            
        }
    }
    
    void* currF = evaluator_create(currFunc);

    double temp;
    switch(xyzPos){
        case -1:
            temp = atoi(evaluator_get_string(currF));
            break;
        case 0:
            temp = evaluator_evaluate_x(currF, results[xyz[0]]);
            break;
        case 1:
            temp = evaluator_evaluate_x_y(currF, results[xyz[0]], results[xyz[1]]);
            break;
        case 2:
            temp = evaluator_evaluate_x_y_z(currF, results[xyz[0]], results[xyz[1]], results[xyz[2]]);
            break;
        default:
            perror("Socorro! Ajudem-me");
            exit(1);
            break;
    }
    return temp;
}


// Calcula as funções e retorna o maior valor dentre elas
double maiorFunc(){
    double max = 0; 
    for(int i = 0; i < n; i++){
        resultsFuncs[i] = calculaFunc(sFuncs[i]);
        max = maior(fabs(max), fabs(resultsFuncs[i]));
    }
    return max;
}

void calculaNovoX(double *old, double *new, double *d) {
    for(int i = 0; i < n; i++) {
        old[i] = new[i];
        new[i] = old[i] + d[i];
    }
}

void calculaSL(double **sl) {
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n; j++) 
            sl[i][j] = evaluator_evaluate_x(jacobs[i][j], results[j]);    
}

int newton() {
    resultsFuncs = (double *) calloc(n, sizeof(double));
    delta = (double *) calloc(n, sizeof(double));
    double *oldX = (double *) calloc(n, sizeof(double));

    int iter, criterio1, criterio2;

    iter = 0;

    double **sl = criaSL();

    printf("%d\n", n);
    for(int i = 0; i < n; i++) {
        printf("%s = 0\n", sFuncs[i]);
    }
    
    criterio1 = 1;
    criterio2 = 1;

    // Calcula o tempo levado pelo algoritmo para executar os cálculos
    tempoTotal = timestamp();

    while(criterio1 && criterio2) {

        printf("#\n");
        for(int i = 0; i < n; i++){
            printf("x%d = %lf\n", i + 1, results[i]);
        }

        double maior = 0;

        maior = maiorFunc();

        if(maior < epsilon)
            criterio2 = 0;
        
        // Calcula o tempo levado pelo algoritmo para executar os cálculos
        tempoCriaJacobs = timestamp();
        criaJacobs();
        tempoCriaJacobs = timestamp() - tempoCriaJacobs;

        tempoCalcJacobs = timestamp();
        calculaSL(sl);
        tempoCalcJacobs = timestamp() - tempoCalcJacobs;

        tempoSL = timestamp();
        calculaGauss(sl, resultsFuncs, delta);
        calculaNovoX(oldX, results, delta);
        tempoSL = timestamp() - tempoSL;

        iter++;
        criterio1 = (iter < MAXIT);
    }

    tempoTotal = timestamp() - tempoTotal;

    return 1;
}