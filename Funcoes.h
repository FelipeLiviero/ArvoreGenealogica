#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct {
    int dia, mes, ano;
} ANIVERSARIO;

typedef struct no {
    char nomeSobrenome[100];           
    char nomeMae[100];
    char nomePai[100];
    ANIVERSARIO aniversario;
    
    struct no* nomeSobrenomePai;          
    struct no* NomeSobrenomeMae;           
    struct no* irmaoMaisNovo;  
    struct no* irmaoMaisVelho;
} NO, *PONT;

void inicializar(PONT* raiz);
PONT criarNo(); 
PONT inserirPessoa(PONT raiz); 
void imprimirArvore(PONT raiz);

#endif