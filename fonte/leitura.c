#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "lista.h"
#include "grafo.h"

#define TAM_BUF 64

// Verifica se as strings a e b são "iguais", desconsiderando
// eventuais caracteres sobressalentes na string a.
// Isso é necessário para detectar uso de pronome possessivo no inglês.
// NÃO é comutativa.
// Exemplo: compararStrings("Sansas","Sansa") = true.
static bool compararStrings(const char *a, const char *b)
{
    for(int i = 0; b[i]; i++)
        if(a[i] != b[i]) return false;

    return true;
}

// Caso a string "nome" seja igual a alguma string em "personagens",
// retorna o termo da enumeração associada a ela.
// Caso contrário, retorna um elemento especial da enumeração: Ninguem.
static enum personagem personagemMencionado(const char *nome)
{
    static const char* personagens[QTD_PERSONAGENS] = 
    {"Arya", "Sam", "Bran", "Jaime", "Sansa", "Brienne", "Catelyn", "Tyrion", "Cersei", "Varys"};

    for(int i = 0; i < QTD_PERSONAGENS; i++)
        if(compararStrings(nome,personagens[i]))
            return i;

    return Ninguem;
}

// Remove os caracteres não-alfabéticos da string "a".
static void extrairNome(char *a)
{
	int j = 0;
    for(int i = 0; a[i]; i++)
        if(a[i] >= 'A' && a[i] <= 'z')
            a[j++] = a[i];
	a[j] = 0;
}

// Gera o grafo a partir da leitura do arquivo.
unsigned **lerArquivo(FILE *arq)
{
    unsigned **grafo = criarGrafo(QTD_PERSONAGENS);
    struct node *lista = criarLista(); 

    char palavra[TAM_BUF];

    // Quantidade de palavras lidas desde a última atualização da lista.
    int atraso = 0;
    
    while(EOF != fscanf(arq,"%s",palavra))
    {
        // Remove os caracteres não-alfabéticos da palavra lida.
        // Caso essa remoção resulte em uma string vazia, não contabiliza palavra lida.
        extrairNome(palavra);
        if(!(*palavra)) continue;

        atraso++;

        // Verifica se a palavra lida é uma das palavras buscadas.
        enum personagem personagem = personagemMencionado(palavra);

        // Atualiza a lista e zera o contador sempre que uma das palavras buscadas for lida.
        if(personagem != Ninguem){
            atualizarLista(lista,atraso,personagem,grafo);
            atraso = 0;
        }
    }

    liberarLista(lista); 
    fclose(arq);

    return grafo;
}
