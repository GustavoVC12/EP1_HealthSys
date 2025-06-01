# Nome do executável final
EXEC = healthsys

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Wno-unused-result

# Arquivos-fonte (.c) e cabeçalhos (.h)
SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

# Regra principal
all: $(EXEC)

# Compilação
$(EXEC): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@"

# Debug mode opcional
debug: 
	$(CC) $(CFLAGS) -O0 $(SRCS) -o $(EXEC)

# Limpeza
clean:
	rm -f $(EXEC)
