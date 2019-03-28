#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define NONE  -1
#define BRANCO 0
#define CINZA  1
#define PRETO  2

typedef struct aresta {
	int nome;
	struct aresta *prox;
} Aresta;

typedef struct vert {
	int nome;
	int componente;
	Aresta *prim;
} Vertice;

void imprimeGrafo(Vertice G[], int ordem);
void criaGrafo(Vertice **G, int ordem);
int  acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
int  calculaTamanho(Vertice G[], int ordem);
int contaComponenets(Vertice G[], int ordem);

void criaGrafo(Vertice **G, int ordem) {
	int i;
	*G = (Vertice*) malloc(sizeof(Vertice)*ordem);
	
	for (i = 0; i < ordem; i++) {
		(*G)[i].nome = i;
		(*G)[i].componente = 0; /* 0: sem componente atribuida */
		(*G)[i].prim = NULL;
	}
}

int acrescentaAresta(Vertice G[], int ordem, int v1, int v2) {
	if (v1 < 0 || v1 >= ordem)
	   return 0;
	if (v2 < 0 || v2 >= ordem)
	   return 0;
	
	Aresta *A1 = (Aresta *) malloc(sizeof(Aresta));
	A1->nome = v2;
	A1->prox = G[v1].prim;
	G[v1].prim = A1;

	Aresta *A2 = (Aresta *) malloc(sizeof(Aresta));
	A2->nome = v1;
	A2->prox = G[v2].prim;
	G[v2].prim = A2;
	
	return 1;
}

int  calculaTamanho(Vertice G[], int ordem) {
	int i;
	int totalArestas = 0;
	
	for (i = 0; i < ordem; i++) {
		int j;
		Aresta *aux = G[i].prim;
		for (j = 0; aux != NULL; aux = aux->prox, j++);
		totalArestas += j;	
	}

	return totalArestas / 2 + ordem;
}

void imprimeGrafo(Vertice G[], int ordem){
	int i;

	printf("\nOrdem:   %d",ordem);
	printf("\nTamanho: %d",calculaTamanho(G, ordem));
	printf("\nLista de Adjacencia:\n");

	for (i = 0; i < ordem; i++) {
		printf("\n    V%d (Comp:%2d): ", i, G[i].componente);
		Aresta *aux = G[i].prim;
		for( ; aux != NULL; aux = aux->prox)
			printf("%3d", aux->nome);
	}
	printf("\n\n");
}

// Conta o numero de componentes em um grafo
int contaComponenets(Vertice G[], int ordem) {
	int numeroComponentes = 0;
	int i;

	// percorre cada vetor do grafo
	for (i = 0; i < ordem; i++) {
		// Acrescenta e marca o primeiro 
		// vetor como o primeiro componente
		if (G[i].componente == 0) {
			numeroComponentes++;
			G[i].componente = numeroComponentes;
		}

		Aresta *aux = G[i].prim;
		// Passa por todas as arestas adjacentes
		for ( ; aux != NULL; aux = aux->prox) {
			// Se a aresta nao tiver componente (estiver com 0)
			// ela recebe o numero do componente no qual
			// foi referenciada pela primeira vez na lista de 
			// adjacencia
			if (G[aux->nome].componente == 0) {
				G[aux->nome].componente = numeroComponentes;
			}
		}
	}

	printf("\nNumero componentes: %d\n", numeroComponentes);

	return numeroComponentes;
}

int main(int argc, char *argv[]) {
	Vertice *G;
	int ordemG = 8;
	
	criaGrafo(&G, ordemG);

	// Teste 1
	// acrescentaAresta(G,ordemG,0,1);
	// acrescentaAresta(G,ordemG,0,3);
	// acrescentaAresta(G,ordemG,3,1);
	// acrescentaAresta(G,ordemG,2,4);
	
	// Teste 2
	acrescentaAresta(G,ordemG,3,4);
	acrescentaAresta(G,ordemG,4,2);
	acrescentaAresta(G,ordemG,5,4);
	acrescentaAresta(G,ordemG,2,3);
	acrescentaAresta(G,ordemG,3,7);

	// Chamada da funcao que retorna o numero de
	// componentes no grafo
	contaComponenets(G, ordemG);

	imprimeGrafo(G, ordemG);

    system("PAUSE");
	return 0;
}
