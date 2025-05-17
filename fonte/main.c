#include <stdio.h>
#include <stdlib.h>
#include "componentes_conexos.h"
#include "betweeness.h"
#include "dijkstra.h"
#include "leitura.h"
#include "livros.h"
#include "lista.h"
#include "grafo.h"

extern const char* personagens[QTD_PERSONAGENS];

static void exibirSaida(unsigned**,double**,char*,double*,int,int);
static void exibirMatriz(unsigned**,int);
static void exibirGrafoD(double**,int);
static void exibirBetweeness(double*,int);

static const struct livro livros[QTD_LIVROS] = 
    { GUERRA_DOS_TRONOS, "A Guerra dos Tronos",
      FURIA_DOS_REIS, "A Fúria dos Reis",
      TORMENTA_DE_ESPADAS, "A Tormenta de Espadas",
      FESTIM_DOS_CORVOS, "O Festim dos Corvos",
      DANCA_DOS_DRAGOES, "A Dança dos Dragões"};

/*------------------------------------------MÉTODO MAIN-------------------------------------------*/

int main(int argc, char **argv)
{
    // Por padrão, lê o livro 3, mas o primeiro argumento em
    // linha de comando seleciona um dos 5 livros.
    int num = (argc < 2) ? LIVRO_PADRAO : atoi(argv[1]);
    if(num < 1 || num > QTD_LIVROS){
        printf("O argumento precisa ser um número entre 1 e %d:\n\n", QTD_LIVROS);
        for(int i = 0; i < QTD_LIVROS; i++)
            printf("%s\n", livros[i].nome);
        return -1;
    }

    FILE *arq = fopen(livros[num-1].caminho,"r");
    if(!arq){
        printf("\nERRO: Arquivo %s não encontrado.\n\n", livros[num-1].caminho); 
        return -2;
    }

    unsigned **grafoInt = lerArquivo(arq);
    double **grafoDouble = inverterArestas(grafoInt,QTD_PERSONAGENS);
    NoNoInt *caminhos = completeDijkstra(QTD_PERSONAGENS, grafoDouble);

    double betweeness[QTD_PERSONAGENS];
    calculaBetweeness(caminhos,betweeness);

    int numComponentes = contarComponentesConexos(grafoInt, QTD_PERSONAGENS);
    int numArestas = quantidadeArestas(grafoDouble,QTD_PERSONAGENS);
    int circuitRank = (numArestas - QTD_PERSONAGENS + numComponentes);

    exibirSaida(grafoInt,grafoDouble,livros[num-1].nome,betweeness,
        QTD_PERSONAGENS,circuitRank);

    freeWays(caminhos);
    liberarGrafo((void**) grafoInt,QTD_PERSONAGENS);
    liberarGrafo((void**) grafoDouble,QTD_PERSONAGENS);

    return 0;
}

/*-------------------------------FUNÇÕES PARA EXIBIR NA SAÍDA PADRÃO--------------------------------*/

static void exibirSaida(unsigned **grafoInt, double **grafoDouble, 
    char *nomeDoLivro, double *betweeness, int tam, int circuitRank)
{
    printf("\n\t\t\t\t\tLIVRO: %s\n\n", nomeDoLivro);
    puts("             Arya   |   Sam   |  Bran   |  Jaime  |  Sansa  | Brienne | Catelyn | Tyrion  |  Cersei  |  Varys  ");
    exibirMatriz(grafoInt,tam);    putchar('\n');
    exibirGrafoD(grafoDouble,tam); putchar('\n');
    exibirBetweeness(betweeness, tam);
}

static char* nomes[QTD_PERSONAGENS] = {"Arya   ", "Sam    ", "Bran   ", "Jaime  ", "Sansa  ",
    "Brienne", "Catelyn", "Tyrion ", "Cersei ", "Varys  "};

// Gambiarra pra exibir a matriz na saída padrão.
static void exibirMatriz(unsigned** matriz, int tam)
{
    for(int i = 0; i < tam; i++){
        printf("%s", nomes[i]);
        for(int j = 0; j < tam; j++)
           printf("%10d", matriz[i][j]);
        putchar('\n');
    }
}

static void exibirBetweeness(double *b, int tam){
    for(int i = 0; i < tam; i++)
        printf("b[%s] = %lf\n", personagens[i], b[i]);
    putchar('\n');
}

static void exibirGrafoD(double **grafoD, int tam)
{
    for(int i = 0; i < tam; i++){
        printf("%s    ", nomes[i]);
        for(int j = 0; j < tam; j++)
            printf("%9lf ",grafoD[i][j]);
        putchar('\n');
    }
}