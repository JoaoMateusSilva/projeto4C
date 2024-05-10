#include <stdio.h>
#include <string.h>
#include "banco.h"

ERROS criarCliente(Cliente clientes[], int *numClientes) {
    if (*numClientes >= MAX_CLIENTES)
        return MAX_CLIENTES_ALCANCADOS;

    Cliente novoCliente;

    printf("Digite o nome do cliente: ");
    fgets(novoCliente.nome, TAM_NOME, stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

    printf("Digite o CPF: ");
    fgets(novoCliente.cpf, TAM_CPF, stdin);
    novoCliente.cpf[strcspn(novoCliente.cpf, "\n")] = '\0';

    printf("Selecione o tipo de conta (1 - Comum, 2 - Plus): ");
    scanf("%d", &novoCliente.tipoConta);
    clearBuffer();

    printf("Digite o valor inicial da conta: ");
    scanf("%lf", &novoCliente.saldo);
    clearBuffer();

    printf("Digite a senha: ");
    fgets(novoCliente.senha, TAM_SENHA, stdin);
    novoCliente.senha[strcspn(novoCliente.senha, "\n")] = '\0';

    clientes[*numClientes] = novoCliente;
    *numClientes += 1;

    return OK;
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}
