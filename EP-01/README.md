# RESOLUÇÃO DE EQUAÇÕES NÃO LINEARES
*MÉTODO DE NEWTON-RAPHSON E DA SECANTE*

## ALUNOS

Eduardo Rosso Barbosa - GRR20190378 - ERB19

Victor Daniel Stella Paiva - GRR20200234 - VDSP20

## CRITÉRIOS DE PARADA

Os critérios de parada utilizados para esta implementação foram:

* **Critério 1:** `Max_iter` 
Valor inteiro obtido através da entrada feita pelo usuário e que deve ser no mínimo igual a 3. Simboliza o número máximo de iterações que o algoritmo pode realizar antes de ser parado, caso nenhum dos outros critérios abaixo o faça antes;
* **Critério 2:** `newton_crit < epsilon`
A partir das informações de entrada, o 'newton_crit' é calculado usando os dois útimos valores obtidos através do método de Newton-Raphson aplicado à função, sendo o da iteração atual e o da anterior. Essa relação é estabelecida à partir da fórmula do erro absoluto. A Estabelecemos então que este valor não poderia ser maior e nem igual ao epsilon informado pelo usuário;
* **Critério 3:** `secante_crit < epsilon`
Da mesma forma que o 'newton_crit', o valor da 'secante_crit' é obtido através dos dois útimos valores do método da Secante e da fórmula do erro absoluto entre esses valores. Ainda, determinamos que este valor também não poderia ser maior e nem igual ao epsilon informado pelo usuário;
* **Critério 4:** `ulp <= 1` 
A ULP é calculada com os valores da iteração atual obtidos nos métodos de Newton-Raphson e Secante, ambos convertidos para um tipo de dado que torna possível a representação e manipulação em número de bits. A partir desses valores, calculamos o módulo da diferença entre o módulo de cada um, de forma a garantir que o resultado obtido seja a distância em bits desses dois valores. Caso essa ULP resultante seja menor ou igual a 1 (menor distância entre dois números decimais que a máquina consegue representar), o algoritmo irá parar.

## INFORMAÇÕES RELEVANTES

Devido ao fato de que o cálculo da secante exige ter dois valores anteriores previamente cálculados, nosso algoritmo entra no loop somente à partir da terceira iteração. Essa foi a abordagem mais conveniente para contornarmos essa limitação matemática.

Para compilar, utilize `make`;

Para executar, utilize `./ep01.out` seguido de uma flag para entrada e outra para a saída, ambas com seus respectivos arquivos. Um exemplo seria: `./ep01.out < entrada.in > saida.csv`.
