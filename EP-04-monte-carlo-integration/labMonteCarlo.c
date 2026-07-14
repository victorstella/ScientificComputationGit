#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define DIFF 0.0
#define POINTS_NUMBER 10000000

#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)

// Integral Monte Carlo da função Styblinski-Tang de 2, 4 e 8 variáveis
double *styblinskiTang(double a, double b, int namostras) {
  double *resultado = (double *) calloc(3, sizeof(double));
  
  for (int e = 0; e < 3; e ++) { // Calcula a integral por Monte Carlo para 2, 4 e 8 dimensões
    resultado[e] = 1;
    double soma = 0.0;
    int dimensao = 1 << (e + 1);
  
    if (e == 0) printf("\nMetodo de Monte Carlo (x, y).\n");
    else if (e == 1) printf("\nMetodo de Monte Carlo (w, x, y, z).\n");
    else printf("\nMetodo de Monte Carlo (s, t, u, v, w, x, y, z).\n");

    printf("a = (%f), b = (%f), n = (%d), variaveis = %d\n", a, b, namostras, dimensao);

    double interval = b - a, randX = 0, soma_aux = 0, soma_total = 0, x_square = 0;

    double t_inicial = timestamp();

    for (int i = 0; i < namostras; i++) {
      randX = NRAND * interval + a;
      
      x_square = randX * randX;
      soma_aux = (x_square * x_square) - (16 * x_square) + (5 * randX);
      
      soma_total = soma + soma_aux;
      soma = soma_total;
    }

    resultado[e] = pow(interval, dimensao) * ((dimensao / 2) * soma_total / namostras);
  
    double t_final = timestamp();
    printf("Tempo decorrido: %f seg.\n\n", t_final - t_inicial);
  }
  
  return resultado;
}


double retangulos_xy(double a, double b, int npontos) {

  double h = (b - a) / npontos;
  double resultado;
  double soma = 0;
  
  printf("\nMetodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%1.8f)\n", a, b, npontos, h);
  
  double soma_aux = 0, soma_total = 0, dx = a, dxAux = 0, dx_square = 0;

  double t_inicial = timestamp();
  
  for (int j = 0; j < npontos; j++) {
    dx_square = dx * dx;

    soma_aux = (dx_square * dx_square) - (16 * dx_square) + (5 * dx);

    soma_total = soma + soma_aux;
    soma = soma_total;

    dxAux = dx;
    dx = dxAux + h;
  }

  resultado = (h * h) * npontos * soma;  
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n\n", t_final - t_inicial);
  
  return resultado;
}


int main(int argc, char **argv) {

  if (argc < 3 || argc > 3) {
    printf("\nUtilização: %s inicial final\n", argv[0]);
    return 1;
  }

  double a = atof(argv[1]), b = atof(argv[2]);

  SRAND(20211);

  double *monteCarlo = styblinskiTang(a, b, POINTS_NUMBER);
  double retangulos = retangulos_xy(a, b, POINTS_NUMBER); // 24994

  printf("Resultado pelo método de Monte Carlo (2 variáveis): %1.16f\n", monteCarlo[0]);
  printf("Resultado pelo método de Monte Carlo (4 variáveis): %1.16f\n", monteCarlo[1]);
  printf("Resultado pelo método de Monte Carlo (8 variáveis): %1.16f\n\n", monteCarlo[2]);

  printf("Resultado pelo método dos Retângulos: %1.16f\n\n", retangulos);

  free(monteCarlo);
  return 0;
}

