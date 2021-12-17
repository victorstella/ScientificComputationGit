
#include "gauss.h"

void gauss_seidel(sl_t *sl) {

    sl->diagonal_central[0] = sl->jacobi_solution[0][0];
    sl->diagonal_direita[0] = sl->jacobi_solution[0][1];

    for(int i = 1; i < sl->n - 1; i++) {
        sl->diagonal_central[i] = sl->jacobi_solution[i][i];
        sl->diagonal_direita[i] = sl->jacobi_solution[i][i + 1];
        sl->diagonal_esquerda[i] = sl->jacobi_solution[i][i - 1];
    }

    sl->diagonal_esquerda[sl->n - 1] = sl->jacobi_solution[sl->n - 1][sl->n - 2];
    sl->diagonal_central[sl->n - 1] = sl->jacobi_solution[sl->n-1][sl->n - 1];

    double *a = sl->diagonal_esquerda;
    double *d = sl->diagonal_central;
    double *c = sl->diagonal_direita;

    double maior = 0;
    double oldMaior = 0;

    do {
        oldMaior = maior;
    
        sl->delta_x[0] = (sl->evaluated_curr_x[0] - (c[0] * sl->delta_x[1])) / d[0];
        if (maior < fabs(sl->delta_x[0])) maior = sl->delta_x[0];
        printf("ççç %1.16lf\n", sl->delta_x[0]);
    
        for (int i = 1; i < sl->n - 1; i++) {
            sl->delta_x[i] = (sl->evaluated_curr_x[i] - (a[i - 1] * sl->delta_x[i - 1]) - (c[i] * sl->delta_x[i + 1])) / d[i];
            if (maior < fabs(sl->delta_x[i])) maior = sl->delta_x[i];
            printf("ççç %1.16lf\n", sl->delta_x[i]);
        }

        sl->delta_x[sl->n - 1] = (sl->evaluated_curr_x[sl->n - 1] - (a[sl->n - 2] * sl->delta_x[sl->n - 2])) / d[sl->n - 1];
        if (maior < fabs(sl->delta_x[sl->n - 1])) maior = sl->delta_x[sl->n - 1];
        printf("ççç %1.16lf\n", sl->delta_x[sl->n - 1]);

        printf("Diferença = %1.16f\n", fabs(fabs(maior) - fabs(oldMaior)));
    
    } while (fabs(fabs(maior) - fabs(oldMaior)) > 0.00001);
    printf("Saiu com maior = %1.16lf > %1.16lf\n", fabs(fabs(maior) - fabs(oldMaior)), 0.00001 );
}

/**
 * Resolve o sl e descobre o delta
 * @param sl, Sistema Linear que tem as funcoes, as aproximacoes de x e o delta
 * @return 
 */
//void gauss_seidel(sl_t *sl, double tol) {
    /*
void gauss_seidel(sl_t *sl) {
    double d = sl->jacobi_solution[0][0], 
        a = sl->jacobi_solution[1][0], 
        c = sl->jacobi_solution[0][1];

    sl->delta_x[0] = (sl->evaluated_curr_x[0] - (c * sl->delta_x[1])) / d;
    
    for (int i = 1; i < sl->n - 1; i++)
        sl->delta_x[i] = (sl->evaluated_curr_x[i] - (a * sl->delta_x[i - 1]) - (c * sl->delta_x[i + 1])) / sl->jacobi_solution[i][i];

    sl->delta_x[sl->n - 1] = (sl->evaluated_curr_x[sl->n - 1] - (a * sl->delta_x[sl->n - 2])) / sl->jacobi_solution[sl->n - 1][sl->n - 1];


    for (int j = 0; j < sl->n; j++)
        for (int l = 0; l < sl->n; l++) printf(">[%d][%d] jacobi_solution: %f\n", j, l, sl->jacobi_solution[j][l]);

    for (int k = 0; k < sl->n; k++) printf("> delta_x%d: %1.16f  --  a: %f | d: %f | c: %f | b: %f\n", k + 1, sl->delta_x[k], a, sl->jacobi_solution[k][k], c, sl->evaluated_curr_x[k]);

    for (int m = 0; m < sl->n; m++)
        printf("* %d * evaluated_curr_x: %f | x_aprox: %f | x_aprox_old: %f\n", m + 1, sl->evaluated_curr_x[m], sl->x_aprox[m], sl->x_aprox_old[m]);
}*/


// Encontra maior valor no SL na coluna k
int encontraMax(double** sl, int k, int n) {
    int posMaior = k;
    for (int l = k; l < n; l++) {
        if(fabs(sl[l][k]) > fabs(sl[posMaior][k]))
            posMaior = l;
    }
    return posMaior;
}

// Troca o conteúdo de 2 linhas do SL e do vetor de resultados
void trocaLinha(double **sl, double *res, int a, int b, int n) {
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
void triangulariza(double **sl, double *resultsFuncs, int n) {
    int pivo = 0;

    // Encontra o pivo para cada coluna do SL
    for (int i = 0; i < n - 1; i++) {
        pivo = encontraMax(sl, i, n);
        if (i != pivo)
            trocaLinha(sl, resultsFuncs, i, pivo, n);
        
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
 void retroSubst(double **sl, double *resultsFuncs, double* delta, int n) {
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
void calculaGauss(double **sl, double *resultsFuncs, double* delta, int n){
    for(int i = 0; i < n; i++)
        resultsFuncs[i] = -resultsFuncs[i];

    triangulariza(sl, resultsFuncs, n);
    retroSubst(sl, resultsFuncs, delta, n);

    for(int i = 0; i < n; i++)
        resultsFuncs[i] = -resultsFuncs[i];
}
