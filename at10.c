#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Encomenda {
    char descricao[100];
    float distancia;
    struct Encomenda* proxima;
} Encomenda;

Encomenda* cabeca = NULL;

void inserirEncomenda(char* descricao, float distancia) {
    Encomenda* novaEncomenda = (Encomenda*)malloc(sizeof(Encomenda));
    strcpy(novaEncomenda->descricao, descricao);
    novaEncomenda->distancia = distancia;
    novaEncomenda->proxima = NULL;

    if (cabeca == NULL || cabeca->distancia > distancia) {
        novaEncomenda->proxima = cabeca;
        cabeca = novaEncomenda;
        return;
    }

    Encomenda* atual = cabeca;
    while (atual->proxima != NULL && atual->proxima->distancia < distancia) {
        atual = atual->proxima;
    }

    novaEncomenda->proxima = atual->proxima;
    atual->proxima = novaEncomenda;
}

void exibirEncomendas() {
    Encomenda* atual = cabeca;
    if (atual == NULL) {
        printf("Nenhuma encomenda a exibir.\n");
        return;
    }

    printf("Encomendas na ordem de entrega:\n");
    while (atual != NULL) {
        printf("Descricao: %s, Distancia: %.2f km\n", atual->descricao, atual->distancia);
        atual = atual->proxima;
    }
}

void removerEncomenda(float distancia) {
    Encomenda* atual = cabeca;
    Encomenda* anterior = NULL;

    while (atual != NULL && atual->distancia != distancia) {
        anterior = atual;
        atual = atual->proxima;
    }

    if (atual == NULL) {
        printf("Encomenda com distancia %.2f km não encontrada.\n", distancia);
        return;
    }

    if (anterior == NULL) {
        cabeca = atual->proxima;
    } else {
        anterior->proxima = atual->proxima;
    }

    free(atual);
    printf("Encomenda com distância %.2f km removida com sucesso.\n", distancia);
}

int main() {
    int opcao;
    char descricao[100];
    float distancia;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir encomenda\n");
        printf("2. Exibir encomendas\n");
        printf("3. Remover encomenda\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a descricao da encomenda: ");
                scanf(" %[^\n]", descricao);
                printf("Digite a distancia para o destinatario (em km): ");
                scanf("%f", &distancia);
                inserirEncomenda(descricao, distancia);
                break;
            case 2:
                exibirEncomendas();
                break;
            case 3:
                printf("Digite a distancia da encomenda a ser removida (em km): ");
                scanf("%f", &distancia);
                removerEncomenda(distancia);
                break;
            case 4:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    while (cabeca != NULL) {
        removerEncomenda(cabeca->distancia);
    }

    return 0;
}
