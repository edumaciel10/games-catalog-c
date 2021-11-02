JOGO = Jogo/Jogo.c
MAIN = main.c
UTIL = Util/Util.c
PILHA = Pilha/PilhaEncadeada.c
LISTA = Lista/ListaDuplamenteEncadeada.c
BINARY = main
NAME = TAD

all:
	gcc -Wall -g $(LISTA) $(MAIN) -L. -l_util -o $(BINARY)

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r $(NAME).zip *

clean:
	@rm *.o

objlib:
	gcc -Wall -pedantic -Werror -Wextra -c -fPIC $(UTIL) $(JOGO)

lib:
	ar -rcs lib_util.a *.o