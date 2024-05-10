
#include <stdio.h>
#include <string.h>
#include "banco.h"

int main (){

    
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

    }
  while (opcao != '0');
};

