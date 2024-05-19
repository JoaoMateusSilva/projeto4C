#include "banco.h"
#include <stdio.h>
#include <string.h>

int main() {
  Cliente clientes[MAX_CLIENTES];
  int numClientes = 0;
  ERROS erro;
  
  ERROS errocarregar = carregarClientes(clientes, &numClientes);
  if (errocarregar != OK) {
    switch (errocarregar) {
    case ABRIR:
      printf("Erro ao abrir o arquivo\n");
      break;
    case FECHAR:
      printf("Erro ao fechar o arquivo\n");
      break;
    case LER:
      printf("Erro ao ler no arquivo\n");
      break;
    default:
      printf("Erro desconhecido ao carregar clientes\n");
    }
  }
  
  int opcao;
  
  do {
    printf("\n ================== Menu ================== \n");
    printf("1. Novo cliente\n");
    printf("2. Apagar Cliente\n");
    printf("3. Listar cliente\n ");
    printf("4. Debito\n");
    printf("5. Depósito\n");
    printf("6. Extrato\n");
    printf("7. Tranferência entre contas \n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%i", &opcao);
    clearBuffer();
    
    switch (opcao) {
    case 1:
      erro = criarCliente(clientes, &numClientes);
      if (erro == MAX_CLIENTES_ALCANCADOS) {
        printf("Limite de clientes atingido\n");
      } else if (erro == OK) {
        printf("Cliente criado\n");
      } else {
        printf("Erro\n");
      }
      break;

    case 2:
      erro = deletarCliente(clientes, &numClientes);
      if (erro == OK) {
        printf("Cliente deletado\n");
      } else {
        printf("Erro ao deletar cliente\n");
      }
      break;

    case 3:
      erro = listarCliente(clientes, numClientes);
      if (erro == SEM_CLIENTES) {
        printf("Nenhum cliente cadastrado\n");
      }
      break;

    case 4:
      erro = debitarValor(clientes, numClientes);
      if (erro == OK) {
        printf("Débito realizado com sucesso.\n");
      } else if (erro == CREDENCIAIS_INVALIDAS) {
        printf("CPF ou senha incorretos\n");
      } else if (erro == SALDO_INSUFICIENTE) {
        printf("Saldo insuficiente para realizar o débito\n");
      } else {
        printf("Erro ao realizar débito\n");
      }
      break;

    case 5:
      erro = depositarValor(clientes, numClientes);
      if (erro == CLIENTE_NAO_ENCONTRADO) {
        printf("Cliente não encontrado para o CPF informado\n");
      }
      break;

    case 6:
      erro = extrato(clientes, numClientes);
      if (erro == CREDENCIAIS_INVALIDAS) {
        printf("CPF ou senha incorretos. Extrato não gerado.\n");
      } else if (erro == OK) {
        printf(
            "Extrato gerado com sucesso. Verifique o arquivo extrato.txt!\n");
      } else {
        printf("Erro ao gerar extrato.txt!\n");
      }
      break;

    case 7:
      erro = transferencia(clientes, numClientes);
      if (erro == CREDENCIAIS_INVALIDAS)
        printf("CPF ou senha incorretos.\n");
      else if (erro == CLIENTE_NAO_ENCONTRADO)
        printf("CPF da conta de destino não encontrado\n");
      else
        printf("Saldo insuficiente na conta de origem para realizar a "
               "transferência com a taxa\n");
      break;

    case 0:
      printf("Fechando...\n");
      break;
    default:
      printf("Opção invalida\n");
      break;
    }
  } while (opcao != 0);

  ERROS errosalvar = salvarClientes(clientes, numClientes);
  if (errosalvar == ABRIR)
    printf("erro ao abrir o arquivo\n");
  else if (errosalvar == FECHAR)
    printf("erro ao fechar o arquivo\n");
  else if (errosalvar == ESCREVER)
    printf("erro ao escrever no arquivo\n");
}
