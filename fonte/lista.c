#include <stdlib.h>
#include "lista.h"

#define DIST_MAX 100

//Colocado para debug. A ser removido.
unsigned long qtdTotal = 0;

//Cria um nó contendo o valor informado.
static struct node *criarNo(enum personagem personagem)
{
    struct node *novoNo = malloc(sizeof(struct node)); qtdTotal++;
    novoNo->personagem = personagem;
    novoNo->distancia = 0;
    novoNo->prox = NULL;
    return novoNo;
}

//Insere um nó no início da lista.
static void inserirNo(struct node *lista, struct node *noInsere)
{
    noInsere->prox = lista->prox;
    lista->prox = noInsere;
}

//Cria a cabeça de uma nova lista.
struct node *criarLista(void) {return criarNo(Ninguem);}

// Desaloca toda a lista a partir do nó fornecido.
void liberarLista(struct node *lista)
{
    while(lista){
        struct node *prox = lista->prox;
        free(lista);
        lista = prox;
    }
}

// Atualiza a lista do histórico dos nomes lidos nas últimas 100 palavras.
// @param lista: Cabeça da lista.
// @param atraso: Número de palavras lidas desde a última atualização.
// @param persMencionado: Nome que acaba de ser lido.
// @param grafo: Matriz de adjacência do grafo.
void atualizarLista(struct node *lista, int atraso, enum personagem persMencionado, unsigned **grafo)
{
    struct node *ant = lista;
    struct node *node = lista->prox;

    while(node)
    {
        // Atualiza a distância.
        node->distancia += atraso;

        // Se o nome registrado na lista estiver a mais de 100 
        // palavras de distância da atual posição de leitura, libera
        // toda a lista a partir daquele ponto, pois todos os nomes seguintes
        // também estarão a mais de 100 palavras de distância.
        if(node->distancia > DIST_MAX){
            liberarLista(node);
            ant->prox = NULL;
            break;
        }

        // Se os dois nomes estão a uma distância <= 100 e são diferentes,
        // incrementa o peso da aresta entre eles.
        if(persMencionado != node->personagem){
            grafo[node->personagem][persMencionado]++;
            grafo[persMencionado][node->personagem]++;
        }

        ant = node;
        node = node->prox;
    }

    // Registra nome lido e insere-o na lista.
    inserirNo(lista,criarNo(persMencionado));
}