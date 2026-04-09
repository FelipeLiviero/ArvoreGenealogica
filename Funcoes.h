#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia, mes, ano;
} ANIVERSARIO;

typedef struct no {
    char nomeSobrenome[100];
    char nomeMae[100];
    char nomePai[100];
    ANIVERSARIO aniversario;

    struct no *ptrPai;
    struct no *ptrMae;
    struct no *irmaoMaisNovo;
    struct no *irmaoMaisVelho;
} NO, *PONT;

void inicializar   (PONT *raiz);
PONT criarNo       (const char *nome, const char *mae,
                    const char *pai,  ANIVERSARIO niver);
PONT inserirPessoa (PONT raiz);
PONT removerPessoa (PONT raiz, const char *nomeAlvo);
PONT buscarPessoa  (PONT raiz, const char *nome);
void imprimirNo    (PONT p);
void imprimirArvore(PONT raiz);
void imprimirPai   (PONT raiz, const char *nome);
void imprimirMae   (PONT raiz, const char *nome);
void imprimirIrmaos(PONT raiz, const char *nome);
void liberarArvore (PONT raiz);

#endif
