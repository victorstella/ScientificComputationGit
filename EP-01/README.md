# README ICC 

## Alunos 
Eduardo Rosso Barbosa - GRR20190378 - ERB19
Victor Paiva Stella - GRR - VSP20

## CRITÉRIOS DE PARADA

Os critérios de parada utilizados para esta implementação foram

* **Critério 1:** `Max_iter` 
Quando atingido o máximo de iterações, o algorítmo irá parar. Informação obtida através da entrada, têm de ser maior ou igual à 3;
* **Critério 2:** `newton_crit < epsilon`
Palavras
* **Critério 3:** `secante_crit < epsilon`
Explicações
* **Critério 4:** `ulp = 1` 
A ULP é calculada com os valores de phi em x e phi pelo método da secante em x, caso essa ULP seja de 1, o algorítmo irá parar

## INFORMAÇÔES RELEVANTES

Nosso algortimo, devido ao fato de que a secante necessita ter dois valores anteriores cálculados, só entra no loop a partir da terceira iteração, pois essa foi a abordagem mais conveniente para o problema. 

Para compilar, utilize; `make`
Para rodar, um exemplo seria: `./ep01.out < entrada.in > saida.csv`