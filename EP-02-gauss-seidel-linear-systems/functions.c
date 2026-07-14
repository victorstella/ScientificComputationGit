#include "functions.h"

int n, k, MAXIT; // Dimensão da matriz, número de diagonais e número máximo de iterações respectivamente
float epsilon; // Epsilon fornecido na entrada
double *results; // Array de resultados (X's)
void **funcs; // Array de ponteiros para funções
double **diagonal; // Array de ponteiros para os valores das diagonais

int p, q;

// Verifica se evaluate foi criado corretamente
void verificaErro(void *funcao) {
    if(funcao == NULL){
        perror("Erro na entrada de dados.");
        exit(0);
    }
}

// Lê e trata os inputs
void inputs(){
    char *sIn = ""; // Função de Entrada

    size_t len = 0;

    scanf("%d", &n);
    scanf("%d", &k);

    funcs = (void **) calloc(k + 1, sizeof(void *));

    getline(&sIn, &len, stdin);
    sIn[strcspn (sIn, "\n")] = '\0';

        for (int i = 0; i < k + 1; i++){ 
            getline(&sIn, &len, stdin);
            sIn[strcspn (sIn, "\n")] = '\0';

            funcs[i] = evaluator_create(sIn);
            verificaErro(&funcs[i]);
        }

    scanf("%f", &epsilon);
    scanf("%d", &MAXIT);

    free(sIn);
}

// Cria sistema linear utilizando estrutura de diagonais
void criaSL() {
    p = ceil(k / 2.0), q = floor(k / 2.0);

    diagonal = (double **) calloc((k + 1), sizeof(double *));
    
    // Cria diagonais que começam na primeira linha pra matriz
    for(int i = 0; i < p; i++){
        diagonal[i] = (double *) calloc((n - p + i + 1), sizeof(double));
        for(int j = 0; j < (n - p + i + 1); j++){
            diagonal[i][j] = evaluator_evaluate_x(funcs[i], j);
            printf("%.0f ", diagonal[i][j]);
        }
        printf("\n");
    }

    // Cria diagonais que começam na primeira coluna pra matriz
    for(int i = 1; i <= q; i++){
        diagonal[p + i - 1] = (double *) calloc((n - i), sizeof(double));
        for(int j = 0; j < n - i; j++){
            diagonal[p + i - 1][j] = evaluator_evaluate_x(funcs[p + i - 1], j);
            printf("%.0f ", diagonal[p + i - 1][j]);
        }
        printf("\n");
    }    

    // Cria diagonal[k], vetor de valores de termos idependentes da matriz
    diagonal[k] = (double *) calloc(n, sizeof(double));
    for(int i = 0; i < n; i++){
        diagonal[k][i] = evaluator_evaluate_x(funcs[k], i);
        printf("%.0f ", diagonal[k][i]);
    }
    printf("\n");

}

// Aloca array de resultados
void criaArrayResultado() {
    results = (double *) calloc(n, sizeof(double));
}

// Calcula recursivamente o somatório dos elementos à direita do elemento atual
double somaDireita(int i, int di){
    if(di < 0) return 0;

    if(i > (n - p + di)) return 0;

    return diagonal[di][i]*results[i+p-1-di] + somaDireita(i, di-1);
}

// Calcula recursivamente o somatório dos elementos à esquerda do elemento atual
double somaEsquerda(int i, int di) {
    if(di >= k) return 0;

    if(i < 0 ) return 0;
    
    return diagonal[di][i] * results[i] + somaEsquerda(i - 1, di + 1);
}

// Calcula o somatório dos elementos na mesma linha do elemento atual
double somatorio(int i){
    double inter = somaDireita(i, p-2) + somaEsquerda(i - 1, p);
    return inter;
}

// Calcula erro relativo entre o valor atual do X e seu valor anterior
double calculaER(double new, double old){
    return fabs( (new - old) / new );
}

// Retorna o maior entre 2 valores
double maior(double a, double b){
    if(a > b) return a;
    else if(b > a) return b;
    else return a;
}

// Aplica o método de Gauss-Seidel repetidamente até os critérios de parada serem satisfeitos
double calculaGauss() {
    int iter = 0;
    int criterio1 = 0;
    double novoResult = 0, maiorER = 0, eAux = 0;

    double *dMaior = diagonal[p - 1], *vetorSolucao = diagonal[k];

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
}

void printa_resultados() {
    printf("\n----\n\n");

    for(int i = 0; i < n; i++){
        printf("%f ", results[i]);
    }printf("\n");
}

// Desaloca ponteiros
void destroi_funcoes() {
    for(int i = 0; i < k; i++)
        free(diagonal[i]);
    free(diagonal);
    free(results);
    
    for(int i = 0; i < k + 1; i++)
        evaluator_destroy(funcs[i]);
    free(funcs);
}