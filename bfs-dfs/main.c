/* 
Alden Merlin Fachetti Barbosa - 4132505-2
Clauber Pereira Stipkovic Halic - 3124304-5
Maurício Eidi Saijo Araki - 3156627-8
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#define MAX_FILA 100

#define NONE -1
#define BRANCO 0
#define CINZA 1
#define PRETO 2

typedef struct a {
    int nome;
    struct aresta *prox;
} Aresta;

typedef struct v {
    int nome;
    int cor;
    int distancia;
    int tempoInicio;
    int tempoFim;
    int pi;
    Aresta *prim;
} Vertice;

void criaFila(int **fila,int *topo, int tamanho){
    int i;
 
    *fila = (int *) malloc(tamanho * sizeof(int));
    *topo = -1;
    
    for(i = 0; i < tamanho; i++){
        (*fila)[i] = -1;
    }
}

void criaGrafo(Vertice **G, int ordem) {
    int i;
    *G = (Vertice*) malloc(sizeof(Vertice) * ordem);

    for (i = 0; i < ordem; i++) {
        (*G)[i].nome = i;
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
}

int calculaTamanho(Vertice G[], int ordem) {
    int i;
    int totalArestas = 0;

    for (i = 0; i < ordem; i++) {
        int j;
        Aresta *aux = G[i].prim;
        for (j = 0; aux != NULL; aux = aux->prox, j++);
        totalArestas += j;
    }

    return (totalArestas/2) + ordem;
}

void enfileirar(int fila[], int *posicao, int iVertice, int tamanho) {
    if (*posicao < tamanho) {
        *posicao++;
        fila[*posicao] = iVertice;
    }
}

int desenfileirar(int fila[], int *posicao) {
    int v, i;
    if (*posicao >= 0) {
        v = fila[0];
        
        for (i = 0; i < *posicao; i++)
            fila[i] = fila[i + 1];
        fila[i] = -1; /* limpa o valor da ultima posicao. */
        (*posicao)--;
        return v;
    }

    return -1;
}

void ImprimeLargura(Vertice G[], int ordem) {
    int i;
    printf("\nResultado da busca em largura:\nVertice\t  D\t PI");
    for (i=0; i < ordemG; i++) {
        printf("\n  V%d\t  %d \t %d", i, G[i].d, G[i].pi);
    }
    printf("\n\n");
    int i;
    for (i = 0; i < ordem; i++) {
        printf("Distancia de V%d = %d\n", i, G[i].distancia);
    }
    printf("\n\n");
}

void Largura(Vertice G[], int ordemG, int vInicial) {
    int v, i, *fila, posicao;

    for (i = 0; i < ordemG; i++) {
        if (i != vInicial) {
            G[i].cor = BRANCO;
            G[i].distancia = 1000; /* Distancia maxima para nao gerar segmentation fault */
        }
    }

    G[vInicial].cor = CINZA;
    G[vInicial].distancia = 0;

    criaFila(&fila, &posicao, ordemG);
    enfileirar(fila, &posicao, vInicial, ordemG);

    while (isFilaVazia(fila, &posicao) == 0) {
        v = desenfileirar(fila, &posicao);
        Aresta *aux = G[v].prim;
        for (; aux != NULL; aux = aux->prox){
            if (G[aux->nome].cor == BRANCO) {
                G[aux->nome].cor = CINZA;
                G[aux->nome].distancia = G[v].distancia + 1;
                enfileirar(fila, &posicao, aux->nome, ordemG);
            }
        }
        G[v].cor = PRETO;
    }
}

void visitas(Vertice G[], int v, int *count) {
    *count = *count + 1;

    G[v].tempoInicio = *count;
    G[v].cor = CINZA;
    
    Aresta *aux = G[v].prim;
    for (; aux != NULL; aux= aux->prox) {
        if (G[aux->nome].cor == BRANCO) {
            // G[aux->nome].pi = v;
            visitas(G, aux->nome, count);
        }
    }

    G[v].cor = PRETO;
    *count = *count + 1;
    G[v].tempoFim = *count;
}

void ImprimeProfundidade(Vertice G[], int ordem) {
    int i;
    // printf("\nResultado da busca em profundidade:\nVertice\t \t S \t F");
    for (i = 0; i < ordem; i++)
        printf("\n  V%d\t %d \t %d", i, G[i].tempoFim, G[i].tempoFim);
}

int isFilaVazia(int fila[], int *posicao) {
    if ((*posicao) == -1)
        return 1;
    return 0;
}

void Profundidade(Vertice G[], int ordemG) {
    int i, count;

    for (i = 0; i < ordemG; i++) {
        G[i].cor = BRANCO;
    }

    count = 0;
    for (i = 0; i < ordemG; i++) {
        if (G[i].cor == BRANCO)
            visitas(G, i, &count);
    }
}

void imprimeGrafo(Vertice G[], int ordem) {
    int i;

    printf("\nOrdem:\t%d", ordem);
    printf("\nTamanho:\t%d", calculaTamanho(G, ordem));
    printf("\nLista de Adjacencia:\n");

    for (i = 0; i < ordem; i++) {
        printf("\nV %d: ", i);
        Aresta *aux = G[i].prim;
        for (; aux != NULL; aux = aux->prox)
            printf("%3d", aux->nome);
    }
    printf("\n\n");
}

void algoritmoBuscaLargura(Vertice G[], int ordem, int vInicial) {
    printf("Busca em largura do V0:\n");
    Largura(G, ordem, vInicial);
    ImprimeLargura(G, ordem);
}

void algoritmoBuscaProfundidade(Vertice G[], int ordem) {
    printf("Busca em profundidade - Inicio em V0:\n");
    Profundidade(G, ordem);
    ImprimeProfundidade(G, ordem);
}

int main() {
    Vertice *G;
    int ordem = 10;

    criaGrafo(&G, ordem);

    /* Código apresentado em sala */
    /* Inicializacao dos vetores pelo indice 0 */
    acrescentaAresta(G, ordem, 0, 2);
    acrescentaAresta(G, ordem, 3, 4);
    acrescentaAresta(G, ordem, 4, 2);
    acrescentaAresta(G, ordem, 5, 4);
    acrescentaAresta(G, ordem, 2, 3);
    acrescentaAresta(G, ordem, 3, 7);

    imprimeGrafo(G, ordem);

    algoritmoBuscaLargura(G, ordem, 0);
    // algoritmo_busca_profundidade(G, ordemG);

    return 0;
}
