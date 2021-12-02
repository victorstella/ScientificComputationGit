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
double styblinskiTang(double a, double b, int namostras)
{
  double resultado = 1;
  double soma = 0.0;
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = 2\n", a, b, namostras);

  double t_inicial = timestamp();

  int interval = b - a, randX = 0;
  double cte = 1 / (namostras * 2);
  
  for (int g = 0; g < 2; g++) {
    for (int i = 0; i < namostras; i++) {
      randX = (int) a + (int) NRAND * interval;
      soma += (randX ^ 4) - 16 * (randX ^ 2) + 5 * randX;
    }

    resultado += (double) interval * cte * soma;
  }

  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


double retangulos_xy(double a, double b, int npontos) {

  double h;
  double resultado;
  double soma = 0;
  
  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%f)\n", a, b, npontos, h);
  
  double t_inicial = timestamp();
  
  h = (b - a) / npontos;
  double xi = 0;

  for (int l = 0; l < 2; l++) {
    xi = a;
    soma = 0;
    for (int k = 0; k < npontos; k++) {
      soma += (((int) xi ^ 4) - 16 * ((int) xi ^ 2) + 5 * xi);
      xi += h;
    }
    resultado += soma / 2;
    printf("soma: %f, resultado: %f, xi: %f\n", soma, resultado, xi);
  }
  
  // xi ok
  // h ok

  printf("***h*h: %1.16d\n", (int) h ^ 2);

  resultado *= (int) h ^ 2;
  
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

  printf("Resultado pelo método de Monte Carlo: %f\n", monteCarlo);
  printf("Resultado pelo método dos Retângulos: %f\n", retangulos);

  return 0;
}

