#include "functions.h"

int main(int argc, char **argv) {

    inputs();

    newton();

    /* criaArrayResultado();

    // Calcula o tempo levado pelo algoritmo para executar os cálculos
    double tempo;
    tempo = timestamp();

    calculaGauss();

    // Para a contagem de tempo de execução dos cálculos
    tempo = timestamp() - tempo;
    
    // Printa os resultados e o tempo gasto
    printa_resultados();
    printf("tempo: %.8f\n", tempo);

    destroi_funcoes(); */

    exit(1);
}
