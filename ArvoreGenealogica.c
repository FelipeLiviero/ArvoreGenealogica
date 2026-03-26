#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcoes.h" 

// Inicializando
void inicializar(PONT* raiz) {
    *raiz = NULL;
}

// Criando nó 
PONT criarNo(char* nomeSobrenome, char* nomeSobrenomeMae, char* NomeSobrenomePai, ANIVERSARIO niver) {
    PONT novo = (PONT)malloc(sizeof(NO));
    if (novo) {
        strcpy(novo->nome, nome);
        strcpy(novo->nomeMae, mae);
        strcpy(novo->nomePai, pai);
        novo->aniversario = niver;
        novo->contador = 1;
        novo->irmaoMaisNovo = NULL;
        novo->irmaoMaisVelho = NULL;
    }
    return novo;
}

// Inserindo pessoa
PONT inserirPessoa(PONT raiz) {
    char nome[100], mae[100], pai[100], dataStr[15];
    ANIVERSARIO niver;

    printf("Digite o nome e sobrenome da pessoa: ");
    fgets(nome, 100, stdin); nome[strcspn(nome, "\n")] = '\0';

    printf("Digite o nome da Mãe: ");
    fgets(mae, 100, stdin); mae[strcspn(mae, "\n")] = '\0';

    printf("Digite o nome do Pai: ");
    fgets(pai, 100, stdin); pai[strcspn(pai, "\n")] = '\0';

    printf("Digite a data (dd/mm/aaaa): ");
    fgets(dataStr, 15, stdin);
    
    if (sscanf(dataStr, "%d/%d/%d", &niver.data, &niver.mes, &niver.ano) != 3) {
        printf("Erro: Formato de data invalido!\n");
        return raiz;
    }

    PONT novoNo = criarNo(nome, mae, pai, niver);

    if (raiz == NULL) return novoNo;

    PONT atual = raiz;
    while (atual->irmaoMaisNovo != NULL) atual = atual->irmaoMaisNovo;
    atual->irmaoMaisNovo = novoNo;
    novoNo->irmaoMaisVelho = atual;

    return raiz; 
}

// Removendo pessoa 
PONT removerPessoa(PONT raiz, char* nomeAlvo) {
    if (raiz == NULL) return NULL;

    // Se achou a pessoa
    if (strcmp(nomeAlvo, raiz->nome) == 0) {
        PONT temp = raiz->irmaoMaisNovo;
        free(raiz);
        return temp;
    }
    
    // Se não achou
    raiz->irmaoMaisNovo = removerPessoa(raiz->irmaoMaisNovo, nomeAlvo);
    return raiz;
}

int main() {
    PONT raiz;
    inicializar(&raiz);
    
    raiz = inserirPessoa(raiz);
    
    printf("\nPessoa inserida: %s\n", raiz->nome);
    
    return 0;
}