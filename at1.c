#include <stdio.h>
#include <stdlib.h>

#define MAX_PEDIDOS 20

typedef struct {
    int pedidos[MAX_PEDIDOS];
    int inicio;
    int fim;
} FilaPedidos;

void inicializarFila(FilaPedidos *fila) {
    fila->inicio = 0;
    fila->fim = 0;
}

int filaVazia(FilaPedidos *fila) {
    return fila->inicio == fila->fim;
}

int filaCheia(FilaPedidos *fila) {
    return fila->fim == MAX_PEDIDOS;
}

void adicionarPedido(FilaPedidos *fila, int pedido) {
    if (!filaCheia(fila)) {
        fila->pedidos[fila->fim] = pedido;
        fila->fim++;
    }
}

void removerPedido(FilaPedidos *fila) {
    if (!filaVazia(fila)) {
        fila->inicio++;
    }
}

void exibirPedidos(FilaPedidos *fila) {
    if (!filaVazia(fila)) {
        for (int i = fila->inicio; i < fila->fim; i++) {
            printf("Pedido %d\n", fila->pedidos[i]);
        }
    }
}

int main() {
    FilaPedidos fila;
    inicializarFila(&fila);

    int opcao, pedido;

    do {
        printf("\n----- Gerenciamento de Pedidos -----\n");
        printf("1. Adicionar novo pedido\n");
        printf("2. Exibir todos os pedidos\n");
        printf("3. Remover pedido atendido\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o número do pedido: ");
                scanf("%d", &pedido);
                adicionarPedido(&fila, pedido);
                break;
            case 2:
                exibirPedidos(&fila);
                break;
            case 3:
                removerPedido(&fila);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
