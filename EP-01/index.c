#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <matheval.h>

void main(int argc, char **argv) {
  char *fx;
  double x0, epsilon;
  int max_iter;

  char *endptr;
  void *diffFx;

  // Verify correct number of inputs
  //if (argc != 4) {
  //  perror("Incorrect number of inputs, 4 expected!");
  //  exit(1);
  //}

  // Fill the variables with the respective input information
  fx = (char *) calloc(strlen(argv[0]), sizeof(char));
  strcpy(fx, argv[0]);
  //x0 = strtod(argv[1], &endptr);
  //epsilon = strtod(argv[2], &endptr);
  //max_iter = atoi(argv[3]);

  void *Fx = evaluator_create(fx);
  diffFx = evaluator_derivative_x(Fx);

  printf("f(4) = %s\n", evaluator_get_string(diffFx));

  evaluator_destroy (Fx);
  evaluator_destroy (diffFx);
  free(fx);


  exit(1);
}