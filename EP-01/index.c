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
  double x0, epsilon;
  int max_iter = 0;
  
  size_t len = 0;

  double fxTrueZero = 0;

  getline(&fx, &len, stdin);
  fx[strcspn (fx, "\n")] = '\0';
  scanf("%lf", &x0);
  scanf("%lf", &epsilon);
  scanf("%d", &max_iter);

  printf("%s\n", fx);
  printf("%le\n", x0);
  printf("%le\n", epsilon);
  printf("%d\n", max_iter);
  f = evaluator_create(fx);
  assert(f);
  
  if(f == NULL){
    perror("Erro na entrada de dados.");
    exit(0);
  }

  fxTrueZero = evaluator_evaluate_x(f, ZERO);
  diffFx = evaluator_derivative_x(f);
  printf("\n>> f'(x) = %s\n\n", evaluator_get_string(diffFx));

  printf("0, %1.16e, %1.16e\n", x0, x0);

  for(int i = 1; fabs(x0 - fxTrueZero) >= epsilon && i <= max_iter; i++) {
    diffFx = evaluator_derivative_x(diffFx);
    x0 = evaluator_evaluate_x(diffFx, ZERO);
    printf("%d, %1.16e, %1.16e\n", i, x0, fabs(x0 - fxTrueZero));
  }

  evaluator_destroy(f);
  evaluator_destroy(diffFx);

  free(fx);

  exit(1);
}