main./* 
Alden Merlin Fachetti Barbosa - 4132505-2
Clauber Pereira Stipkovic Halic - 3124304-5
Maurício Eidi Saijo Araki - 3156627-8
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_FILA 100

#define NONE -1
#define BRANCO 0
#define CINZA 1
#define PRETO 2

typedef bool;
#define false 0
#define true 1

typedef struct aresta
{
    int nome;
    struct aresta *prox;
    int Vassociados[2];
} Aresta;

typedef struct vertices
{
    int nome;
    int cor;
    Aresta *prim;
    int distancia;
    int PChegada;
    int NChegadas;
} Vertice;

void imprimeGrafo(Vertice G[], int ordem);
void criaGrafo(Vertice **G, int ordem);
int acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
int calcumaTamanho(Vertice G[], int ordem);
void Largura(Vertice G[], int ordemG);
bool IsProximos(Vertice G[], Vertice vertice);
void enfileirar(Vertice vertices[], Vertice v);
Vertice desenfileirar(Vertice vertices[]);
void Imprime1(Vertice G[], int ordem);
void Imprime2(Vertice G[], int ordem);
void visitas(Vertice G[], Vertice v);
void algoritmo_busca_largura(Vertice G[], int ordem);
void algoritmo_busca_profundidade(Vertice G[], int ordem);

typedef struct fila
{
    Vertice seq_vertices[MAX_FILA];
    int cabeca;
    int cauda;
} FILA_GRAFOS;

int i;
int VProx;
int count;
FILA_GRAFOS fila;

void criaGrafo(Vertice **G, int ordem)
{
    int i;
    *G = (Vertice *)malloc(sizeof(Vertice) * ordem);

    for (i = 0; i < ordem; i++)
    {
        (*G)[i].nome = i;
        (*G)[i].prim = NULL;
    }
}

int acrescentaAresta(Vertice G[], int ordem, int v1, int v2)
{
    if (v1 < 0 || v1 >= ordem)
        return 0;
    if (v2 < 0 || v2 >= ordem)
        return 0;

    Aresta *A1 = (Aresta *)malloc(sizeof(Aresta));
    A1->nome = v2;
    A1->prox = G[v1].prim;
    A1->Vassociados[0] = v1;
    A1->Vassociados[1] = v2;
    G[v1].prim = A1;

    Aresta *A2 = (Aresta *)malloc(sizeof(Aresta));
    A2->nome = v1;
    A2->prox = G[v2].prim;
    A2->Vassociados[0] = v1;
    A2->Vassociados[1] = v2;
    G[v2].prim = A2;
}

int calculaTamanho(Vertice G[], int ordem)
{
    int i;
    int totalArestas = 0;

    for (i = 0; i < ordem; i++)
    {
        int j;
        Aresta *aux = G[i].prim;
        for (j = 0; aux != NULL; aux = aux->prox, j++)
            ;
        totalArestas += j;
    }
    return totalArestas / 2 + ordem;
}

void imprimeGrafo(Vertice G[], int ordem)
{
    int i;

    printf("\nOrdem:   %d", ordem);
    printf("\nTamanho: %d", calculaTamanho(G, ordem));
    printf("\nLista de Adjacencia:\n");

    for (i = 0; i < ordem; i++)
    {
        printf("\n    V%d: ", i);
        Aresta *aux = G[i].prim;
        for (; aux != NULL; aux = aux->prox)
            printf("%3d", aux->nome);
    }
    printf("\n\n");
}

bool IsProximos(Vertice G[], Vertice vertice)
{
    Aresta *aux = vertice.prim;

    for (; aux != NULL; aux = aux->prox)
    {
        if (aux->Vassociados[0] != vertice.nome && G[aux->Vassociados[0]].cor == BRANCO)
        {
            VProx = aux->Vassociados[0];
            return true;
        }
        else if (aux->Vassociados[1] != vertice.nome && G[aux->Vassociados[1]].cor == BRANCO)
        {
            VProx = aux->Vassociados[1];
            return true;
        }
    }
    return false;
}

void enfileirar(Vertice vertices[], Vertice v)
{
    vertices[fila.cauda] = v;
    if (fila.cauda == MAX_FILA)
        fila.cauda = 0;
    else
        fila.cauda++;
}

Vertice desenfileirar(Vertice vertices[])
{
    Vertice v = vertices[fila.cabeca];
    if (fila.cabeca == MAX_FILA)
        fila.cabeca = 0;
    else
        fila.cabeca++;

    return v;
}

void Imprime1(Vertice G[], int ordem)
{

    for (i = 0; i < ordem; i++)
    {
        Vertice vertice;
        for (vertice = G[i]; i < ordem; i++)
            printf("Distancia de V%d = %d\n", i, G[i].distancia);
    }
    printf("\n\n");
}

void Largura(Vertice G[], int ordemG)
{
    fila.cabeca = 0;
    fila.cauda = 0;

    int i, verticeCount;
    for (i = 0; i < ordemG; i++)
        G[i].cor = BRANCO;

    verticeCount = 0;
    enfileirar(fila.seq_vertices, G[verticeCount]);

    while ((fila.cabeca - fila.cauda) != 0)
    {
        Vertice verticeAtual = desenfileirar(fila.seq_vertices);

        for (; IsProximos(G, verticeAtual) == true;)
        {
            if (G[VProx].cor == BRANCO)
            {
                G[VProx].cor = CINZA;
                G[VProx].distancia = verticeAtual.distancia + 1;
                enfileirar(fila.seq_vertices, G[VProx]);
            }
        }
        G[verticeCount].cor = PRETO;
        verticeCount++;
    }
}

void visitas(Vertice G[], Vertice v)
{
    count = count + 1;
    G[v.nome].PChegada = count;
    G[v.nome].cor = CINZA;
    for (; IsProximos(G, v) == true;)
    {
        if (G[VProx].cor == BRANCO)
        {
            visitas(G, G[VProx]);
        }
    }
    G[v.nome].cor = PRETO;
    count++;
    G[v.nome].NChegadas = count;
}

void Imprime2(Vertice G[], int ordem)
{
    int i;
    for (i = 0; i < ordem; i++)
    {
        Vertice vertice;
        for (vertice = G[i]; i < ordem; i++)
            printf("V%d = %d - %d\n", i, G[i].PChegada, G[i].NChegadas);
    }
}

void Profundidade(Vertice G[], int ordemG)
{
    int i;
    for (i = 0; i < ordemG; i++)
    {
        G[i].cor = BRANCO;
    }
    count = 0;
    for (i = 0; i < ordemG; i++)
    {
        if (G[i].cor == BRANCO)
            visitas(G, G[i]);
    }
}

void algoritmo_busca_largura(Vertice G[], int ordem)
{
    printf("Busca em largura do V0:\n");
    Largura(G, ordem);
    Imprime1(G, ordem);
}

void algoritmo_busca_profundidade(Vertice G[], int ordem)
{
    printf("Busca em profundidade - Inicio em V0:\n");
    Profundidade(G, ordem);
    Imprime2(G, ordem);
}

int main()
{
    Vertice *G;
    int ordemG = 10;

    criaGrafo(&G, ordemG);
    acrescentaAresta(G, ordemG, 3, 4);
    acrescentaAresta(G, ordemG, 4, 2);
    acrescentaAresta(G, ordemG, 5, 4);
    acrescentaAresta(G, ordemG, 2, 3);
    acrescentaAresta(G, ordemG, 3, 7);

    imprimeGrafo(G, ordemG);

    algoritmo_busca_largura(G, ordemG);
    algoritmo_busca_profundidade(G, ordemG);
    system("PAUSE");

    return 0;
}
