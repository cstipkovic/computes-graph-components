
/* Trabalho feito em grupo.
	- Rabah Zeineddine - 41502779
    - Gustavo Dechechi - 31559042
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#define MAX_FILA  100
#define MAX_VALUE 99999
#define NONE  -1
#define BRANCO 0
#define CINZA  1
#define PRETO  2

typedef struct aresta {
    int nome;
    struct aresta *prox;
} Aresta;

/* S representa o tempo descoberto no lugar de usar d para nao sobrescrever a de busca em largura*/

typedef struct vert {
    int nome;
    int cor;
    int d;
    int s;
    int f;
    int pi;
    Aresta *prim;
} Vertice;



void imprimeGrafo(Vertice G[], int ordem);
void imprimirGrafoEmLargura(Vertice G[],int ordemG);
void imprimeGrafoEmProfundidade(Vertice G[],int ordemG);
void criaGrafo(Vertice **G, int ordem);
int  acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
void criaFila(int **fila,int *topo,int tamanho);
void enfileirar(int fila[],int *topo,int indiceVertice,int tamanho);
int desenfileirar(int fila[],int *topo);
int filaVazia(int fila[],int *topo);
void buscaEmLargura(Vertice G[],int verticeInicial,int ordem);
void buscaEmProfundidade(Vertice G[], int ordemG);
void buscaEmProfundidadeVisita(Vertice G[],int u, int *time);


void criaGrafo(Vertice **G, int ordem) {
    int i;
    *G= (Vertice*) malloc(sizeof(Vertice)*ordem);

    for(i=0; i<ordem; i++) {
        (*G)[i].nome = i;
        (*G)[i].prim = NULL;
    }
}

int acrescentaAresta(Vertice G[], int ordem, int v1, int v2) {
    if (v1<0 || v1 >= ordem)
        return 0;
    if (v2<0 || v2 >= ordem)
        return 0;

    Aresta *A1= (Aresta *) malloc(sizeof(Aresta));
    A1->nome= v2;
    A1->prox= G[v1].prim;
    G[v1].prim= A1;

    Aresta *A2= (Aresta *) malloc(sizeof(Aresta));
    A2->nome= v1;
    A2->prox= G[v2].prim;
    G[v2].prim= A2;
}


int  calcumaTamanho(Vertice G[], int ordem) {
    int i;
    int totalArestas=0;

    for (i=0; i<ordem; i++) {
        int j;
        Aresta *aux= G[i].prim;
        for(j=0; aux != NULL; aux= aux->prox, j++);
        totalArestas += j;
    }
    return totalArestas/2 + ordem;
}

void imprimeGrafo(Vertice G[], int ordem) {
    int i;

    for (i=0; i<ordem; i++) {
        printf("\nV%d: ", i);
        Aresta *aux= G[i].prim;
        for( ; aux != NULL; aux= aux->prox)
            printf("%3d", aux->nome);
    }
    printf("\n\n");
}

void imprimirGrafoEmLargura(Vertice G[],int ordemG){
    int i;
    printf("\nResultado da busca em largura:\nVertice\t  D\t PI");
    for (i=0; i < ordemG; i++) {
        printf("\n  V%d\t  %d \t %d", i, G[i].d, G[i].pi);
    }
    printf("\n\n");
}

void imprimeGrafoEmProfundidade(Vertice G[],int ordemG){
    int i;
    printf("\nResultado da busca em profundidade:\nVertice\t  PI \t S \t F");
    for (i=0; i < ordemG; i++) {
        printf("\n  V%d\t  %d \t %d \t %d", i,  G[i].pi, G[i].s, G[i].f);
    }
    printf("\n\n");
}

void criaFila(int **fila,int *topo, int tamanho){
    int i;
    /* Fila com indice de vertices */
    *fila = (int *) malloc(tamanho * sizeof(int));
    *topo = -1;
    /* As posicoes da fila sao inicializadas com -1 pois ha vertices com 0 */
    for(i = 0; i < tamanho; i++){
        (*fila)[i] = -1;
    }
}

void enfileirar(int fila[],int *topo, int indiceVertice, int tamanho){
    if( (*topo) < tamanho ){
        (*topo)++;
        fila[(*topo)] = indiceVertice;
    }
}

