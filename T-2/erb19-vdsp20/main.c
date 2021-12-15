#include "functions.h"
#include "newtonSNL.h"
#include "sl_t.h"

int main(int argc, char **argv) {

    int valida_input = 1;

    sl_t * sl;

    // Laço principal do programa, onde em cada loop ocorre a solução de um dos SL
    do {

        sl = inputs();

        destroi_sl(sl);
        
    } while(sl != NULL);


    exit(1);
}
