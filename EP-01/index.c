#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include <matheval.h>

#define ZERO 0

/*
Ler f(x)
Ler x0
Ler epsilon
Ler max_iter


Calcula derivada de f(x)


// As primeiras duas iterações têm de ser diferentes pois a secante necessita de dois primeiros resultados para gerar os outros
Primeira iteração {
  Calcula nwt_x = phi() = x0-(f(x0)/f'(x0))
  Calcula sec_x = sec() = nwt_x-( (f(nwt_x)*(nwt_x*x0)) / (f(nwt_x)*f(x0)) )

  Calcula nwt_crit = | ((nwt_x - x0)*100)/nwt_x |
  Calcula sec_crit = | ((sec_x - nwt_x)*100)/sec_x |

  Calcula EA = |sec_x-nwt_x|
  Calcula ER = |EA/nwt_x|

  Calcula ULPs = (?)
}

nwt_x_old = nwt_x

sec_x_old = sec_x
sec_x_old_old = nwt_x

Segunda iteração {
  Calcula nwt_x = phi() = nwt_x_old-(f(nwt_x_old)/f'(nwt_x_old))
  Calcula sec_x = sec() = sec_x_old-( (f(sec_x_old)*(sec_x_old*sec_x_old_old)) / (f(nwt_x)*f(sec_x_old_old)) )

  Calcula nwt_crit = | ((nwt_x - nwt_x_old)*100)/nwt_x |
  Calcula sec_crit = | ((sec_x - sec_x_old)*100)/sec_x |

  Calcula EA = |sec_x-nwt_x|
  Calcula ER = |EA/nwt_x|

  Calcula ULPs = (?)
}


Outras iterações {
  nwt_x_old = nwt_x

  sec_x_old_old = sec_x_old
  sec_x_old = sec_x


  Calcula nwt_x = phi() = nwt_x_old-(f(nwt_x_old)/f'(nwt_x_old))
  Calcula sec_x = sec() = sec_x_old-( (f(sec_x_old)*(sec_x_old*sec_x_old_old)) / (f(nwt_x)*f(sec_x_old_old)) )

  Calcula nwt_crit = | ((nwt_x - nwt_x_old)*100)/nwt_x |
  Calcula sec_crit = | ((sec_x - sec_x_old)*100)/sec_x |

  Calcula EA = |sec_x-nwt_x|
  Calcula ER = |EA/nwt_x|

  Calcula ULPs = (?)
} Até (crits < epsilon OU max_iter )

*/

void *funcF, *funcPHI, *funcDPHI;


void init(){
  void *f, *diffFx; // Função de entrada e derivada
  char *sF;

  size_t len = 0;
  double fxTrueZero = 0;

  double x0, epsilon;
  int max_iter = 0;
  

  // Recebe f e remove \n
  getline(&sF, &len, stdin);
  sF[strcspn (sF, "\n")] = '\0';

  // Recebe outras variáveis 
  scanf("%lf", &x0);
  scanf("%lf", &epsilon);
  scanf("%d", &max_iter);

  printf("%s\n", sF);
  printf("%le\n", x0);
  printf("%le\n", epsilon);
  printf("%d\n", max_iter);

  funcF = evaluator_create(sF);
  
  if(funcF == NULL){
    perror("Erro na entrada de dados.");
    exit(0);
  }


  // Calcula derivada de f 
  funcDPHI = evaluator_derivative_x(funcF);
  printf("\n>> f'(x) = %s\n\n", evaluator_get_string(funcDPHI));

  printf("0, %1.16e, %1.16e\n", x0, x0);


  free(sF);


/* 
  // Só testando
  for(int i = 1; fabs(x0 - fxTrueZero) >= epsilon && i <= max_iter; i++) {
    diffFx = evaluator_derivative_x(diffFx);
    x0 = evaluator_evaluate_x(diffFx, ZERO);
    printf("%d, %1.16e, %1.16e\n", i, x0, fabs(x0 - fxTrueZero));
  }
*/

}

// Funções matemáticas
double f(double x){
  return evaluator_evaluate_x(funcF, x);
}

double phi(double x){
  return evaluator_evaluate_x(funcPHI, x);
}

double dphi(double x){
  return evaluator_evaluate_x(funcDPHI, x);
}

int nwt_crit(double nwt_old){


  return 1;
}

int calcula_tudao(){

  return 1;
}

void destroi_funcoes(){
  evaluator_destroy(funcF);
  evaluator_destroy(funcPHI);
  evaluator_destroy(funcDPHI);
}

int main(int argc, char **argv) {


  init();

  exit(1);
}