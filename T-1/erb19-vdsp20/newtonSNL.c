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

// Busca em str todas as substrings a e troca por b
// Retorna quantas substrings a foram encontradas em str
int buscaETroca(char *str, char *a, char b){
    if(strlen(a) == 0) return 0;

    int vezes = 0;
    size_t tamSTR = strlen(str);
    int tamA = strlen(a);
    int i =-1;

    //printf("Procurando %s em %s, (%ld)\n", a, str, strlen(a));
    int overDigit;
    char*p;
    
    p = strstr(str, a);
    while(p){
        overDigit = 0;
        i = p - str;

        while(isdigit(str[i + 1 + overDigit])){
            overDigit++;
        }
        //printf("over = %d, tamA = %d\n", overDigit, tamA);
        if(overDigit == tamA-1){
            str[i] = b;
            for(int j = 1; j < tamA; j++) {
                str[i + j] = ' ';
            }

            //printf("Deu %s\n\n", str);

            vezes++;
        }else{
            return 0;
        }
        p = strstr(str, a);
        //exit(1);
    }

    //printf("Boaa %s\n\n", str);
        //exit(1);


    return vezes;

}

// Calcula uma nova aproximação
double calculaFunc(char *func) {

    int xyz[3] = {-1, -1, -1}, xyzPos = 0;
    char var;

    char *currFunc = strdup(func);

    int xValue = 0;

    char currX[4];
    
    //printf("\n-> Entrou() = %s\n", currFunc);
    for(int i = 1; i <= n && xyzPos <= 2; i++) {

        for(int j = 0; j < strlen(currFunc); j++) {
            sprintf(currX, "x%d", i);

            switch(xyzPos){
                case 0:
                    var = 'x';
                    break;
                case 1:
                    var = 'y';
                    break;
                case 2:
                    var = 'z';
                    break;
                default:
                    printf("Help!%i\n", xyzPos);
                    exit(1);
                    break;
            }

            if(buscaETroca(currFunc, currX, var) > 0){
                xyz[xyzPos] = i-1;
                xyzPos++;
                break;
            }
        }

        
    }
    //printf("Saiu com f() = %s; xyzPos=%d, results{%d, %d, %d} = {%lf, %lf, %lf}\n", currFunc, xyzPos, xyz[0], xyz[1], xyz[2], results[0], results[1], results[2]);

    void* currF = evaluator_create(currFunc);

    double temp;
    switch(xyzPos){
        case 0:
            temp = atoi(evaluator_get_string(currF));
            break;
        case 1:
            temp = evaluator_evaluate_x(currF, results[xyz[0]]);
            break;
        case 2:
            temp = evaluator_evaluate_x_y(currF, results[xyz[0]], results[xyz[1]]);
            break;
        case 3:
            temp = evaluator_evaluate_x_y_z(currF, results[xyz[0]], results[xyz[1]], results[xyz[2]]);
            break;
        default:
            perror("Socorro! Ajudem-me");
            exit(1);
            break;
    }
    return temp;
}

/*
// Calcula uma nova aproximação
double calculaFunc(char *func) {

    int xyz[3] = {-1, -1, -1}, xyzPos = 0;

    int temVar = 0;

    char *currFunc = strdup(func);
    char currX[6];
    int xValue = 0;
    
    printf("\n-> Entrou() = %s\n", currFunc);
    for(int i = 1; i <= n && xyzPos <= 2; i++) {
        printf("\n>>Troca currX por x<<\n");
        strcpy(currX, "x");
        temVar = 0;
        // Percorre a função atual, procurando uma ocorrência do caractere 'x' 
        for(int k = 0; k < strlen(currFunc); k++) {
            printf("k:%d HUMMMMMMMMMMMMMMMMMMMMMM  %s\n", k, &currFunc[k]);
                int numSize = 0;
            if(currFunc[k] == 'x') {
                if(strcmp(currX, "x") == 0){
                    // Encontrado um X, verifica se o valor a seguir é um número e descobre quantas casas decimais possui
                    while(isdigit(currFunc[k + numSize + 1])) {
                        numSize++;
                    }
                    strncpy(currX, &currFunc[k+1], numSize);

                    if (numSize > 0){
                        temVar = 1;
                        printf("Procurando x%s\n", currX);
                        xValue = atoi(currX) - 1;
                        xyz[xyzPos] = xValue;
                    }
                }
                if (strncmp(&currFunc[k], currX, strlen(currX))) {
                    printf("Achei! > %s\n", &currFunc[k]);
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
                    printf("Troca por %c\n", currFunc[k]);

                    for (int l = 0; l < numSize; l++) {
                        currFunc[k + l + 1] = ' ';
                    }
                }

            }
        }
        if(temVar) xyzPos++;
        
    }
    printf("Saiu com f() = %s; xyzPos=%d, results{%d, %d, %d} = {%lf, %lf, %lf}\n", currFunc, xyzPos, xyz[0], xyz[1], xyz[2], results[0], results[1], results[2]);

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
*/


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