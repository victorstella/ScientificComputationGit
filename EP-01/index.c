#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include <matheval.h>
#include <assert.h> // Para função assert (debugagem)

#define ZERO 0

int main(int argc, char **argv) {
  void *f, *diffFx; // Função de entrada e derivada
  char *fx;
  double x0;
  int max_iter = 0;
  
  size_t len = 0;
  ssize_t lnSize;
  int lnTam;

  double fxTrueZero = 0;

  lnTam = getline(&fx, &len, stdin);
  printf(">> f(x) = %s, (%d)\n", fx, lnTam);
  f = evaluator_create(fx);
  assert(f);
  
  if(f == NULL){
    perror("Erro na expressão");
    exit(0);
  }

  fxTrueZero = evaluator_evaluate_x(f, ZERO);
  diffFx = evaluator_derivative_x(f);
  printf(">> f'(x) = %s\n", evaluator_get_string(diffFx));

  x0 = evaluator_evaluate_x(diffFx, ZERO);
  printf("%d, %1.16e, %1.16e\n", max_iter, x0, fabs(x0 - fxTrueZero));

  for(max_iter = 1; fabs(x0 - fxTrueZero) <= __DBL_EPSILON__; max_iter++) {
    diffFx = evaluator_derivative_x(diffFx);
    x0 = evaluator_evaluate_x(diffFx, ZERO);
    printf("%d, %1.16e, %1.16e\n", max_iter, x0, fabs(x0 - fxTrueZero));
  }

  evaluator_destroy(f);
  evaluator_destroy(diffFx);

  free(fx);

  exit(1);
}