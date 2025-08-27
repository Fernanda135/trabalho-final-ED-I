#include "estruturas.h"
#include "pilha.c"
#include "fila.c"
#include "lista.c"


int main() {
    Pilha* estacionamento = criarPilha();
    filaEspera fila;
    iniciarFila(&fila);

    ListaCadastro lista;
    inicializarLista(&lista);

    int opcao;
    do {
        printf("\n-------------------------");
        printf("\n      ESTACIONAMENTO\n");
        printf("-------------------------\n");
        printf("1. Estacionar carro\n");
        printf("2. Retirar carro\n");
        printf("3. Listar carros\n");
        printf("4. Buscar carro\n");
        printf("5. Mostrar fila de espera\n");
        printf("6. Listar cadastrados\n");
        printf("7. Relatorios\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Carro* novo = malloc(sizeof(Carro));
                printf("Digite a placa do carro: ");
                scanf("%7s", novo->placa);
                printf("Digite o tempo de permanencia: ");
                scanf("%d", &novo->tempo);
                empilhar(estacionamento, &fila, novo);
                inserirCadastro(&lista, *novo);
                break;
            }
            case 2: {
                char placaBusca[8];
                printf("Digite a placa do carro a retirar: ");
                scanf("%7s", placaBusca);
                retirarCarro(estacionamento, &fila, placaBusca);
                if (!cheia(estacionamento)) {
                    Carro* espera = desenfileirar(&fila);
                    if (espera != NULL) {
                        empilhar(estacionamento, &fila, espera);
                        printf("Carro %s da fila entrou no estacionamento.\n", espera->placa);
                    }
                }
                break;
            }
            case 3:
                listarEstacionamento(estacionamento);
                break;
            case 4: {
                char placaBusca[8];
                printf("Digite a placa para buscar: ");
                scanf("%7s", placaBusca);
                buscar(estacionamento, placaBusca);
                break;
            }
            case 5:
                listarFila(&fila);
                break;
            case 6:
                listarCadastros(&lista);
                break;
            case 7:
                relatorios(estacionamento, &lista);
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
