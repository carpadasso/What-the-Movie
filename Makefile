# Makefile do projeto Qual o Filme
# Curitiba, Paraná - Junho, 2023

# Nome do Projeto
PROJ_NAME=qualFilme
# Arquivos .c
C_SOURCE=$(wildcard *.c)
# Arquivos .h
H_SOURCE=$(wildcard *.h)
# Objetos
OBJ=$(C_SOURCE:.c=.o)
# Compilador
CC=gcc
# Flags do Compilador
CC_FLAGS=-c -Wall -O2

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~