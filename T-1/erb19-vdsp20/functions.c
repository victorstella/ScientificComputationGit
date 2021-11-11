#include "functions.h"

int MAXIT; // Número máximo de iterações respectivamente
float epsilon; // Epsilon fornecido na entrada
double *results; // Array de aproximações (X's)
double *resultsFuncs; // Array de resultados das Funcoes com os X's atuais
char **sFuncs; // Array de funções em forma de strings
void **funcs, ***jacobs; // Array de funções em forma de ponteiros para void e a matriz jacobiana seguindo a mesma estrutura com 1 dimensão a mais

// Verifica se evaluate foi criado corretamente
void verificaErro(void *funcao) {
    if(funcao == NULL){
        perror("Erro na entrada de dados.");
        exit(1);
    }
}

// Lê e trata as entradas
void inputs(){
    char *sIn = ""; // String para receber dinamicamente as funções de entrada
    char aux[124]; // String auxiliar

    size_t len = 0;


    scanf("%d\n", &n); // Lê número de funções

    // Aloca espaço para elas de acordo com a quantidade
    funcs = (void **) calloc(n, sizeof(void *));
    sFuncs = (char **) calloc(n, sizeof(char *));

    // Lê n funções de entrada e verifica se foram criadas
    for (int i = 0; i < n; i++) { 
        getline(&sIn, &len, stdin);
        sIn[strcspn (sIn, "\n")] = '\0';
        printf("Entrada: %s\n", sIn);
        funcs[i] = evaluator_create(sIn);
        verificaErro(funcs[i]);
    }

    // Aloca e lê n aproximações iniciais de cada X
    results = (double *) calloc(n, sizeof(double));
    
    for (int j = 0; j < n; j++) {
        scanf("%lf", &results[j]);
        printf("valor inicial: %lf\n", results[j]);
    }

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
}

// Cria matriz jacobiana
void criaJacobs() {

   char *currFunc, currX[3];  // Declara as strings que receberão dinamicamente a função e o X sendo tratados

    jacobs = (void ***) calloc(n, sizeof(void **)); // Aloca um array de arrays de ponteiros para void (matriz jacobiana)

    // Percorre cada função da entrada, alocando o espaço necessário na matriz
    for (int i = 0; i < n; i++) {
        jacobs[i] = (void **) calloc(n, sizeof(void *));
        
        // Trata a função n vezes, uma para cada possível X na função, após cada tratamento, calcula a derivada da função
        for (int j = 0; j < n; j++) {    
            currFunc = strdup(sFuncs[i]);
            printf("\nsFuncs(%d) -> %s\n", i, currFunc);
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
                        for (int l = 0; l < numSize; l++) {
                            currFunc[k + l + 1] = ' ';
                        }
                        
                    }

                }

            }

            printf(">f(%d) %s \n", i, currFunc);

            void *currFuncDx = evaluator_derivative_x(evaluator_create(currFunc));
            printf(">df(%d)/dx = %s = %f \n", i, evaluator_get_string(currFuncDx) ,evaluator_evaluate_x(currFuncDx, 4));

            // Insere a derivada obtida na matriz jacobiana
            jacobs[i][j] = currFuncDx;
            
        }
    
    }

    printf("\nMatriz Jacobiana vv:\n");
    for(int m = 0 ; m < n; m++) {
        for(int h = 0; h < n; h++) {
            printf("%s | ", evaluator_get_string(jacobs[m][h]));
        }
        printf("\n");
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



// Calcula uma nova aproximação
double calculaFunc(char *func) {

    int xyz[3] = {-1, -1, -1}, xyzPos = -1;

    char *currFunc = strdup(func);
    char aux[6];

    printf("\n-> currFunc() = %s", currFunc);
    
    for(int i = 1; i <= n && xyzPos <= 2; i++) {
        aux[0] = 'x';
        aux[1] = '\0';
        // Percorre a função atual, procurando uma ocorrência do caractere 'x' 
        for(int k = 0; k < strlen(currFunc); k++) {
            if(currFunc[k] == aux[0]) {
                int numSize = 0;
                if(strcmp(aux, "x") == 0){
                    // Encontrado um X, verifica se o valor a seguir é um número e descobre quantas casas decimais possui
                    while(isdigit(currFunc[k + numSize + 1])) {
                        aux[numSize] = currFunc[k + numSize + 1];
                        numSize++;
                        aux[numSize] = '\0';
                    }

                    if (numSize > 0){
                        xyzPos++;
                        xyz[xyzPos] = atoi(aux) - 1;
                    }
                }
                if (strncmp(&currFunc[k], aux, strlen(aux))) {
                    switch(xyzPos){
                        case 0:
                            currFunc[k] = 'x';
                            break;
                        case 1:
                            currFunc[k] = 'y';
                            break;
                        case 2:
                            currFunc[k] = 'z';
                            break;
                        default:
                            printf("Help!%i\n", xyzPos);
                            exit(1);
                            break;
                    }

                    for (int l = 0; l < numSize; l++) {
                        currFunc[k + l + 1] = ' ';
                    }
                }

            }
            
        }
    }
    printf("\nSaiu com f() = %s; xyzPos=%d, results{%d, %d, %d} = {%lf, %lf, %lf}\n", currFunc, xyzPos, xyz[0], xyz[1], xyz[2], results[0], results[1], results[2]);
    
    void* currF = evaluator_create(currFunc);

    double temp;
    switch(xyzPos){
        case -1:
            temp = atoi(evaluator_get_string(currF));
            break;
        case 0:
            temp = evaluator_evaluate_x(currF, results[xyz[0]]);
            break;
        case 1:
            temp = evaluator_evaluate_x_y(currF, results[xyz[0]], results[xyz[1]]);
            break;
        case 2:
            temp = evaluator_evaluate_x_y_z(currF, results[xyz[0]], results[xyz[1]], results[xyz[2]]);
            break;
        default:
            perror("Socorro! Ajudem-me");
            exit(1);
            break;
    }
    //printf("temp = %lf\n", temp);
    return temp;
}

double** criaSL() {
    double **sl = (double **) calloc(n, sizeof(double *));
    for (int a = 0; a < n; a++) {
        sl[a] = (double *) calloc(n, sizeof(double));
    }

    printf("\nSL!! vv\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            sl[i][j] = evaluator_evaluate_x(jacobs[i][j], results[j]);
            printf("-> sl[%d][%d] %lf |", i, j, sl[i][j]);
        }
        printf("\n");
    }

    return sl;
}

// Retorna o maior entre 2 valores
double maior(double a, double b){
    if(a > b) return a;
    else if(b > a) return b;
    else return a;
}

// Calcula as funções e retorna o maior valor dentre elas
double maiorFunc(){
    double max = 0; 
    for(int i = 0; i < n; i++){
        resultsFuncs[i] = calculaFunc(sFuncs[i]);
        printf("> ResultFunc[%d] = %lf\n", i, resultsFuncs[i]);
        max = maior(fabs(max), fabs(resultsFuncs[i]));
    }
    return max;
}

int newton(){
    resultsFuncs = (double *) calloc(n, sizeof(double));

    int iter, criterio1;

    iter = 0;

    double maior = 0;

    criaJacobs();

    maior = maiorFunc();

    double **sl = criaSL();

    calculaGauss(sl, resultsFuncs, results);

    if(maior < epsilon)
        return 1;

    while(criterio1){

        iter++;
        criterio1 = (iter < MAXIT);
    }
    return 1;
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