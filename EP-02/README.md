# SOLUÇÃO DE SISTEMAS LINEARES
*MÉTODO DE GAUSS-SEIDEL*

## ALUNOS

Eduardo Rosso Barbosa - GRR20190378 - ERB19

Victor Daniel Stella Paiva - GRR20200234 - VDSP20

## CRITÉRIOS DE PARADA

Os critérios de parada utilizados para esta implementação foram:

* **Critério 1:** `gauss < epsilon` 
A partir das informações de entrada, o 'gauss' é calculado e estabelecemos então que este valor não poderia ser maior e nem igual ao epsilon informado pelo usuário;
* **Critério 2:** `Max_iter` 
Valor inteiro obtido através da entrada feita pelo usuário e que deve ser no mínimo igual a 1. Simboliza o número máximo de iterações que o algoritmo pode realizar antes de ser parado, caso o outro critério não o faça antes.


Para compilar, utilize `make`;

Para executar, utilize `./ep02.out` seguido dos arquivos de entrada e saída. Um exemplo seria: `./ep02 < entrada.in > saida.out`.