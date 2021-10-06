#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include <matheval.h>

#define ZERO 0

/*
Ler f(x)
Ler h0 ...nwt_x0
Ler epsilon
Ler max_iter


Calcula derivada de f(x)


// As primeiras duas iterações têm de ser diferentes pois a secante necessita de dois primeiros resultados para gerar os outros
Primeira iteração {
  Calcula nwt_x = phi() = h0-(f(h0)/f'(h0))
  Calcula sec_x = sec() = nwt_x-( (f(nwt_x)*(nwt_x*h0)) / (f(nwt_x)*f(h0)) )

  Calcula nwt_crit = | ((nwt_x - h0)*100)/nwt_x |
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

int nwt_crit(){

}

int calcula_tudao(){


}


int main(int argc, char **argv) {
  void *f, *diffFx; // Função de entrada e derivada
  char *fx;
  double x0, epsilon;
  int max_iter = 0;
  
  int condicao1, condicao2;

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