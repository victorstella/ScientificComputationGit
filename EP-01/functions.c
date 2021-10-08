#include "functions.h"

void *funcF, *funcDF, *funcPHI, *funcSEC; // Funções globais

// Verifica se evaluate foi criado corretamente
void verificaErro(void* funcao) {
  if(funcao == NULL){
    perror("Erro na entrada de dados.");
    exit(0);
  }
}

void criaF(char* sF) {
  // Cria função F 
  funcF = evaluator_create(sF);
  verificaErro(funcF);
  printf("\n>> f(x) = %s\n", evaluator_get_string(funcF));
}

void derivaF() {
  // Deriva função F
  funcDF = evaluator_derivative_x(funcF);
  verificaErro(funcDF);

  printf(">> f'(x) = %s\n\n", evaluator_get_string(funcDF));
}

void criaPhi(char* sPHI) {
  // Cria função PHI
  sprintf(sPHI, "x-(%s/%s)", evaluator_get_string(funcF), evaluator_get_string(funcDF));
  funcPHI = evaluator_create(sPHI);
  verificaErro(funcPHI);

  printf(">> phi(x) = %s\n", evaluator_get_string(funcPHI));
}

void criaSec(char* sSEC) {
  // Cria função SEC
  char* funcF_new = strdup(evaluator_get_string(funcF)); 
    
  for (int k = 0; funcF_new[k] != '\0'; k++) {
    if (funcF_new[k] == 'x') funcF_new[k] = 'y';
  }

  sprintf(sSEC, "x-((%s*(x-y))/(%s-%s))", evaluator_get_string(funcF), evaluator_get_string(funcF), funcF_new );
  funcSEC = evaluator_create(sSEC);
  verificaErro(funcSEC);

  printf(">> sec(x) = %s\n", evaluator_get_string(funcSEC));

  free(funcF_new);
}

double calcula_ea(double new, double old) {
    return fabs(new - old);
}

double calcula_er(double new, double old) {
    return fabs( (new - old) / new );
}

long int calcula_ulp(double da, double db) {
  long int ia, ib, ulp;

  memcpy(&ia, &da, sizeof(da));
  memcpy(&ib, &db, sizeof(db));

  ulp = labs(labs(ia) - labs(ib));

  return ulp;
}

void imprime_csv(
  int i,
  double nwt_x1,
  double nwt_crit,
  double sec_x1,
  double sec_crit,
  double ea_nwt_sec,
  double er_nwt_sec,
  long int ULP
){
  printf(
    "%d, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %1.16e, %ld\n",
    i, nwt_x1, nwt_crit, sec_x1, sec_crit, ea_nwt_sec, er_nwt_sec, ULP
  );
}

void init() {
  void *f, *diffFx; // Função de entrada e derivada
  char *sF, sPHI[128], sSEC[128]; // String da função f, phi, sec
  double
    x0,
    epsilon,
    newton,
    oldton,
    newton_crit = 1,
    new_secante = 1,
    old_secante = 0,
    aux_secante = 0,
    secante_crit = 1,
    er_nwt_sec = 0,
    ea_nwt_sec = 0;
  
  long int ulp = 0;

  int max_iter, iter = 0, criterio_1 = 1, criterio_2 = 1, criterio_3 = 1, criterio_4 = 1;

  size_t len = 0;

  // Recebe f e remove \n
  getline(&sF, &len, stdin);
  sF[strcspn (sF, "\n")] = '\0';

  // Recebe outras variáveis 
  scanf("%lf", &x0);
  scanf("%lf", &epsilon);
  scanf("%d", &max_iter);

  printf("sF  -> %s\n", sF);
  printf("x0  -> %1.16e\n", x0);
  printf("eps -> %le\n", epsilon);
  printf("maxi-> %d\n", max_iter);

  criaF(sF);
  derivaF();
  criaPhi(sPHI);
  criaSec(sSEC);

  // Iteração zero
  imprime_csv(iter, x0, newton_crit, new_secante, secante_crit, ea_nwt_sec, er_nwt_sec, ulp);

  // Primeira iteração
  iter ++;
  newton = phi(x0);
  newton_crit = calcula_er(newton, x0);
  new_secante = sec(newton, x0);
  secante_crit = calcula_er(new_secante, newton);

  imprime_csv(iter, newton, newton_crit, new_secante, secante_crit, ea_nwt_sec, er_nwt_sec, ulp);
  
  // Segunda iteração
  iter++;
  oldton = newton;
  newton = phi(oldton);
  newton_crit = calcula_er(newton, oldton);

  old_secante = new_secante;
  new_secante = sec(old_secante, newton);
  secante_crit = calcula_er(new_secante, old_secante);
  
  ea_nwt_sec = calcula_ea(newton, new_secante);
  er_nwt_sec = calcula_er(newton, new_secante);

  ulp = calcula_ulp(newton, new_secante);

  imprime_csv(iter, newton, newton_crit, new_secante, secante_crit, ea_nwt_sec, er_nwt_sec, ulp);

  // Terceira iteração ...
  while (criterio_1 && criterio_2 && criterio_3 && criterio_4) {
    iter++;
    oldton = newton;
    newton = phi(oldton);
    newton_crit = calcula_er(newton, oldton);
    
    aux_secante = new_secante;
    new_secante = sec(new_secante, old_secante);
    old_secante = aux_secante;
    secante_crit = calcula_er(new_secante, old_secante);
    
    ea_nwt_sec = calcula_ea(newton, new_secante);
    er_nwt_sec = calcula_er(newton, new_secante);
    
    ulp = calcula_ulp(newton, new_secante);

    imprime_csv(iter, newton, newton_crit, new_secante, secante_crit, ea_nwt_sec, er_nwt_sec, ulp);

    criterio_1 = (iter <= max_iter);
    criterio_2 = (newton_crit >= epsilon);
    criterio_3 = (secante_crit >= epsilon);
    criterio_4 = (ulp > 1);
  }

  free(sF);
}


// Funções matemáticas ---
double f(double x) {
  return evaluator_evaluate_x(funcF, x);
}

double phi(double x) {
  return evaluator_evaluate_x(funcPHI, x);
}

double sec(double x, double y) {
  return evaluator_evaluate_x_y(funcSEC, x, y);
}


void destroi_funcoes() {
  evaluator_destroy(funcF);
  evaluator_destroy(funcDF);
  evaluator_destroy(funcPHI);
  evaluator_destroy(funcSEC);
}