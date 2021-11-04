#include "functions.h"

int main(int argc, char **argv) {
  if(argc < 5) {
    perror("Erro na entrada de dados.");
    exit(0);
  }

  if(argc - 4 < argv[1]) {
    perror("Sistema impossível.");
    exit(0);
  }

  double tempo;
  tempo = timestamp();

  init();

  tempo = timestamp() - tempo;
  printf("tempo: %d", tempo);

  exit(1);
}