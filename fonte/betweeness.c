#include "betweeness.h"

static int qtdCaminhos(NoNoInt* caminhos){
    int quantidade = 0;
    for(;caminhos;caminhos=caminhos->prox) quantidade++;
    return quantidade;
}

static int maiorElemento(double *v, int tam){
    int maior = 0;

    for(int i = 1; i < tam; i++)
        if(v[i] > v[maior])
            maior = i;

    return maior;
}

static void exploraPilha(NoInt* pilha, int *centralidade){
    pilha = pilha->prox;
    while(pilha->prox){
        centralidade[pilha->data]++;
        pilha = pilha->prox;
    }
}

enum personagem personagemCentral(NoNoInt* caminhos, double* betweeness){

    int centralidade[QTD_PERSONAGENS];

    int qtdCaminhosMin = qtdCaminhos(caminhos);

    for(int i = 0; i < QTD_PERSONAGENS; i++){
        centralidade[i] = 0; 
        betweeness[i] = 0.0;
    }

    while(caminhos){
        exploraPilha(caminhos->stack,centralidade);
        caminhos = caminhos->prox;
    }

    for(int i = 0; i < QTD_PERSONAGENS; i++)
        betweeness[i] = (double) centralidade[i] / qtdCaminhosMin;

    return maiorElemento(betweeness,QTD_PERSONAGENS);
}
