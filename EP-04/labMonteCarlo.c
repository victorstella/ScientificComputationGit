#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
// #include "randomNR.h"

#define DIFF 0.0
// #define POINTS_NUMBER 10000000

#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)

// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double styblinskiTang(double a, double b, int namostras) {
  double resultado = 1;
  double soma = 0.0;
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = 2\n", a, b, namostras);

  double interval = b - a, randX = 0;

  double t_inicial = timestamp();

  for (int i = 0; i < namostras; i++) {
    for (int j = 0; j < 2; j++) {
      randX = a + NRAND * interval;
      soma += fabs(pow(randX, 4) - (16 * pow(randX, 2)) + (5 * randX));
    }
    soma /= 2;
  }

  /* for (int j = 0; j < namostras; j++) {
    randX = a + NRAND * interval;
    soma_j += (pow(randX, 4) - (16 * pow(randX, 2)) + (5 * randX)) / 2;
  } */

  resultado = interval * (soma / namostras);
  
  printf("\n\n***soma: %1.16f, resultado: %1.16f, dx: %1.16f\n\n", soma, resultado, randX);

  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


double retangulos_xy(double a, double b, int npontos) {

  double h;
  double resultado;
  double soma_i = 0, soma_j = 0;
  
  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%f)\n", a, b, npontos, h);
  
  double dx_i = a, dx_j = a, soma_abs = 0;

  double t_inicial = timestamp();
  
  h = (b - a) / npontos;

  double somaAux = 0;
  double dxAux = 0;
  printf("começou1");
  for (int i = 0; i < npontos; i++) {
    for (int c = 0; c < 2; c++) {
      somaAux += pow(dx_i, 4) - (16 * pow(dx_i, 2)) + (5 * dx_i);
    }
    soma_i = somaAux / 2;
    dxAux = dx_i;
    dx_i = dxAux + h;
  }

  somaAux = 0;
  printf("começou2");
  for (int j = 0; j < npontos; j++) {
    for (int c = 0; c < 2; c++) {
      somaAux += pow(dx_j, 4) - (16 * pow(dx_j, 2)) + (5 * dx_j);
    }
    soma_j = somaAux / 2;
    dxAux = dx_j;
    dx_j = dxAux + h;
  }

  // xi ok
  // h ok
  
  resultado = soma_i * soma_j * pow(h, 2);

  printf("\n\n***soma_i: %1.16f, soma_j: %1.16f resultado: %1.16f, dx_i: %1.16f, dx_j: %1.16f\n\n", soma_i, soma_j, resultado, dx_i, dx_j);
  
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


int main(int argc, char **argv) {

  if (argc < 5) {
    printf("Utilização: %s inicial final n_amostras n_variaveis\n", argv[0]);
    return 1;
  }

  double a = atof(argv[1]), b = atof(argv[2]);
  int nAmostras = atoi(argv[3]), nVars = atoi(argv[4]);

  SRAND(20211);

  double monteCarlo = styblinskiTang(a, b, nAmostras);
  double retangulos = retangulos_xy(a, b, nAmostras);

  printf("Resultado pelo método de Monte Carlo: %1.16f\n", monteCarlo);
  printf("Resultado pelo método dos Retângulos: %1.16f\n", retangulos);

  return 0;
}

