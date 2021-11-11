#include "functions.h"

int n, MAXIT; // Número de funções e número máximo de iterações respectivamente
float epsilon; // Epsilon fornecido na entrada
double *results; // Array de aproximações (X's)
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
    
    for (int j = 0; j < n - 1; j++) {
        scanf("%lf ", &results[j]);
        printf("valor inicial: %lf\n", results[j]);
    }

    scanf("%lf", &results[n]);
    printf("valor inicial: %lf\n", results[n]);

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

// Retorna o maior entre 2 valores
double maior(double a, double b){
    if(a > b) return a;
    else if(b > a) return b;
    else return a;
}

double calculaFunc(int funcPos) {

    int xyz[3] = {-1, -1, -1}, xyzPos = -1;

    char *currFunc = strdup(sFuncs[funcPos]);
    char aux[6];
    
    printf("Trocando para -> %s\n", currFunc);


    for(int i = 0; i < n || xyzPos <= 2; i++) {
        aux[0] = 'x';
        // Percorre a função atual, procurando uma ocorrência do caractere 'x' 
        for(int k = 0; k < strlen(currFunc); k++) {
            if(currFunc[k] == aux[0]) {
                int numSize = 0;
                if(strcmp(aux, "x") == 0){
                    // Encontrado um X, verifica se o valor a seguir é um número e descobre quantas casas decimais possui
                    while(isdigit(currFunc[k + numSize + 1])) {
                        aux[numSize] = currFunc[k + numSize + 1];
                        numSize++;
                    }
                    aux[numSize] = '\0';

                    if (numSize > 0){
                        xyzPos++;
                        xyz[xyzPos] = atoi(aux);
                    }
                }else if (strncmp(&currFunc[k], aux, strlen(aux))) {
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
                            perror("Help!");
                            exit(1);
                            break;
                    }

                    for (int l = 0; l < numSize; l++) {
                        currFunc[k + l + 1] = ' ';
                    }
                }

            }
            
        }
        printf("\ntrocaVars -> %s\n", currFunc);
    }
    switch(xyzPos){
        case 0:            
            return evaluator_evaluate_x(currFunc, results[xyz[0]]);
            break;
        case 1:
            return evaluator_evaluate_x_y(currFunc, results[xyz[0]], results[xyz[1]]);
            break;
        case 2:
            return evaluator_evaluate_x_y_z(currFunc, results[xyz[0]], results[xyz[1]], results[xyz[2]]);
            break;
        default:
            perror("Socorro!");
            exit(1);
            break;
    }
}

double maiorFunc(){
    double max = 0; 
    for(int i = 0; i < n; i++){
        max = maior(max, calculaFunc(i));
    }
    return max;
}

int newton(){
    int iter, criterio1;

    iter = 0;

    criaJacobs();

    maiorFunc();
    
    while(criterio1){

        iter++;
        criterio1 = (iter < MAXIT);
    }
    return 1;
}

// Aplica o método de Gauss repetidamente até os critérios de parada serem satisfeitos
double calculaGauss() {
    //int iter = 0;
    //int criterio1 = 0;
    //double novoResult = 0, maiorER = 0, eAux = 0;

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