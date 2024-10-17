#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nome[50];
} Visitante;

typedef struct {
    Visitante visitantes[MAX];
    int inicio;
    int fim;
} Fila;

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
}

int filaVazia(Fila *fila) {
    return fila->inicio == fila->fim;
}

int filaCheia(Fila *fila) {
    return fila->fim == MAX;
}

void inserirVisitante(Fila *fila, char nome[]) {
    if (filaCheia(fila)) {
        printf("A fila está cheia! Não é possível inserir mais visitantes.\n");
    } else {
        strcpy(fila->visitantes[fila->fim].nome, nome);
        fila->fim++;
        printf("Visitante %s adicionado à fila.\n", nome);
    }
}

void removerVisitante(Fila *fila) {
    if (filaVazia(fila)) {
        printf("A fila está vazia! Nenhum visitante para remover.\n");
    } else {
        printf("Visitante %s saiu da fila.\n", fila->visitantes[fila->inicio].nome);
        fila->inicio++;
    }
}

void exibirFila(Fila *fila) {
    if (filaVazia(fila)) {
        printf("A fila está vazia.\n");
    } else {
        printf("Visitantes na fila:\n");
        for (int i = fila->inicio; i < fila->fim; i++) {
            printf("%d. %s\n", i - fila->inicio + 1, fila->visitantes[i].nome);
        }
    }
}

int main() {
    Fila fila;
    inicializarFila(&fila);

    int opcao;
    char nome[50];

    do {
        printf("\n1. Adicionar visitante\n");
        printf("2. Remover visitante\n");
        printf("3. Exibir fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o nome do visitante: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                inserirVisitante(&fila, nome);
                break;
            case 2:
                removerVisitante(&fila);
                break;
            case 3:
                exibirFila(&fila);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
