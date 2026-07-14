#include "functions.h"

// Lê e trata as entradas
int inputs(sl_t **sl) {
    char *sIn = ""; // String para receber dinamicamente as funções de entrada
    char aux[124]; // String auxiliar
    int n, maxit;
    float epsilon;

    size_t len = 0;

    if (scanf("%d\n", &n) == EOF) { // Lê número de funções
        *sl = NULL;
        return 0;
    }

    void **funcs = calloc(n, sizeof(void *));
    double *aprox_iniciais = calloc(n, sizeof(double));

    if (!aprox_iniciais || !funcs) {
        perror("Erro de alocação de memória.");
        exit(1);
    }

    // Lê n funções de entrada e verifica se foram criadas
    for (int i = 0; i < n; i++) { 
        getline(&sIn, &len, stdin);
        sIn[strcspn (sIn, "\n")] = '\0';
        funcs[i] = evaluator_create(sIn);
    }


    // Lê n aproximações iniciais de cada X
    for (int j = 0; j < n; j++)
        scanf("%lf", &aprox_iniciais[j]);


    // Lê critérios de parada
    scanf("%f\n", &epsilon);
    scanf("%d\n", &maxit);
    
    *sl = inicia_sl_t(n, funcs, aprox_iniciais, epsilon, maxit);

    // Desaloca espaço que não é mais utilizado
    free(sIn);

    free(aprox_iniciais);

    return 1;
}
