#include "functions.h"
#include "gauss.h"

// Encontra maior valor no sistema sl na coluna i
int encontraMax(double** sl, int k) {
    int posMaior = 0;
    for (int l = 0; l < n; l++) {
        if(sl[l][k] > sl[l][posMaior]){
            posMaior = k;
        }
    }
    return posMaior;
}

void trocaLinha(double **sl, int a, int b){
    double *aux = (double *) calloc(n, sizeof(double));
    
    for (int i = 0; i < n; i++) {
        aux[i] = sl[a][i];
        sl[a][i] = sl[b][i];
        sl[b][i] = aux[i];
    }

    free(aux);
}

// Triangulariza o SL com pivoteamento parcial
void triangulariza(double **sl, double *resultsFuncs){
    int pivo = 0;
  
    for (int i = 0; i < n; i++) {
        pivo = encontraMax(sl, i);
        if (i != pivo) {
            trocaLinha(sl, i, pivo);
        }
        
        for(int j = i + 1; j < n; j++){
            double m = sl[j][i] / sl[i][i];
            sl[j][i] = 0.0;

            for(int k = i + 1; k < n; k++) {
                sl[j][k] -= sl[i][k] * m;
            }

            resultsFuncs[j] -= resultsFuncs[i] * m;
            // calcula multiplicador
            // multiplica todas as linhas
        }
    }
}

// Retro-substitui o SL triangularizado
void retroSubst(double **sl, double *resultsFuncs, double *results){
    double *dx = (double *) calloc(n, sizeof(double));

    dx[n-1] = results[n-1];
    results[n-1] = sl[n-1][n-1] / resultsFuncs[n-1];
    dx[n-1] -= results[n-1];

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (j - 1 > 0) {
                dx[i] = results[i];
                results[i] = (sl[i][j - 1] - sl[i][j] * results[i + 1]) / resultsFuncs[i];
                dx[i] -= results[i];
            }
        }
    }
}
/*
    a b c   p 
    0 d e   q
    0 0 f   r

    a*x + b*y + c*z = p
          d*y + e*z = q
                f*z = r -> z = r/f

    a*x + b*y + c*z = p
          d*y + e*z = q -> y = (q - e*z)/d
                f*z = r

*/

void calculaGauss(double **sl, double *resultsFuncs, double *results){
    triangulariza(sl, resultsFuncs);
    retroSubst(sl, resultsFuncs, results);

/*
// Aplica o método de Gauss repetidamente até os critérios de parada serem satisfeitos
double calculaGauss() {
    int iter = 0;
    int criterio1 = 0;
    double novoResult = 0, maiorER = 0, eAux = 0;

    do{
        for(int i = 0; i < n; i++){
            novoResult = (vetorSolucao[i] - somatorio(i)) / dMaior[i];

            eAux = calculaER(results[i], novoResult);
            maiorER = maior(eAux, maiorER);

            results[i] = novoResult;
        }

        criterio1 = maiorER > epsilon;
        
        iter++;

    } while(criterio1 && iter < MAXIT);

    free(vetorSolucao); 
    return 1;*/
}
