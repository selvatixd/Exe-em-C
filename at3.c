 #include <stdio.h>
#include <stdlib.h>

typedef struct aluno {
    int matricula;
    struct aluno *prox;
} Aluno;


Aluno* inserirAluno(Aluno* lista, int matricula) {

    Aluno* novo = (Aluno*)malloc(sizeof(Aluno));
    if (novo == NULL) {
        printf("Erro de alocação de memória!\n");
        return lista;
    }


    novo->matricula = matricula;
    novo->prox = lista;


    return novo;
}


void imprimirLista(Aluno* lista) {
    Aluno* temp = lista;

    if (temp == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    printf("Lista de Alunos:\n");
    while (temp != NULL) {
        printf("Matrícula: %d\n", temp->matricula);
        temp = temp->prox;
    }
}


void buscarAluno(Aluno* lista, int matricula) {
    Aluno* temp = lista;

    while (temp != NULL) {
        if (temp->matricula == matricula) {
            printf("Aluno com matrícula %d encontrado.\n", matricula);
            return;
        }
        temp = temp->prox;
    }
    printf("Aluno com matrícula %d não encontrado.\n", matricula);
}


void liberarLista(Aluno* lista) {
    Aluno* temp;

    while (lista != NULL) {
        temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

int main() {
    Aluno* lista = NULL;
    int opcao, matricula;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir aluno\n");
        printf("2. Imprimir lista de alunos\n");
        printf("3. Buscar aluno por matrícula\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o número da matrícula do aluno: ");
                scanf("%d", &matricula);
                lista = inserirAluno(lista, matricula);
                break;
            case 2:
                imprimirLista(lista);
                break;
            case 3:
                printf("Digite a matrícula que deseja buscar: ");
                scanf("%d", &matricula);
                buscarAluno(lista, matricula);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);


    liberarLista(lista);

    return 0;
}
