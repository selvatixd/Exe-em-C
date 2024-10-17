#include <stdio.h>

#define MAX 100

// Estrutura para armazenar os pacientes
struct Paciente {
    char nome[50];
};

// Array para armazenar a fila de pacientes
struct Paciente fila[MAX];
int totalPacientes = 0; // Controla o número de pacientes na fila

void adicionarPaciente() {
    if (totalPacientes < MAX) {
        printf("Digite o nome do paciente: ");
        scanf("%s", fila[totalPacientes].nome);
        totalPacientes++;
        printf("Paciente adicionado à fila!\n");
    } else {
        printf("Fila cheia! Não é possível adicionar mais pacientes.\n");
    }
}

void atenderPaciente() {
    if (totalPacientes > 0) {
        printf("Paciente %s foi atendido.\n", fila[0].nome);

        // Desloca todos os pacientes para a esquerda na fila
        for (int i = 0; i < totalPacientes - 1; i++) {
            fila[i] = fila[i + 1];
        }
        totalPacientes--;
    } else {
        printf("Nenhum paciente na fila.\n");
    }
}

void exibirFila() {
    if (totalPacientes == 0) {
        printf("Nenhum paciente aguardando atendimento.\n");
    } else {
        printf("Pacientes aguardando:\n");
        for (int i = 0; i < totalPacientes; i++) {
            printf("%d. %s\n", i + 1, fila[i].nome);
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\n1. Adicionar Paciente\n");
        printf("2. Atender Paciente\n");
        printf("3. Mostrar Fila\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            adicionarPaciente();
        } else if (opcao == 2) {
            atenderPaciente();
        } else if (opcao == 3) {
            exibirFila();
        } else if (opcao == 4) {
            printf("Saindo...\n");
        } else {
            printf("Opção inválida!\n");
        }
    } while (opcao != 4);

    return 0;
}