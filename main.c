#include <stdio.h>
#include <string.h>
#include "banco.h"

int main() {
    Cliente clientes[MAX_CLIENTES];
    int numClientes = 0;
    ERROS erro;
    char opcao;

    do {
        printf("\n ================== Menu ================== ");
        printf("1. Novo cliente \n");
        printf("2. Apagar Cliente \n");
        printf("3. Listar cliente \n ");
        printf("4. Debito \n");
        printf("5. Depósito \n");
        printf("6. Extrato \n");
        printf("7. Tranferência entre contas \n");
        printf("0. Sair \n");
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);
        clearBuffer();

        switch (opcao) {
            case '1':
                erro = criarCliente(clientes, &numClientes);
                if (erro == MAX_CLIENTES_ALCANCADOS) {
                    printf("Limite de clientes atingido\n");
                } else if (erro == OK) {
                    printf("Cliente criado\n");
                } else {
                    printf("Erro\n");
                }
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '0':
                printf("Fechando\n");
                break;
            default:
                printf("Opção invalida\n");
                break;
        }
    } while (opcao != '0');

    return 0;
}
