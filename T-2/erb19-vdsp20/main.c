#include "functions.h"
#include "newtonSNL.h"
#include "sl_t.h"

int main(int argc, char **argv) {

    int valida_input = 1;

    sl_t *sl;

    // Laço principal do programa, onde em cada loop ocorre a solução de um dos SL
    do {

        sl = inputs();

        newton(sl);

        destroi_sl(sl);
        
    } while(sl != NULL);


    printf("\n-- Acabou o programa :)--\n");
    exit(1);
}