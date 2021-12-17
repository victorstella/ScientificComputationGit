#include "functions.h"
#include "newtonSNL.h"
#include "sl_t.h"

int main(int argc, char **argv) {

    int valida_input = 1;

    sl_t *sl;

    int end = 1;
    /* int end[] = calloc(1, sizeof(int));
    end[0] = 1;
 */
    // Laço principal do programa, onde em cada loop ocorre a solução de um dos SL
    do {

        end = inputs(&sl);

        newton(sl);

        destroi_sl(sl);
        
    } while(end);


    printf("\n-- Acabou o programa :)--\n");
    exit(1);
}