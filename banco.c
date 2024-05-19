#include "banco.h"
#include <stdio.h>
#include <string.h>

void adicionarTransacao(Cliente *cliente, char tipo, double valor) {
  if (cliente->numTransacoes < MAX_TRANSACOES) {
    Transacao t;
    t.tipo = tipo;
    t.valor = valor;
    cliente->historico[cliente->numTransacoes] = t;
    cliente->numTransacoes++;
  }
}

ERROS carregarClientes(Cliente clientes[], int *numClientes) {
  FILE *file = fopen("clientes.bin", "rb");

  if (file == NULL)
    return ABRIR;
  int qtd = fread(numClientes, sizeof(int), 1, file);

  if (qtd != 1)
    return LER;
  
  qtd = fread(clientes, sizeof(Cliente), *numClientes, file);
  
  if (qtd < *numClientes)
    return LER;
  
  if (fclose(file))
    return FECHAR;
  return OK;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

ERROS salvarClientes(Cliente clientes[], int numClientes) {
  FILE *file = fopen("clientes.bin", "wb");
  if (file == NULL)
    return ABRIR;

  int qtd = fwrite(clientes, sizeof(Cliente), numClientes, file);
  if (qtd < numClientes)
    return ESCREVER;

  qtd = fwrite(&numClientes, sizeof(int), 1, file);
  if (qtd != 1)
    return ESCREVER;

  if (fclose(file))
    return FECHAR;

  return OK;
}

ERROS criarCliente(Cliente clientes[], int *numClientes) {
  Cliente novoCliente;

  if (*numClientes >= MAX_CLIENTES) {
    return MAX_CLIENTES_ALCANCADOS;
  }

  printf("Digite o nome do cliente (apenas letras): ");
  fgets(novoCliente.nome, TAM_NOME, stdin);
  novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

  printf("Digite o CPF (apenas números, sem pontuação): ");
  fgets(novoCliente.cpf, TAM_CPF, stdin);
  novoCliente.cpf[strcspn(novoCliente.cpf, "\n")] = '\0';

  printf("\nSelecione o tipo de conta:\n");
  printf("1 - Comum (Máximo de R$1.000 em débito)\n");
  printf("2 - Plus (Máximo de R$5.000 em débito)\n");
  printf("Sua escolha: ");
  fgets(&novoCliente.tipoConta, TAM_TIPOCONTA, stdin);
  novoCliente.tipoConta = getchar();

  printf("Digite o valor inicial da conta (valor positivo): ");
  if (scanf("%lf", &novoCliente.saldo) != 1 || novoCliente.saldo <= 0) {
    printf("O saldo inicial precisa ser um valor positivo.\n");
    return CREDENCIAIS_INVALIDAS;
  }
  clearBuffer();

  printf("Digite a senha (mínimo 8 caracteres, incluindo letras maiúsculas, "
         "minúsculas e caracteres especiais): ");
  fgets(novoCliente.senha, TAM_SENHA, stdin);
  novoCliente.senha[strcspn(novoCliente.senha, "\n")] = '\0';

  clientes[*numClientes] = novoCliente;
  (*numClientes)++;

  return OK;
}

ERROS deletarCliente(Cliente clientes[], int *numClientes) {
  char cpfDeletar[TAM_CPF];

  printf("Digite o CPF do cliente que deseja deletar: ");
  fgets(cpfDeletar, TAM_CPF, stdin);
  cpfDeletar[strcspn(cpfDeletar, "\n")] = '\0';

  int i, encontrado = 0;

  for (i = 0; i < *numClientes; i++) {
    if (strcmp(clientes[i].cpf, cpfDeletar) == 0) {
      for (int j = i; j < *numClientes - 1; j++) {
        clientes[j] = clientes[j + 1];
      }
      (*numClientes)--;
      encontrado = 1;
      break;
    }
  }

  if (encontrado) {
    return OK;
  } else {
    return CLIENTE_NAO_ENCONTRADO;
  }
}

ERROS listarCliente(Cliente clientes[], int numClientes) {
  if (numClientes == 0) {
    return SEM_CLIENTES;
  }

  printf("Lista de clientes:\n");
  for (int i = 0; i < numClientes; i++) {
    printf("Cliente %d:\n", i + 1);
    printf("Nome: %s\n", clientes[i].nome);
    printf("CPF: %s\n", clientes[i].cpf);
    printf("Tipo de conta: %c\n", clientes[i].tipoConta);
    printf("Saldo: %.2lf\n", clientes[i].saldo);
    printf("\n");
  }
  return OK;
}

ERROS debitarValor(Cliente clientes[], int numClientes) {
  char cpfDebito[TAM_CPF];
  char senhaDebito[TAM_SENHA];
  double valorDebito = 0;
  int indexCliente = -1;

  printf("Digite o CPF: ");
  scanf("%s", cpfDebito);
  clearBuffer();

  printf("Digite a senha: ");
  scanf("%s", senhaDebito);
  clearBuffer();

  for (int i = 0; i < numClientes; i++) {
    if (strcmp(clientes[i].cpf, cpfDebito) == 0 &&
        strcmp(clientes[i].senha, senhaDebito) == 0) {
      indexCliente = i;
      break;
    }
  }

  if (indexCliente == -1) {
    printf("CPF ou senha incorretos\n");
    return CREDENCIAIS_INVALIDAS;
  }

  if (indexCliente < 0 || indexCliente >= numClientes) {
    return CLIENTE_NAO_ENCONTRADO;
  }

  printf("Digite o valor do débito: ");
  scanf("%lf", &valorDebito);
  clearBuffer();

  double taxa = 0.0;

  if (clientes[indexCliente].tipoConta == '1') {
    taxa = valorDebito * TAXA_COMUM;
  } else if (clientes[indexCliente].tipoConta == '2') {
    taxa = valorDebito * TAXA_PLUS;
  }
  if (clientes[indexCliente].saldo < valorDebito + taxa) {
    return SALDO_INSUFICIENTE;
  }
  clientes[indexCliente].saldo -= (valorDebito + taxa);
  adicionarTransacao(&clientes[indexCliente], 'D', valorDebito + taxa);
  return OK;
}

ERROS depositarValor(Cliente clientes[], int numClientes) {
  char cpfDeposito[TAM_CPF];
  double valorDeposito = 0;

  printf("Digite o CPF do cliente para o depósito: ");
  scanf("%s", cpfDeposito);
  clearBuffer();

  int indexCliente = -1;

  for (int i = 0; i < numClientes; i++) {
    if (strcmp(clientes[i].cpf, cpfDeposito) == 0) {
      indexCliente = i;
      break;
    }
  }
  if (indexCliente == -1) {
    return CLIENTE_NAO_ENCONTRADO;
  }

  if (indexCliente < 0 || indexCliente >= numClientes) {
    return CLIENTE_NAO_ENCONTRADO;
  }

  printf("Digite o valor do depósito: ");
  scanf("%lf", &valorDeposito);
  clearBuffer();

  clientes[indexCliente].saldo += valorDeposito;
  adicionarTransacao(&clientes[indexCliente], 'C', valorDeposito);
  return OK;
}

ERROS extrato(Cliente clientes[], int numClientes) {
  char cpfExtrato[TAM_CPF];
  char senhaExtrato[TAM_SENHA];
  int indexCliente = -1;

  printf("Digite o CPF: ");
  fgets(cpfExtrato, TAM_CPF, stdin);
  cpfExtrato[strcspn(cpfExtrato, "\n")] = '\0';

  printf("Digite a senha: ");
  fgets(senhaExtrato, TAM_SENHA, stdin);
  senhaExtrato[strcspn(senhaExtrato, "\n")] = '\0';

  for (int i = 0; i < numClientes; i++) {
    if (strcmp(clientes[i].cpf, cpfExtrato) == 0 &&
        strcmp(clientes[i].senha, senhaExtrato) == 0) {
      indexCliente = i;
      break;
    }
  }

  if (indexCliente == -1) {
    return CLIENTE_NAO_ENCONTRADO;
  
  FILE *file = fopen("extrato.txt", "w");
  if (file == NULL) {
    return ABRIR;
  }
    
    fprintf(file, "Extrato de Operações para o Cliente:\n");
    fprintf(file, "CPF: %s\n", clientes[indexCliente].cpf);
    fprintf(file, "Nome: %s\n", clientes[indexCliente].nome);
    fprintf(file, "Tipo de conta: %c\n", clientes[indexCliente].tipoConta);
    fprintf(file, "Saldo Atual: %.2lf\n\n", clientes[indexCliente].saldo);

    fprintf(file, "------ Histórico de Transações ------\n");
    for (int i = 0; i < clientes[indexCliente].numTransacoes; i++) {
      Transacao t = clientes[indexCliente].historico[i];

      if (t.tipo == 'D') {
        fprintf(file, "Débito: %.2lf\n", t.valor);
      } else if (t.tipo == 'C') {
        fprintf(file, "Crédito: %.2lf\n", t.valor);
      }
    }

    fclose(file);

    return OK;
  } else {
    return CREDENCIAIS_INVALIDAS;
  }
}

ERROS transferencia(Cliente clientes[], int numClientes) {
  char cpfOrigem[TAM_CPF];
  char senhaOrigem[TAM_SENHA];
  char cpfDestino[TAM_CPF];
  double valorTransferencia = 0;
  int indexOrigem = -1;
  int indexDestino = -1;

  printf("Digite o CPF da conta de origem: ");
  scanf("%s", cpfOrigem);
  clearBuffer();

  printf("Digite a senha da conta de origem: ");
  scanf("%s", senhaOrigem);
  clearBuffer();

  for (int i = 0; i < numClientes; i++) {
    if (strcmp(clientes[i].cpf, cpfOrigem) == 0 &&
        strcmp(clientes[i].senha, senhaOrigem) == 0) {
      indexOrigem = i;
      break;
    }
  }

  if (indexOrigem == -1) {
    printf("CPF ou senha incorretos\n");
    return CREDENCIAIS_INVALIDAS;
  }

  printf("Digite o CPF da conta de destino: ");
  scanf("%s", cpfDestino);
  clearBuffer();
  
  for (int i = 0; i < numClientes; i++) {
    if (strcmp(clientes[i].cpf, cpfDestino) == 0) {
      indexDestino = i;
      break;
    }
  }
  
  if (indexDestino == -1) {
    printf("CPF da conta de destino não encontrado\n");
    return CLIENTE_NAO_ENCONTRADO;
  }
  
  printf("Digite o valor a ser transferido: ");
  scanf("%lf", &valorTransferencia);
  clearBuffer();

  double taxaOrigem = 0.0;

  if (clientes[indexOrigem].tipoConta == '1') {
    taxaOrigem = valorTransferencia * TAXA_COMUM;
  } else if (clientes[indexOrigem].tipoConta == '2') {
    taxaOrigem = valorTransferencia * TAXA_PLUS;
  }
  if (clientes[indexOrigem].saldo < valorTransferencia + taxaOrigem) {
    return SALDO_INSUFICIENTE;
  }
  clientes[indexOrigem].saldo -= (valorTransferencia + taxaOrigem);
  clientes[indexDestino].saldo += valorTransferencia;

  adicionarTransacao(&clientes[indexOrigem], 'D',
                     valorTransferencia + taxaOrigem);
  adicionarTransacao(&clientes[indexDestino], 'C', valorTransferencia);

  return OK;
}
