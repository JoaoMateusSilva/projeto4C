#define MAX_CLIENTES 1000
#define TAM_NOME 50
#define TAM_CPF 15
#define TAM_SENHA 10
#define MAX_TRANSACOES 100
#define TAM_TIPOCONTA 1
#define TAXA_COMUM 0.05
#define TAXA_PLUS 0.03

typedef struct Transacao {
  char tipo;
  double valor;
} Transacao;

typedef struct Cliente {
  char nome[TAM_NOME];
  char cpf[TAM_CPF];
  char tipoConta;
  double saldo;
  char senha[TAM_SENHA];
  Transacao historico[MAX_TRANSACOES];
  int numTransacoes;
} Cliente;

typedef enum {
  OK,
  MAX_CLIENTES_ALCANCADOS,
  CLIENTE_NAO_ENCONTRADO,
  SEM_CLIENTES,
  CREDENCIAIS_INVALIDAS,
  SALDO_INSUFICIENTE,
  ESCREVER,
  ABRIR,
  FECHAR,
  LER
} ERROS;

ERROS carregarClientes(Cliente clientes[], int *numClientes);
ERROS salvarClientes(Cliente clientes[], int numClientes);
ERROS criarCliente(Cliente clientes[], int *numClientes);
ERROS deletarCliente(Cliente clientes[], int *numClientes);
ERROS listarCliente(Cliente clientes[], int numClientes);
ERROS debitarValor(Cliente clientes[], int numClientes);
ERROS depositarValor(Cliente clientes[], int numClientes);
ERROS extrato(Cliente clientes[], int numClientes);
ERROS transferencia(Cliente clientes[], int numClientes);

void adicionarTransacao(Cliente *cliente, char tipo, double valor);
void clearBuffer();
