#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <matheval.h>
#include <assert.h> // Para função assert (debugagem)

void main(int argc, char **argv) {
  void *f; // Função de entrada
  char *fx = NULL;
  double x0, epsilon;
  int max_iter;

  char *endptr;
  void *diffFx;

  size_t len = 0;
  ssize_t lnSize;
  int lnTam;

  // Verify correct number of inputs
  //if (argc != 4) {
  //  perror("Incorrect number of inputs, 4 expected!");
  //  exit(1);
  //}

  // Fill the variables with the respective input information
  //fx = (char *) calloc(strlen(argv[0]), sizeof(char)); // Utiliza entrada por arg ao invés de stdin
  //strcpy(fx, argv[0]);
  //x0 = strtod(argv[1], &endptr);
  //epsilon = strtod(argv[2], &endptr);
  //max_iter = atoi(argv[3]);

  lnTam = getline(&fx, &len, stdin);
  printf(">> %s, (%d)", fx, lnTam);
  f = evaluator_create(fx);
  assert(f);

  if(f == NULL){
    perror("Erro na expressão");
    exit(0);
  }else{
    printf("Deu boa\n");
    exit(1);
  }


  void *Fx = evaluator_create(fx);
  diffFx = evaluator_derivative_x(Fx);

  printf("f(4) = %s\n", evaluator_get_string(diffFx));

  evaluator_destroy (Fx);
  evaluator_destroy (diffFx);
  free(fx);

  exit(1);
}