int desenfileirar(int fila[], int *topo){
    int vertice,i;
    if( (*topo) >= 0){
            vertice = fila[0];
        
        for(i =0; i < (*topo) ; i++){
            fila[i] = fila[i+1];
        }
        fila[i] = -1; /* Anular o ultimo valor que estava na posicao do Topo. */
        (*topo)--;
        return vertice;
    }
    return -1;
}

int filaVazia(int fila[], int *topo){
    if( (*topo) == -1)
        return 1;
    return 0;
}

void buscaEmLargura(Vertice G[], int verticeInicial, int ordem){
    int vertice,i, *fila, topo;
    
    for ( i = 0 ; i < ordem ; i++) {
        if( i != verticeInicial ){
            G[i].cor = BRANCO;
            G[i].d = MAX_VALUE;
            G[i].pi = -1;
        }
    }
    
    G[verticeInicial].cor = CINZA;
    G[verticeInicial].d = 0;
    G[verticeInicial].pi = -1;
    
    criaFila(&fila, &topo,  ordem);
    enfileirar(fila, &topo, verticeInicial,ordem);
    
    while(filaVazia(fila, &topo) == 0){
        vertice = desenfileirar(fila, &topo);
        Aresta *aux= G[vertice].prim;
        for(; aux != NULL   ; aux= aux->prox){
            if(G[aux->nome].cor == BRANCO){
                G[aux->nome].cor = CINZA;
                G[aux->nome].d = G[vertice].d + 1;
                G[aux->nome].pi = vertice;
                enfileirar(fila,&topo, aux->nome, ordem);
            }
        }
        G[vertice].cor = PRETO;
    }
}

void buscaEmProfundidade(Vertice G[], int ordemG){
    int i, time;
    for( i = 0 ; i < ordemG; i++ ){
        G[i].cor = BRANCO;
        G[i].pi = -1;
    }
    time = 0;
    for( i = 0; i < ordemG ; i++ ){
        if(G[i].cor == BRANCO ){
            buscaEmProfundidadeVisita(G,i, &time);
        }
    }
}

void buscaEmProfundidadeVisita(Vertice G[],int u, int *time){
    *time = *time + 1;
    G[u].s = *time;
    G[u].cor = CINZA;
    
    Aresta *aux= G[u].prim;
    for(; aux != NULL   ; aux= aux->prox){
        if(G[aux->nome].cor == BRANCO){
            G[aux->nome].pi = u;
            buscaEmProfundidadeVisita(G, aux->nome, time);
        }
    }
    G[u].cor = PRETO;
    *time = *time + 1;
    G[u].f = *time;
}


int main(int argc, char *argv[]) {
    Vertice *G;
    int ordemG= 11;

    criaGrafo(&G, ordemG);
    
    /* O codigo utiliza o codigo apresentado na sala. neste codigo a inicializacao dos vertices comeca pelo indice zero
	*/
    /* A representacao Grafica do Grafo a ser adicionado baseada no grafo representado na sala de aula (23/04/2018)
     
        V0 --- V1           V10     V9
        |      |             |      |
        |      |             |      |
        V2 --- V3 --- V4 --- V6 --- V7
               |
               |
               V5
               |
               |
               V8
    */

    acrescentaAresta(G,ordemG,0,2);
    acrescentaAresta(G,ordemG,0,1);
    acrescentaAresta(G,ordemG,3,1);
    acrescentaAresta(G,ordemG,3,5);
    acrescentaAresta(G,ordemG,3,4);
    acrescentaAresta(G,ordemG,3,2);
    acrescentaAresta(G,ordemG,4,6);
    acrescentaAresta(G,ordemG,6,10);
    acrescentaAresta(G,ordemG,6,7);
    acrescentaAresta(G,ordemG,7,9);
    acrescentaAresta(G,ordemG,5,8);
    
    printf("\nTamanho: %d\n",calcumaTamanho(G, ordemG));
    imprimeGrafo(G, ordemG);
    
    buscaEmLargura(G,0,ordemG);
    imprimirGrafoEmLargura(G, ordemG);
    buscaEmProfundidade(G,ordemG);
    imprimeGrafoEmProfundidade(G,ordemG);
    
    return 0;
}
