# EP1 - Estrutura de Dados: Sistema de Clínica (HealthSys)
Este projeto é um sistema simples de gerenciamento de pacientes para uma clínica médica. O sistema faz a leitura de dados a partir de um arquivo CSV e permite a busca de pacientes pelo nome ou CPF com base em prefixos. Mais funcionalidades serão implementadas em etapas futuraS.

---

## Como compilar e executar
Este projeto foi desenvolvido em C e deve ser compilado em ambientes Linux com GCC 11 (como Ubuntu 22.04).

### Requisitos
- GCC (versão 11 ou compatível)
- Make

### Compilação e execução
No terminal, dentro do diretório do projeto:
make           # Compila o projeto
./healthsys    # Executa o programa
make clean     # Remove o executável


### Organização do Projeto:
| Arquivo            | Descrição                                                  |
| ------------------ | ---------------------------------------------------------- |
| `main.c`           | Função principal com o menu de opções                      |
| `bdpacientes.h`    | Definições das estruturas e declarações das funções do TAD |
| `bdpacientes.c`    | Implementação das funcionalidades do sistema               |
| `bd_pacientes.csv` | Base de dados dos pacientes (entrada do sistema)           |
| `Makefile`         | Script de automação da compilação                          |


### Principais TADs e estruturas
- Paciente - representa um paciente individual com os seguintes campos:
  - id: inteiro
  - cpf: string (formato XXX.XXX.XXX-XX)
  - nome: string
  - idade: inteiro
  - data_cadastro: string (formato AAAA-MM-DD)
- BDPaciente - representa um banco de pacientes com os seguintes campos:
  - um vetor estático de pacientes (MAX_PACIENTES = 10);
  - um campo total que armazena a quantidade atual de pacientes carregados.

### Funcionalidades implementadas
- Leitura do CSV: os dados do arquivo bd_pacientes.csv são carregados ao iniciar o sistema. Cada linha é convertida em uma struct Paciente e armazenada no vetor do TAD BDPaciente.

- Impressão de pacientes: listar todos os pacientes cadastrados ou um paciente individual.

- Consulta por prefixo: o usuário pode buscar pacientes pelo nome ou CPF. A busca considera prefixos (exemplo: "Mari" encontra "Maria Oliveira" e "Maria Madalena"). O sistema mostra os resultados e pergunta se o usuário deseja realizar outra busca.


### Decisões de implementação
- O sistema foi estruturado para manter o main.c o mais limpo possível, delegando toda a lógica ao TAD BDPaciente;
- Funções como bd_busca() abstraem a lógica de input, busca e impressão dos resultados;
- A função bd_criarPaciente() foi criada para centralizar a construção da struct Paciente, facilitando futuras inserções (Parte 2 do trabalho);
- Alocação dinâmica na busca por nome e CPF (bd_buscaNome e bd_buscaCPF) para criar dinamicamente um vetor de resultados.
