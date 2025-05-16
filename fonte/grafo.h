#ifndef _H_GRAFO
#define _H_GRAFO

unsigned **criarGrafo(int tam);
double **inverterArestas(unsigned **grafoInt, int tam);
void liberarGrafo(void **grafo, int tam);
int quantidadeArestas(double **grafo, int tam);

#endif