# INTEGRAÇÃO NUMÉRICA
*Integração da função Styblinski-Tang através dos métodos de Monte Carlo pela média e dos Retângulos*

*(sendo 2 dimensões para a dos retângulos e 2, 4 e 8 dimensões para a de Monte Carlo)*

## ALUNOS

Eduardo Rosso Barbosa - GRR20190378 - ERB19

Victor Daniel Stella Paiva - GRR20200234 - VDSP20

## ANÁLISE DE COMPARAÇÕES

* Considerando n = 2 dimensões, o método dos Retângulos se mostrou mais próximo dos resultados usados como base, obtidos através de ferramentas de calculo como WolframAlpha. Dessa forma, para 10⁷ pontos usados no método dos retângulos e 10⁷ amostras aleatórias para o método de Monte Carlo, os resultados foram -2184,53346123 e -2184,58452856 respectivamente. A ferramenta utilizada como referência obteve -2184,53333333.

* Para que o resultado do método dos retângulos fique mais proximo possível do obtido pelo de Monte Carlo com 10⁷ amostras, é necessário diminuir a quantidade de pontos para apenas 24994. Conforme visto em aula, acreditamos que isso se deve ao erro numérico das operações matemáticas superar a precisão dos métodos conforme o número de pontos/amostras aumenta. Assim, uma quantidade menor de pontos elimina boa parte do erro obtido no resultado mostrado anteriormente. Ainda, podemos concluir que o resultado obtido pelo método de Monte Carlo sofre mais com esses erros numéricos, uma vez que para 10⁷ pontos e amostras, o método dos retângulos se mostrou mais proximo do valor desejado.

* Como o intervalo analisado em cada dimensão é o mesmo, podemos verificar que as amostras são idênticos para cada dimensão calculada. Dessa forma, o resultado para n = 4 é basicamente o mesmo que o obtido para n = 2 multiplicado por 2, da mesma forma, para n = 8 se aproxima muito do obtido por n = 2 multiplicado por 4 e também por n = 4 multiplicado por 2.

* O código foi o mais otimizado possível, cuidando para não utilizar laços desnecessários e para que não tivessem subexpressões desnecessárias neles, calculando valores utilizados nos laços fora dos mesmos e não tendo nenhuma dependência de dados dentro deles usando variáveis auxiliares o tempo todo. Utilizamos apenas 1 alocação de memória de um ponteiro para double, acessado contíguamente e sem realocações. Também, evitamos ao máximo funções da biblioteca math.h que podem ser facilmente substituídas mas que tomam tempo, não acessamos dados desnecessariamente e não inicializamos memória antes de ser necessário. Além disso, otimizamos bastante os calculos através de algebrismos e fatorações, de forma a usar menos laços e realizar menos operações.

## INFORMAÇÕES RELEVANTES

Como a função Styblinski-Tang consiste em um somatório relacionado ao número de variáveis (dimensões) e este somatório é dividido por 2, consideramos que a divisão pode ser eliminada, de forma a tornar-se uma constante dada por 1/2, que multiplica a função. Também, como a função do somatório se repete para cada dimensão, recebendo basicamente os mesmos valores dentro do intervalo todas as vezes que calculada, consideramos que nesta aplicação específica, o somatório consiste apenas de n multiplicado pela função principal, eliminando o somatório de Styblinski-Tang. Este mesmo princípio foi aplicado ào segundo somatório do método dos retângulos, considerado assim uma simples multiplicação pelo número de pontos. Assim, essa constante n que agora multiplica a função pode ser combinada com a outra constante 1/2 obtida, de forma que fique (n / 2) * f( x1, ... , xn ). Nos dois métodos, para n = 2 a constante desaparece, para n = 4 se torna 2 e para n = 8 fica 4, assim:

* ### Monte Carlo
(b - a) * (1 / nAmostras) * (n / 2) * sum( f( x1, ... , xn ) )

n = 2 dimensões: (b - a) * (1 / nAmostras) * sum( f( x1, ... , xn ) )

n = 4 dimensões: (b - a) * (1 / nAmostras) * 2 * sum( f( x1, ... , xn ) )

n = 8 dimensões: (b - a) * (1 / nAmostras) * 4 * sum( f( x1, ... , xn ) )

* ### Retângulos
h² * nPontos * (n / 2) * sum( f( x1, ... , xn ) )

n = 2 dimensões: h² * nPontos * sum( f( x1, ... , xn ) )