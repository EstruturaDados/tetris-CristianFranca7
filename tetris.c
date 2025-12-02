//---Bibliotecas Necessárias---
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//---Constantes Globais---
#define TAM_FILA 10   //capacidade total da fila
#define INICIAL 5     //quantidade inicial de peças

//---Definição da estrutura---
typedef struct {
    char nome;  
    int id;
} Peca;

//---Fila Circular---
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

//---Protótipos---
void inicializarFila(Fila *f);
Peca gerarPeca(int id);
void enqueue(Fila *f, Peca x);
void dequeue(Fila *f);
void exibirFila(const Fila *f);

//---Função main()---
int main() {
    Fila fila;
    inicializarFila(&fila);

    int opcao;
    int geradorID = INICIAL; //IDs começam após os 5 iniciais

    do {
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, gerarPeca(geradorID++));
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

//---Implementação das Funções---

//Inicializa fila e insere 5 peças iniciais
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;

    for (int i = 0; i < INICIAL; i++) {
        enqueue(f, gerarPeca(i));
    }
}

//Gera peça automaticamente
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

//Insere peça no fim
void enqueue(Fila *f, Peca x) {
    if (f->quantidade == TAM_FILA) {
        printf("\nFila cheia! Não é possível adicionar mais peças.\n");
        return;
    }

    f->itens[f->fim] = x;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;

    printf("\nPeça [%c %d] inserida com sucesso!\n", x.nome, x.id);
}

//Remove peça da frente
void dequeue(Fila *f) {
    if (f->quantidade == 0) {
        printf("\nA fila está vazia! Não há peça para jogar.\n");
        return;
    }

    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;

    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
}

//Mostra todas as peças da fila
void exibirFila(const Fila *f) {
    printf("\n====================================\n");
    printf("         FILA DE PEÇAS FUTURAS\n");
    printf("====================================\n");

    if (f->quantidade == 0) {
        printf("Fila vazia.\n");
        return;
    }

    int idx = f->inicio;

    for (int i = 0; i < f->quantidade; i++) {
        Peca p = f->itens[idx];
        printf("[%c %d] ", p.nome, p.id);
        idx = (idx + 1) % TAM_FILA;
    }

    printf("\n\n(Quantidade: %d/%d)\n", f->quantidade, TAM_FILA);
}