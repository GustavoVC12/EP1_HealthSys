#include <stdio.h>
#include "bdpacientes.h"

int main(void) {
  BDPaciente bd = bd_criarBanco(); // inicializa banco
  bd_carregar_csv(&bd); // carrega pacientes do CSV

  // menu
  char opcao;
  while(1){
    printFrame();
    printf("HealthSys\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente (indisponível)\n");
    printf("3 - Remover paciente (indisponível)\n");
    printf("4 - Inserir paciente (indisponível)\n");
    printf("5 - Imprimir lista de pacientes\n");
    printf("Q - Sair\n");
    printf(">>");
    (void)scanf(" %c", &opcao); // input da ação

    switch(opcao){
      case '1':{ // consultar paciente
        bd_busca(&bd);
        clearConsole();
        break;
      }
      case '5': // imprimir lista de pacientes
        bd_imprimir_lista(&bd);
        clearConsole();
        break;
      case 'Q':
      case 'q':
        printf("Encerrando programa...\n"); // sair

        clearConsole();
        finalizar(&bd);
        return 0;
      default:
        printf("Opção inválida. Tente novamente."); // valor incorreto inserido
        clearConsole();
    }
  }
  return 0;
}
