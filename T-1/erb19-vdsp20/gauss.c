#include "functions.h"
#include "gauss.h"

// Encontra maior valor no sistema sl na coluna k
int encontraMax(double** sl, int k) {
    int posMaior = k;
    for (int l = k; l < n; l++) {
        if(fabs(sl[l][k]) > fabs(sl[posMaior][k])){
            posMaior = l;
        }
    }
    return posMaior;
}

void trocaLinha(double **sl, double *res, int a, int b){
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
void triangulariza(double **sl, double *resultsFuncs){
    int pivo = 0;

    for (int i = 0; i < n-1; i++) {
        pivo = encontraMax(sl, i);
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
 void retroSubst(double **sl, double *resultsFuncs, double* delta){
    double soma;
    for(int i = 0; i < n; i++){
        soma = 0;
        for(int j = i; j > 0; j--){
            soma += sl[n - (i + 1)][j] * delta[n-j];
        }
        delta[n - (i + 1)] = (resultsFuncs[n - (i + 1)] - soma ) / sl[n - (i + 1)][n - (i + 1)];
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

    i:1 delta[n-2] = (resultsFuncs[n-2] - (sl[n-2][n-1]*delta[n-1])) / sl[n-2][n-2] 

    i:2 delta[n-3] = (resultsFuncs[n-3] - (sl[n-3][n-1]*delta[n-2]) - (sl[n-3][n-2]*delta[n-1])) / sl[n-3][n-3] 
    i:2 delta[0] = (resultsFuncs[0] - (sl[0][2]*delta[0]) - (sl[0][1]*delta[1])) / sl[0][0] 
                                                            j:2                          j:1

*/




void calculaGauss(double **sl, double *resultsFuncs, double* delta){
    for(int i = 0; i < n; i++){
        resultsFuncs[i] = -resultsFuncs[i];
    }

    triangulariza(sl, resultsFuncs);



    retroSubst(sl, resultsFuncs, delta);


    for(int i = 0; i < n; i++){
        resultsFuncs[i] = -resultsFuncs[i];
    }
    

}
