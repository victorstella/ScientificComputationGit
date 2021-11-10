# SOLUÇÃO DE SISTEMAS NÃO LINEARES
*MÉTODO DE NEWTON*

## ALUNOS

Eduardo Rosso Barbosa - GRR20190378 - ERB19

Victor Daniel Stella Paiva - GRR20200234 - VDSP20

## FUNCIONAMENTO

O método de Newton é um método iterativo para resolução de sistemas de equações não lineares. O seu nome é uma homenagem ao matemático, físico, astrônomo, teólogo e autor Isaac Newton.

O algoritmo espera receber uma entrada com as seguintes informações nesta ordem:

* Dimensão do sistema não linear (número de equações);
* Uma lista com todas as funções do sistema;
* Uma sequência de valores, onde cada um equivale à igualdade de cada uma das equações (número de valores igual ao de funções);
* O epsilon, sendo a tolerância no método de Newton;
* O número máximo de iterações.

## CRITÉRIOS DE PARADA

Os critérios de parada utilizados para esta implementação foram:

* **Critério 1:** `maiorER < epsilon` 
O erro relativo é calculado à partir do valor atual de algum dos X's do sistema e seu valor na iteração anterior. Esse calculo é repetido para todos os X's do sistema, guardando sempre o maior deles até o momento. Assim, foi estabelecido que o maior desses erros não pode ser maior e nem igual ao epsilon informado pelo usuário;
* **Critério 2:** `MAXIT` 
Esta constante é obtida através da entrada feita pelo usuário e simboliza o número máximo de iterações que o algoritmo pode realizar antes de ser parado.

O algoritmo irá parar apenas quando os dois critérios acima forem satisfeitos, portanto, é muito provável que o número máximo de iterações estabelecido seja ultrapassado antes do programa parar.

Para compilar, utilize `make`;

Para executar, utilize `./newtonSNL -o <arquivo_saida>` que pode receber ou não o argumento para indicar um arquivo de saída. Um exemplo seria: `./newtonSNL -o saida.out` ou apenas `./newtonSNL`, que irá imprimir o resultado na saída padrão.