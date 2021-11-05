# SOLUÇÃO DE SISTEMAS LINEARES
*MÉTODO DE GAUSS-SEIDEL*

## ALUNOS

Eduardo Rosso Barbosa - GRR20190378 - ERB19

Victor Daniel Stella Paiva - GRR20200234 - VDSP20

## FUNCIONAMENTO

O método de Gauss-Seidel é um método iterativo para resolução de sistemas de equações lineares. O seu nome é uma homenagem aos matemáticos alemães Carl Friedrich Gauss e Philipp Ludwig von Seidel.

O algoritmo espera receber uma entrada com as seguintes informações nesta ordem:

* Dimensão do sistema linear;
* Número de diagonais (sempre ímpar);
* Uma lista com todas as funções do sistema linear;
* O epsilon, sendo a tolerância no método de Gauss-Seidel;
* O número máximo de iterações.

## CRITÉRIOS DE PARADA

Os critérios de parada utilizados para esta implementação foram:

* **Critério 1:** `maiorER < epsilon` 
O erro relativo é calculado à partir do valor atual de algum dos X's do sistema e seu valor na iteração anterior. Esse calculo é repetido para todos os X's do sistema, guardando sempre o maior deles até o momento. Assim, foi estabelecido que o maior desses erros não pode ser maior e nem igual ao epsilon informado pelo usuário;
* **Critério 2:** `MAXIT` 
Esta constante é obtida através da entrada feita pelo usuário e simboliza o número máximo de iterações que o algoritmo pode realizar antes de ser parado.

O algoritmo irá parar apenas quando os dois critérios acima forem satisfeitos, portanto, é muito provável que o número máximo de iterações estabelecido seja ultrapassado antes do programa parar.

Para compilar, utilize `make`;

Para executar, utilize `./ep02` seguido dos arquivos de entrada e saída. Um exemplo seria: `./ep02 < entrada.in > saida.out`.