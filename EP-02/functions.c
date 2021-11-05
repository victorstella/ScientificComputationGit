#include "functions.h"

int n, k, MAXIT;
float epsilon;
double* results;
void** funcs; // Array de ponteiro para funções
double** diagonal;

/*
    CASO k IMPAR
    k = 5; p=2; q=3
        __p__
        c b a                  f
       |1 0 0 0  0 0| |x0|   |1|
    q|d|0 4 0 1  0 0| |x1|   |2|
     |e|1 2 7 0  2 0|*|x2| = |4|
       |0 1 4 10 0 3| |x3|   |8|
       |0 0 1 6 13 0| |x4|   |16|
       |0 0 0 1 8 16| |x5|   |32|

    CASO k PAR
    k = 6; p=3; q=3
        __p___
        c b a                  g
       |1 0 0 0  0 0| |x0|   |1|
    q|d|0 4 0 1  0 0| |x1|   |2|
     |e|1 2 7 0  2 0|*|x2| = |4|
     |f|1 1 4 10 0 3| |x3|   |8|
       |0 1 1 6 13 0| |x4|   |16|
       |0 0 1 1 8 16| |x5|   |32|

    k = p+q

    p = piso(k/2)
    q = teto(k/2)


    A: a0 b1 c2 d3 
    B: a0 b0 c0 d0  e0 
    C: a1 b4 c7 d10 e13 f16 
    D: b0 c2 d4 e6 f8 
    E: c1 d1 e1 f1 
*/


// Verifica se evaluate foi criado corretamente
void verificaErro(void* funcao) {
    if(funcao == NULL){
        perror("Erro na entrada de dados.");
        exit(0);
    }
}

void inputs(){
    char *sIn; // Função de Entrada

    size_t len = 0;

    scanf("%d", &n);
    printf("Lido n(%d)\n", n);
    scanf("%d", &k);
    printf("Lido k(%d)\n", k);


    funcs = (void*) calloc(k, sizeof( void* ));


    getline(&sIn, &len, stdin);
    sIn[strcspn (sIn, "\n")] = '\0';

        for (int i = 0; i < k+1; i++){ 
            getline(&sIn, &len, stdin);
            sIn[strcspn (sIn, "\n")] = '\0';

            funcs[i] = evaluator_create(sIn);
            verificaErro(&funcs[i]);
            printf("> %s\n", evaluator_get_string(funcs[i]));
        }


    scanf("%f", &epsilon);
    printf("Lido epsilon(%f)\n", epsilon);
    scanf("%d", &MAXIT);
    printf("Lido MAXIT(%d)\n", MAXIT);

}

void criaSL() {
    int p = ceil(k / 2.0), q = floor(k / 2.0);
    diagonal = (double**) calloc((k+1), sizeof(double*));
    
    for(int i = 0; i < p; i++){
        diagonal[i] = (double*) calloc((n - p + i + 1), sizeof(double));
        for(int j = 0; j < (n - p + i + 1); j++){
            diagonal[i][j] = evaluator_evaluate_x(funcs[i], j);
            printf("%.0f ", diagonal[i][j]);
        }
        printf("\n");
    }
    
    printf("**\n");
    

    for(int i = 1; i <= q; i++){
        diagonal[p + i - 1] = (double*) calloc((n - i), sizeof(double));
        for(int j = 0; j < n - i; j++){
            diagonal[p + i - 1][j] = evaluator_evaluate_x(funcs[p + i - 1], j);
            printf("%.0f ", diagonal[p + i - 1][j]);
        }
        printf("\n");
    }
    
    printf("**\n");
    

    diagonal[k] = (double*) calloc(n, sizeof(double));
    for(int i = 0; i<n; i++){
        diagonal[k][i] = evaluator_evaluate_x(funcs[k], i);
        printf("%.0f ", diagonal[k][i]);
    }
    printf("\n");

}

void criaArrayResultado() {
    results = (double*) calloc(n, sizeof(double));
}

double somaDireita(int i, int di){
    if(di<=0 && i<(sizeof(diagonal[di])/sizeof(diagonal[di][0])))
        return diagonal[di][i] + somaDireita(i, di-1);
    
}

double somaEsquerda(int i, int di) {
    if(di<=k && i>=0)
        return diagonal[di][i] + somaEsquerda(i-1, di+1);
}

double somatorio(int i){
    return somaDireita(i, p) + somaEsquerda(i);
}

double calculaGauss() {
    int criterio1 = 1;

    double* dMaior = diagonal[p], dB = diagonal[k];

    do{
        for(int i = 0; i < n; i++){
            results[i] = (dB[i] - somatorio(i)) / dMaior[i];
        }
    } while(criterio1);       
}

/*
    k = 6; p=3; q=3
        __p___
        c b a                  g
       |1 0 0 0  0 0| |x0|   |1|
    q|d|0 4 0 1  0 0| |x1|   |2|
     |e|1 2 7 0  2 0|*|x2| = |4|
     |f|1 1 4 10 0 3| |x3|   |8|
       |0 1 1 6 13 0| |x4|   |16|
       |0 0 1 1 8 16| |x5|   |32|
       Testa commit
*/

void init() {}

void imprime_out() {}

double gauss() {}

void destroi_funcoes() {}