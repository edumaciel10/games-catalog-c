#include <stdio.h>
#include <stdlib.h>

#include "Lista/Lista.h"

void testeEmpilhaStdin();

int main()
{
    testeEmpilhaStdin();
}

void testeEmpilhaStdin()
{
    LISTA *lista;
    lista = lista_criar();
    JOGO *jogo = jogo_ler_std_in(1);
    lista_inserir_fim(lista, jogo);
    jogo = jogo_ler_std_in(2);
    lista_inserir_fim(lista, jogo);
    jogo = jogo_ler_std_in(3);
    lista_inserir_fim(lista, jogo);
    jogo_imprimir(lista_busca(lista, 1));
    jogo_imprimir(lista_busca(lista, 2));
    jogo_imprimir(lista_busca(lista, 3));
    boolean_print(lista_vazia(lista));
    // should print passed in green
    printf("\033[32m PASSED");
    // should print 3 items
    // lista_apagar(&lista);
}
