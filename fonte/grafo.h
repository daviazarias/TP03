#ifndef _H_GRAFO
#define _H_GRAFO

#include "lista.h"

unsigned **criarGrafo(int tam);
double **inverterArestas(unsigned **grafoInt, int tam);
void liberarGrafo(void **grafo, int tam);
int quantidadeArestas(unsigned **grafo, int tam);

void gerarDot(double** grafo, int tam,
    const char* nomeArquivo, enum personagem persCentral);

#endif