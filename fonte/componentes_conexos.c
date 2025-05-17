#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"
#include "componentes_conexos.h"

// Função para visitar um componente conexo usando DFS (Depth-First Search)
static void dfs(unsigned **grafo, int vertice, int tam, bool *visitado) {
    visitado[vertice] = true; // Marca o vértice como visitado

    // Itera sobre todos os vértices adjacentes ao vértice atual
    for (int i = 0; i < tam; i++) {
        // Se há uma aresta entre o vértice atual e o vértice 'i'
        // E 'i' não foi visitado, visita 'i' recursivamente
        if (grafo[vertice][i] > 0 && !visitado[i]) {
            dfs(grafo, i, tam, visitado);
        }
    }
}

// Função para contar o número de componentes conexos em um grafo
int contarComponentesConexos(unsigned **grafo, int tam) {
    bool *visitado = calloc(tam, sizeof(bool)); // Array para rastrear vértices visitados
    int numComponentes = 0;

    // Itera sobre todos os vértices do grafo
    for (int i = 0; i < tam; i++) {
        // Se o vértice não foi visitado, encontramos um novo componente conexo
        if (!visitado[i]) {
            dfs(grafo, i, tam, visitado); // Visita o componente usando DFS
            numComponentes++;
        }
    }

    free(visitado); // Libera a memória alocada para o array 'visitado'
    return numComponentes;
}