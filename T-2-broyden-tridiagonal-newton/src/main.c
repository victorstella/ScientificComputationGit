#include "functions.h"
#include "newtonSNL.h"
#include "sl_t.h"
#include "likwid.h"

int main(int argc, char **argv) {

    LIKWID_MARKER_INIT;

    int valida_input = 1;

    sl_t *sl;

    int end = 1;

    // Laço principal do programa, onde em cada loop ocorre a solução de um dos SL
    do {

        end = inputs(&sl);

        newton(sl);

        destroi_sl(sl);
        
    } while(end);


    exit(1);
}