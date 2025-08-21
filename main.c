#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VAGAS 5

//CARRO
typedef struct Carro {
    char placa[8];
    int tempo;
    struct Carro* prox;
} Carro;

//PILHA
typedef struct {
    Carro* topo;
    int tamanho;
} Pilha;

//FILA DE ESPERA
typedef struct No {
    Carro* carro;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
} filaEspera;

//FUNÇÕES DA FILA
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
        printf("Fila de espera vazia.\n");
        return NULL;
    }
    No *temp = f->inicio;
    Carro* result = temp->carro;

    f->inicio = f->inicio->prox;
    if(f->inicio == NULL) {
        f->fim = NULL;
    }
    free(temp);
    printf("Veiculo %s saiu da fila de espera.\n", result->placa);
    return result;
}

void listarFila(filaEspera* f) {
    No* aux = f->inicio;
    if (aux == NULL) {
        printf("Fila de espera vazia.\n");
        return;
    }
    printf("--- Fila de espera ---\n");
    while (aux != NULL) {
        printf("Carro %s - %d minutos\n", aux->carro->placa, aux->carro->tempo);
        aux = aux->prox;
    }
}

//FUNÇÕES DA PILHA
Pilha* criarPilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

bool vazia(Pilha* p) {
    return p->topo == NULL;
}

bool cheia(Pilha* p) {
    return p->tamanho >= MAX_VAGAS;
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

Carro* desempilhar(Pilha* p, filaEspera* f) {
    if (vazia(p)) {
        printf("Estacionamento vazio!\n");
        return NULL;
    }
    Carro* c = p->topo;
    p->topo = c->prox;
    p->tamanho--;
    printf("Veiculo %s retirado.\n", c->placa);

    if (p->tamanho < MAX_VAGAS) {
        Carro* espera = desenfileirar(f);
        if (espera != NULL) {
            empilhar(p, f, espera);
            printf("Veivulo %s da fila de espera entrou para o estacionamento!\n", espera->placa);
        }
    }

    return c;
}

void listarEstacionamento(Pilha* p) {
    if (vazia(p)) {
        printf("Estacionamento vazio!\n");
        return;
    }
    
    printf("\n-------------------------\n");
    printf("Estacionamento");
    printf("\n-------------------------\n");
    Carro* aux = p->topo;
    while (aux != NULL) {
        printf("Carro %s - %d minutos\n", aux->placa, aux->tempo);
        aux = aux->prox;
    }
}


//ORDENAR - BUBBLE SORT
void ordenar(Pilha* p) {
    if (vazia(p) || p->topo->prox == NULL) return;

    Carro* i;
    Carro* j;
    for (i = p->topo; i != NULL; i = i->prox) {
        for (j = i->prox; j != NULL; j = j->prox) {
            if (i->tempo > j->tempo) {
                int tempTempo = i->tempo;
                i->tempo = j->tempo;
                j->tempo = tempTempo;

                char tempPlaca[8];
                strcpy(tempPlaca, i->placa);
                strcpy(i->placa, j->placa);
                strcpy(j->placa, tempPlaca);
            }
        }
    }
}


//BUSCA - SEQUENCIAL
Carro* buscar(Pilha* p, char placa[]) {
    Carro* aux = p->topo;
    while (aux != NULL) {
        if (aux->placa == placa) {
            printf("Carro %s foi encontrado no estacionamneto.\n", placa);
            return aux;
        }
        aux = aux->prox;
    }
    printf("Carro %s nao foi encontrado no estacionamneto.\n", placa);
    return NULL;
}


int main() {
    Pilha* estacionamento = criarPilha();
    filaEspera fila;
    iniciarFila(&fila);

    int opcao;
    do {
        printf("\n-------------------------");
        printf("\n      ESTACIONAMENTO\n");
        printf("-------------------------\n");
        printf("1. Estacionar carro\n");
        printf("2. Retirar carro\n");
        printf("3. Listar carros\n");
        printf("4. Ordenar por tempo\n");
        printf("5. Buscar carro\n");
        printf("6. Lista de espera\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");
        getchar();

        switch(opcao) {
            case 1: {
                Carro* novo = malloc(sizeof(Carro));
                printf("Digite a placa do carro: ");
                scanf("%7s", novo->placa);
                printf("Digite o tempo de permanencia: ");
                scanf("%d", &novo->tempo);
                empilhar(estacionamento, &fila, novo);
                break;
            }
            case 2:
                desempilhar(estacionamento, &fila);
                break;
            case 3:
                listarEstacionamento(estacionamento);
                break;
            case 4:
                ordenar(estacionamento);
                printf("Estacionamento ordenado por tempo.\n");
                break;
            case 5: {
                char placaBusca[8];
                printf("Digite a placa para buscar: ");
                scanf("%s", placaBusca);
                buscar(estacionamento, placaBusca);
                break;
            }
            case 6:
                listarFila(&fila);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);


    return 0;
}