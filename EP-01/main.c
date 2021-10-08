#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include <matheval.h>
#include "functions.h"

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


int main(int argc, char **argv) {

  init();

/* 
  // Só testando
  for(int i = 1; fabs(x0 - fxTrueZero) >= epsilon && i <= max_iter; i++) {
    diffFx = evaluator_derivative_x(diffFx);
    x0 = evaluator_evaluate_x(diffFx, ZERO);
    printf("%d, %1.16e, %1.16e\n", i, x0, fabs(x0 - fxTrueZero));
  }
*/

  exit(1);
}