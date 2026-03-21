#include <stdio.h>
#include <Strlib.h>
#include <Funcoes.h>

// Inicializando
void inicializar(PONT* raiz) {
    *raiz = NULL;
}

// Criando nó
PONT criarNo(char nomeSobrenome, char nomeSobrenomeMae; char nomeSobrenomePai, char dataNascimento) {
    PONT novo = ;

}

PONT inserirPessoa (PONT raiz); {
    // Definimos um tamanho máximo para o nome 
    char nomeSobrenome[100];
    char nomeSobrenomeMae[100];
    char nomeSobrenomePai[100];
    char dataNascimento[10];

    printf("Digite o nome e sobrenome da pessoa: \n");

    if (fgets(nomeSobrenome, sizeof(nomeSobrenome), stdin)) {
        nomeSobrenome[strcspn(nomeSobrenome, "\n")] = '\0'; //strcspn retira o \n apos clicar enter
    };

    printf("Digite o nome e sobrenome da Mãe dessa pessoa: \n")

    if (fgets(nomeSobrenomeMae, sizeof(nomeSobrenomeMae), stdin)) {
        nomeSobrenomeMae[strcspn(nomeSobrenomeMae, "\n")] = '\0'; 
    };

    printf("Digite o nome e sobrenome do pai dessa pessoa: ")

    (fgets(nomeSobrenomePai, sizeof(nomeSobrenomePai), stdin)) {
        nomeSobrenomePai[strcspn(nomeSobrenomePai, "\n")] = '\0'; 
    };

    printf("Digite a data de nascimento dessa pessoa: \n Ex: xx/xx/xxxx \n")
}



int main() {

}