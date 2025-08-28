#include "estruturas.h"

void iniciarFila(filaEspera *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

bool enfileirar(filaEspera *f, Carro* c) {
    No *novoNo = malloc(sizeof(No));
    if (!novoNo) return false;
    novoNo->carro = c;
    novoNo->prox = NULL;

    if(f->fim != NULL) {
        f->fim->prox = novoNo;
    }
    f->fim = novoNo;

    if (f->inicio == NULL) {
        f->inicio = novoNo;
    }

    printf("Veiculo %s foi para a fila de espera.\n", c->placa);
    return true;
}

Carro* desenfileirar(filaEspera *f) {
    if(f->inicio == NULL) {
        return NULL;
    }
    No *temp = f->inicio;
    Carro* result = temp->carro;

    f->inicio = f->inicio->prox;
    if(f->inicio == NULL) {
        f->fim = NULL;
    }
    free(temp);
    return result;
}

void listarFila(filaEspera* f) {
    No* aux = f->inicio;
    if (aux == NULL) {
        printf("Fila de espera vazia.\n");
        return;
    }
    printf("\n--- Fila de espera ---\n");
    while (aux != NULL) {
        printf("Carro %s - %d minutos\n", aux->carro->placa, aux->carro->tempo);
        aux = aux->prox;
    }
}