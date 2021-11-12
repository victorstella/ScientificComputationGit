#include "functions.h"
#include "gauss.h"

// Encontra maior valor no sistema sl na coluna k
int encontraMax(double** sl, int k) {
    int posMaior = 0;
    for (int l = k; l < n; l++) {
        if(sl[l][k] > sl[posMaior][k]){
            posMaior = l;
        }
    }
    return posMaior;
}

void trocaLinha(double **sl, double *res, int a, int b){
    double aux;
    printf("\ntrocação franca\n");
    for (int i = 0; i < n; i++) {
        printf("Troca %lf e %lf\n", sl[a][i], sl[b][i]);
        aux = sl[a][i];
        sl[a][i] = sl[b][i];
        sl[b][i] = aux;
    }
    aux = res[a];
    res[a] = res[b];
    res[b] = aux;
}
/*!
  Troca duas linhas de um Sistema Triangular
  L Sistema triangular a ter linhas trocadas
  i Número da linha a ser trocada.
  iPivo Número da outra linha a ser trocada.

void trocaLinhaL(S_tri *L, int i, int iPivo){
    if(i > 0) {
        double temp;
        for(int j = 0; j <= i - 1; j++) {
            temp = L->coef[i][j];
            L->coef[i][j] = L->coef[iPivo][j];
            L->coef[iPivo][j] = temp;
        }
    }
}*/

// Triangulariza o SL com pivoteamento parcial
void triangulariza(double **sl, double *resultsFuncs){
    int pivo = 0;

    for (int i = 0; i < n-1; i++) {
        pivo = encontraMax(sl, i);
        printf("Pivot[coluna %d] = %d\n", i, pivo);
        if (i != pivo) {
            trocaLinha(sl, resultsFuncs, i, pivo);
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
 void retroSubst(double **sl, double *resultsFuncs, double* delta, double *results){

for(int i = 0; i<n; i++){
    printf("\n>> rf[%d] = %lf", i, resultsFuncs[i]);
}printf("\n");

    double soma;
    soma = 0;
    for(int i = 0; i < n; i++){
        for(int j = i; j > 0; j--){
            printf("\n%lf + (%lf*%lf) = ", soma, sl[n-(i+1)][j], delta[j]);
            soma += sl[n-(i+1)][j]*delta[j];
            printf(" %lf\n", soma);
        }
        delta[n-(i+1)] = (resultsFuncs[n-(i+1)] - soma ) / sl[n-(i+1)][n-(i+1)];
        printf("Divide (%lf[%d] - %lf) por %lf\n",(resultsFuncs[n-(i+1)]), n-(i+1), soma ,sl[n-(i+1)][n-(i+1)]);
    }
} 
/*
    a b c   p 
    0 d e   q
    0 0 f   r

    |a*x + b*y + c*z = p -> x = (p - c*z - b*y)/a
    |      d*y + e*z = q -> y = (q - e*z)/d
    |            f*z = r -> z = r/f
    
    n=3;
    i:0 delta[n-1] = (resultsFuncs[n-1] ) / sl[n-1][n-1] 

    i:1 delta[n-2] = (resultsFuncs[n-2] - (sl[n-2][n-1]*resultsFuncs[n-2])) / sl[n-2][n-2] 

    i:2 delta[n-3] = (resultsFuncs[n-3] - (sl[n-3][n-1]*resultsFuncs[n-3]) - (sl[n-3][n-2]*resultsFuncs[n-2])) / sl[n-3][n-3] 
    i:2 delta[0] = (resultsFuncs[0] - (sl[0][2]*resultsFuncs[0]) - (sl[0][1]*resultsFuncs[1])) / sl[0][0] 
                                                            j:2                          j:1

*/


/* double newX(double **sl, double *resultsFuncs, double *results, double *delta, int i, int j) {

    if (i > 0) return newX(sl, resultsFuncs, results, delta, i, j - 1) + sl[i][j] * results[i];
    else return 0;
}
void retroSubst(double **sl, double *resultsFuncs, double* delta, double *results){

    delta[n-1] = resultsFuncs[n-1] / sl[n-1][n-1];
    double temp;
    for (int i = n - 2; i > 0; i--) {
        temp = newX(sl, resultsFuncs, results, delta, i, i);
        delta[i] = (resultsFuncs[i] - temp) / sl[i][n - 1];
        printf("delta[%d] = (%f - %f) / %f = %f\n", i, resultsFuncs[i], temp , sl[i][n - 1],delta[i]);
    }
} */


void calculaGauss(double **sl, double *resultsFuncs, double* delta, double *results){
    triangulariza(sl, resultsFuncs);

    printf("\nTRIANGULARIZAD000\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%lf | ", sl[i][j]);
        }printf("\n");
    }
for(int i = 0; i<n; i++){
    printf("\n>> rf[%d] = %lf", i, resultsFuncs[i]);
}printf("\n");
    
    printf("results > ");
    for(int i = 0; i < n; i++){
        printf("%lf |", results[i]);
    }printf("\n");

    retroSubst(sl, resultsFuncs, delta, results);


    printf("delta > ");
    for(int i = 0; i < n; i++){
        printf("%lf |", delta[i]);
    }printf("\n");

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
