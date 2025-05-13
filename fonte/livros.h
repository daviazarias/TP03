#ifndef _H_LIVROS
#define _H_LIVROS

#define LIVRO_PADRAO 3
#define QTD_LIVROS 5

#define DIRETORIO_LIVROS "./livros/"

#define GUERRA_DOS_TRONOS   DIRETORIO_LIVROS "A-Game-Of-Thrones.txt"
#define FURIA_DOS_REIS      DIRETORIO_LIVROS "A-Clash-of-Kings.txt"
#define TORMENTA_DE_ESPADAS DIRETORIO_LIVROS "A-Storm-of-Swords.txt"
#define FESTIM_DOS_CORVOS   DIRETORIO_LIVROS "A-Feast-for-Crows.txt"
#define DANCA_DOS_DRAGOES   DIRETORIO_LIVROS "A-Dance-With-Dragons.txt"

struct livro {
    char* caminho;
    char* nome;
};
    
#endif