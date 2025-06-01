#ifndef BDPACIENTES_H
#define BDPACIENTES_H

//////////////////////////////////// ESTRUTURAS ////////////////////////////////////
typedef struct paciente { // define a estrutura do paciente
    int id;
    char cpf[15]; // xxx.xxx.xxx-xx
    char nome[100];
    int idade;
    char data_cadastro[11]; // AAAA-MM-DD
} Paciente;

typedef struct bdpaciente { // define a estrutura do banco de dados
    Paciente *pacientes; // ponteiro para o vetor de pacientes
    int total; // número atual de pacientes
    int capacidade; // capacidade inicial
} BDPaciente;

BDPaciente bd_criarBanco(); // cria e retorna o banco de dados

Paciente bd_criarPaciente(int pId, const char *pCpf, const char *pNome, int pIdade, const char *pData); // cria e retorna o paciente



//////////////////////////////////// CARREGAMENTO E MANIPULAÇÃO DO ARQUIVO ////////////////////////////////////
void bd_carregar_csv(BDPaciente *bd); // carrega os dados do arquivo para o banco



//////////////////////////////////// BUSCA DE PACIENTE ////////////////////////////////////
void bd_busca(const BDPaciente *bd); // coleta parâmetros pra busca do paciente e chama a busca adequada

// busca e retornar todas as ocorrências de um prefixo de nome
int* bd_buscaNome(const BDPaciente *bd, const char *prefixo, int *total);

// busca e retornar todas as ocorrências de um prefixo de CPF
int* bd_buscaCPF(const BDPaciente *bd, const char *prefixo, int *total);



//////////////////////////////////// IMPRESSÃO DE DADOS ////////////////////////////////////
void bd_imprimir_paciente(const Paciente *p); // imprime um paciente específico
void bd_imprimir_lista(const BDPaciente *bd); // imprime a lista de pacientes



//////////////////////////////////// UTILIDADES ////////////////////////////////////
void printFrame(); // divisória para melhor legibilidade

void confirma(); // aguarda o sinal do usuário para prosseguir

void clearConsole(); // limpa o console

void finalizar(BDPaciente *bd); // libera a memória alocada para o banco


#endif
