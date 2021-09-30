#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <matheval.h>

void main(int argc, char **argv) {
  char *fx, *diffFx;
  double x0, epsilon;
  int max_iter;

  char *endptr;

  // Verify correct number of inputs
  if (argc != 4) {
    perror("Incorrect number of inputs, 4 expected!");
    exit(1);
  }

  // Fill the variables with the respective input information
  fx = (char *) calloc(strlen(argv[0]), sizeof(char));
  strcpy(fx, argv[0]);
  x0 = strtod(argv[1], &endptr);
  epsilon = strtod(argv[2], &endptr);
  max_iter = atoi(argv[3]);

  evaluator_derivative_x();
}