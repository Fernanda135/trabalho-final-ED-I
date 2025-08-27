#include "estruturas.h"

bool vazia(Pilha* p) {
    return p->topo == NULL;
}

bool cheia(Pilha* p) {
    return p->tamanho >= MAX_VAGAS;
}

Pilha* criarPilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

void empilhar(Pilha* p, filaEspera* f, Carro* c) {
    if(cheia(p)) {
        enfileirar(f, c);
    } else {
        c->prox = p->topo;
        p->topo = c;
        p->tamanho++;
        printf("Veiculo %s estacionado.\n", c->placa);
    }
}

Carro* desempilhar(Pilha* p) {
    if (vazia(p)) {
        return NULL;
    }
    Carro* c = p->topo;
    p->topo = c->prox;
    p->tamanho--;
    return c;
}

void listarEstacionamento(Pilha* p) {
    if (vazia(p)) {
        printf("Estacionamento vazio!\n");
        return;
    }
    
    printf("\n--- Estacionamento ---\n");
    Carro* aux = p->topo;
    while (aux != NULL) {
        printf("Carro %s - %d minutos\n", aux->placa, aux->tempo);
        aux = aux->prox;
    }
}
