#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 100

typedef struct {
    int codigo;
    char titulo[50];
} Livro;

typedef struct {
    Livro livros[MAX_LIVROS];
    int total;
} Biblioteca;

void inicializarBiblioteca(Biblioteca *b) {
    b->total = 0;
}

void adicionarLivro(Biblioteca *b, int codigo, char titulo[]) {
    if (b->total < MAX_LIVROS) {
        b->livros[b->total].codigo = codigo;
        strcpy(b->livros[b->total].titulo, titulo);
        b->total++;
    }
}

void exibirLivros(Biblioteca *b) {
    if (b->total > 0) {
        for (int i = 0; i < b->total; i++) {
            printf("Código: %d, Título: %s\n", b->livros[i].codigo, b->livros[i].titulo);
        }
    }
}

void removerLivro(Biblioteca *b, int codigo) {
    for (int i = 0; i < b->total; i++) {
        if (b->livros[i].codigo == codigo) {
            for (int j = i; j < b->total - 1; j++) {
                b->livros[j] = b->livros[j + 1];
            }
            b->total--;
            break;
        }
    }
}

int main() {
    Biblioteca biblioteca;
    inicializarBiblioteca(&biblioteca);

    int opcao, codigo;
    char titulo[50];

    do {
        printf("\n----- Gerenciamento de Acervo -----\n");
        printf("1. Adicionar novo livro\n");
        printf("2. Exibir todos os livros\n");
        printf("3. Remover livro danificado\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o código do livro: ");
                scanf("%d", &codigo);
                printf("Digite o título do livro: ");
                scanf(" %[^\n]s", titulo);
                adicionarLivro(&biblioteca, codigo, titulo);
                break;
            case 2:
                exibirLivros(&biblioteca);
                break;
            case 3:
                printf("Digite o código do livro a ser removido: ");
                scanf("%d", &codigo);
                removerLivro(&biblioteca, codigo);
                break;
            case 0:
                printf("fechando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
