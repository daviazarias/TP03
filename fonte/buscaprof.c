#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void buscaProf(double **grafo, int vertice, bool *visitado, int tam)
{
    visitado[vertice] = true;
    for(int i = 0; i < tam; i++)
        if(!visitado[i] && grafo[vertice][i] != INFINITY)
            buscaProf(grafo,i,visitado,tam);
}

int componentesConexos(double **grafo, int tam)
{
    bool visitado[tam];
    int componentes = 0;

    for(int i = 0; i < tam; i++)
        visitado[i] = false;
    
    for(int i = 0; i < tam; i++)
        if(!visitado[i]){
            buscaProf(grafo,i,visitado,tam);
            componentes++;
        }

    return componentes;
}