#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "grafo.h"

extern const char* personagens[QTD_PERSONAGENS];

unsigned **criarGrafo(int tam)
{
    unsigned **grafo = malloc(tam*sizeof(unsigned*));
    for(int i = 0; i < tam; i++)
        grafo[i] = calloc(tam,sizeof(unsigned));

    return grafo;
}

void liberarGrafo(void **grafo, int tam)
{
    for(int i = 0; i < tam; i++)
        free(grafo[i]);
    free(grafo);
}

double **inverterArestas(unsigned **grafoInt, int tam)
{
    double **grafoDouble = malloc(tam*sizeof(double*));
    for(int i = 0; i < tam;i++)
        grafoDouble[i] = malloc(tam*sizeof(double));
    
    for(int i = 0; i < tam; i++)
        for(int j = 0; j < tam; j++)
            grafoDouble[i][j] = (grafoInt[i][j]) ? 1.0 / grafoInt[i][j] : INFINITY;
    return grafoDouble;
}

int quantidadeArestas(unsigned **grafo, int tam)
{
    int qtd = 0;
    
    for(int i = 0; i < tam; i++)
        for(int j = i + 1; j < tam; j++)
            if(grafo[i][j] > 0)
                qtd++;

    return qtd;
}

void gerarDot(double** grafo, int tam, const char* nomeArquivo, enum personagem persCentral)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        fprintf(stderr,"Erro ao abrir arquivo");
        exit(-3);
    }

    fprintf(arquivo, "graph G {\n");

    // Imprime todos os nós
    for (int i = 0; i < tam; ++i) {
        fprintf(arquivo, "    %s", personagens[i]);
        if(i == persCentral)
            fprintf(arquivo, " [color=red, style=filled]");
        else
            fprintf(arquivo, " [color=orange, style=filled]");
        fprintf(arquivo,";\n");
    }

    // Imprime as arestas sem duplicar (i < j)
    for (int i = 0; i < tam; ++i) {
        for (int j = i + 1; j < tam; ++j) {
            if (grafo[i][j] != INFINITY) {
                fprintf(arquivo, "    %s -- %s [label=\"%.3f\"];\n", 
                    personagens[i], personagens[j], grafo[i][j]);
            }
        }
    }

    fprintf(arquivo, "}\n");
    fclose(arquivo);
}