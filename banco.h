#define MAX_CLIENTES 100
#define TAM_NOME 50
#define TAM_CPF 15
#define TAM_SENHA 10

typedef struct Cliente {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    int tipoConta;
    double saldo;
    char senha[TAM_SENHA];
} Cliente;

typedef enum {OK, MAX_CLIENTES_ALCANCADOS} ERROS;

ERROS criarCliente(Cliente clientes[], int *numClientes);

void clearBuffer();
