# ANÁLISE DE DESEMEPNHO
*COMPARAÇÃO DE ALGORITMOS DE SOLUÇÃO DE SISTEMAS LINARES*

## ALUNOS

Eduardo Rosso Barbosa - GRR20190378 - ERB19

Victor Daniel Stella Paiva - GRR20200234 - VDSP20

## OTIMIZAÇÕES

* **Alocação do sistema linear**
**Não otimizado:** Utiliza a lógica tradicional de alocar n ponteiros e em seguida alocar um vetor de tamanho n para cada.
**Otimizado:** Aloca o espaço adequado para toda a matriz. Além disso, entende que não pode alocar uma linha que seja potência de 2, portanto nestes casos aloca n+1 ponteiros e em cada um aloca um vetor de tamanho n, quando 

* **Método Gauss-Jacobi**
**Não otimizado:** Utiliza a lógica tradicional, caminhando pela diagonal, calculando a parte da soma de cada x e inserindo no cálculo do x em questão. 
**Otimizado:** Faz o mesmo que otimizado porém com 4 x's sequenciais ao mesmo tempo, devido à dependência de dados (os x's anteriores ainda não calulcados) altera a lógica para que some as partes que não dependam dos x's ainda não calculados, depois multiplicam-se os x que agora estão calculados.

## INFORMAÇÕES RELEVANTES

Os valores apresentados nos gráficos remetem exclusivamente aos trechos de código referentes ao método Gauss-Jacobi, ou seja, leituras, alocações, liberação de memória, criação de sistemas lineares, etc, não estão inclusos.

* **Arquitetura do Processador de testes**
CPU name: Intel(R) Core(TM) i5-6200U CPU @ 2.30GHz
CPU type: Intel Skylake processor
Sockets: 1
Cores per socket: 2
Threads per core: 2