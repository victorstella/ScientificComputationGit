#include "functions.h"

void *funcG;

// Verifica se evaluate foi criado corretamente
void verificaErro(void* funcao) {
  if(funcao == NULL){
    perror("Erro na entrada de dados.");
    exit(0);
  }
}

void criaGauss() {}

double calculaGauss() {}

void init() {}

void imprime_out() {}

double gauss() {}

void destroi_funcoes() {}