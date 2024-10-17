#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char nome[100];
    int pontuacao;
    struct Node* proximo;
} Node;

Node* lista = NULL;

void adicionarPontuacao(char* nome, int pontuacao) {
    Node* novo = (Node*)malloc(sizeof(Node));
    strcpy(novo->nome, nome);
    novo->pontuacao = pontuacao;
    novo->proximo = NULL;

    if (!lista || lista->pontuacao > pontuacao) {
        novo->proximo = lista;
        lista = novo;
        return;
    }

    Node* atual = lista;
    while (atual->proximo && atual->proximo->pontuacao < pontuacao) {
        atual = atual->proximo;
    }

    novo->proximo = atual->proximo;
    atual->proximo = novo;
}

void listarPontuacoes() {
    Node* atual = lista;
    if (!atual) {
        printf("Nenhuma pontuacao disponivel.\n");
        return;
    }

    printf("Pontuacoes registradas:\n");
    while (atual) {
        printf("Jogador: %s, Pontuacao: %d\n", atual->nome, atual->pontuacao);
        atual = atual->proximo;
    }
}

void removerJogador(char* nome) {
    Node* atual = lista;
    Node* anterior = NULL;

    while (atual && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) {
        printf("Jogador %s nao encontrado.\n", nome);
        return;
    }

    if (anterior) {
        anterior->proximo = atual->proximo;
    } else {
        lista = atual->proximo;
    }

    free(atual);
    printf("Pontuacao de %s removida.\n", nome);
}

int main() {
    int opcao;
    char nome[100];
    int pontuacao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar pontuacao\n");
        printf("2. Listar pontuacoes\n");
        printf("3. Remover jogador\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome do jogador: ");
                scanf(" %[^\n]", nome);
                printf("Pontuacao: ");
                scanf("%d", &pontuacao);
                adicionarPontuacao(nome, pontuacao);
                break;
            case 2:
                listarPontuacoes();
                break;
            case 3:
                printf("Nome do jogador a remover: ");
                scanf(" %[^\n]", nome);
                removerJogador(nome);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 4);

    while (lista) {
        removerJogador(lista->nome);
    }

    return 0;
}
