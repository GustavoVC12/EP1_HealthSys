# Nome do executável
EXEC = healthsys

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Wno-unused-result

# Arquivos-fonte e cabeçalhos
SRCS = main.c bdpacientes.c
HEADERS = bdpacientes.h

# Regra padrão
all: $(EXEC)

# Como gerar o executável
$(EXEC): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

# Modo debug (sem otimizações)
debug:
	$(CC) $(CFLAGS) -O0 $(SRCS) -o $(EXEC)

# Limpeza dos arquivos gerados
clean:
	rm -f $(EXEC)
