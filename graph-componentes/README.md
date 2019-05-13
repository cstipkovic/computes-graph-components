# computes-graph-components
C program to calculate how many components a graph has.

# Work definition (pt-br)
Problema: elaborar um programa em C para calcular quantas componentes um grafo tem.

Na sua solução, será obrigatório o uso do programa em C apresentado em aula. Você deverá apenas acrescentar a parte do código específica para o problema proposto.

Apesar de existirem alguns algoritmos eficientes para resolver o problema, sua solução deverá, obrigatoriamente, ser baseada na seguinte estratégia:

"Para identificar todos os vértices de uma componente, consulte as arestas do grafo procurando por uma que tenha um extremo já na componente e o outro extremo sem componente atribuída. Encontrando tal aresta, inclua o novo vértice na componente; caso contrário, todos os vértices da componente foram identificados e inicie o tratamento de uma (eventual) nova componente."

Implemente funções que resolvam partes do problema deixando a arte de exibição dos resultados para uma única função específica para isso.