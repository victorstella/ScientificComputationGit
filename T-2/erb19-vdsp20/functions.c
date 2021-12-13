#include "functions.h"

void **funcs; // Array de funções em forma de ponteiros para void e a matriz jacobiana seguindo a mesma estrutura com 1 dimensão a mais

// Lê e trata as entradas
int inputs (){
    char *sIn = ""; // String para receber dinamicamente as funções de entrada
    char aux[124]; // String auxiliar

    size_t len = 0;

    if (scanf("%d\n", &n) == EOF) // Lê número de funções
        return 0;

    // Aloca espaço para variáveis necessárias
    funcs = (void **) calloc(n, sizeof(void *));
    sFuncs = (char **) calloc(n, sizeof(char *));
    results = (double *) calloc(n, sizeof(double));

    if (!funcs || !results || !sFuncs) {
        perror("Erro de alocação de memória.");
        exit(1);
    }

    // Lê n funções de entrada e verifica se foram criadas
    for (int i = 0; i < n; i++) { 
        getline(&sIn, &len, stdin);
        sIn[strcspn (sIn, "\n")] = '\0';
        funcs[i] = evaluator_create(sIn);
        
        if (funcs[i] == NULL) {
            perror("Erro na entrada de dados.");
            exit(1);
        }
    }

    // Lê n aproximações iniciais de cada X
    for (int j = 0; j < n; j++)
        scanf("%lf", &results[j]);

    // Aloca a memória necessária para cada string do array
    for (int k = 0; k < n; k++) {
        sprintf(aux, "%s", evaluator_get_string(funcs[k]));
        sFuncs[k] = (char *) calloc(strlen(aux) , sizeof(char));
        strcpy(sFuncs[k], aux);
    }

    // Lê critérios de parada
    scanf("%f\n", &epsilon);
    scanf("%d\n", &MAXIT);

    // Desaloca espaço que não é mais utilizado
    free(sIn);

    return 1;
}

// Cria matriz jacobiana
void criaJacobs() {

   char *currFunc, currX[3];  // Declara as strings que receberão dinamicamente a função e o X sendo tratados

    jacobs = (void ***) calloc(n, sizeof(void **)); // Aloca um array de arrays de ponteiros para void (matriz jacobiana)

    if(!jacobs) {
        perror("Erro de alocação de memória.");
        exit(1);
    }

    // Percorre cada função da entrada, alocando o espaço necessário na matriz
    for (int i = 0; i < n; i++) {
        jacobs[i] = (void **) calloc(n, sizeof(void *));
        
        // Trata a função n vezes, uma para cada possível X na função, após cada tratamento, calcula a derivada da função
        for (int j = 0; j < n; j++) {    
            currFunc = strdup(sFuncs[i]);
            sprintf(currX, "x%d", j + 1);
            
            // Percorre a função atual, procurando uma ocorrência do caractere 'x' 
            for(int k = 0; k < strlen(currFunc); k++) {
                if(currFunc[k] == 'x') {
                    int numSize = 0;

                    // Encontrado um X, verifica se o valor a seguir é um número e descobre quantas casas decimais possui
                    while(isdigit(currFunc[k + numSize + 1]))
                        numSize++;
                    
                    // Verifica se o X encontrado de fato corresponde ao X de interesse (ex.: x1, x2, etc)
                    if (strncmp(&currFunc[k], currX, numSize + 1) == 0) {
                        
                        // Caso seja, substitui cada valor numérico imediatamente após este X por espaços em branco (ex.: 'x2' se torna 'x ')
                        for (int l = 0; l < numSize; l++)
                            currFunc[k + l + 1] = ' ';
                    }

                }

            }

            // Calcula a derivada parcial e insere a função obtida na matriz jacobiana
            void *currFuncDx = evaluator_derivative_x(evaluator_create(currFunc));
            jacobs[i][j] = currFuncDx;
        }
    
    }
}

// Retorna o maior entre 2 valores
double maior(double x, double y) {
    double a, b;
    a = fabs(x);
    b = fabs(y);

    if(a > b) return a;
    else if(b > a) return b;
    else return a;
}

// Desaloca ponteiros
void destroi_funcoes() {
    free(results);
    
    for(int i = 0; i < n; i++){
        evaluator_destroy(funcs[i]);
        
        for(int j = 0; j < n; j++){
            evaluator_destroy(jacobs[i][j]);
        }
    }
    free(funcs);
    free(sFuncs);
    free(jacobs);
}