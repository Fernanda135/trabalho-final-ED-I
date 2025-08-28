#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VAGAS 5

// CARRO
typedef struct Carro {
    char placa[8];
    int tempo;
    struct Carro* prox;
} Carro;

// PILHA (ESTACIONAMENTO)
typedef struct {
    Carro* topo;
    int tamanho;
} Pilha;

// FILA DE ESPERA
typedef struct No {
    Carro* carro;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
} filaEspera;

// LISTA SIMPLES (CADASTRADOS)
typedef struct NoCadastro {
    Carro carro;
    struct NoCadastro* prox;
} NoCadastro;

typedef struct {
    NoCadastro* inicio;
    int tamanho;
} ListaCadastro;

// VARIÁVEIS GLOBAIS
extern int totalManobras;


//FUNÇÕES

// Pilha
Pilha* criarPilha();
bool vazia(Pilha* p);
bool cheia(Pilha* p);
void empilhar(Pilha* p, filaEspera* f, Carro* c);
Carro* desempilhar(Pilha* p);
void listarEstacionamento(Pilha* p);

// Fila
void iniciarFila(filaEspera *f);
bool enfileirar(filaEspera *f, Carro* c);
Carro* desenfileirar(filaEspera *f);
void listarFila(filaEspera* f);

// Lista
void inicializarLista(ListaCadastro* lista);
void inserirCadastro(ListaCadastro* lista, Carro carro);
void listarCadastros(ListaCadastro* lista);

// Funções extras
Carro* buscar(Pilha* p, char placa[]);
int retirarCarro(Pilha* p, filaEspera* f, char placa[]);
void relatorios(Pilha* p, ListaCadastro* lista);

#endif