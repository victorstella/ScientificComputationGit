#include "functions.h"
#include "newtonSNL.h"

int main(int argc, char **argv) {

    int vai = 1;

    do{
        
        vai = inputs();

        if(vai == 0) exit(1);

        // Calcula o tempo levado pelo algoritmo para executar os cálculos

        newton();
        

        printf("###########\n");
        printf("# Tempo Total: %f\n", tempoTotal);
        printf("# Tempo Derivadas: %f\n", tempoCriaJacobs);
        printf("# Tempo Jacobiana: %f\n", tempoCalcJacobs);
        printf("# Tempo SL: %f\n", tempoSL);
        printf("###########\n\n");


        destroi_funcoes();
    }while(vai);

    exit(1);
}
