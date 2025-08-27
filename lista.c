#include "estruturas.h"

int totalManobras = 0;

void inicializarLista(ListaCadastro* lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

void inserirCadastro(ListaCadastro* lista, Carro carro) {
    NoCadastro* novo = (NoCadastro*) malloc(sizeof(NoCadastro));
    novo->carro = carro;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        NoCadastro* aux = lista->inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    lista->tamanho++;
}

void listarCadastros(ListaCadastro* lista) {
    NoCadastro* aux = lista->inicio;
    if (aux == NULL) {
        printf("Nenhum carro cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Cadastrados ---\n");
    while (aux != NULL) {
        printf("Carro %s - %d minutos\n", aux->carro.placa, aux->carro.tempo);
        aux = aux->prox;
    }
}

// BUSCA
Carro* buscar(Pilha* p, char placa[]) {
    Carro* aux = p->topo;
    while (aux != NULL) {
        if (strcmp(aux->placa, placa) == 0) {
            printf("Carro %s foi encontrado no estacionamento.\n", placa);
            return aux;
        }
        aux = aux->prox;
    }
    printf("Carro %s nao foi encontrado no estacionamento.\n", placa);
    return NULL;
}

// SAÍDA DE CARRO
int retirarCarro(Pilha* p, filaEspera* f, char placa[]) {
    Pilha* aux = criarPilha();
    int manobras = 0;
    Carro* retirado = NULL;

    while (!vazia(p)) {
        Carro* c = desempilhar(p);
        manobras++;
        if (strcmp(c->placa, placa) == 0) {
            retirado = c;
            break;
        } else {
            empilhar(aux, f, c);
        }
    }

    while (!vazia(aux)) {
        Carro* c = desempilhar(aux);
        empilhar(p, f, c);
    }
    free(aux);

    if (retirado != NULL) {
        printf("Carro %s retirado com %d manobras.\n", placa, manobras-1);
        totalManobras += (manobras-1);
        free(retirado);
        return manobras-1;
    } else {
        printf("Carro %s nao estava no estacionamento.\n", placa);
        return 0;
    }
}

// RELATÓRIOS
void relatorios(Pilha* p, ListaCadastro* lista) {
    printf("\n--- Relatorios ---\n");

    printf("Ocupacao: %d/%d\n", 
        p->tamanho, MAX_VAGAS, 
        (p->tamanho * 100.0) / MAX_VAGAS);

    NoCadastro* aux = lista->inicio;
    int n = lista->tamanho;
    if (n == 0) {
        printf("Nenhum carro cadastrado ainda.\n");
    } else {
        Carro* vetor = malloc(n * sizeof(Carro));
        int i=0;
        while (aux != NULL) {
            vetor[i++] = aux->carro;
            aux = aux->prox;
        }
        for (int a=0; a<n-1; a++) {
            for (int b=a+1; b<n; b++) {
                if (vetor[a].tempo < vetor[b].tempo) {
                    Carro temp = vetor[a];
                    vetor[a] = vetor[b];
                    vetor[b] = temp;
                }
            }
        }
        printf("\nTop 5 permanencias:\n");
        for (int k=0; k<n && k<5; k++) {
            printf("%s - %d minutos\n", vetor[k].placa, vetor[k].tempo);
        }
        free(vetor);
    }
    printf("\nTotal de manobras realizadas: %d\n", totalManobras);
}
