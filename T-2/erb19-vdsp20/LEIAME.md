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

* **Critério 1:** `MAXIT` 
Esta constante é obtida através da entrada feita pelo usuário e simboliza o número máximo de iterações que o algoritmo pode realizar antes de ser parado.
* **Critério 2:** `maior < epsilon` 
O maior valor de X do vetor de resultados do SL é calculado e comparado com o valor do epsilon. Assim, foi estabelecido que este maior X não pode ser maior e nem igual ao epsilon informado pelo usuário;
* **Critério 3:** `delta < epsilon`
A cada iteração, o delta representa a diferença entre o valor da aproximação atual de um determinado X e seu valor na iteração anterior. Assim, essa diferença de qualquer um dos Xs não pode ser menor que o epsilon.

O algoritmo irá parar apenas quando os três critérios acima forem satisfeitos.

Para compilar, utilize `make`;

Para executar, utilize `./newtonSNL < arquivo_entrada > arquivo_saida` que pode receber ou não os argumentos para indicar os arquivos de entrada e saída. Um exemplo seria: `./newtonSNL < entrada.in > saida.out` ou apenas `./newtonSNL`, que irá receber da entrada padrão e imprimir o resultado na saída padrão.