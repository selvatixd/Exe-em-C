#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    char nome[100];
    int quantidade;
    struct Produto* proximo;
} Produto;

Produto* cabeca = NULL;

void adicionarProduto(char* nome, int quantidade) {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    strcpy(novoProduto->nome, nome);
    novoProduto->quantidade = quantidade;
    novoProduto->proximo = cabeca;
    cabeca = novoProduto;
}

void removerProduto(char* nome, int quantidade) {
    Produto* atual = cabeca;
    Produto* anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Produto %s não encontrado.\n", nome);
        return;
    }

    if (atual->quantidade < quantidade) {
        printf("Quantidade insuficiente de %s. Disponível: %d.\n", nome, atual->quantidade);
        return;
    }

    atual->quantidade -= quantidade;

    if (atual->quantidade == 0) {
        if (anterior == NULL) {
            cabeca = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
        free(atual);
    }
}

void exibirProdutos() {
    Produto* atual = cabeca;
    if (atual == NULL) {
        printf("Estoque vazio.\n");
        return;
    }

    printf("Produtos disponíveis no estoque:\n");
    while (atual != NULL) {
        printf("Produto: %s, Quantidade: %d\n", atual->nome, atual->quantidade);
        atual = atual->proximo;
    }
}

int main() {
    int opcao;
    char nome[100];
    int quantidade;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar produto\n");
        printf("2. Remover produto\n");
        printf("3. Exibir produtos\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nome do produto: ");
                scanf(" %[^\n]", nome);
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                adicionarProduto(nome, quantidade);
                break;
            case 2:
                printf("Digite o nome do produto: ");
                scanf(" %[^\n]", nome);
                printf("Digite a quantidade a ser removida: ");
                scanf("%d", &quantidade);
                removerProduto(nome, quantidade);
                break;
            case 3:
                exibirProdutos();
                break;
            case 4:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);

    while (cabeca != NULL) {
        removerProduto(cabeca->nome, cabeca->quantidade);
    }

    return 0;
}

