#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Compromisso {
  int hora;
  int minuto;
  char descricao[100];
  struct Compromisso *prox;
} Compromisso;

Compromisso *criarCompromisso(int hora, int minuto, char descricao[]) {
  Compromisso *novo = (Compromisso *)malloc(sizeof(Compromisso));
  novo->hora = hora;
  novo->minuto = minuto;
  strcpy(novo->descricao, descricao);
  novo->prox = NULL;
  return novo;
}

void inserirCompromisso(Compromisso **agenda, int hora, int minuto,
                        char descricao[]) {
  Compromisso *novo = criarCompromisso(hora, minuto, descricao);

  if (*agenda == NULL || (*agenda)->hora > hora ||
      ((*agenda)->hora == hora && (*agenda)->minuto > minuto)) {
    novo->prox = *agenda;
    *agenda = novo;
  } else {
    Compromisso *atual = *agenda;
    while (atual->prox != NULL &&
           (atual->prox->hora < hora ||
            (atual->prox->hora == hora && atual->prox->minuto < minuto))) {
      atual = atual->prox;
    }
    novo->prox = atual->prox;
    atual->prox = novo;
  }
}

void exibirCompromissos(Compromisso *agenda) {
  if (agenda == NULL) {
    printf("Nenhum compromisso agendado.\n");
    return;
  }
  Compromisso *atual = agenda;
  while (atual != NULL) {
    printf("%02d:%02d - %s\n", atual->hora, atual->minuto, atual->descricao);
    atual = atual->prox;
  }
}

void removerCompromisso(Compromisso **agenda, int hora, int minuto) {
  if (*agenda == NULL) {
    printf("Nenhum compromisso encontrado para remover.\n");
    return;
  }

  Compromisso *atual = *agenda;
  Compromisso *anterior = NULL;
  while (atual != NULL && (atual->hora != hora || atual->minuto != minuto)) {
    anterior = atual;
    atual = atual->prox;
  }

  if (atual == NULL) {
    printf("Compromisso não encontrado.\n");
    return;
  }

  if (anterior == NULL) {
    *agenda = atual->prox;
  } else {
    anterior->prox = atual->prox;
  }

  free(atual);
  printf("Compromisso removido.\n");
}

int main() {
  Compromisso *agenda = NULL;
  int opcao, hora, minuto;
  char descricao[100];

  do {
    printf("\n1. Inserir compromisso bill\n");
    printf("2. Exibir compromissos bill\n");
    printf("3. Remover compromisso bill\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao bill: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Digite o horario (hora e minuto): ");
      scanf("%d %d", &hora, &minuto);
      printf("Digite a descricao do compromisso: ");
      getchar();
      fgets(descricao, 100, stdin);
      descricao[strcspn(descricao, "\0")] = '\0';

      inserirCompromisso(&agenda, hora, minuto, descricao);
      break;
    case 2:
      exibirCompromissos(agenda);
      break;
    case 3:
      printf("Digite o horario do compromisso a remover bill (hora e minuto): ");
      scanf("%d %d", &hora, &minuto);
      removerCompromisso(&agenda, hora, minuto);
      break;
    case 0:
      printf("Adeus Bill...\n");
      break;
    default:
      printf("Opcao invalida, ai nao bill!\n");
    }
  } while (opcao != 0);

  Compromisso *atual = agenda;
  while (atual != NULL) {
    Compromisso *prox = atual->prox;
    free(atual);
    atual = prox;
  }

  return 0;
}
