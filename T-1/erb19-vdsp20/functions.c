#include "functions.h"

int n, MAXIT; // Dimensão da matriz, número de diagonais e número máximo de iterações respectivamente
float epsilon; // Epsilon fornecido na entrada
double *results; // Array de resultados (X's)
void **funcs, **jacobs; // Array de ponteiros para funções
char **sFuncs; // Array de strings

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
    char aux[124]; // Auxiliar

    double *quotients; // Vetor de quocientes

    size_t len = 0;


    scanf("%d\n", &n); // Lê tamanho da matrix

    funcs = (void **) calloc(n, sizeof(void *));
    sFuncs = (char **) calloc(n, sizeof(char *));

    // Lê n funções de entrada
    for (int i = 0; i < n; i++) { 
        getline(&sIn, &len, stdin);
        sIn[strcspn (sIn, "\n")] = '\0';
        printf("Entrada: %s\n", sIn);
    }

    // Aloca e lê n quocientes
    quotients = (double *) calloc(n, sizeof(double));
    
    for (int j = 0; j < n - 1; j++) {
        scanf("%lf ", &quotients[j]);
        printf("quociente: %lf\n", quotients[j]);
    }

    scanf("%lf", &quotients[n]);
    printf("quociente: %lf\n", quotients[n]);

    // "Passa os quocientes para a esquerda"
    for (int k = 0; k < n; k++) {
        
        sprintf(aux, "%s-(%lf)\0", sIn, quotients[k]);

        sFuncs[k] = (char *) calloc(strlen(aux) , sizeof(char));
        strcpy(sFuncs[k], aux);

        funcs[k] = evaluator_create(aux);
        verificaErro(&funcs[k]);

        printf("f%d = %s\n", k, evaluator_get_string(funcs[k]));
    }
    // Lê critérios de parada
    scanf("%f\n", &epsilon);
    scanf("%d\n", &MAXIT);

    printf("\nDeu tudo certo!\n");
    free(sIn);
    free(quotients);
}

// Cria sistema não linear
void criaSNL() {
    
    for (int i = 0; i < n; i++) {
        char *currFunc = evaluator_get_string(funcs[i]);
        
        for (int j = 0; j < n; j++) {

        }
    
    }
    

}

// Aloca array de resultados
void criaArrayResultado() {
    results = (double *) calloc(n, sizeof(double));
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

/*
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

    free(vetorSolucao);   */
}

void printa_resultados() {
    printf("\n----\n\n");

    for(int i = 0; i < n; i++){
        printf("%f ", results[i]);
    }printf("\n");
}

// Desaloca ponteiros
void destroi_funcoes() {
    free(results);
    
    for(int i = 0; i < n + 1; i++)
        evaluator_destroy(funcs[i]);
    free(funcs);
}