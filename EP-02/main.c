#include "functions.h"


int main(int argc, char **argv) {
/*

  if(argc < 5) {
    perror("Erro na entrada de dados.");
    exit(0);
  }

  if(argc - 4 < argv[1]) { // Transformar em int
    perror("Sistema impossível.");
    exit(0);
  }
*/
    inputs();
    criaSL();

    double tempo;
    tempo = timestamp();

    init();

    tempo = timestamp() - tempo;
    printf("tempo: %f", tempo);

    exit(1);
}
