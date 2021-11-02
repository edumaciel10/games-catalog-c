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
    JOGO *jogo = jogo_ler_std_in();
    lista_inserir_fim(lista, jogo);
    jogo = jogo_ler_std_in();
    lista_inserir_fim(lista, jogo);
    jogo_imprimir(lista_busca_ordenada(lista, 1));
    jogo_imprimir(lista_busca_ordenada(lista, 1));
    boolean_print(lista_vazia(lista));
    lista_apagar(&lista);
}
