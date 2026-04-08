#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcoes.h"

static void lerLinha(char *buf, int tam)
{
    if (fgets(buf, tam, stdin))
        buf[strcspn(buf, "\n")] = '\0';
}

static void vincularFilhos(PONT raiz, PONT alvo)
{
    for (PONT p = raiz; p != NULL; p = p->irmaoMaisNovo) {
        if (strcmp(p->nomePai, alvo->nomeSobrenome) == 0)
            p->ptrPai = alvo;
        if (strcmp(p->nomeMae, alvo->nomeSobrenome) == 0)
            p->ptrMae = alvo;
    }
}

void inicializar(PONT *raiz)
{
    *raiz = NULL;
}

PONT criarNo(const char *nome, const char *mae,
             const char *pai,  ANIVERSARIO niver)
{
    PONT novo = (PONT)malloc(sizeof(NO));
    if (!novo) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(novo->nomeSobrenome, nome, 99); novo->nomeSobrenome[99] = '\0';
    strncpy(novo->nomeMae,       mae,  99); novo->nomeMae[99]       = '\0';
    strncpy(novo->nomePai,       pai,  99); novo->nomePai[99]       = '\0';
    novo->aniversario  = niver;
    novo->ptrPai       = NULL;
    novo->ptrMae       = NULL;
    novo->irmaoMaisNovo   = NULL;
    novo->irmaoMaisVelho  = NULL;
    return novo;
}

PONT inserirPessoa(PONT raiz)
{
    char nome[100], mae[100], pai[100], dataStr[15];
    ANIVERSARIO niver;

    printf("  Nome e sobrenome : "); lerLinha(nome, 100);
    printf("  Nome da mae      : "); lerLinha(mae,  100);
    printf("  Nome do pai      : "); lerLinha(pai,  100);
    printf("  Data (dd/mm/aaaa): "); lerLinha(dataStr, 15);

    if (sscanf(dataStr, "%d/%d/%d", &niver.dia, &niver.mes, &niver.ano) != 3) {
        printf("  Erro: formato de data invalido! Use dd/mm/aaaa.\n");
        return raiz;
    }

    if (buscarPessoa(raiz, nome) != NULL) {
        printf("  Aviso: '%s' ja esta na lista.\n", nome);
        return raiz;
    }

    PONT novo = criarNo(nome, mae, pai, niver);

    if (raiz == NULL) {
        raiz = novo;
    } else {
        PONT atual = raiz;
        while (atual->irmaoMaisNovo != NULL)
            atual = atual->irmaoMaisNovo;
        atual->irmaoMaisNovo = novo;
        novo->irmaoMaisVelho = atual;
    }

    novo->ptrPai = buscarPessoa(raiz, pai);
    novo->ptrMae = buscarPessoa(raiz, mae);

    vincularFilhos(raiz, novo);

    printf("  '%s' inserido(a) com sucesso.\n", nome);
    return raiz;
}

PONT buscarPessoa(PONT raiz, const char *nome)
{
    for (PONT p = raiz; p != NULL; p = p->irmaoMaisNovo)
        if (strcmp(p->nomeSobrenome, nome) == 0)
            return p;
    return NULL;
}

PONT removerPessoa(PONT raiz, const char *nomeAlvo)
{
    PONT alvo = buscarPessoa(raiz, nomeAlvo);
    if (!alvo) {
        printf("  '%s' nao encontrado(a).\n", nomeAlvo);
        return raiz;
    }

    for (PONT p = raiz; p != NULL; p = p->irmaoMaisNovo) {
        if (p->ptrPai == alvo) p->ptrPai = NULL;
        if (p->ptrMae == alvo) p->ptrMae = NULL;
    }

    if (alvo->irmaoMaisVelho)
        alvo->irmaoMaisVelho->irmaoMaisNovo = alvo->irmaoMaisNovo;
    if (alvo->irmaoMaisNovo)
        alvo->irmaoMaisNovo->irmaoMaisVelho = alvo->irmaoMaisVelho;

    if (raiz == alvo)
        raiz = alvo->irmaoMaisNovo;

    printf("  '%s' removido(a) com sucesso.\n", alvo->nomeSobrenome);
    free(alvo);
    return raiz;
}

