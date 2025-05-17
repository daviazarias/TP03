NOME_ARQ = grafo
NOME_GRAFO = grafo
ARQS_C = $(wildcard ./fonte/*.c)
ARQS_H = $(wildcard ./fonte/*.h)

ARQS_O = $(subst .c,.o,$(subst ./fonte,./objetos,$(ARQS_C)))

CC = gcc
FLAGS = -O3

all: fonte objetos $(NOME_ARQ)
graph: exibirGrafo

$(NOME_ARQ): $(ARQS_O)
	$(CC) $(FLAGS) $^ -o $@

./objetos/main.o: ./fonte/main.c $(ARQS_H)
	$(CC) $(FLAGS) $< -c -o $@ 

./objetos/%.o : ./fonte/%.c ./fonte/%.h
	$(CC) $(FLAGS) $< -c -o $@

exibirGrafo: $(NOME_GRAFO).dot
	@ dot -Tpng $< -o $(NOME_GRAFO).png

objetos:
	mkdir -p objetos

clean:
	rm -fr objetos $(NOME_ARQ) grafo.png grafo.dot
