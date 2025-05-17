#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "grafo.h"

extern const char* personagens[QTD_PERSONAGENS];

// Aloca uma matriz de adjacências para um grafo de dimensão "tam".
unsigned **criarGrafo(int tam)
{
    unsigned **grafo = malloc(tam*sizeof(unsigned*));
    for(int i = 0; i < tam; i++)
        grafo[i] = calloc(tam,sizeof(unsigned));

    return grafo;
}

// Desaloca a matriz de adjacências do grafo.
void liberarGrafo(void **grafo, int tam)
{
    for(int i = 0; i < tam; i++)
        free(grafo[i]);
    free(grafo);
}

// Inverte os valores de uma matriz de inteiros g0, gerando uma matriz
// de ponto flutuante g1, calculando o valor do número inverso para
// cada número em g0. (inverso de 0 é infinito)
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

// Retorna o número de arestas na matriz de adjacências "grafo".
int quantidadeArestas(unsigned **grafo, int tam)
{
    int qtd = 0;
    
    for(int i = 0; i < tam; i++)
        for(int j = i + 1; j < tam; j++)
            if(grafo[i][j] > 0)
                qtd++;

    return qtd;
}

// Gera um arquivo .dot correspondente ao grafo cuja matriz de adjacências
// é passada como parâmetro. O vértice correspondente a "persCentral" é
// colorido de vermelho, enquanto os demais são coloridos de laranja. 
void gerarDot(double** grafo, int tam, const char* nomeArquivo, enum personagem persCentral)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        fprintf(stderr,"Erro ao abrir arquivo");
        exit(-3);
    }

    fprintf(arquivo, "graph G {\n");

    // Imprime todos os nós
    for (int i = 0; i < tam; i++) {
        fprintf(arquivo, "    %s [color=", personagens[i]);
        if(i == persCentral)
            fprintf(arquivo, "red");
        else
            fprintf(arquivo, "orange");
        fprintf(arquivo,", style=filled];\n");
    }

    // Imprime as arestas sem duplicar (i < j)
    for (int i = 0; i < tam; i++) {
        for (int j = i + 1; j < tam; j++) {
            if (grafo[i][j] != INFINITY) {
                fprintf(arquivo, "    %s -- %s [label=\"%.3f\"];\n", 
                    personagens[i], personagens[j], grafo[i][j]);
            }
        }
    }

    fprintf(arquivo, "}\n");
    fclose(arquivo);
}