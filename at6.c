#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char nome[100];
    float valor;
    struct Item* proximo;
} Item;

Item* listaProdutos = NULL;

void adicionarProduto(char* nome, float valor) {
    Item* novoItem = (Item*)malloc(sizeof(Item));
    strcpy(novoItem->nome, nome);
    novoItem->valor = valor;
    novoItem->proximo = NULL;

    if (listaProdutos == NULL || listaProdutos->valor > valor) {
        novoItem->proximo = listaProdutos;
        listaProdutos = novoItem;
        return;
    }

    Item* atual = listaProdutos;
    while (atual->proximo != NULL && atual->proximo->valor < valor) {
        atual = atual->proximo;
    }

    novoItem->proximo = atual->proximo;
    atual->proximo = novoItem;
}
void listarProdutos() {
    Item* atual = listaProdutos;
    if (atual == NULL) {
        printf("Não há produtos disponíveis.\n");
        return;
    }

    printf("Lista de produtos:\n");
    while (atual != NULL) {
        printf("Produto: %s, Preço: R$ %.2f\n", atual->nome, atual->valor);
        atual = atual->proximo;
    }
}

void excluirProduto(char* nome) {
    Item* atual = listaProdutos;
    Item* anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Produto %s não encontrado.\n", nome);
        return;
    }

    if (anterior == NULL) {
        listaProdutos = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Produto %s removido com sucesso.\n", nome);
}

int main() {
    int opcao;
    char nome[100];
    float valor;

    do {
        printf("\nMenu de Compras:\n");
        printf("1. Adicionar produto\n");
        printf("2. Listar produtos\n");
        printf("3. Excluir produto\n");
        printf("4. Sair\n");
        printf("Selecione uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome do produto: ");
                scanf(" %[^\n]", nome);
                printf("Preço do produto: ");
                scanf("%f", &valor);
                adicionarProduto(nome, valor);
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                printf("Nome do produto a excluir: ");
                scanf(" %[^\n]", nome);
                excluirProduto(nome);
                break;
            case 4:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
        }
    } while (opcao != 4);

    while (listaProdutos != NULL) {
        excluirProduto(listaProdutos->nome);
    }

    return 0;
}