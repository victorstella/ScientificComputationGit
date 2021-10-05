#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include <matheval.h>

#include <assert.h> // Para função assert (debugagem)

#define ZERO 0

int main(int argc, char **argv) {
  void *f; // Função de entrada
  char *fx = NULL;
  double x0 = 1, epsilon = DBL_EPSILON;
  int max_iter = 1;

  //char *endptr;
  void *diffFx = NULL;

  size_t len = 0;
  ssize_t lnSize;
  int lnTam;

  double fxTrueZero = 0;
  void *aux = NULL;


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
    //exit(1);
  }

  fxTrueZero = evaluator_evaluate_x(f, ZERO);
  diffFx = evaluator_derivative_x(f);
  x0 = evaluator_evaluate_x(diffFx, ZERO);

  for(max_iter; abs(x0 - fxTrueZero) <= epsilon; max_iter++) {
    aux = diffFx;
    diffFx = evaluator_derivative_x(aux);
    x0 = evaluator_evaluate_x(diffFx, ZERO);
  }




  printf("f'(x) = %s\n", evaluator_get_string(diffFx));
  printf("f'(0) = %1.16e\n", x0);


  printf("ate aqui ok");
  evaluator_destroy (f);
  evaluator_destroy (diffFx);

  free(f);
  free(diffFx);
  free(fx);

  exit(1);
}