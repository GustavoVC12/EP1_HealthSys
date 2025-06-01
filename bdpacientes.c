#include "bdpacientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////// ESTRUTURAS ////////////////////////////////////
// cria e retorna o banco de dados
BDPaciente bd_criarBanco(){
    BDPaciente bd;
    bd.total = 0;
    return bd;
}

// cria a estrutura do paciente
Paciente bd_criarPaciente(int pId, const char *pCpf, const char *pNome, int pIdade, const char *pData){
    Paciente p;
    p.id = pId;
    strcpy(p.cpf, pCpf);
    strcpy(p.nome, pNome);
    p.idade = pIdade;
    strcpy(p.data_cadastro, pData); // strings exigem str copy
    return p;
}



//////////////////////////////////// CARREGAMENTO E MANIPULAÇÃO DO ARQUIVO ////////////////////////////////////
// carrega os dados do arquivo para o banco
void bd_carregar_csv(BDPaciente *bd){
    FILE *arquivo = fopen("bd_pacientes.csv", "r"); // abre o arquivo .csv
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }

    char linha[100]; // armazena cada linha

    (void)fgets(linha, sizeof(linha), arquivo); // pula o cabeçalho
    
    while(fgets(linha, sizeof(linha), arquivo)){
        linha[strcspn(linha, "\n")] = '\0'; // remove o \n (se houver)

        char *token = strtok(linha, ","); // separa a string em campos
        if(token == NULL) continue;
        int id = atoi(token); // id era string, agora int

        token = strtok(NULL, ",");
        char cpf[15];
        strcpy(cpf, token);

        token = strtok(NULL, ",");
        char nome[100];
        strcpy(nome, token);

        token = strtok(NULL, ",");
        int idade = atoi(token); // idade era string, agora int

        token = strtok(NULL, ",");
        char data[11];
        strcpy(data, token);

        Paciente p = bd_criarPaciente(id, cpf, nome, idade, data); // cria um paciente com os dados extraídos
        if(bd->total < MAX_PACIENTES){ // checa se o limite não foi atingido
            bd->pacientes[bd->total++] = p;
        } else {

            printf("Número máximo de pacientes atingido.");
            break;
        }
    }

    fclose(arquivo); // fecha arquivo
}



//////////////////////////////////// BUSCA DE PACIENTE ////////////////////////////////////
// coleta parâmetros pra busca do paciente e chama a busca adequada
void bd_busca(const BDPaciente *bd){
    int metodo; // tipo de busca a ser realizada
    while(1){ // busca até o usuário decidir parar
        clearConsole();
        printFrame();
        char prefixo[100]; // prefixo a ser buscado
        int resultados[MAX_PACIENTES]; // vetor com os resultados

        printf("Escolha o modo de consulta:\n");
        printf("1 - Por nome\n");
        printf("2 - Por CPF\n");
        printf("3 - Retornar ao menu principal\n");
        printf(">>");
        (void)scanf("%d", &metodo);
        
        if(metodo==3){
            printf("Busca cancelada.\n");
            confirma();
            break; // encerra o loop
        }

        if(metodo != 1 && metodo != 2){
            printf("Opção inválida. Tente novamente.\n");
            continue; // volta ao início do loop
        }

        printf("Digite o prefixo a ser buscado: ");
        (void)scanf(" %[^\n]", prefixo);

        int total = 0;
        if(metodo == 1){
            total = bd_buscaNome(bd, prefixo, resultados);
        } else if(metodo == 2){
            total = bd_buscaCPF(bd, prefixo, resultados);
        }

        if(total == 0){
            printf("Nenhum paciente encontrado.\n");
        } else {
            clearConsole();
            printFrame();
            printf("Pacientes encontrados: %d.\n", total);
            printf("ID | CPF            | Nome                 | Idade | Data Cadastro\n");
            printf("---------------------------------------------------------------\n");
            for(int i=0; i<total; i++){
                bd_imprimir_paciente(&bd->pacientes[resultados[i]]);
            }
        }

        // Pergunta se quer continuar apenas após uma busca válida
        char continuar;
        printf("\nFazer outra busca? [Y/N]");
        printf("\n>>");
        (void)scanf(" %c", &continuar);
        if(continuar != 'Y' && continuar != 'y'){
            break; // sai do loop
        }
    }
}


// busca e retornar todas as ocorrências de um prefixo de nome
int bd_buscaNome(const BDPaciente *bd, const char *prefixo, int resultados[]){
    int total = 0;
    for(int i=0; i<bd->total; i++){ // busca pacientes com o prefixo no nome
        if(strncmp(bd->pacientes[i].nome, prefixo, strlen(prefixo)) == 0){
            resultados[total++] = i; // insere os índices dos pacientes encontrados no vetor
        }
    } 
    return total; // retorna o número de correspondências
}

// busca e retornar todas as ocorrências de um prefixo de CPF
int bd_buscaCPF(const BDPaciente *bd, const char *prefixo, int resultados[]){
    int total = 0;
    for(int i=0; i<bd->total; i++){ // busca pacientes com o prefixo no cpf
        if(strncmp(bd->pacientes[i].cpf, prefixo, strlen(prefixo)) == 0){
            resultados[total++] = i; // insere os índices dos pacientes encontrados no vetor
        }
    }
    return total; // retorna o número de correspondências
}



//////////////////////////////////// IMPRESSÃO DE DADOS ////////////////////////////////////
// imprime um paciente específico
void bd_imprimir_paciente(const Paciente *p){
    printf("%2d | %-14s | %-20s | %5d | %s\n",
           p->id, p->cpf, p->nome, p->idade, p->data_cadastro);
}

// imprime os pacientes da lista
void bd_imprimir_lista(const BDPaciente *bd){
    clearConsole();
    printFrame();
    printf("ID | CPF             | Nome                  | Idade | Data Cadastro\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < bd->total; i++) {
        Paciente p = bd->pacientes[i];
        printf("%2d | %-14s | %-20s | %5d | %s\n",
               p.id, p.cpf, p.nome, p.idade, p.data_cadastro);
    }
    confirma();
}

    

//////////////////////////////////// UTILIDADES ////////////////////////////////////
void printFrame(){ // divisória para melhor legibilidade
    printf("====================================================================\n");
}

void confirma(){ // aguarda o sinal do usuário para prosseguir
    printf("Confirmar [Enter]");
    while (getchar() != '\n');  // limpa buffer
    getchar();                  // espera o usuário apertar Enter
}

void clearConsole(){ // limpa o console
    printf("\n\n\n");
}