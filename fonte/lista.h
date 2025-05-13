#ifndef _H_LISTA
#define _H_LISTA

#define QTD_PERSONAGENS 10

enum personagem 
{ Ninguem = -1
, Arya    // 0
, Sam     // 1
, Bran    // 2
, Jaime   // 3
, Sansa   // 4  
, Brienne // 5
, Catelyn // 6
, Tyrion  // 7
, Cersei  // 8
, Varys   // 9
};

// Lista encadeada que registra os nomes lidos nas 100 últimas palavras.
struct node {
    enum personagem personagem; 
    int distancia;
    struct node *prox;
};

struct node *criarLista(void);
void atualizarLista(struct node *lista, int atraso, enum personagem persMencionado, unsigned **grafo);
void liberarLista(struct node* lista);

#endif