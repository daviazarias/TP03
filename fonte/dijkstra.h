#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include<stdbool.h>

#define INF INFINITY 

// ------- Declarações de tipos -------

typedef struct No {
    double data;
    struct No* prox;
} No;

// Estrutura para representar um nó na pilha
typedef struct NoInt {
    int data;
    struct NoInt* prox; // Corrigido para NoInt*
} NoInt;

// Estrutura para representar um No de NosInt
typedef struct NoNoInt{
    NoInt* stack;
    struct NoNoInt* prox;   
}NoNoInt;


// Estrutura para representar os vértices no algoritmo de Dijkstra
typedef struct VisX {
    double weight;
    bool visited;
    struct VisX* previous;
} VisX;

// Declaração das funções
NoNoInt* completeDijkstra(int numOfVert, double **mat);
VisX* dijkstraAlgoritm(int numOfVert, double** mat, int arrive);
void printWay(VisX* vetor, int tam);

NoInt* push(int item, NoInt* stack);
NoNoInt* push_2(NoInt* way, NoNoInt* ways);
NoNoInt* wayInList(VisX* vetor, int numOfVert, NoNoInt* ways);
void printNoNoInt(NoNoInt* allWays);
NoInt* reverseStack(NoInt* stack);
void printNameWay(NoNoInt* allWays, char** nomes);

void freeStack(NoInt* way);
void liberarCaminhos(NoNoInt* ways);

#endif