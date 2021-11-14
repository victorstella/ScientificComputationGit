#include "functions.h"
#include "newtonSNL.h"

int main(int argc, char **argv) {

    int validaInput = 1;

    // Laço principal do programa, onde em cada loop ocorre a solução de um dos SL
    do{
        validaInput = inputs();

        if(validaInput == 0) exit(1);

        newton();

        printf("###########\n");
        printf("# Tempo Total: %f\n", tempoTotal);
        printf("# Tempo Derivadas: %f\n", tempoCriaJacobs);
        printf("# Tempo Jacobiana: %f\n", tempoCalcJacobs);
        printf("# Tempo SL: %f\n", tempoSL);
        printf("###########\n\n");

        destroi_funcoes();

    } while(validaInput);

    exit(1);
}
