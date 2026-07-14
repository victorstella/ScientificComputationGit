#include "functions.h"
#include "gauss.h"

// Encontra maior valor no SL na coluna k
int encontraMax(double** sl, int k) {
    int posMaior = k;
    for (int l = k; l < n; l++) {
        if(fabs(sl[l][k]) > fabs(sl[posMaior][k]))
            posMaior = l;
    }
    return posMaior;
}

// Troca o conteúdo de 2 linhas do SL e do vetor de resultados
void trocaLinha(double **sl, double *res, int a, int b) {
    double aux;
    for (int i = 0; i < n; i++) {
        aux = sl[a][i];
        sl[a][i] = sl[b][i];
        sl[b][i] = aux;
    }
    aux = res[a];
    res[a] = res[b];
    res[b] = aux;
}

// Triangulariza o SL com pivoteamento parcial
void triangulariza(double **sl, double *resultsFuncs) {
    int pivo = 0;

    // Encontra o pivo para cada coluna do SL
    for (int i = 0; i < n - 1; i++) {
        pivo = encontraMax(sl, i);
        if (i != pivo)
            trocaLinha(sl, resultsFuncs, i, pivo);
        
        // Calcula multiplicador
        for(int j = i + 1; j < n; j++) {
            double m = sl[j][i] / sl[i][i];
            sl[j][i] = 0.0;

            // Multiplica todas as linhas pelo multiplicador
            for(int k = i + 1; k < n; k++)
                sl[j][k] -= sl[i][k] * m;
            
            // Multiplica todas as posições do vetor de resultados pelo multiplicador
            resultsFuncs[j] -= resultsFuncs[i] * m;
        }
    }
}

// Retro-substitui o SL triangularizado
 void retroSubst(double **sl, double *resultsFuncs, double* delta) {
    double soma;
    for(int i = 0; i < n; i++) {
        soma = 0;
        for(int j = i; j > 0; j--)
            soma += sl[n - (i + 1)][j] * delta[n - j];
        delta[n - (i + 1)] = (resultsFuncs[n - (i + 1)] - soma ) / sl[n - (i + 1)][n - (i + 1)];
    }
} 

// Inverte o sinal dos valores do vetor de resultados para efetuar a triangularização e a retrosubstituição
// Depois inverte novamente para o vetor ficar como era inicialmente.
void calculaGauss(double **sl, double *resultsFuncs, double* delta){
    for(int i = 0; i < n; i++)
        resultsFuncs[i] = -resultsFuncs[i];

    triangulariza(sl, resultsFuncs);
    retroSubst(sl, resultsFuncs, delta);

    for(int i = 0; i < n; i++)
        resultsFuncs[i] = -resultsFuncs[i];
}
