#include "betweeness.h"

// Retorna a quantidade de caminhos presentes na lista "caminhos".
static int qtdCaminhos(NoNoInt* caminhos){
    int quantidade = 0;
    for(;caminhos;caminhos=caminhos->prox) quantidade++;
    return quantidade;
}

// Retorna o índice do maior elemento no vetor "v".
static int maiorElemento(double *v, int tam){
    int maior = 0;

    for(int i = 1; i < tam; i++)
        if(v[i] > v[maior])
            maior = i;

    return maior;
}

// Atualiza o vetor de centralidade de acordo com o caminho representado
// em "lista". O primeiro e o último valor da lista não são considerados.
static void atualizaCentralidade(NoInt* lista, int *centralidade){
    lista = lista->prox;
    while(lista->prox){
        centralidade[lista->data]++;
        lista = lista->prox;
    }
}

// Preenche o vetor "betweeness" com os índices de betweeness de cada 
// vértice presente na lista de caminhos, retornando o índice com
// o maior valor de betweeness.
enum personagem calculaBetweeness(NoNoInt* caminhos, double* betweeness){

    int centralidade[QTD_PERSONAGENS];

    int qtdCaminhosMin = qtdCaminhos(caminhos);

    for(int i = 0; i < QTD_PERSONAGENS; i++){
        centralidade[i] = 0; 
        betweeness[i] = 0.0;
    }

    while(caminhos){
        atualizaCentralidade(caminhos->stack,centralidade);
        caminhos = caminhos->prox;
    }

    for(int i = 0; i < QTD_PERSONAGENS; i++)
        betweeness[i] = (double) centralidade[i] / qtdCaminhosMin;

    return maiorElemento(betweeness,QTD_PERSONAGENS);
}
