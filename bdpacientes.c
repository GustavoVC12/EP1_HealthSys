#include "bdpacientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// capacidade inicial do banco
#define INICIAL_CAPACIDADE 10



//////////////////////////////////// ESTRUTURAS ////////////////////////////////////
BDPaciente bd_criarBanco(){ // cria e retorna o banco de dados
    BDPaciente bd;
    bd.capacidade = INICIAL_CAPACIDADE;
    bd.total = 0;
    bd.pacientes = malloc(sizeof(Paciente) * bd.capacidade);
    if(bd.pacientes == NULL){ // verifica se o vetor foi criado
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    return bd;
}

Paciente bd_criarPaciente(int pId, const char *pCpf, const char *pNome, int pIdade, const char *pData){ // cria e retorna o paciente
    Paciente p;
    p.id = pId;
    strcpy(p.cpf, pCpf);
    strcpy(p.nome, pNome);
    p.idade = pIdade;
    strcpy(p.data_cadastro, pData);
    return p;
}



//////////////////////////////////// CARREGAMENTO E MANIPULAÇÃO DO ARQUIVO ////////////////////////////////////
void bd_carregar_csv(BDPaciente *bd){ // carrega os dados do arquivo para o banco
    FILE *arquivo = fopen("bd_pacientes.csv", "r");
    if(arquivo == NULL){ // verifica se o arquivo foi aberto
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char linha[100]; // linha do fgets
    (void)fgets(linha, sizeof(linha), arquivo); // pula o cabeçalho

    while(fgets(linha, sizeof(linha), arquivo)){ // percorre o arquivo
        linha[strcspn(linha, "\n")] = '\0';

        char *token = strtok(linha, ",");
        if (token == NULL) continue;
        int id = atoi(token); // string -> int

        token = strtok(NULL, ",");
        char cpf[15];
        strcpy(cpf, token);

        token = strtok(NULL, ",");
        char nome[100];
        strcpy(nome, token);

        token = strtok(NULL, ",");
        int idade = atoi(token); // string -> int

        token = strtok(NULL, ",");
        char data[11];
        strcpy(data, token);

        Paciente p = bd_criarPaciente(id, cpf, nome, idade, data);

        // realoca memória se necessário
        if (bd->total >= bd->capacidade){
            bd->capacidade *= 2;
            bd->pacientes = realloc(bd->pacientes, sizeof(Paciente) * bd->capacidade);
            if(bd->pacientes == NULL){
                printf("Erro ao realocar memória.\n");
                exit(1);
            }
        }

        bd->pacientes[bd->total++] = p; // p se torna o último paciente
    }

    fclose(arquivo); // fecha o arquivo
}



//////////////////////////////////// BUSCA DE PACIENTE ////////////////////////////////////
// coleta parâmetros pra busca do paciente e chama a busca adequada
void bd_busca(const BDPaciente *bd){
    int metodo; // opção escolhida
    while(1){
        clearConsole();
        printFrame();

        printf("Escolha o modo de consulta:\n");
        printf("1 - Por nome\n");
        printf("2 - Por CPF\n");
        printf("3 - Retornar ao menu principal\n");
        printf(">>");
        (void)scanf(" %d", &metodo);

        if(metodo == 3){
            printf("Busca cancelada.\n");
            confirma();
            break; // finaliza busca
        }

        if(metodo != 1 && metodo != 2){
            printf("Opção inválida. Tente novamente.\n");
            continue; // reinicia busca
        }

        printf("Digite o prefixo a ser buscado: ");
        int total = 0; // nº de resultados
        int *resultados = NULL;

        if(metodo == 1){
            char prefixo[100]; // tamanho máximo do nome
            (void)scanf(" %[^\n]", prefixo); // prefixo a ser buscado
            resultados = bd_buscaNome(bd, prefixo, &total);
        } else {
            char prefixo[15]; // tamanho máximo do cpf
            (void)scanf(" %[^\n]", prefixo); // prefixo a ser buscado
            resultados = bd_buscaCPF(bd, prefixo, &total);
        }

        if(total == 0){ // sem resultados
            printf("Nenhum paciente encontrado.\n");
        } else {
            clearConsole();
            printFrame();
            printf("Pacientes encontrados: %d.\n", total);
            printf("ID | CPF            | Nome                 | Idade | Data Cadastro\n");
            printf("---------------------------------------------------------------\n");
            for (int i = 0; i < total; i++) {
                bd_imprimir_paciente(&bd->pacientes[resultados[i]]);
            }
        }

        free(resultados); // limpa o vetor de resultados

        // verifica se o usuário quer fazer outra busca
        char continuar;
        printf("\nFazer outra busca? [Y/N]");
        printf("\n>>");
        (void)scanf(" %c", &continuar);
        if (continuar != 'Y' && continuar != 'y') break;
    }
}

// busca e retornar todas as ocorrências de um prefixo de nome
int* bd_buscaNome(const BDPaciente *bd, const char *prefixo, int *total){
    int *resultados = malloc(sizeof(int) * bd->total); // vetor para armazenar os resultados
    *total = 0; // nº de resultados encontrados
    for(int i = 0; i < bd->total; i++){
        if(strncmp(bd->pacientes[i].nome, prefixo, strlen(prefixo)) == 0){
            resultados[(*total)++] = i; // índice do resultado é armazenado
        }
    }
    return resultados;
}

// busca e retornar todas as ocorrências de um prefixo de CPF
int* bd_buscaCPF(const BDPaciente *bd, const char *prefixo, int *total){
    int *resultados = malloc(sizeof(int) * bd->total);
    *total = 0;
    for(int i = 0; i < bd->total; i++){
        if(strncmp(bd->pacientes[i].cpf, prefixo, strlen(prefixo)) == 0){
            resultados[(*total)++] = i;
        }
    }
    return resultados;
}



//////////////////////////////////// IMPRESSÃO DE DADOS ////////////////////////////////////
void bd_imprimir_paciente(const Paciente *p){ // imprime um paciente específico
    printf("%2d | %-14s | %-20s | %5d | %s\n",
           p->id, p->cpf, p->nome, p->idade, p->data_cadastro);
}

void bd_imprimir_lista(const BDPaciente *bd){ // imprime a lista de pacientes
    clearConsole();
    printFrame();
    printf("ID | CPF            | Nome                 | Idade | Data Cadastro\n");
    printf("---------------------------------------------------------------\n");
    for(int i = 0; i < bd->total; i++){
        Paciente p = bd->pacientes[i];
        printf("%2d | %-14s | %-20s | %5d | %s\n",
               p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
    }
    confirma();
}

//////////////////////////////////// UTILIDADES ////////////////////////////////////
void printFrame(){
    printf("\n====================================================================\n");
}

void confirma(){
    printf("Confirmar [Enter]");
    while (getchar() != '\n');
    getchar();
}

void clearConsole(){
    printf("\n\n\n");
}

void finalizar(BDPaciente *bd){
    free(bd->pacientes);
    printf("Memória limpa. Código encerrado.");
}
