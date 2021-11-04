#include "functions.h"

void inputs(){
  int n, k, MAXIT;
  float epsilon;
  char *sIn; // Função de Entrada
  void** funcs; // Ponteiro para funções

  size_t len = 0;

  scanf("%d", &n);
  printf("Lido n(%d)\n", n);
  scanf("%d", &k);
  printf("Lido k(%d)\n", k);

  funcs = (void*)malloc(k*sizeof( void* ));


  getline(&sIn, &len, stdin);
  sIn[strcspn (sIn, "\n")] = '\0';

  for (int i = 0; i<n; i++){ 
    getline(&sIn, &len, stdin);
    sIn[strcspn (sIn, "\n")] = '\0';


    funcs[i] = evaluator_create(sIn);
    verificaErro(&funcs[i]);
    printf("> %s\n", evaluator_get_string(funcs[i]));
  }


  scanf("%f", &epsilon);
  printf("Lido epsilon(%f)\n", epsilon);
  scanf("%d", &MAXIT);
  printf("Lido MAXIT(%d)\n", MAXIT);

}

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


  double tempo;
  tempo = timestamp();

  init();

  tempo = timestamp() - tempo;
  printf("tempo: %f", tempo);

  exit(1);
}


/*
Lê entradas
Transforma 

*/