#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "dijkstra.h"

// ------- Funcoes auxiliares ------
NoInt* push(int item, NoInt* stack) {
    NoInt* aux = malloc(sizeof(NoInt));
    aux->data = item;
    aux->prox = stack;
    return aux;
}

NoNoInt* push_2(NoInt* way, NoNoInt* ways){
    NoNoInt* aux = malloc(sizeof(NoNoInt));
    aux->stack = way;
    aux->prox = ways;
    return aux;
}

// ------- Função dijkstra base -------

VisX* dijkstraAlgoritm(int numOfVert, double** mat, int arrive) {
    
    VisX* vertices = malloc(numOfVert * sizeof(VisX));
    for(int i = 0; i < numOfVert; i++) {
        vertices[i].previous = NULL;
        vertices[i].weight = INF;
        vertices[i].visited = false;
    }
    vertices[arrive].weight = 0;

    int aux;
    bool cond;
    do{
        aux = -1;
        for(int j = 0; j < numOfVert; j++) {
            if (!vertices[j].visited && (aux == -1 || vertices[j].weight < vertices[aux].weight)) {
                aux = j;
            }
        }
        if (aux == -1) break; // todos visitados

        vertices[aux].visited = true;
        
        for(int j = 0; j < numOfVert; j++){
            if(mat[aux][j] != INF && !vertices[j].visited){
                double novaDist = vertices[aux].weight + mat[aux][j];
                if(novaDist < vertices[j].weight){ 
                    vertices[j].weight = novaDist;
                    vertices[j].previous = &vertices[aux];
                }
            }
        }

        cond = false;
        for(int j = 0; j < numOfVert; j++){
            if(!vertices[j].visited) cond = true;
        }
    }while(cond);

    return vertices;
}

// ---- Função de impressão de caminho ---- 
void printWay(VisX* vetor, int tam){
    for(int i = 0; i < tam; i++){
        if (vetor[i].weight == INF) {
            printf("inacessível");
        } 
        else if(vetor[i].previous != NULL){
            printf("Caminho para V%d: ", i);
            VisX* current = &vetor[i];
            while(current != NULL){
                printf("V%ld ", current - vetor);
                current = current->previous;
            }
            puts("");
        }
    }
}

// ----- Funcao para reverter a ordem do caminho
NoInt* reverseStack(NoInt* stack) {
    NoInt* prev = NULL;
    while (stack) {
        NoInt* next = stack->prox;
        stack->prox = prev;
        prev = stack;
        stack = next;
    }
    return prev;
}

// Funcao de adicionar os caminhos na lista de caminhos
NoNoInt* wayInList(VisX* vetor, int numOfVert, NoNoInt* ways){
    for(int i = 0; i < numOfVert; i++){
        NoInt* way = NULL;
        if(vetor[i].weight != INF && vetor[i].previous != NULL){
            VisX* current = &vetor[i];
            way = NULL;

            int start = -1, end = current - vetor; 
            while(current != NULL){
                start = current - vetor;
                way = push(start, way);
                current = current->previous;
            }
            if (start < end) {
                ways = push_2(way, ways);
            }

        }
    }
    return ways;
}

// ---- Funcao de todos os caminhos em Dijkstra ---- 
NoNoInt* completeDijkstra(int numOfVert, double **mat) {
    NoNoInt* allWays = NULL;
    allWays = NULL;
    for(int i = 0; i < numOfVert; i++){
        VisX* tmp = dijkstraAlgoritm(numOfVert, mat, i);
        allWays = wayInList(tmp, numOfVert, allWays);
    }
    return allWays;
}

// --- Imprime NoNoInt ---
void printNoNoInt(NoNoInt* allWays) {
    const char* personagens[10] = 
    {"Arya", "Sam", "Bran", "Jaime", "Sansa", "Brienne", "Catelyn", "Tyrion", "Cersei", "Varys"};
    int i = 0;
    NoNoInt* ant, *retorno;
    while(allWays != NULL) {
        ant = allWays;
        printf("Caminho%d: ", i);
        NoInt* caminho = reverseStack(ant->stack);
        while (caminho != NULL) {
            printf("%s ", personagens[caminho->data]);
            caminho = caminho->prox;
        }
        allWays = allWays->prox;
        i++;
        puts(""); 
    }
}

void printNameWay(NoNoInt* allWays, char** nomes){
    int i = 0;
    NoNoInt* ant;
    while(allWays != NULL) {
        ant = allWays;
        printf("Caminho%d: ", i);
        NoInt* caminho = reverseStack(ant->stack);
        while (caminho != NULL) {
            printf("%s ", nomes[caminho->data]);
            caminho = caminho->prox;
        }
        allWays = allWays->prox;
        i++;
        puts(""); 
    }
}

void freeStack(NoInt* way){
    NoInt* prev = NULL;
    while(way){
        prev = way;
        way = way->prox;
        free(prev);
    }
}

void freeWays(NoNoInt* ways){
    NoNoInt *prev = NULL;
    while(ways){
        prev = ways;
        ways = ways->prox;
        freeStack(prev->stack);
        free(prev);
    }
}
