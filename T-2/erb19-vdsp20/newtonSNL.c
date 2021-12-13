#include "newtonSNL.h"

double *delta;

// Aloca espaço para o SL
double** criaSL() {
    double **sl = (double **) calloc(n, sizeof(double *));

    if(!sl) {
        perror("Erro de alocação de memória.");
        exit(1);
    }

    for (int a = 0; a < n; a++)
        sl[a] = (double *) calloc(n, sizeof(double));

    return sl;
}


// Busca em str todas as substrings a e troca por b
// Retorna quantas substrings a foram encontradas em str
int buscaETroca(char *str, char *a, char b) {
    
    if(strlen(a) == 0) return 0;

    int vezes = 0;
    size_t tamSTR = strlen(str);
    int tamA = strlen(a);
    int i = -1;

    int overDigit;
    char *p;
    
    p = strstr(str, a);
    while(p) {
        overDigit = 0;
        i = p - str;

        while(isdigit(str[i + 1 + overDigit]))
            overDigit++;

        if(overDigit == tamA - 1) {
            str[i] = b;
            for(int j = 1; j < tamA; j++)
                str[i + j] = ' ';

            vezes++;
        } else return 0;

        p = strstr(str, a);
    }

    return vezes;
}

// Troca os Xs por x, y e z. Calcula a nova aproximação
double calculaFunc(char *func) {

    int xyz[3] = {-1, -1, -1}, xyzPos = 0;
    char var;

    char *currFunc = strdup(func);

    int xValue = 0;

    char currX[4];
    
    for(int i = 1; i <= n && xyzPos <= 2; i++) {

        for(int j = 0; j < strlen(currFunc); j++) {
            sprintf(currX, "x%d", i);

            switch(xyzPos) {
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
                    perror("A equação possui mais de 3 variáveis diferentes.");
                    exit(1);
                    break;
            }

            if(buscaETroca(currFunc, currX, var) > 0) {
                xyz[xyzPos] = i - 1;
                xyzPos++;
                break;
            }
        }

        
    }

    void* currF = evaluator_create(currFunc);

    double temp;
    switch(xyzPos) {
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
            perror("A equação possui mais de 3 variáveis diferentes.");
            exit(1);
            break;
    }
    return temp;
}
// Calcula as funções e retorna o maior valor dentre elas
double maiorFunc() {
    double max = 0; 
    for(int i = 0; i < n; i++) {
        resultsFuncs[i] = calculaFunc(sFuncs[i]);
        max = maior(fabs(max), fabs(resultsFuncs[i]));
    }
    return max;
}

// Calcula nova aproximação para dados X e delta
int calculaNovoX(double *old, double *new, double *d) {
    int diff = 1;
    for(int i = 0; i < n; i++) {
        old[i] = new[i];
        new[i] = old[i] + d[i];
        if(fabs(d[i]) <= fabs(epsilon)) diff = 0;
    }
    return diff;
}

// Calcula o valor de cada posição da jacobiana aplicando o respectivo X de results
void calculaSL(double **sl) {
    char** varNames;
    int countVars;

    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n; j++){
            evaluator_get_variables(jacobs[i][j], &varNames, &countVars);
            sl[i][j] = evaluator_evaluate(jacobs[i][j], countVars, varNames, &results[j]);
            
            printf("Calculando jacobs = %s, countVars = %d = ", evaluator_get_string(jacobs[i][j]), countVars);
            for(int k = 0; k < countVars; k++){
                printf("(%s=%f) ", varNames[k], results[k]);
            }printf("\n");
        
        }

}

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

        // Calcula o tempo total levado pelo algoritmo para executar os cálculos
        tempoTotal = timestamp();

        maior = maiorFunc();

        if(maior < epsilon)
            criterio2 = 0;
        
        // Calcula o tempo levado pelo algoritmo para criar a matriz jacobiana
        tempoCriaJacobs = timestamp();
        criaJacobs();
        tempoCriaJacobs = timestamp() - tempoCriaJacobs;

        // Calcula o tempo levado para calcular a matriz jacobiana
        tempoCalcJacobs = timestamp();
        // Calcula o tempo levado para calcular o sistema linear por Gauss
        tempoSL = timestamp();
        calculaSL(sl);
        tempoCalcJacobs = timestamp() - tempoCalcJacobs;

        calculaGauss(sl, resultsFuncs, delta);
        criterio3 = calculaNovoX(oldX, results, delta);
        
        tempoSL = timestamp() - tempoSL;

        iter++;
        if(iter > MAXIT)
            criterio1 = 0;
        
        tempoTotal = timestamp() - tempoTotal;
    } while(criterio1 && criterio2 && criterio3);

    return 1;
}