void imprimirNo(PONT p)
{
    if (!p) return;
    printf("  ┌─────────────────────────────────────────\n");
    printf("  │ Nome      : %s\n",  p->nomeSobrenome);
    printf("  │ Pai       : %s%s\n", p->nomePai[0] ? p->nomePai : "(nao informado)",
                                     p->ptrPai ? " [na lista]" : "");
    printf("  │ Mae       : %s%s\n", p->nomeMae[0] ? p->nomeMae : "(nao informado)",
                                     p->ptrMae ? " [na lista]" : "");
    printf("  │ Nascimento: %02d/%02d/%04d\n",
           p->aniversario.dia, p->aniversario.mes, p->aniversario.ano);
    printf("  └─────────────────────────────────────────\n");
}

void imprimirArvore(PONT raiz)
{
    printf("\n   LISTA COMPLETA \n");
    if (!raiz) { printf("  (vazia)\n\n"); return; }
    for (PONT p = raiz; p != NULL; p = p->irmaoMaisNovo)
        imprimirNo(p);
    printf("\n");
}

void imprimirPai(PONT raiz, const char *nome)
{
    PONT p = buscarPessoa(raiz, nome);
    if (!p) { printf("  '%s' nao encontrado(a).\n", nome); return; }

    printf("\n  ═══ PAI de %s ═══\n", nome);
    if (p->ptrPai)
        imprimirNo(p->ptrPai);
    else if (p->nomePai[0])
        printf("  Pai registrado como '%s', mas nao esta na lista.\n", p->nomePai);
    else
        printf("  Pai nao informado.\n");
}

void imprimirMae(PONT raiz, const char *nome)
{
    PONT p = buscarPessoa(raiz, nome);
    if (!p) { printf("  '%s' nao encontrado(a).\n", nome); return; }

    printf("\n  ═══ MAE de %s ═══\n", nome);
    if (p->ptrMae)
        imprimirNo(p->ptrMae);
    else if (p->nomeMae[0])
        printf("  Mae registrada como '%s', mas nao esta na lista.\n", p->nomeMae);
    else
        printf("  Mae nao informada.\n");
}

void imprimirIrmaos(PONT raiz, const char *nome)
{
    PONT p = buscarPessoa(raiz, nome);
    if (!p) { printf("  '%s' nao encontrado(a).\n", nome); return; }

    printf("\n  ═══ IRMAOS de %s ═══\n", nome);

    int achou = 0;
    for (PONT q = raiz; q != NULL; q = q->irmaoMaisNovo) {
        if (q == p) continue;
        int mesmoPai = p->nomePai[0] && strcmp(p->nomePai, q->nomePai) == 0;
        int mesmaMae = p->nomeMae[0] && strcmp(p->nomeMae, q->nomeMae) == 0;
        if (mesmoPai || mesmaMae) {
            imprimirNo(q);
            achou = 1;
        }
    }
    if (!achou) printf("  Nenhum irmao encontrado na lista.\n");
}

int main(void)
{
    PONT raiz;
    inicializar(&raiz);

    int opcao;
    char nome[100];

    printf("     ARVORE GENEALOGICA           \n");

    do {
        printf("\n  1. Inserir pessoa\n");
        printf("  2. Remover pessoa\n");
        printf("  3. Buscar pessoa\n");
        printf("  4. Imprimir todos\n");
        printf("  5. Imprimir pai\n");
        printf("  6. Imprimir mae\n");
        printf("  7. Imprimir irmaos\n");
        printf("  0. Sair\n");
        printf("  Opcao: ");
        scanf("%d", &opcao);
        getchar(); /* consome '\n' deixado pelo scanf */

        switch (opcao) {
            case 1:
                printf("\n Inserir \n");
                raiz = inserirPessoa(raiz);
                break;

            case 2:
                printf("\n Remover \n");
                printf("  Nome a remover: "); lerLinha(nome, 100);
                raiz = removerPessoa(raiz, nome);
                break;

            case 3:
                printf("\n Buscar \n");
                printf("  Nome a buscar: "); lerLinha(nome, 100);
                PONT res = buscarPessoa(raiz, nome);
                if (res) imprimirNo(res);
                else printf("  '%s' nao encontrado(a).\n", nome);
                break;

            case 4:
                imprimirArvore(raiz);
                break;

            case 5:
                printf("  Nome da pessoa: "); lerLinha(nome, 100);
                imprimirPai(raiz, nome);
                break;

            case 6:
                printf("  Nome da pessoa: "); lerLinha(nome, 100);
                imprimirMae(raiz, nome);
                break;

            case 7:
                printf("  Nome da pessoa: "); lerLinha(nome, 100);
                imprimirIrmaos(raiz, nome);
                break;

            case 0:
                printf("  Encerrando...\n");
                break;

            default:
                printf("  Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberarArvore(raiz);
    return 0;
}
